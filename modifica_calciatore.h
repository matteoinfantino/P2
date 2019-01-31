#ifndef MODIFICA_CALCIATORE_H
#define MODIFICA_CALCIATORE_H

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

class Modifica_Calciatore : public QDialog
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
    QDoubleSpinBox *stipendioBase;
    QDateEdit *scadenza;
    QSpinBox *presenze;
    QSpinBox *bonus;
    QSpinBox *malus;
    QCheckBox *chiave;
public:
    explicit Modifica_Calciatore(QListWidget*, QScrollArea*, Modello*, int, QWidget *parent = nullptr);

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

#endif // MODIFICA_CALCIATORE_H
