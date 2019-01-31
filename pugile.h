#ifndef PUGILE_H
#define PUGILE_H
#include "atleta.h"

class Pugile : public Atleta
{
private:
    int vittorie;
    int vittorieKO;
    int sconfitteKO;
public:
    Pugile(string = "Unk", string = "Unk", QDate = QDate(), double = 0.0, QDate = QDate(), int = 0, int = 0, int = 0);
    double stipendio() const override;
    string info() const override;
    int getVittorie() const;
    void setVittorie(int value);
    int getVittorieKO() const;
    void setVittorieKO(int value);
    int getSconfitteKO() const;
    void setSconfitteKO(int value);
};

#endif // PUGILE_H
