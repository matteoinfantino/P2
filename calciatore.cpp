#include "calciatore.h"

Calciatore::Calciatore(string n, string c, QDate d, double s, QDate scad, int p, int b, int m, bool ch)
    : Atleta(n,c,d,s,scad), presenze(p), bonus(b), malus(m), giocatoreChiave(ch) {}

double Calciatore::stipendio() const{
    double stip = getStipendioBase() + presenze*50 + bonus*200 - malus*100 + giocatoreChiave*500 - isYoung()*500;
    return stip > 0 ? stip : 0.0;
}

string Calciatore::info() const{
    string stream;
    stream = Atleta::info();
    std::stringstream value;
    value << std::fixed << std::setprecision(2) << stipendio();
    stream += "\nSport: Calcio\nStipendio Totale Mese Corrente: " + value.str() + "€";
    return stream;
}

void Calciatore::setPresenze(int value){
    presenze = value;
}

void Calciatore::setBonus(int value){
    bonus = value;
}

void Calciatore::setMalus(int value){
    malus = value;
}

void Calciatore::setGiocatoreChiave(bool value){
    giocatoreChiave = value;
}

int Calciatore::getPresenze() const{
    return presenze;
}

int Calciatore::getBonus() const{
    return bonus;
}

int Calciatore::getMalus() const{
    return malus;
}

bool Calciatore::getGiocatoreChiave() const{
    return giocatoreChiave;
}

