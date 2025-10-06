#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <cmath>

/* 

Написать программу, чтобы провести статистическую обработку текста. 

Определить энтропию, приходящуюся в среднем на одну букву, длину кода при равномерном кодировании и избыточность.

Построить схему алфавитного кодирования для однобуквенных сочетаний методом Шеннона-Фано. 

Найти среднюю длину элементарного кода, эффективность сжатия. Закодировать текст. Декодировать текст. 

Построить схему алфавитного кодирования для двухбуквенных сочетаний методом Шеннона-Фано. 
Найти среднюю длину элементарного кода, эффективность сжатия, сравнить с результатами для однобуквенных сочетаний. 
Закодировать текст. Декодировать текст. 

*/

std::map<std::string, double> calcStr(std::string& textholder) {

    std::map<std::string, double> frequencies;
    std::map<std::string, double> bigram_frequencies;

    for (int i = 0; textholder[i]; i++) {
            std::string c;
            c += textholder[i];
            frequencies[c]++;
    }
    
}


double entropy (const std::map<std::string, double>& frequencies) {
    double total_count = 0;
    for (const std::pair<const std::string, double>& pair : frequencies) {
        total_count += pair.second;
    }

    if (total_count == 0) return 0.0;

    double entropy = 0.0;
    for (const std::pair<const std::string, double>& pair : frequencies) {
        double probability = pair.second / total_count;
        if (probability > 0) {
            entropy -= probability * log2(probability);
        }
    }
    return entropy;
}

void takeFrom(std::ifstream& file, std::string& textholder) {

    if(file.is_open()) {
        std::string templine;
        while(std::getline(file, templine)) {
            textholder += templine; 
        }
        file.close();
    } else {std::cerr << "unable to open file" << std::endl;}


}

int main() {

    std::ifstream file("task2.txt");
    std::ofstream outputFile("task2_out.txt");
    std::string textholder;

    takeFrom(file, textholder);



}