#include "modifica_nuotatore.h"

QString Modifica_Nuotatore::getNome() const{
    return nome->text();
}

QString Modifica_Nuotatore::getCognome() const{
    return cognome->text();
}

QDate Modifica_Nuotatore::getNascita() const{
    return nascita->date();
}

double Modifica_Nuotatore::getBase() const{
    return stipendioBase->value();
}

QDate Modifica_Nuotatore::getScadenza() const{
    return scadenza->date();
}

double Modifica_Nuotatore::getSponsor() const{
    return sponsor->value();
}

int Modifica_Nuotatore::getOri() const{
    return ori->value();
}

int Modifica_Nuotatore::getArgenti() const{
    return argenti->value();
}

int Modifica_Nuotatore::getBronzi() const{
    return bronzi->value();
}

Modifica_Nuotatore::Modifica_Nuotatore(QListWidget* t, QScrollArea* i, Modello* m, int ind, QWidget *parent) :
    QDialog(parent), text(t),info(i), model(m), index(ind),nome(new QLineEdit(this)), cognome(new QLineEdit(this)),
    nascita(new QDateEdit(this)), stipendioBase(new QDoubleSpinBox(this)), scadenza(new QDateEdit(this)),
    sponsor(new QDoubleSpinBox(this)), ori(new QSpinBox(this)), argenti(new QSpinBox(this)),
    bronzi(new QSpinBox(this))
{
    QRegExp rx("[a-zA-Z ']*");
    QValidator *rxv = new QRegExpValidator(rx,this);
    nome->setValidator(rxv);
    cognome->setValidator(rxv);

    setWindowTitle("Modifica Nuotatore");

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

    Nuotatore *nuot = static_cast<Nuotatore*>(model->getItem(index));
    nome->setText(QString::fromStdString(nuot->getNome()));
    cognome->setText(QString::fromStdString(nuot->getCognome()));
    nascita->setDate(nuot->getDataNascita());
    stipendioBase->setValue(nuot->getStipendioBase());
    scadenza->setDate(nuot->getScadenzaCertificato());
    sponsor->setValue(nuot->getSponsor());
    ori->setValue(nuot->getOri());
    argenti->setValue(nuot->getArgenti());
    bronzi->setValue(nuot->getBronzi());

    setLayout(form);

    connect(conferma, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void Modifica_Nuotatore::confirm(){
    QRegExp rx("[ ']*");
    if(getNome() == "" || getCognome() == "" || rx.exactMatch(getNome()) || rx.exactMatch(getCognome())){
        QMessageBox *mex = new QMessageBox(this);
        mex->resize(300,80);
        mex->setText("Campi obbligatori mancanti o non validi\nI campi obbligatori sono contrassegnati con l'asterisco");
        mex->exec();
    }
    else{
        Nuotatore *nuot = static_cast<Nuotatore*>(model->getItem(index));
        nuot->setNome(getNome().toStdString());
        nuot->setCognome(getCognome().toStdString());
        nuot->setDataNascita(getNascita());
        nuot->setStipendioBase(getBase());
        nuot->setScadenzaCertificato(getScadenza());
        nuot->setSponsor(getSponsor());
        nuot->setOri(getOri());
        nuot->setArgenti(getArgenti());
        nuot->setBronzi(getBronzi());

        text->item(index)->setText(getCognome());
        close();
    }
}
