#include "staff.h"

Staff::Staff(string n, string c, QDate d, double p, int o) : Tesserato(n,c,d), pagaOraria(p), oreMese(o) {}

int Staff::getOreMese() const{
    return oreMese;
}

void Staff::setOreMese(int value){
    oreMese = value;
}

double Staff::getPagaOraria() const{
    return pagaOraria;
}

void Staff::setPagaOraria(double value){
    pagaOraria = value;
}
