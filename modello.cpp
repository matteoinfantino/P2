#include "modello.h"

Modello::Modello() {}

Modello::~Modello() {
    for (Qontainer<Tesserato*>::Iterator it = polisportiva.begin(); it != polisportiva.end(); it++)
        delete *it;
}

// Metodo per aggiungere un tesserato t
void Modello::add(Tesserato* t){
    polisportiva.push_back(t);
}

// Metodo per togliere un tesserato t
void Modello::remove(int i) {
    polisportiva.remove(i);
}

Tesserato *Modello::getItem(int i){
    return polisportiva.getItem(i);
}

double Modello::calcoloStip() const{

    double stip = 0.0;
    for(Qontainer<Tesserato*>::Constiterator cit = polisportiva.cbegin(); cit != polisportiva.cend(); ++cit)
        stip += (**cit).stipendio();

    return stip;
}

void Modello::ordAlfa(){

    Qontainer<Tesserato*>::Iterator begin = polisportiva.begin(), end = polisportiva.end();
    for( ; begin != end; begin++){
      Qontainer<Tesserato*>::Iterator minIt = polisportiva.min_element(begin, end);
      polisportiva.swap( *minIt, *begin);
    }
}

int Modello::sizeModel() const{
    return polisportiva.size();
}

void Modello::addCalc(std::string nome, std::string cognome, QDate nascita, double stip, QDate scadenza,
                      int pres, int bonus, int malus, double chiave){

    Tesserato* nuovo = new Calciatore(nome,cognome,nascita,stip,scadenza,pres,bonus,malus,chiave);
    add(nuovo);
}

void Modello::addNuot(std::string nome, std::string cognome, QDate nascita, double stip, QDate scadenza,
                      double spons, int o, int a, int b){

    Tesserato* nuovo = new Nuotatore(nome,cognome,nascita,stip,scadenza,spons,o,a,b);
    add(nuovo);
}

void Modello::addPug(std::string nome, std::string cognome, QDate nascita, double stip, QDate scadenza,
                     int v, int vKO, int sKO){

    Tesserato* nuovo = new Pugile(nome,cognome,nascita,stip,scadenza,v,vKO,sKO);
    add(nuovo);
}

void Modello::addDir(std::string nome, std::string cognome, QDate nascita, double paga, int ore, int comm, bool mas){

    Tesserato* nuovo = new Dirigente(nome,cognome,nascita,paga,ore,comm,mas);
    add(nuovo);
}

void Modello::addAll(std::string nome, std::string cognome, QDate nascita, double paga, int ore, int vitt, bool ob){

    Tesserato* nuovo = new Allenatore(nome,cognome,nascita,paga,ore,vitt,ob);
    add(nuovo);
}

void Modello::saveToFile(){
    XML xml("../ProjectP2/data.xml");
    xml.write(polisportiva);
}

void Modello::loadFromFile(){
    XML xml("../ProjectP2/data.xml");
    polisportiva = xml.read();
}
