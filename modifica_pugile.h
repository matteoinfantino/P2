#ifndef MODIFICA_PUGILE_H
#define MODIFICA_PUGILE_H

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

#include "modello.h"

class Modifica_Pugile : public QDialog
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
    QSpinBox *vittorie;
    QSpinBox *vittorieKO;
    QSpinBox *sconfitteKO;
public:
    explicit Modifica_Pugile(QListWidget*, QScrollArea*, Modello*, int,QWidget *parent = nullptr);

    QString getNome() const;
    QString getCognome() const;
    QDate getNascita() const;
    double getBase() const;
    QDate getScadenza() const;
    int getVittorie() const;
    int getVittKO() const;
    int getSconfitteKO() const;

public slots:
    void confirm();
};

#endif // MODIFICA_PUGILE_H
