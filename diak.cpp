#include "diak.h"

Diak::Diak(const string &veznev, const string &kernev, const std::vector<std::string> &idop,
        unsigned osztaly, unsigned orasz): vezeteknev(veznev), keresztnev(kernev), idopontok(idop), osztaly(osztaly), oraszam(orasz) 
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

unsigned Diak::getOsztaly() const{
    return osztaly;
}
void Diak::setOsztaly(unsigned input){
    osztaly = input; 
}

unsigned Diak::getOraszam() const{
    return oraszam;
}
void Diak::setOraszam(unsigned input){
    if(input >= 0) oraszam = input;
}

