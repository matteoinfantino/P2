#ifndef MODIFICA_NUOTATORE_H
#define MODIFICA_NUOTATORE_H

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

class Modifica_Nuotatore : public QDialog
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
    QDoubleSpinBox *sponsor;
    QSpinBox *ori;
    QSpinBox *argenti;
    QSpinBox *bronzi;
public:
    explicit Modifica_Nuotatore(QListWidget*, QScrollArea*, Modello*, int, QWidget *parent = nullptr);

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

#endif // MODIFICA_NUOTATORE_H
