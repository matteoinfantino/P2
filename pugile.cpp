#include "pugile.h"

int Pugile::getVittorie() const{
    return vittorie;
}

void Pugile::setVittorie(int value){
    vittorie = value;
}

int Pugile::getVittorieKO() const{
    return vittorieKO;
}

void Pugile::setVittorieKO(int value){
    vittorieKO = value;
}

int Pugile::getSconfitteKO() const{
    return sconfitteKO;
}

void Pugile::setSconfitteKO(int value){
    sconfitteKO = value;
}

Pugile::Pugile(string n, string c, QDate d, double s, QDate scad, int vic, int vicKO, int defKO)
    : Atleta(n,c,d,s,scad), vittorie(vic), vittorieKO(vicKO), sconfitteKO(defKO) {}

double Pugile::stipendio() const{
    double stip = getStipendioBase() + vittorie*100 + vittorieKO*200 - sconfitteKO*50 - isYoung()*50;
    return stip > 0 ? stip : 0.0;
}

string Pugile::info() const{
    string stream;
    stream = Atleta::info();
    std::stringstream value;
    value << std::fixed << std::setprecision(2) << stipendio();
    stream += "\nSport: Pugilato\nStipendio del mese corrente: " + value.str() + "€";
    return stream;
}


