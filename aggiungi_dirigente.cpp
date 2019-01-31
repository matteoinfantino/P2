#include "aggiungi_dirigente.h"

QString Aggiungi_Dirigente::getNome() const{
    return nome->text();
}

QString Aggiungi_Dirigente::getCognome() const{
    return cognome->text();
}

QDate Aggiungi_Dirigente::getNascita() const{
    return nascita->date();
}

double Aggiungi_Dirigente::getPagaOraria() const{
    return pagaOraria->value();
}

int Aggiungi_Dirigente::getOreMese() const{
    return oreMese->value();
}

int Aggiungi_Dirigente::getCommissioni() const{
    return commissioni->value();
}

bool Aggiungi_Dirigente::getMaster() const{
    return master->checkState();
}

Aggiungi_Dirigente::Aggiungi_Dirigente(QListWidget* t, QScrollArea* i, Modello* m,QWidget *parent) :
    QDialog(parent), text(t),info(i), model(m), nome(new QLineEdit(this)), cognome(new QLineEdit(this)),
    nascita(new QDateEdit(this)), pagaOraria(new QDoubleSpinBox(this)), oreMese(new QSpinBox(this)),
    commissioni(new QSpinBox(this)), master(new QCheckBox(this))
{
    QRegExp rx("[a-zA-Z ']*");
    QValidator *rxv = new QRegExpValidator(rx,this);
    nome->setPlaceholderText("Es. Mario");
    cognome->setPlaceholderText("Es. Rossi");
    nome->setValidator(rxv);
    cognome->setValidator(rxv);

    setWindowTitle("Aggiungi Dirigente");

    QFormLayout *form = new QFormLayout(this);

    form->addRow("Nome*",nome);
    form->addRow("Cognome*",cognome);

    nascita->setDisplayFormat("dd.MM.yyyy");
    form->addRow("Data di nascita",nascita);

    pagaOraria->setMaximum(1000000000.00);
    form->addRow("Salario Orario",pagaOraria);

    oreMese->setMaximum(300);
    form->addRow("Ore Lavorative",oreMese);
    form->addRow("Commissioni",commissioni);
    form->addRow("Master",master);

    QPushButton *conferma = new QPushButton("Conferma",this);
    form->addWidget(conferma);

    conferma->setDefault(true);

    setLayout(form);

    connect(conferma, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void Aggiungi_Dirigente::confirm(){
    QRegExp rx("[ ']*");
    if(getNome() == "" || getCognome() == "" || rx.exactMatch(getNome()) || rx.exactMatch(getCognome())){
        QMessageBox *mex = new QMessageBox(this);
        mex->resize(300,80);
        mex->setText("Campi obbligatori mancanti o non validi\nI campi obbligatori sono contrassegnati con l'asterisco");
        mex->exec();
    }
    else{
        model->addDir(getNome().toStdString(),getCognome().toStdString(),getNascita(),getPagaOraria(),getOreMese(),
                       getCommissioni(),getMaster());
        text->addItem(getCognome());

        nome->clear();
        cognome->clear();
        nascita->setDate(QDate(2000,01,01));
        pagaOraria->setValue(0.0);
        oreMese->setValue(0);
        commissioni->setValue(0);
        master->setChecked(false);
    }
}
