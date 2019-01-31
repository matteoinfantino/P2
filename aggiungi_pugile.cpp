#include "aggiungi_pugile.h"

QString Aggiungi_Pugile::getNome() const{
    return nome->text();
}

QString Aggiungi_Pugile::getCognome() const{
    return cognome->text();
}

QDate Aggiungi_Pugile::getNascita() const{
    return nascita->date();
}

double Aggiungi_Pugile::getBase() const{
    return stipendioBase->value();
}

QDate Aggiungi_Pugile::getScadenza() const{
    return scadenza->date();
}

int Aggiungi_Pugile::getVittorie() const{
    return vittorie->value();
}

int Aggiungi_Pugile::getVittKO() const{
    return vittorieKO->value();
}

int Aggiungi_Pugile::getSconfitteKO() const{
    return sconfitteKO->value();
}

Aggiungi_Pugile::Aggiungi_Pugile(QListWidget* t, QScrollArea* i, Modello* m,QWidget *parent) :
    QDialog(parent), text(t),info(i), model(m), nome(new QLineEdit(this)), cognome(new QLineEdit(this)),
    nascita(new QDateEdit(this)), stipendioBase(new QDoubleSpinBox(this)), scadenza(new QDateEdit(this)),
    vittorie(new QSpinBox(this)), vittorieKO(new QSpinBox(this)), sconfitteKO(new QSpinBox(this))
{
    QRegExp rx("[a-zA-Z ']*");
    QValidator *rxv = new QRegExpValidator(rx,this);
    nome->setPlaceholderText("Es. Mario");
    cognome->setPlaceholderText("Es. Rossi");
    nome->setValidator(rxv);
    cognome->setValidator(rxv);

    setWindowTitle("Aggiungi Pugile");

    QFormLayout *form = new QFormLayout();

    form->addRow("Nome*",nome);
    form->addRow("Cognome*",cognome);

    nascita->setDisplayFormat("dd.MM.yyyy");
    form->addRow("Data di nascita",nascita);

    stipendioBase->setMaximum(1000000000.00);
    form->addRow("Stipendio base",stipendioBase);

    scadenza->setDisplayFormat("dd.MM.yyyy");
    form->addRow("Scadenza Certificato",scadenza);
    form->addRow("Vittorie",vittorie);
    form->addRow("Vittorie KO",vittorieKO);
    form->addRow("Sconfitte KO",sconfitteKO);

    QPushButton *conferma = new QPushButton("Conferma",this);
    form->addWidget(conferma);

    setLayout(form);

    connect(conferma, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void Aggiungi_Pugile::confirm(){
    QRegExp rx("[ ']*");
    if(getNome() == "" || getCognome() == "" || rx.exactMatch(getNome()) || rx.exactMatch(getCognome())){
        QMessageBox *mex = new QMessageBox(this);
        mex->resize(300,80);
        mex->setText("Campi obbligatori mancanti o non validi\nI campi obbligatori sono contrassegnati con l'asterisco");
        mex->exec();
    }
    else{
        model->addPug(getNome().toStdString(),getCognome().toStdString(),getNascita(),getBase(),getScadenza(),
                       getVittorie(),getVittKO(),getSconfitteKO());
        text->addItem(getCognome());

        nome->clear();
        cognome->clear();
        nascita->setDate(QDate(2000,01,01));
        stipendioBase->setValue(0.0);
        scadenza->setDate(QDate(2000,01,01));
        vittorie->setValue(0);
        vittorieKO->setValue(0);
        sconfitteKO->setValue(0);
    }
}
