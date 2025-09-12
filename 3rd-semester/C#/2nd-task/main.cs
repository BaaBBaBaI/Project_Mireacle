namespace _2nd_task;

public class main
{
    static void Main()
    {
        Console.WriteLine("Choose task: {Task 1, Task 2}");
        string? choice = Console.ReadLine();
        int taskNum = int.Parse(choice);
        switch (taskNum)
        {
            case 1:
            {
                Console.WriteLine("Введите 2 числа по формату '## ##' (день и с какого дня началось)");
                string? str = Console.ReadLine();
                int[] numbers = str.Split(' ').Select(x => int.Parse(x)).ToArray();
                byte result = Exer1.CheckDay(numbers[0], numbers[1]);
                switch (result)
                {
                    case 0: { str = " не "; break; }
                    case 1: { str = " "; break; }
                    case 2: { Console.WriteLine("ERROR"); return; }
                }

                Console.WriteLine($"День {numbers[0]}{str}является выходным.");
                break;
            }
            case 2:
            {
                Console.WriteLine("Введите число");
                string? str = Console.ReadLine();
                int number = int.Parse(str);
                if (number > 150000) { Console.WriteLine("Max 150000"); return; }
                Dictionary<int, int> result = Exer2.BankNote(number);
                if (result is null)
                {
                    Console.WriteLine("Не выдаст");
                    break;
                }
                Console.WriteLine("Нужно выдать:");
                foreach (KeyValuePair<int, int> pair in result)
                {
                    Console.WriteLine($"{pair.Value} по {pair.Key}");
                }
                break;
                
            }
                
        }
       
    }
}