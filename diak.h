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
        int osztaly;
        int oraszam;   

    public:

        Diak(const string &vezeteknev, const string &keresztnev, const std::vector<std::string> &idopontok,
        int osztaly, int oraszam);
        
        std::string getVezeteknev() const;
        void setVezeteknev(std::string);

        std::string getKeresztnev() const;
        void setKeresztnev(std::string);

        std::vector<std::string> getIdopontok() const;
        void setIdopontok(std::vector<std::string>);

        int getOsztaly() const;
        void setOsztaly(int);

        int getOraszam() const;
        void setOraszam(int);
};

#endif