#include "tesserato.h"

void Tesserato::setNome(const string &value){
    nome = value;
}

void Tesserato::setCognome(const string &value){
    cognome = value;
}

void Tesserato::setDataNascita(const QDate &value){
    dataNascita = value;
}

Tesserato::Tesserato(string n, string c, QDate d) : nome(n), cognome(c), dataNascita(d) {}

std::ostream& operator<<(std::ostream& out, const Tesserato& t){
    out << t.info() << std::endl;
    return out;
}

QDate Tesserato::getDataNascita() const{
    return dataNascita;
}

string Tesserato::getNome() const{
    return nome;
}

string Tesserato::getCognome() const{
    return cognome;
}

std::string Tesserato::info() const{
    string stream;
    stream = "Nome: " + nome + "\nCognome: " + cognome + "\nData di Nascita: " + dataNascita.toString().toStdString();
    return stream;
}

bool Tesserato::operator==(const Tesserato & t){
    return nome == t.nome && cognome == t.cognome &&  dataNascita == t.dataNascita;
}

bool Tesserato::operator!=(const Tesserato & t){
    return nome != t.nome || cognome != t.cognome || dataNascita != t.dataNascita;
}

bool Tesserato::operator<(const Tesserato& t){   //uso strcasecmp invece di un semplice controllo if(cognome < t.cognome)
                                                 //per rendere l'ordine alfabetico case insensitive
    const char *strcogn1 = cognome.c_str();
    const char *strcogn2 = t.cognome.c_str();
    const char *strnom1 = cognome.c_str();
    const char *strnom2 = t.cognome.c_str();
    if(strcasecmp(strcogn1,strcogn2) < 0)
        return true;
    else{
        if(strcasecmp(strcogn1,strcogn2) == 0){
            if(strcasecmp(strnom1,strnom2) < 0)
                return true;
            else
                return false;
        }
    }

    return false;
}
