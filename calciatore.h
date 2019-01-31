#ifndef CALCIATORE_H
#define CALCIATORE_H

#include "atleta.h"

class Calciatore : public Atleta
{
private:
    int presenze; //presenze in match ufficiali
    int bonus;  //Per tutti gol, assist. Per difensori porta inviolata. Per portiere rigore parato e porta inviolata.
    int malus;  //ritardi o assenze ad allenamenti/partite. Espulsioni e squalifiche. Codice etico violato
    bool giocatoreChiave;
public:
    Calciatore(string = "Unk", string = "Unk", QDate = QDate(), double = 0.0, QDate = QDate(), int = 0, int = 0, int = 0, bool = false);
    double stipendio() const override;
    string info() const override;

    void setPresenze(int value);
    void setBonus(int value);
    void setMalus(int value);
    void setGiocatoreChiave(bool value);

    int getPresenze() const;
    int getBonus() const;
    int getMalus() const;
    bool getGiocatoreChiave() const;
};

#endif // CALCIATORE_H
