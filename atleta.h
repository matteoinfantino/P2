#ifndef ATLETA_H
#define ATLETA_H
#include "tesserato.h"

class Atleta : public Tesserato
{
private:
    double stipendioBase;
    QDate scadenzaCertificato;
public:
    Atleta(string, string, QDate, double, QDate);
    bool isYoung() const;
    string info() const override;

    QDate getScadenzaCertificato() const;
    void setScadenzaCertificato(const QDate &value);
    double getStipendioBase() const;
    void setStipendioBase(double value);
};

#endif // ATLETA_H
