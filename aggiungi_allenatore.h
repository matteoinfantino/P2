#ifndef AGGIUNGI_ALLENATORE_H
#define AGGIUNGI_ALLENATORE_H

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QListWidget>
#include <QScrollArea>
#include <QCheckBox>
#include <QMessageBox>

#include "modello.h"

class Aggiungi_Allenatore : public QDialog
{
    Q_OBJECT

private:
    QListWidget* text;
    QScrollArea* info;
    Modello* model;

    QLineEdit *nome;
    QLineEdit *cognome;
    QDateEdit *nascita;

    QDoubleSpinBox *pagaOraria;
    QSpinBox *oreMese;
    QSpinBox *vittorie;
    QCheckBox *obiettivi;
public:
    explicit Aggiungi_Allenatore(QListWidget*, QScrollArea*, Modello*, QWidget *parent = nullptr);

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

#endif // AGGIUNGI_ALLENATORE_H
