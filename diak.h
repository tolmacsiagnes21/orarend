#ifndef DIAK_H
#define DIAK_H

#include <string>
#include <vector>
using namespace std;

class Diak{
    private:
        std::string vezeteknev;
        std::string keresztnev;
        std::vector<std::string> idopontok;
        unsigned osztaly;
        unsigned oraszam;   

    public:
        Diak(string vezeteknev, string keresztnev, std::vector<std::string> idopontok,
        unsigned osztaly, unsigned oraszam);
        
        std::string getVezeteknev();
        void setVezeteknev(std::string);

        std::string getKeresztnev();
        void setKeresztnev(std::string);

        std::vector<std::string> getIdopontok();
        void setIdopontok(std::vector<std::string>);

        unsigned getOsztaly();
        void setOsztaly(unsigned);

        unsigned getOraszam();
        void setOraszam(unsigned);
};

#endif