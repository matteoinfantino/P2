#ifndef TESSERATO_H
#define TESSERATO_H

#include <QDate>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
using std::string;

class Tesserato
{
    friend std::ostream& operator<<(std::ostream &, const Tesserato&);
private:
    string nome;
    string cognome;
    QDate dataNascita;
public:
    Tesserato(string, string, QDate);
    virtual ~Tesserato() = default;
    virtual double stipendio() const = 0;
    virtual string info() const;

    QDate getDataNascita() const;
    string getNome() const;
    string getCognome() const;

    //operatori
    bool operator==(const Tesserato&);
    bool operator!=(const Tesserato &);
    bool operator<(const Tesserato&);
    void setNome(const string &value);
    void setCognome(const string &value);
    void setDataNascita(const QDate &value);
};


#endif // TESSERATO_H
