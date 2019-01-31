#include "modifica_dirigente.h"

QString Modifica_Dirigente::getNome() const{
    return nome->text();
}

QString Modifica_Dirigente::getCognome() const{
    return cognome->text();
}

QDate Modifica_Dirigente::getNascita() const{
    return nascita->date();
}

double Modifica_Dirigente::getPagaOraria() const{
    return pagaOraria->value();
}

int Modifica_Dirigente::getOreMese() const{
    return oreMese->value();
}

int Modifica_Dirigente::getCommissioni() const{
    return commissioni->value();
}

bool Modifica_Dirigente::getMaster() const{
    return master->checkState();
}

Modifica_Dirigente::Modifica_Dirigente(QListWidget* t, QScrollArea* i, Modello* m, int ind, QWidget *parent) :
    QDialog(parent), text(t),info(i), model(m), index(ind), nome(new QLineEdit(this)), cognome(new QLineEdit(this)),
    nascita(new QDateEdit(this)), pagaOraria(new QDoubleSpinBox(this)), oreMese(new QSpinBox(this)), commissioni(new QSpinBox(this)),
    master(new QCheckBox(this))
{
    QRegExp rx("[a-zA-Z ']*");
    QValidator *rxv = new QRegExpValidator(rx,this);
    nome->setValidator(rxv);
    cognome->setValidator(rxv);
    setWindowTitle("Modifica Dirigente");

    QFormLayout *form = new QFormLayout();

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

    Dirigente *dir = static_cast<Dirigente*>(model->getItem(index));
    nome->setText(QString::fromStdString(dir->getNome()));
    cognome->setText(QString::fromStdString(dir->getCognome()));
    nascita->setDate(dir->getDataNascita());
    pagaOraria->setValue(dir->getPagaOraria());
    oreMese->setValue(dir->getOreMese());
    commissioni->setValue(dir->getCommisioni());
    if(dir->getMaster() == true)
        master->setChecked(true);
    else
        master->setChecked(false);

    setLayout(form);

    connect(conferma, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void Modifica_Dirigente::confirm(){
    QRegExp rx("[ ']*");
    if(getNome() == "" || getCognome() == "" || rx.exactMatch(getNome()) || rx.exactMatch(getCognome())){
        QMessageBox *mex = new QMessageBox(this);
        mex->resize(300,80);
        mex->setText("Campi obbligatori mancanti o non validi\nI campi obbligatori sono contrassegnati con l'asterisco");
        mex->exec();
    }
    else{
        Dirigente *dir = static_cast<Dirigente*>(model->getItem(index));
        dir->setNome(getNome().toStdString());
        dir->setCognome(getCognome().toStdString());
        dir->setDataNascita(getNascita());
        dir->setPagaOraria(getPagaOraria());
        dir->setOreMese(getOreMese());
        dir->setCommisioni(getCommissioni());
        dir->setMaster(getMaster());

        text->item(index)->setText(getCognome());
        close();
    }
}
