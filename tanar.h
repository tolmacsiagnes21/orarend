#ifndef TANAR_H
#define TANAR_H

#include <string>
#include <vector>
using namespace std;

class Tanar{
    private:
        std::string vezeteknev;
        std::string keresztnev;
        std::vector<std::string> idopontok;
        std::vector<unsigned> tanitottOsztalyok;
        unsigned maxOrak;   

    public:
        Tanar( const string &vezeteknev, const string &keresztnev, const std::vector<std::string> &idopontok,
        const std::vector<unsigned> &tanitottOsztalyok, unsigned maxOrak);
        std::string getVezeteknev() const;
        void setVezeteknev(std::string);

        std::string getKeresztnev() const;
        void setKeresztnev(std::string);

        std::vector<std::string> getIdopontok() const;
        void setIdopontok(std::vector<std::string>);

        std::vector<unsigned> getTanitottOsztalyok() const;
        void setTanitottOsztalyok(std::vector<unsigned>);

        unsigned getMaxOrak() const;
        void setMaxOrak(unsigned);
};

#endif