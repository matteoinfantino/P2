#ifndef MODELLO_H
#define MODELLO_H

#include<fstream>
#include "qontainer.h"
#include "tesserato.h"
#include "calciatore.h"
#include "nuotatore.h"
#include "pugile.h"
#include "dirigente.h"
#include "allenatore.h"
#include "xml.h"

class Modello
{
private:
    Qontainer<Tesserato*> polisportiva;
public:
    Modello();
    ~Modello();

    void add(Tesserato*);
    void remove(int);
    Tesserato* getItem(int);
    double calcoloStip() const;
    void ordAlfa();
    int sizeModel() const;
    void addCalc(string,string,QDate,double,QDate,int,int,int,double);
    void addNuot(string,string,QDate,double,QDate,double,int,int,int);
    void addPug(string,string,QDate,double,QDate,int,int,int);
    void addDir(string,string,QDate,double,int,int,bool);
    void addAll(string,string,QDate,double,int,int,bool);

    void saveToFile();
    void loadFromFile();
};

#endif // MODELLO_H
