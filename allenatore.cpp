#include "allenatore.h"

bool Allenatore::getObiettivi() const{
    return obiettivi;
}

void Allenatore::setObiettivi(bool value){
    obiettivi = value;
}

int Allenatore::getVittorie() const{
    return vittorie;
}

void Allenatore::setVittorie(int value){
    vittorie = value;
}

Allenatore::Allenatore(string n, string c, QDate d, double p, int o, int vitt, bool ob)
    : Staff(n,c,d,p,o), vittorie(vitt), obiettivi(ob) {}

double Allenatore::stipendio() const{
    double stip = getPagaOraria()*getOreMese() + vittorie*100 + obiettivi*300;
    return stip > 0 ? stip : 0.0;
}

std::string Allenatore::info() const{
    string stream;
    stream = Staff::info();
    std::stringstream value;
    value << std::fixed << std::setprecision(2) << stipendio();
    stream += "\nRuolo: Allenatore\nStipendio del mese corrente: " + value.str() + "€\n";
    return stream;
}
