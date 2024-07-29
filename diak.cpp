#include "diak.h"

Diak::Diak(const string &veznev, const string &kernev, const std::vector<std::string> &idop,
        int osztaly, int orasz): vezeteknev(veznev), keresztnev(kernev), idopontok(idop), osztaly(osztaly), oraszam(orasz) 
        {}
std::string Diak::getVezeteknev() const{

    return vezeteknev;
}
void Diak::setVezeteknev(std::string input){
    vezeteknev = input;
}

std::string Diak::getKeresztnev() const{
    return keresztnev;
}
void Diak::setKeresztnev(std::string input){
    keresztnev = input;
}

std::vector<std::string> Diak::getIdopontok() const{
    return idopontok;
}
void Diak::setIdopontok(std::vector<std::string> input){
    idopontok = input;
}

int Diak::getOsztaly() const{
    return osztaly;
}
void Diak::setOsztaly(int input){
    osztaly = input; 
}

int Diak::getOraszam() const{
    return oraszam;
}
void Diak::setOraszam(int input){
    if(input >= 0) oraszam = input;
}

