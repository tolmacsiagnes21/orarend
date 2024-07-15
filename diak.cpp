#include "diak.h"

Diak::Diak(string veznev, string kernev, std::vector<std::string> idop,
        unsigned osztaly, unsigned orasz){
            setVezeteknev(veznev);
            setKeresztnev(kernev);
            setIdopontok(idop);
            setOsztaly(osztaly);
            setOraszam(orasz);
        }
std::string Diak::getVezeteknev(){

    return vezeteknev;
}
void Diak::setVezeteknev(std::string input){
    vezeteknev = input;
}

std::string Diak::getKeresztnev(){
    return keresztnev;
}
void Diak::setKeresztnev(std::string input){
    keresztnev = input;
}

std::vector<std::string> Diak::getIdopontok(){
    return idopontok;
}
void Diak::setIdopontok(std::vector<std::string> input){
    idopontok = input;
}

unsigned Diak::getOsztaly(){
    return osztaly;
}
void Diak::setOsztaly(unsigned input){
    osztaly = input; 
}

unsigned Diak::getOraszam(){
    return oraszam;
}
void Diak::setOraszam(unsigned input){
    if(input >= 0) oraszam = input;
}

