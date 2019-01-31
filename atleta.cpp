#include "atleta.h"

Atleta::Atleta(string n, string c, QDate d, double s, QDate scad) : Tesserato(n,c,d), stipendioBase(s), scadenzaCertificato(scad) {}

bool Atleta::isYoung() const{
    return getDataNascita().year() >= 1994 ? true : false;
}

string Atleta::info() const{
    string stream = Tesserato::info();
    stream += "\nScadenza certificato medico: " + scadenzaCertificato.toString().toStdString();
    return stream;
}

QDate Atleta::getScadenzaCertificato() const{
    return scadenzaCertificato;
}

void Atleta::setScadenzaCertificato(const QDate &value){
    scadenzaCertificato = value;
}

double Atleta::getStipendioBase() const{
    return stipendioBase;
}

void Atleta::setStipendioBase(double value){
    stipendioBase = value;
}
