#include "aggiungi_calciatore.h"

QString Aggiungi_Calciatore::getNome() const{
    return nome->text();
}

QString Aggiungi_Calciatore::getCognome() const{
    return cognome->text();
}

QDate Aggiungi_Calciatore::getNascita() const{
    return nascita->date();
}

double Aggiungi_Calciatore::getBase() const{
    return stipendioBase->value();
}

QDate Aggiungi_Calciatore::getScadenza() const
{
    return scadenza->date();
}

int Aggiungi_Calciatore::getPresenze() const{
    return presenze->value();
}

int Aggiungi_Calciatore::getBonus() const{
    return bonus->value();
}

int Aggiungi_Calciatore::getMalus() const{
    return malus->value();
}

bool Aggiungi_Calciatore::getChiave() const{
    return chiave->checkState();
}

Aggiungi_Calciatore::Aggiungi_Calciatore(QListWidget* t, QScrollArea* i, Modello* m,QWidget *parent) :
    QDialog(parent), text(t),info(i), model(m), nome(new QLineEdit(this)), cognome(new QLineEdit(this)),
    nascita(new QDateEdit(this)), stipendioBase(new QDoubleSpinBox(this)), scadenza(new QDateEdit(this)),
    presenze(new QSpinBox(this)), bonus(new QSpinBox(this)), malus(new QSpinBox(this)), chiave(new QCheckBox(this))
{
    QRegExp rx("[a-zA-Z ']*");
    QValidator *rxv = new QRegExpValidator(rx,this);
    nome->setPlaceholderText("Es. Mario");
    cognome->setPlaceholderText("Es. Rossi");
    nome->setValidator(rxv);
    cognome->setValidator(rxv);

    setWindowTitle("Aggiungi Calciatore");

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

    conferma->setDefault(true);

    setLayout(form);

    connect(conferma, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void Aggiungi_Calciatore::confirm(){

    QRegExp rx("[ ']*");
    if(getNome() == "" || getCognome() == "" || rx.exactMatch(getNome()) || rx.exactMatch(getCognome())){
        QMessageBox *mex = new QMessageBox(this);
        mex->resize(300,80);
        mex->setText("Campi obbligatori mancanti o non validi\nI campi obbligatori sono contrassegnati con l'asterisco");
        mex->exec();
    }
    else{
        model->addCalc(getNome().toStdString(),getCognome().toStdString(),getNascita(),getBase(),getScadenza(),
                       getPresenze(),getBonus(),getMalus(),getChiave());
        text->addItem(getCognome());

        nome->clear();
        cognome->clear();
        nascita->setDate(QDate(2000,01,01));
        stipendioBase->setValue(0.0);
        scadenza->setDate(QDate(2000,01,01));
        presenze->setValue(0);
        bonus->setValue(0);
        malus->setValue(0);
        chiave->setChecked(false);
    }
}

