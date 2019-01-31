#ifndef AGGIUNGI_DIRIGENTE_H
#define AGGIUNGI_DIRIGENTE_H

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

class Aggiungi_Dirigente : public QDialog
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
    QSpinBox *commissioni;
    QCheckBox *master;
public:
    explicit Aggiungi_Dirigente(QListWidget*, QScrollArea*, Modello*, QWidget *parent = nullptr);

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

#endif // AGGIUNGI_DIRIGENTE_H
