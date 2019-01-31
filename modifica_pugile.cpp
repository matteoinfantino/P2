#include "modifica_pugile.h"

QString Modifica_Pugile::getNome() const{
    return nome->text();
}

QString Modifica_Pugile::getCognome() const{
    return cognome->text();
}

QDate Modifica_Pugile::getNascita() const{
    return nascita->date();
}

double Modifica_Pugile::getBase() const{
    return stipendioBase->value();
}

QDate Modifica_Pugile::getScadenza() const{
    return scadenza->date();
}

int Modifica_Pugile::getVittorie() const{
    return vittorie->value();
}

int Modifica_Pugile::getVittKO() const{
    return vittorieKO->value();
}

int Modifica_Pugile::getSconfitteKO() const{
    return sconfitteKO->value();
}

Modifica_Pugile::Modifica_Pugile(QListWidget* t, QScrollArea* i, Modello* m, int ind, QWidget *parent) :
    QDialog(parent), text(t),info(i), model(m), index(ind), nome(new QLineEdit(this)), cognome(new QLineEdit(this)),
    nascita(new QDateEdit(this)), stipendioBase(new QDoubleSpinBox(this)), scadenza(new QDateEdit(this)),
    vittorie(new QSpinBox(this)), vittorieKO(new QSpinBox(this)), sconfitteKO(new QSpinBox(this))
{
    QRegExp rx("[a-zA-Z ']*");
    QValidator *rxv = new QRegExpValidator(rx,this);
    nome->setValidator(rxv);
    cognome->setValidator(rxv);
    setWindowTitle("Modifica Pugile");

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

    Pugile *pug = static_cast<Pugile*>(model->getItem(index));
    nome->setText(QString::fromStdString(pug->getNome()));
    cognome->setText(QString::fromStdString(pug->getCognome()));
    nascita->setDate(pug->getDataNascita());
    stipendioBase->setValue(pug->getStipendioBase());
    scadenza->setDate(pug->getScadenzaCertificato());
    vittorie->setValue(pug->getVittorie());
    vittorieKO->setValue(pug->getVittorieKO());
    sconfitteKO->setValue(pug->getSconfitteKO());

    setLayout(form);

    connect(conferma, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void Modifica_Pugile::confirm(){
    QRegExp rx("[ ']*");
    if(getNome() == "" || getCognome() == "" || rx.exactMatch(getNome()) || rx.exactMatch(getCognome())){
        QMessageBox *mex = new QMessageBox(this);
        mex->resize(300,80);
        mex->setText("Campi obbligatori mancanti o non validi\nI campi obbligatori sono contrassegnati con l'asterisco");
        mex->exec();
    }
    else{
        Pugile *pug = static_cast<Pugile*>(model->getItem(index));
        pug->setNome(getNome().toStdString());
        pug->setCognome(getCognome().toStdString());
        pug->setDataNascita(getNascita());
        pug->setStipendioBase(getBase());
        pug->setScadenzaCertificato(getScadenza());
        pug->setVittorie(getVittorie());
        pug->setVittorieKO(getVittKO());
        pug->setSconfitteKO(getSconfitteKO());

        text->item(index)->setText(getCognome());
        close();
    }
}
