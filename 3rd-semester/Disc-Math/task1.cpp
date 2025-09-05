#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

void takeFrom(std::ifstream& file, std::string& textholder) {

    if(file.is_open()) {
        std::string templine;
        while(std::getline(file, templine)) {
            textholder += templine; 
        }
        file.close();
    } else {std::cerr << "unable to open file" << std::endl;}


}

std::string formEdit(std::string& textholder) {

    std::string holded;

    for (int i = 0; textholder[i]; i++) {
        if ( !isalpha(textholder[i]) || textholder[i] == ' ' ) { continue; } else {
            if ( isupper(textholder[i]) ) {
                holded += tolower(textholder[i]);
            } else { holded += textholder[i]; }
        }
    }
    return holded;

}

void pushTo(std::ofstream& outputFile, std::string& textholder) {

    outputFile << textholder << std::endl; return;

}

int calcStr(std::string& textholder, char action) {


    
}



/*
Для однобуквенных сочетаний (монограмм):
Используйте std::map<char, int>.
Читайте файл посимвольно.
Для каждого прочитанного символа c увеличивайте значение счетчика в мапе: frequencies[c]++;.
Если символа еще нет в мапе, он будет автоматически добавлен со значением 1.
 */

/*     
Для двухбуквенных сочетаний (биграмм):
Используйте std::map<std::string, int>.
Для формирования биграмм понадобится "скользящее окно" из двух символов. Читайте из файла первый символ prev_char.
Затем в цикле читайте следующий символ current_char.
Создайте строку (биграмму) из этих двух символов: std::string bigram; bigram += prev_char; bigram += current_char;.
Увеличьте счетчик для этой биграммы: bigram_frequencies[bigram]++;.
"Сдвиньте" окно: prev_char = current_char; и перейдите к следующей итерации.
 */

void postprocess(std::string& textholder, char action);

int main() {

    std::ifstream file("task1.txt");
    std::ofstream outputFile("task1_out.txt");
    std::string textholder;

    takeFrom(file, textholder);

    std::string editedtextholder = formEdit(textholder);
    pushTo(outputFile, editedtextholder);


    return 0;

}