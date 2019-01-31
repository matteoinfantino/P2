#ifndef VISTA_H
#define VISTA_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QScrollArea>
#include <QMenuBar>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <regex>

#include "modello.h"
#include "aggiungi.h"
#include "modifica_calciatore.h"
#include "modifica_nuotatore.h"
#include "modifica_pugile.h"
#include "modifica_dirigente.h"
#include "modifica_allenatore.h"

class Vista : public QWidget {
    Q_OBJECT
private:
    Modello *model;

    QListWidget *text;
    QScrollArea *info;

    QLabel* infoLabel;

    QLineEdit *cerca;

    QDateEdit *date;
    QDoubleSpinBox *stip;
    QDateEdit *scad;
public:
    Vista(QWidget *parent = nullptr);
     ~Vista();

    void loadData();

public slots:
    void saveData();
    void choose();
    void display();
    void remove();
    void calcoloStipendi();
    void ordineAlfa();
    void search() const;
    void modify();
    void about();
    void removeOptions();
    void removeCalc();
    void removeNuot();
    void removePug();
    void removeDir();
    void removeAll();
    void removeDate();
    void removeStip();
    void removeScad();
};

#endif // WIDGET_H
