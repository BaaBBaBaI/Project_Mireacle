#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include <cmath>

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

std::map<std::string, int> calcStr(std::string& textholder, char action) {

    std::map<std::string, int> frequencies;
    std::map<std::string, int> bigram_frequencies;

    switch (action) {

    case 's': {

        for (int i = 0; textholder[i]; i++) {
            std::string c;
            c += textholder[i];
            frequencies[c]++;
    }
    break;
    }

    case 'm': {

        for (int i = 1; textholder[i]; i++) {
            std::string bigram;
            bigram += textholder[i-1];
            bigram += textholder[i];
            frequencies[bigram]++;
    }
    break;
    }

    default:
        break;
    }

    return frequencies;
    
    
}

void postprocess(std::string& textholder, char action) {

    switch (action)
    {
    case 'e': {

         

        break;
    }
        
    
    default:
        break;
    }

}

int main() {

    std::ifstream file("task1.txt");
    std::ofstream outputFile("task1_out.txt");
    std::string textholder;

    takeFrom(file, textholder);

    std::string editedtextholder = formEdit(textholder);
    pushTo(outputFile, editedtextholder);




    return 0;

}