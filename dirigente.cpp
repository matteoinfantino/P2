#include "dirigente.h"

Dirigente::Dirigente(string n, string c, QDate d, double p, int o, int comm, bool mast)
    : Staff(n,c,d,p,o), commisioni(comm), master(mast) {}

int Dirigente::getCommisioni() const{
    return commisioni;
}

void Dirigente::setCommisioni(int value){
    commisioni = value;
}

bool Dirigente::getMaster() const{
    return master;
}

void Dirigente::setMaster(bool value){
    master = value;
}

double Dirigente::stipendio() const{
    double stip = getPagaOraria()*getOreMese() + commisioni*100 + master*500;
    return stip > 0 ? stip : 0.0;
}

string Dirigente::info() const{
    string stream;
    stream = Staff::info();
    std::stringstream value;
    value << std::fixed << std::setprecision(2) << stipendio();
    stream += "\nRuolo: Dirigente\nStipendio del mese corrente: " + value.str() + "€\n";
    return stream;
}
