#ifndef XML_H
#define XML_H

#include <QString>
#include "modello.h"
#include "tesserato.h"
#include "calciatore.h"
#include "nuotatore.h"
#include "qontainer.h"

class XML{
private:
    QString filename;
public:
    XML(QString);
    Qontainer<Tesserato*> read() const;
    void write(Qontainer<Tesserato*>&) const;
};

#endif // XML_H
