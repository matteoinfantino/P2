#include "aggiungi.h"

Aggiungi::Aggiungi(QListWidget* t, QScrollArea* i, Modello* m,QWidget *parent) :
    QDialog(parent), text(t),info(i), model(m), popupButton(new QPushButton(this))
{
    resize(300,90);
    setWindowTitle("Tipologia Tesserato");

    QVBoxLayout *v = new QVBoxLayout();
    v->setSpacing(0);

    popupButton->setText("Seleziona");

    QMenu *menu = new QMenu(this);
    QAction *calc = new QAction("Calciatore", menu);
    QAction *nuot = new QAction("Nuotatore", menu);
    QAction *pug = new QAction("Pugile", menu);
    QAction *dirig = new QAction("Dirigente", menu);
    QAction *all = new QAction("Allenatore",menu);

    menu->addAction(calc);
    menu->addAction(nuot);
    menu->addAction(pug);
    menu->addAction(dirig);
    menu->addAction(all);

    popupButton->setMenu(menu);

    v->addWidget(popupButton);

    QHBoxLayout *h = new QHBoxLayout();
    QPushButton *conferma = new QPushButton("Conferma",this);
    QPushButton *annulla = new QPushButton("Annulla",this);
    h->addWidget(annulla);
    h->addWidget(conferma);

    v->addLayout(h);
    setLayout(v);

    connect(calc,SIGNAL(triggered(bool)),this,SLOT(calcSlot()));
    connect(nuot,SIGNAL(triggered(bool)),this,SLOT(nuotSlot()));
    connect(pug,SIGNAL(triggered(bool)),this,SLOT(pugSlot()));
    connect(dirig,SIGNAL(triggered(bool)),this,SLOT(dirigSlot()));
    connect(all,SIGNAL(triggered(bool)),this,SLOT(allSlot()));
    connect(annulla,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(conferma,SIGNAL(clicked(bool)),this,SLOT(add()));
}

void Aggiungi::calcSlot() const{    
    popupButton->setText("Calciatore");
}

void Aggiungi::nuotSlot() const{
    popupButton->setText("Nuotatore");
}

void Aggiungi::pugSlot() const{
    popupButton->setText("Pugile");
}

void Aggiungi::dirigSlot() const{
    popupButton->setText("Dirigente");
}

void Aggiungi::allSlot() const{
    popupButton->setText("Allenatore");
}

void Aggiungi::add() {

    if(popupButton->text() == "Calciatore"){
        Aggiungi_Calciatore *window = new Aggiungi_Calciatore(text,info,model,this);
        window->exec();
    }
    else{
        if(popupButton->text() == "Nuotatore"){
            Aggiungi_Nuotatore *window = new Aggiungi_Nuotatore(text,info,model,this);
            window->exec();
        }
        else{
            if(popupButton->text() == "Pugile"){
                Aggiungi_Pugile *window = new Aggiungi_Pugile(text,info,model,this);
                window->exec();
            }
            else{
                if(popupButton->text() == "Dirigente"){
                    Aggiungi_Dirigente *window = new Aggiungi_Dirigente(text,info,model,this);
                    window->exec();
                }
                else{
                    if(popupButton->text() == "Allenatore"){
                        Aggiungi_Allenatore *window = new Aggiungi_Allenatore(text,info,model,this);
                        window->exec();
                    }
                }
            }
        }
    }

    close();
}
