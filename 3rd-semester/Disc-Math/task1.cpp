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

std::string formEdit(std::ofstream& outputFile, std::string& textholder) {

    std::string holded;

    for (int i = 0; textholder[i]; i++) {
        if ( !isalpha(textholder[i]) || textholder[i] == ' ' ) { continue; } else {
            if ( isupper(textholder[i]) ) {
                holded += tolower(textholder[i]);
            } else { holded += textholder[i]; }
        }
    }
    outputFile << holded << std::endl;
    return holded;

}

void pushTo(std::string& textholder);

void calcStr(std::string& textholder, char action);

void postprocess(std::string& textholder, char action);

int main() {

    std::ifstream file("task1.txt");
    std::ofstream outputFile("task1_out.txt");
    std::string textholder;

    takeFrom(file, textholder);

    std::string editedtextholder = formEdit(outputFile, textholder);

    return 0;

}