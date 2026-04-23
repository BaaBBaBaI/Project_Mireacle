### Задание 1: Функция для расчета возраста

Функция принимает дату рождения и вычисляет возраст пользователя в годах на текущий момент, обрабатывая возможные значения `NULL`.

```sql
CREATE OR REPLACE FUNCTION calculate_age(birth_date DATE)
RETURNS INTEGER AS $$
DECLARE
    age_in_years INTEGER;
BEGIN
    -- Обработка случая NULL значения
    IF birth_date IS NULL THEN
        RETURN NULL;
    END IF;

    -- Использование AGE() и EXTRACT(YEAR FROM ...)
    age_in_years := EXTRACT(YEAR FROM AGE(CURRENT_DATE, birth_date));
    
    RETURN age_in_years;
END;
$$ LANGUAGE plpgsql;

```

* 
**Требования:** Имя `calculate_age` , параметр `birth_date DATE` , возвращает `INTEGER`. Используются функции `AGE()` и `EXTRACT`.



---

### Задание 2: Функция категоризации заказа

Функция распределяет заказы по категориям на основе переданной суммы и включает проверку на отрицательные значения.

```sql
CREATE OR REPLACE FUNCTION categorize_order(order_amount DECIMAL(10,2))
RETURNS TEXT AS $$
BEGIN
    -- Проверка на отрицательные значения
    IF order_amount < 0 THEN
        RAISE EXCEPTION 'Сумма заказа не может быть отрицательной';
    END IF;

    -- Логика распределения по категориям
    IF order_amount < 1000 THEN
        RETURN 'МАЛЫЙ';
    ELSIF order_amount <= 5000 THEN
        RETURN 'СРЕДНИЙ';
    ELSIF order_amount <= 20000 THEN
        RETURN 'КРУПНЫЙ';
    ELSE
        RETURN 'ОСОБО КРУПНЫЙ';
    END IF;
END;
$$ LANGUAGE plpgsql;

```

* 
**Требования:** Имя `categorize_order` , параметр `order_amount DECIMAL(10,2)` , возвращает `TEXT`. Логика категорий соответствует суммам: < 1000, 1000-5000, 5000-20000 и более 20000.



---

### Задание 3: Функция генерации номеров заказов

Функция генерирует заданное количество тестовых номеров заказов в формате `ORD-YYYYMM-XXXXXX` и возвращает их в виде таблицы.

```sql
CREATE OR REPLACE FUNCTION generate_order_numbers(count INTEGER)
RETURNS TABLE(order_number TEXT) AS $$
DECLARE
    i INTEGER;
    current_ym TEXT;
    random_digits TEXT;
BEGIN
    -- Получаем текущий год и месяц
    current_ym := TO_CHAR(CURRENT_DATE, 'YYYYMM');

    -- Цикл FOR для генерации указанного количества номеров
    FOR i IN 1..count LOOP
        -- Генерация 6 случайных цифр с дополнением нулями слева
        random_digits := LPAD(FLOOR(RANDOM() * 1000000)::TEXT, 6, '0');
        
        -- Сборка строки формата 'ORD-' + год + месяц + 6 цифр
        order_number := 'ORD-' || current_ym || '-' || random_digits;
        
        -- Возврат текущей строки
        RETURN NEXT;
    END LOOP;
END;
$$ LANGUAGE plpgsql;

```

* 
**Требования:** Имя `generate_order_numbers` , параметр `count INTEGER` , возвращает `TABLE(order_number TEXT)`. Использованы цикл `FOR` и команда `RETURN NEXT`.



---

### Задание 4: Функция перевода средств (Транзакции и обработка ошибок)

Эта функция переводит деньги между счетами таблиц `accounts` и `transactions` , проверяет остатки и обрабатывает ошибки в блоке `EXCEPTION`. В PostgreSQL функции автоматически выполняются внутри транзакции, и при возникновении ошибки в блоке `EXCEPTION` все изменения, сделанные в функции, откатываются.

```sql
CREATE OR REPLACE FUNCTION transfer_money(
    from_account_id INTEGER, 
    to_account_id INTEGER, 
    amount DECIMAL(10,2)
)
RETURNS BOOLEAN AS $$
DECLARE
    sender_balance DECIMAL(10,2);
    receiver_exists BOOLEAN;
BEGIN
    -- 1. Проверить существование обоих счетов
    -- Блокируем строку отправителя для предотвращения состояния гонки (Race Condition)
    SELECT balance INTO sender_balance 
    FROM accounts 
    WHERE id = from_account_id FOR UPDATE;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Счет отправителя (ID: %) не найден', from_account_id;
    END IF;

    -- Проверяем существование получателя
    SELECT EXISTS(SELECT 1 FROM accounts WHERE id = to_account_id FOR UPDATE) INTO receiver_exists;
    IF NOT receiver_exists THEN
        RAISE EXCEPTION 'Счет получателя (ID: %) не найден', to_account_id;
    END IF;

    -- 2. Проверить достаточность средств на отправителе
    IF sender_balance < amount THEN
        RAISE EXCEPTION 'Недостаточно средств на счете отправителя';
    END IF;

    -- Проверка на отрицательную или нулевую сумму (дополнительная защита)
    IF amount <= 0 THEN
        RAISE EXCEPTION 'Сумма перевода должна быть положительной';
    END IF;

    -- 3. Выполнить перевод (происходит в рамках текущей транзакции функции)
    UPDATE accounts SET balance = balance - amount WHERE id = from_account_id;
    UPDATE accounts SET balance = balance + amount WHERE id = to_account_id;

    -- 4. Добавить запись в таблицу transactions
    INSERT INTO transactions (from_account, to_account, amount) 
    VALUES (from_account_id, to_account_id, amount);

    -- Если все прошло успешно
    RETURN TRUE;

-- 5. Обработать возможные ошибки с помощью EXCEPTION
EXCEPTION
    WHEN OTHERS THEN
        -- Вывод информации об ошибке в логи PostgreSQL
        RAISE NOTICE 'Ошибка транзакции перевода: %', SQLERRM;
        -- При попадании в EXCEPTION все изменения таблиц автоматически откатываются
        RETURN FALSE;
END;
$$ LANGUAGE plpgsql;

```

* 
**Требования:** Имя `transfer_money` , параметры `from_account_id INTEGER`, `to_account_id INTEGER`, `amount DECIMAL(10,2)` , возвращает `BOOLEAN`. Логика включает проверку существования счетов , баланса , запись в `transactions` и обработку ошибок.



Хочешь, я напишу для тебя набор `INSERT` и `SELECT` запросов, чтобы ты мог быстро протестировать работу этих функций в своей базе данных?
