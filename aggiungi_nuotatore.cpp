#include "aggiungi_nuotatore.h"

QString Aggiungi_Nuotatore::getNome() const{
    return nome->text();
}

QString Aggiungi_Nuotatore::getCognome() const{
    return cognome->text();
}

QDate Aggiungi_Nuotatore::getNascita() const{
    return nascita->date();
}

double Aggiungi_Nuotatore::getBase() const{
    return stipendioBase->value();
}

QDate Aggiungi_Nuotatore::getScadenza() const{
    return scadenza->date();
}

double Aggiungi_Nuotatore::getSponsor() const{
    return sponsor->value();
}

int Aggiungi_Nuotatore::getOri() const{
    return ori->value();
}

int Aggiungi_Nuotatore::getArgenti() const{
    return argenti->value();
}

int Aggiungi_Nuotatore::getBronzi() const{
    return bronzi->value();
}

Aggiungi_Nuotatore::Aggiungi_Nuotatore(QListWidget* t, QScrollArea* i, Modello* m,QWidget *parent) :
    QDialog(parent), text(t),info(i), model(m), nome(new QLineEdit(this)), cognome(new QLineEdit(this)),
    nascita(new QDateEdit(this)), stipendioBase(new QDoubleSpinBox(this)), scadenza(new QDateEdit(this)),
    sponsor(new QDoubleSpinBox(this)), ori(new QSpinBox(this)), argenti(new QSpinBox(this)), bronzi(new QSpinBox(this))
{
    QRegExp rx("[a-zA-Z ']*");
    QValidator *rxv = new QRegExpValidator(rx,this);
    nome->setPlaceholderText("Es. Mario");
    cognome->setPlaceholderText("Es. Rossi");
    nome->setValidator(rxv);
    cognome->setValidator(rxv);

    setWindowTitle("Aggiungi Nuotatore");

    QFormLayout *form = new QFormLayout();

    form->addRow("Nome*",nome);
    form->addRow("Cognome*",cognome);

    nascita->setDisplayFormat("dd.MM.yyyy");
    form->addRow("Data di nascita",nascita);

    stipendioBase->setMaximum(1000000000.00);
    form->addRow("Stipendio base",stipendioBase);

    scadenza->setDisplayFormat("dd.MM.yyyy");
    form->addRow("Scadenza Certificato",scadenza);
    sponsor->setMaximum(1000000000.00);
    form->addRow("Ricavi da Sponsor",sponsor);
    form->addRow("Ori vinti",ori);
    form->addRow("Argenti vinti",argenti);
    form->addRow("Bronzi vinti",bronzi);

    QPushButton *conferma = new QPushButton("Conferma",this);
    form->addWidget(conferma);

    setLayout(form);

    connect(conferma, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void Aggiungi_Nuotatore::confirm(){

    QRegExp rx("[ ']*");
    if(getNome() == "" || getCognome() == "" || rx.exactMatch(getNome()) || rx.exactMatch(getCognome())){
        QMessageBox *mex = new QMessageBox(this);
        mex->resize(300,80);
        mex->setText("Campi obbligatori mancanti o non validi\nI campi obbligatori sono contrassegnati con l'asterisco");
        mex->exec();
    }
    else{
        model->addNuot(getNome().toStdString(),getCognome().toStdString(),getNascita(),getBase(),getScadenza(),
                       getSponsor(),getOri(),getArgenti(),getBronzi());
        text->addItem(getCognome());

        nome->clear();
        cognome->clear();
        nascita->setDate(QDate(2000,01,01));
        stipendioBase->setValue(0.0);
        scadenza->setDate(QDate(2000,01,01));
        sponsor->setValue(0.0);
        ori->setValue(0);
        argenti->setValue(0);
        bronzi->setValue(0);
    }
}
