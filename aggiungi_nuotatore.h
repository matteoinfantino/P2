#ifndef AGGIUNGI_NUOTATORE_H
#define AGGIUNGI_NUOTATORE_H

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

class Aggiungi_Nuotatore : public QDialog
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
    QDoubleSpinBox *sponsor;
    QSpinBox *ori;
    QSpinBox *argenti;
    QSpinBox *bronzi;
public:
    explicit Aggiungi_Nuotatore(QListWidget*, QScrollArea*, Modello*, QWidget *parent = nullptr);

    QString getNome() const;
    QString getCognome() const;
    QDate getNascita() const;
    double getBase() const;
    QDate getScadenza() const;
    double getSponsor() const;
    int getOri() const;
    int getArgenti() const;
    int getBronzi() const;

public slots:
    void confirm();
};

#endif // AGGIUNGI_NUOTATORE_H
