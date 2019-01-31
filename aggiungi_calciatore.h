#ifndef AGGIUNGI_CALCIATORE_H
#define AGGIUNGI_CALCIATORE_H

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

class Aggiungi_Calciatore : public QDialog
{
    Q_OBJECT

private:
    QListWidget* text;
    QScrollArea* info;
    Modello* model;

    QLineEdit *nome;
    QLineEdit *cognome;
    QDateEdit *nascita;
    QDoubleSpinBox *stipendioBase;
    QDateEdit *scadenza;
    QSpinBox *presenze;
    QSpinBox *bonus;
    QSpinBox *malus;
    QCheckBox *chiave;
public:
    explicit Aggiungi_Calciatore(QListWidget*, QScrollArea*, Modello*, QWidget *parent = nullptr);

    QString getNome() const;
    QString getCognome() const;
    QDate getNascita() const;
    double getBase() const;
    QDate getScadenza() const;
    int getPresenze() const;
    int getBonus() const;
    int getMalus() const;
    bool getChiave() const;

public slots:
    void confirm();
};

#endif // AGGIUNGI_CALCIATORE_H
