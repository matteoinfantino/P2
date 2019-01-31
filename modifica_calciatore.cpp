#include "modifica_calciatore.h"

QString Modifica_Calciatore::getNome() const{
    return nome->text();
}

QString Modifica_Calciatore::getCognome() const{
    return cognome->text();
}

QDate Modifica_Calciatore::getNascita() const{
    return nascita->date();
}

double Modifica_Calciatore::getBase() const{
    return stipendioBase->value();
}

QDate Modifica_Calciatore::getScadenza() const
{
    return scadenza->date();
}

int Modifica_Calciatore::getPresenze() const{
    return presenze->value();
}

int Modifica_Calciatore::getBonus() const{
    return bonus->value();
}

int Modifica_Calciatore::getMalus() const{
    return malus->value();
}

bool Modifica_Calciatore::getChiave() const{
    return chiave->checkState();
}

Modifica_Calciatore::Modifica_Calciatore(QListWidget* t, QScrollArea* i, Modello* m, int ind, QWidget *parent) :
    QDialog(parent), text(t),info(i), model(m), index(ind), nome(new QLineEdit(this)), cognome(new QLineEdit(this)),
    nascita(new QDateEdit(this)), stipendioBase(new QDoubleSpinBox(this)), scadenza(new QDateEdit(this)),presenze(new QSpinBox(this)),
    bonus(new QSpinBox(this)), malus(new QSpinBox(this)), chiave(new QCheckBox(this))
{
    QRegExp rx("[a-zA-Z ']*");
    QValidator *rxv = new QRegExpValidator(rx,this);
    nome->setValidator(rxv);
    cognome->setValidator(rxv);

    setWindowTitle("Modifica Calciatore");

    QFormLayout *form = new QFormLayout();

    form->addRow("Nome*",nome);
    form->addRow("Cognome*",cognome);

    nascita->setDisplayFormat("dd.MM.yyyy");
    form->addRow("Data di nascita",nascita);

    stipendioBase->setMaximum(1000000000.00);
    form->addRow("Stipendio base",stipendioBase);

    scadenza->setDisplayFormat("dd.MM.yyyy");
    form->addRow("Scadenza Certificato",scadenza);
    form->addRow("Presenze",presenze);
    form->addRow("Bonus",bonus);
    form->addRow("Malus",malus);
    form->addRow("Giocatore Chiave",chiave);

    QPushButton *conferma = new QPushButton("Conferma",this);
    form->addWidget(conferma);

    Calciatore *calc = static_cast<Calciatore*>(model->getItem(index));
    nome->setText(QString::fromStdString(calc->getNome()));
    cognome->setText(QString::fromStdString(calc->getCognome()));
    nascita->setDate(calc->getDataNascita());
    stipendioBase->setValue(calc->getStipendioBase());
    scadenza->setDate(calc->getScadenzaCertificato());
    presenze->setValue(calc->getPresenze());
    bonus->setValue(calc->getBonus());
    malus->setValue(calc->getMalus());
    if(calc->getGiocatoreChiave() == true)
        chiave->setChecked(true);
    else
        chiave->setChecked(false);

    setLayout(form);

    connect(conferma, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void Modifica_Calciatore::confirm(){
    QRegExp rx("[ ']*");
    if(getNome() == "" || getCognome() == "" || rx.exactMatch(getNome()) || rx.exactMatch(getCognome())){
        QMessageBox *mex = new QMessageBox(this);
        mex->resize(300,80);
        mex->setText("Campi obbligatori mancanti o non validi\nI campi obbligatori sono contrassegnati con l'asterisco");
        mex->exec();
    }
    else{
        Calciatore *calc = static_cast<Calciatore*>(model->getItem(index));
        calc->setNome(getNome().toStdString());
        calc->setCognome(getCognome().toStdString());
        calc->setDataNascita(getNascita());
        calc->setStipendioBase(getBase());
        calc->setScadenzaCertificato(getScadenza());
        calc->setPresenze(getPresenze());
        calc->setBonus(getBonus());
        calc->setMalus(getMalus());
        calc->setGiocatoreChiave(getChiave());

        text->item(index)->setText(getCognome());
        close();
    }
}
