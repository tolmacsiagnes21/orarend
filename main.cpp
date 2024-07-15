#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include "xlnt/xlnt.hpp"

#include "tanar.h"
#include "diak.h"

using namespace std;

vector<Tanar> readExcelColumnsABCDE_tanar(const std::string &filePath);
vector<Diak> readExcelColumnsABCDE_diak(const std::string &filePath);
std::vector<std::vector<std::vector<std::string>>> constructWeightMatrix(const std::vector<Tanar>& tanarok, const std::vector<Diak>& diakok);
std::vector<std::string> findCommonSlots(const std::vector<std::string>& slots1, const std::vector<std::string>& slots2);

int main()
{
    string filePath = "C:/Users/Agnes/Desktop/orarend/Adatok.xlsx";
    vector<Tanar> tanarok = readExcelColumnsABCDE_tanar(filePath);
    vector<Diak> diakok = readExcelColumnsABCDE_diak(filePath);

    // Construct the weight matrix
     std::vector<std::vector<std::vector<std::string>>> weightMatrix = constructWeightMatrix(tanarok, diakok);


    // for (const auto &tanar : tanarok) {
    //     std::cout << "Surname: " << tanar.getVezeteknev()<< ", Forename: " << tanar.getKeresztnev() << std::endl;
    //     std::cout << "Available Timeslots: ";
    //     for (const auto &slot : tanar.getIdopontok()) {
    //         std::cout << slot << " ";
    //     }
    //     std::cout << std::endl;
    //     std::cout << "Classes: ";
    //     for (const auto &slot : tanar.getTanitottOsztalyok()) {
    //         std::cout << slot << " ";
    //     }
    //     std::cout << std::endl;
    //     std::cout << "Max Availability: " << tanar.getMaxOrak() << std::endl;
    // }

    // for (const auto &diak : diakok) {
    //     std::cout << "Surname: " << diak.getVezeteknev()<< ", Forename: " << diak.getKeresztnev() << std::endl;
    //     std::cout << "Available Timeslots: ";
    //     for (const auto &slot : diak.getIdopontok()) {
    //         std::cout << slot << " ";
    //     }
    //     std::cout << std::endl;
    //     std::cout << "Class: " << diak.getOsztaly() << std::endl;
    //     std::cout << "Max Availability: " << diak.getOraszam() << std::endl;
    // }
    
    return 0;
}

std::vector<std::string> splitString(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<unsigned> splitStringToUnsigned(const std::string &str, char delimiter) {
    std::vector<unsigned> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(static_cast<unsigned>(std::stoul(token)));
    }
    return tokens;
}

std::vector<Tanar> readExcelColumnsABCDE_tanar(const std::string &filePath) {
    xlnt::workbook wb;
    wb.load(filePath);

    xlnt::worksheet ws = wb.sheet_by_title("Tanarok");
    std::vector<Tanar> tanarok;

    for (auto row : ws.rows(false)) {
        std::string surname = row[0].to_string();
        std::string forename = row[1].to_string();
        std::vector<std::string> available_timeslots = splitString(row[2].to_string(), ',');
        std::vector<unsigned> free_slots = splitStringToUnsigned(row[3].to_string(), ',');
        unsigned max_availability = static_cast<unsigned>(stoi(row[4].to_string()));

        tanarok.emplace_back(surname, forename, available_timeslots, free_slots, max_availability);
    }

    return tanarok;
}

std::vector<Diak> readExcelColumnsABCDE_diak(const std::string &filePath) {
    xlnt::workbook wb;
    wb.load(filePath);

    xlnt::worksheet ws = wb.sheet_by_title("Diakok");
    std::vector<Diak> diakok;

    for (auto row : ws.rows(false)) {
        std::string surname = row[0].to_string();
        std::string forename = row[1].to_string();
        std::vector<std::string> available_timeslots = splitString(row[2].to_string(), ',');
        unsigned class_diak = static_cast<unsigned>(stoi(row[3].to_string()));
        unsigned max_availability = static_cast<unsigned>(stoi(row[4].to_string()));

        diakok.emplace_back(surname, forename, available_timeslots, class_diak, max_availability);
    }

    return diakok;
}

// Function to find the intersection of two vectors
std::vector<std::string> findCommonSlots(const std::vector<std::string>& slots1, const std::vector<std::string>& slots2) {
    std::set<std::string> set1(slots1.begin(), slots1.end());
    std::set<std::string> set2(slots2.begin(), slots2.end());
    std::vector<std::string> commonSlots;
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(commonSlots));
    return commonSlots;
}

// Function to construct the weight matrix for the bipartite graph
std::vector<std::vector<std::vector<std::string>>> constructWeightMatrix(const std::vector<Tanar>& tanarok, const std::vector<Diak>& diakok) {
    std::vector<std::vector<std::vector<std::string>>> weightMatrix(tanarok.size(), std::vector<std::vector<std::string>>(diakok.size()));
    for (size_t i = 0; i < tanarok.size(); ++i) {
        for (size_t j = 0; j < diakok.size(); ++j) {
            weightMatrix[i][j] = findCommonSlots(tanarok[i].getIdopontok(), diakok[j].getIdopontok());
        }
    }
    return weightMatrix;
}