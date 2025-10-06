#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include <bits/stdc++.h>
#include <cmath>

void takeFrom(std::ifstream& file, std::string& textholder) {

    if(file.is_open()) {
        std::string templine;
        while(std::getline(file, templine)) {
            textholder +=   templine; 
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

std::map<std::string, double> calcStr(std::string& textholder, char action) {

    std::map<std::string, double> frequencies;
    std::map<std::string, double> bigram_frequencies;

    switch (action) {

    case 's': { // s for single

        for (int i = 0; textholder[i]; i++) {
            std::string c;
            c += textholder[i];
            frequencies[c]++;
    }
    break;
    }

    case 'm': { // m for multi

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


double logg (double a) { return (a > 0.0) ? log2(a) : 0.0; }

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

std::vector<std::pair<std::string, double>> sort_map_by_value(const std::map<std::string, double>& m, bool ascending) {
    std::vector<std::pair<std::string, double>> vec(m.begin(), m.end());
    std::sort(vec.begin(), vec.end(), [ascending](const auto& a, const auto& b) {
        return ascending ? a.second < b.second : a.second > b.second;
    });
    return vec;
};


int main() {

    std::ifstream file("task1.txt");
    std::ofstream outputFile("task1_out.txt");
    std::string textholder;

    takeFrom(file, textholder);

    std::string editedtextholder = formEdit(textholder);
    pushTo(outputFile, editedtextholder);

    std::map<std::string, double> monoFreq = calcStr(textholder, 's');
    std::map<std::string, double> biFreq = calcStr(textholder, 'm');

    double monoEntr = entropy(monoFreq); double biEntr = entropy(biFreq);

    // :p

    int monoN = monoFreq.size();
    if (monoN > 0) {
        double monoH = log2(monoN);
        double redundancy = monoH - monoEntr;
        std::cout << "Code length for uniform coding: " << monoH << std::endl;
        std::cout << "Redundancy of the original text: " << redundancy << std::endl;
        outputFile << "Code length for uniform coding: " << monoH << std::endl;
        outputFile << "Redundancy of the original text: " << redundancy << std::endl;
    }

    
    auto sorted_most = sort_map_by_value(monoFreq, false);
    int numRemove = static_cast<int>(sorted_most.size() * 0.20);
    std::set<char> symbolsRemoveMost;
    for (int i = 0; i < numRemove; ++i) {
        symbolsRemoveMost.insert(sorted_most[i].first[0]);
    }

    std::string textAfterRemoval;
    for (char c : editedtextholder) {
        if (symbolsRemoveMost.find(c) == symbolsRemoveMost.end()) {
            textAfterRemoval += c;
        }
    }
    
    std::map<std::string, double> freqAfterMost = calcStr(textAfterRemoval, 's');
    double entropyRemMost = entropy(freqAfterMost);
    
    std::cout << "\n--- after 20% most frequent deletion ---" << std::endl;
    std::cout << "begining entropy : " << monoEntr << std::endl;
    std::cout << "new entropy: " << entropyRemMost << std::endl;
    outputFile << "\n--- after 20% most frequent deletion ---" << std::endl;
    outputFile << "begining entropy : " << monoEntr << std::endl;
    outputFile << "new entropy: " << entropyRemMost << std::endl;
    
    auto sorted_least = sort_map_by_value(monoFreq, true);
    int numRemoveleast = static_cast<int>(sorted_least.size() * 0.20);
    std::set<char> symbolsRemoveleast;
    for (int i = 0; i < numRemoveleast; ++i) {
        symbolsRemoveleast.insert(sorted_least[i].first[0]);
    }

    std::string textAfterRem;
    for (char c : editedtextholder) {
        if (symbolsRemoveleast.find(c) == symbolsRemoveleast.end()) {
            textAfterRem += c;
        }
    }

    std::map<std::string, double> freqAfterLeast = calcStr(textAfterRem, 's');
    double entropyAfterLeast = entropy(freqAfterLeast);
    
    std::cout << "\n--- after 20 least frequent deletion ---" << std::endl;
    std::cout << "begining entropy : " << monoEntr << std::endl;
    std::cout << "new entropy: " << entropyAfterLeast << std::endl;
    outputFile<< "\n--- after 20 least frequent deletion ---" << std::endl;
    outputFile << "begining entropy : " << monoEntr << std::endl;
    outputFile << "new entropy: " << entropyAfterLeast << std::endl;

    // Nouuu

    return 0;

}