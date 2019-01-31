#ifndef DIRIGENTE_H
#define DIRIGENTE_H
#include "staff.h"

class Dirigente : public Staff
{
private:
    int commisioni;
    bool master;
public:
    Dirigente(string = "Unk", string = "Unk", QDate = QDate(), double = 0.0, int = 0, int = 0, bool = false);
    double stipendio() const override;
    string info() const override;

    int getCommisioni() const;
    void setCommisioni(int value);
    bool getMaster() const;
    void setMaster(bool value);
};

#endif // DIRIGENTE_H
