#include "tanar.h"

Tanar::Tanar(const string &veznev, const string &kernev, const std::vector<std::string> &idop,
       const std::vector<int> &osztalyok, int maxO): vezeteknev(veznev), keresztnev(kernev), idopontok(idop), tanitottOsztalyok(osztalyok), maxOrak(maxO) 
        {}
        
std::string Tanar::getVezeteknev() const{

    return vezeteknev;
}
void Tanar::setVezeteknev(std::string input){
    vezeteknev = input;
}

std::string Tanar::getKeresztnev() const{
    return keresztnev;
}
void Tanar::setKeresztnev(std::string input){
    keresztnev = input;
}

std::vector<std::string> Tanar::getIdopontok() const{
    return idopontok;
}
void Tanar::setIdopontok(std::vector<std::string> input){
    idopontok = input;
}

const std::vector<int>& Tanar::getTanitottOsztalyok() const{
    return tanitottOsztalyok;
}

void Tanar::setTanitottOsztalyok(std::vector<int> input){
    tanitottOsztalyok = input; 
}

int Tanar::getMaxOrak() const{
    return maxOrak;
}
void Tanar::setMaxOrak(int input){
    if(input >= 0) maxOrak = input;
}

