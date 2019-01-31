#include "modifica_allenatore.h"

QString Modifica_Allenatore::getNome() const{
    return nome->text();
}

QString Modifica_Allenatore::getCognome() const{
    return cognome->text();
}

QDate Modifica_Allenatore::getNascita() const{
    return nascita->date();
}

double Modifica_Allenatore::getPagaOraria() const{
    return pagaOraria->value();
}

int Modifica_Allenatore::getOreMese() const{
    return oreMese->value();
}

int Modifica_Allenatore::getVittorie() const{
    return vittorie->value();
}

bool Modifica_Allenatore::getObiettivi() const{
    return obiettivi->checkState();
}

Modifica_Allenatore::Modifica_Allenatore(QListWidget* t, QScrollArea* i, Modello* m, int ind, QWidget *parent) :
    QDialog(parent), text(t),info(i), model(m), index(ind), nome(new QLineEdit(this)), cognome(new QLineEdit(this)),
    nascita(new QDateEdit(this)), pagaOraria(new QDoubleSpinBox(this)), oreMese(new QSpinBox(this)), vittorie(new QSpinBox(this)),
    obiettivi(new QCheckBox(this))
{
    QRegExp rx("[a-zA-Z ']*");
    QValidator *rxv = new QRegExpValidator(rx,this);
    nome->setValidator(rxv);
    cognome->setValidator(rxv);
    setWindowTitle("Modifica Allenatore");

    QFormLayout *form = new QFormLayout();

    form->addRow("Nome*",nome);
    form->addRow("Cognome*",cognome);

    nascita->setDisplayFormat("dd.MM.yyyy");
    form->addRow("Data di nascita",nascita);

    pagaOraria->setMaximum(1000000000.00);
    form->addRow("Salario Orario",pagaOraria);

    oreMese->setMaximum(300);
    form->addRow("Ore Lavorative",oreMese);
    form->addRow("Vittorie",vittorie);
    form->addRow("Obiettivi",obiettivi);

    QPushButton *conferma = new QPushButton("Conferma",this);
    form->addWidget(conferma);

    Allenatore *all = static_cast<Allenatore*>(model->getItem(index));
    nome->setText(QString::fromStdString(all->getNome()));
    cognome->setText(QString::fromStdString(all->getCognome()));
    nascita->setDate(all->getDataNascita());
    pagaOraria->setValue(all->getPagaOraria());
    oreMese->setValue(all->getOreMese());
    vittorie->setValue(all->getVittorie());
    if(all->getVittorie() == true)
        obiettivi->setChecked(true);
    else
        obiettivi->setChecked(false);

    setLayout(form);

    connect(conferma, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void Modifica_Allenatore::confirm(){
    QRegExp rx("[ ']*");
    if(getNome() == "" || getCognome() == "" || rx.exactMatch(getNome()) || rx.exactMatch(getCognome())){
        QMessageBox *mex = new QMessageBox(this);
        mex->resize(300,80);
        mex->setText("Campi obbligatori mancanti o non validi\nI campi obbligatori sono contrassegnati con l'asterisco");
        mex->exec();
    }
    else{
        Allenatore *all = static_cast<Allenatore*>(model->getItem(index));
        all->setNome(getNome().toStdString());
        all->setCognome(getCognome().toStdString());
        all->setDataNascita(getNascita());
        all->setPagaOraria(getPagaOraria());
        all->setOreMese(getOreMese());
        all->setVittorie(getVittorie());
        all->setObiettivi(getObiettivi());

        text->item(index)->setText(getCognome());
        close();
    }
}
