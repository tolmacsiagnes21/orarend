#include <iostream>
#include <vector>
#include <sstream>
#include "xlnt/xlnt.hpp"

#include "tanar.h"
#include "diak.h"

using namespace std;

vector<Tanar> readExcelColumnsABCDE_tanar(const std::string &filePath);
vector<Diak> readExcelColumnsABCDE_diak(const std::string &filePath);

int main()
{
    string filePath = "C:/Users/Agnes/Desktop/orarend/Adatok.xlsx";
    vector<Tanar> tanarok = readExcelColumnsABCDE_tanar(filePath);
    vector<Diak> diakok = readExcelColumnsABCDE_diak(filePath);

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