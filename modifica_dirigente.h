#ifndef MODIFICA_DIRIGENTE_H
#define MODIFICA_DIRIGENTE_H

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

class Modifica_Dirigente: public QDialog
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
    QSpinBox *commissioni;
    QCheckBox *master;
public:
    explicit Modifica_Dirigente(QListWidget*, QScrollArea*, Modello*, int, QWidget *parent = nullptr);

    QString getNome() const;
    QString getCognome() const;
    QDate getNascita() const;
    double getPagaOraria() const;
    int getOreMese() const;
    int getCommissioni() const;
    bool getMaster() const;

public slots:
    void confirm();
};

#endif // MODIFICA_DIRIGENTE_H
