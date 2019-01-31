#ifndef ALLENATORE_H
#define ALLENATORE_H
#include "staff.h"

class Allenatore : public Staff
{
private:
    int vittorie;
    bool obiettivi;
public:
    Allenatore(string = "Unk", string = "Unk", QDate = QDate(), double = 0.0, int = 0, int = 0, bool = false);
    double stipendio() const override;
    string info() const override;

    int getVittorie() const;
    void setVittorie(int value);
    bool getObiettivi() const;
    void setObiettivi(bool value);
};

#endif // ALLENATORE_H
