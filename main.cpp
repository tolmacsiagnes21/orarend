#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <unordered_map>
#include "xlnt/xlnt.hpp"

#include "tanar.h"
#include "diak.h"
#include "hungarian_algorithm.h"

using namespace std;

vector<Tanar> readExcelColumnsABCDE_tanar(const std::string &filePath);
vector<Diak> readExcelColumnsABCDE_diak(const std::string &filePath);
std::vector<std::vector<std::vector<std::string>>> constructWeightMatrix(const std::vector<Tanar>& tanarok, const std::vector<Diak>& diakok);
std::vector<std::string> findCommonSlots(const std::vector<std::string>& slots1, const std::vector<std::string>& slots2);
void greedyAssignment(const std::vector<Tanar>& teachers, const std::vector<Diak>& students, const std::vector<std::vector<std::vector<std::string>>>& weightMatrix);
void assignStudents(std::vector<std::vector<std::vector<std::string>>>& weightMatrix, const std::vector<Tanar>& teachers, const std::vector<Diak>& students);

int main()
{
    string filePath = "C:/Users/Agnes/Desktop/orarend/Adatok.xlsx";
    vector<Tanar> tanarok = readExcelColumnsABCDE_tanar(filePath);
    vector<Diak> diakok = readExcelColumnsABCDE_diak(filePath);

    //Construct the weight matrix
     std::vector<std::vector<std::vector<std::string>>> weightMatrix = constructWeightMatrix(tanarok, diakok);

    //kiírja a lehetséges párosításokat
    //greedyAssignment(tanarok, diakok, weightMatrix);
    assignStudents(weightMatrix, tanarok, diakok);

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

std::vector<int> splitStringToint(const std::string &str, char delimiter) {
    std::vector<int> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(static_cast<int>(std::stoul(token)));
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
        std::vector<int> free_slots = splitStringToint(row[3].to_string(), ',');
        int max_availability = static_cast<int>(stoi(row[4].to_string()));

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
        int class_diak = static_cast<int>(stoi(row[3].to_string()));
        int max_availability = static_cast<int>(stoi(row[4].to_string()));

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
          // Check if the teacher can teach the student's class
            if (std::find(tanarok[i].getTanitottOsztalyok().begin(), tanarok[i].getTanitottOsztalyok().end(), diakok[j].getOsztaly()) != tanarok[i].getTanitottOsztalyok().end()){
                // If the teacher can teach the student's class, find common slots
                weightMatrix[i][j] = findCommonSlots(tanarok[i].getIdopontok(), diakok[j].getIdopontok());
            } else {
                // If the teacher cannot teach the student's class, set an empty slot vector
                weightMatrix[i][j].clear();  // Explicitly clearing to ensure no accidental data
            }    
        }
    }
    return weightMatrix;
}

void greedyAssignment(const std::vector<Tanar>& teachers, const std::vector<Diak>& students, const std::vector<std::vector<std::vector<std::string>>>& weightMatrix) {
    std::vector<bool> assignedStudents(students.size(), false);

    for (size_t i = 0; i < teachers.size(); ++i) {
        std::cout << "Teacher: " << teachers[i].getVezeteknev() << " " << teachers[i].getKeresztnev() << std::endl;
        for (size_t j = 0; j < students.size(); ++j) {
            if (!assignedStudents[j] && !weightMatrix[i][j].empty()) {
                assignedStudents[j] = true;
                std::cout << "  Student: " << students[j].getVezeteknev() << " " << students[j].getKeresztnev() << " -> Common Slots: ";
                for (const auto& slot : weightMatrix[i][j]) {
                    std::cout << slot << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}

// Function to count the frequency of timeslots in the entire weight matrix
std::unordered_map<std::string, int> countSlotFrequency(const std::vector<std::vector<std::vector<std::string>>>& weightMatrix) {
    std::unordered_map<std::string, int> slotFrequency;
    for (const auto& teacherSlots : weightMatrix) {
        for (const auto& studentSlots : teacherSlots) {
            for (const auto& slot : studentSlots) {
                slotFrequency[slot]++;
            }
        }
    }
    return slotFrequency;
}

void assignStudents(std::vector<std::vector<std::vector<std::string>>>& weightMatrix, const std::vector<Tanar>& teachers, const std::vector<Diak>& students) {
    std::vector<bool> assignedStudents(students.size(), false);
    std::vector<int> classesAssigned(teachers.size(), 0); 
    auto slotFrequency = countSlotFrequency(weightMatrix);

    for (size_t i = 0; i < teachers.size(); ++i) {
        std::cout << "Teacher: " << teachers[i].getVezeteknev() << " " << teachers[i].getKeresztnev() << std::endl;
        for (size_t j = 0; j < students.size(); ++j) {
            if (assignedStudents[j] || classesAssigned[i] >= teachers[i].getMaxOrak() || weightMatrix[i][j].empty()) continue;

            // Find the least frequent slot available between teacher i and student j
            std::string selectedSlot;
            int minFrequency = std::numeric_limits<int>::max();
            for (const auto& slot : weightMatrix[i][j]) {
                if (slotFrequency[slot] < minFrequency) {
                    minFrequency = slotFrequency[slot];
                    selectedSlot = slot;
                }
            }

            if (!selectedSlot.empty()) {
                assignedStudents[j] = true;
                classesAssigned[i]++;

                std::cout << "  Student: " << students[j].getVezeteknev() << " " << students[j].getKeresztnev() << " -> Assigned Slot: " << selectedSlot << std::endl;

                // Remove the assigned slot from the current teacher's row in the weight matrix
                for (auto& studentSlots : weightMatrix[i]) {
                    auto it = std::remove(studentSlots.begin(), studentSlots.end(), selectedSlot);
                    studentSlots.erase(it, studentSlots.end());
                }

                // Update the slot frequency as it has been used
                slotFrequency[selectedSlot]--;
            }
        }
    }
}