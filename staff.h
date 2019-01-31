#ifndef STAFF_H
#define STAFF_H
#include "tesserato.h"

class Staff : public Tesserato
{
    double pagaOraria;
    int oreMese;
public:
    Staff(string, string, QDate, double, int);

    double getPagaOraria() const;
    void setPagaOraria(double value);
    int getOreMese() const;
    void setOreMese(int value);
};

#endif // STAFF_H
