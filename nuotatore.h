#ifndef NUOTATORE_H
#define NUOTATORE_H
#include "atleta.h"

class Nuotatore : public Atleta
{
private:
    double sponsor;
    int ori;
    int argenti;
    int bronzi;
public:
    Nuotatore(string = "Unk", string = "Unk", QDate = QDate(), double = 0.0, QDate = QDate(),
              double = 0.0, int = 0, int = 0, int = 0);

    double stipendio() const override;
    string info() const override;

    double getSponsor() const;
    int getOri() const;
    int getArgenti() const;
    int getBronzi() const;

    void setSponsor(double value);
    void setOri(int value);
    void setArgenti(int value);
    void setBronzi(int value);
};

#endif // NUOTATORE_H

