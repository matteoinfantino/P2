#ifndef MODIFICA_ALLENATORE_H
#define MODIFICA_ALLENATORE_H

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QListWidget>
#include <QScrollArea>
#include <QMessageBox>
#include <QCheckBox>

#include "modello.h"

class Modifica_Allenatore : public QDialog
{
    Q_OBJECT
private:
    QListWidget* text;
    QScrollArea* info;
    Modello* model;
    int index;

    QLineEdit *nome;
    QLineEdit *cognome;
    QDateEdit *nascita;
    QDoubleSpinBox *pagaOraria;
    QSpinBox *oreMese;
    QSpinBox *vittorie;
    QCheckBox *obiettivi;
public:
    explicit Modifica_Allenatore(QListWidget*, QScrollArea*, Modello*, int, QWidget *parent = nullptr);

    QString getNome() const;
    QString getCognome() const;
    QDate getNascita() const;
    double getPagaOraria() const;
    int getOreMese() const;
    int getVittorie() const;
    bool getObiettivi() const;

public slots:
    void confirm();
};

#endif // MODIFICA_ALLENATORE_H
