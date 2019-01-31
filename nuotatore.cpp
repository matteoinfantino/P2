#include "nuotatore.h"

Nuotatore::Nuotatore(string n, string c, QDate d, double s, QDate scad, double spon, int o, int a, int b)
    : Atleta(n,c,d,s,scad), sponsor(spon), ori(o), argenti(a), bronzi(b) {}

double Nuotatore::stipendio() const{
    double stip = getStipendioBase() + sponsor + ori*200 + argenti*100 + bronzi*50 - isYoung()*100;
    return stip > 0 ? stip : 0.0;
}

string Nuotatore::info() const{
    string stream;
    stream = Atleta::info();
    std::stringstream value;
    value << std::fixed << std::setprecision(2) << stipendio();
    stream += "\nSport: Nuoto\nStipendio del mese corrente: " + value.str() + "€";
    return stream;
}

double Nuotatore::getSponsor() const{
    return sponsor;
}

int Nuotatore::getOri() const{
    return ori;
}

int Nuotatore::getArgenti() const{
    return argenti;
}

int Nuotatore::getBronzi() const{
    return bronzi;
}

void Nuotatore::setSponsor(double value){
    sponsor = value;
}

void Nuotatore::setOri(int value){
    ori = value;
}

void Nuotatore::setArgenti(int value){
    argenti = value;
}

void Nuotatore::setBronzi(int value){
    bronzi = value;
}
