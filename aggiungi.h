#ifndef AGGIUNGI_H
#define AGGIUNGI_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>

#include "aggiungi_calciatore.h"
#include "aggiungi_nuotatore.h"
#include "aggiungi_pugile.h"
#include "aggiungi_dirigente.h"
#include "aggiungi_allenatore.h"

class Aggiungi : public QDialog
{
    Q_OBJECT

private:
    QListWidget* text;
    QScrollArea* info;
    Modello* model;

    QPushButton *popupButton;

public:
    explicit Aggiungi(QListWidget*, QScrollArea*, Modello*, QWidget *parent = nullptr);

public slots:
    void calcSlot() const;
    void nuotSlot() const;
    void pugSlot() const;
    void dirigSlot() const;
    void allSlot() const;
    void add();
};

#endif // AGGIUNGI_H
