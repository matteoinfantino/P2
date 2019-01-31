#include "vista.h"

Vista::Vista(QWidget *parent) :
    QWidget(parent), model(new Modello()), text(new QListWidget(this)), info(new QScrollArea(this)), infoLabel(new QLabel()),
    cerca(new QLineEdit(this)), date(new QDateEdit()), stip(new QDoubleSpinBox()), scad(new QDateEdit())
{
    resize(720,380);
    setMinimumSize(720,300);
    setMaximumSize(1000,700);

    loadData();

    // Creo tutti i layout che mi servono
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *menuLayout = new QVBoxLayout();
    QHBoxLayout *secondLayout = new QHBoxLayout();
    QVBoxLayout *thirdLayout = new QVBoxLayout();
    QVBoxLayout *fourthLayout = new QVBoxLayout();
    QHBoxLayout *fifthLayout = new QHBoxLayout();
    QHBoxLayout *sixthLayout = new QHBoxLayout();

    // Creo il menu
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *menu = new QMenu("File", menuBar);
    QMenu *menu2 = new QMenu("Help", menuBar);
    QAction *save = new QAction("Save", menu);
    QAction *exit = new QAction("Exit", menu);
    QAction *about = new QAction("About",menu2);

    // Assemblo il menu
    menuBar->addMenu(menu);
    menuBar->addMenu(menu2);
    menu->addAction(save);
    menu->addAction(exit);
    menu2->addAction(about);
    menuLayout->addWidget(menuBar);
    menu->setObjectName("save");

    // Assemblo il mainLayout
    mainLayout->addLayout(menuLayout);
    mainLayout->addLayout(secondLayout);

    secondLayout->addLayout(thirdLayout);
    secondLayout->addLayout(fourthLayout);

    thirdLayout->setSpacing(0);
    QRegExp rx("[a-zA-Z]*");
    QValidator *rxv = new QRegExpValidator(rx,this);
    cerca->setValidator(rxv);
    cerca->setPlaceholderText("Cerca");
    thirdLayout->addWidget(cerca);
    cerca->setObjectName("searchBar");
    thirdLayout->addWidget(text);

    fourthLayout->setSpacing(0);
    fourthLayout->addWidget(info);
    fourthLayout->addLayout(fifthLayout);

    QPushButton *aggiungi = new QPushButton("Aggiungi");
    QPushButton *modifica = new QPushButton("Modifica");
    fifthLayout->addWidget(aggiungi);
    fifthLayout->addWidget(modifica);

    fourthLayout->addLayout(sixthLayout);
    QPushButton *rimuovi = new QPushButton("Rimuovi");
    QPushButton *rimozione = new QPushButton("Opzioni Rimozione");
    sixthLayout->addWidget(rimuovi);
    sixthLayout->addWidget(rimozione);

    QPushButton *calcolo = new QPushButton("Calcolo Totale Stipendi");
    fourthLayout->addWidget(calcolo);

    QPushButton *ordineAlfa = new QPushButton("Ordine Alfabetico");
    fourthLayout->addWidget(ordineAlfa);

    // Infine imposto il layout principale dell'applicazione
    setLayout(mainLayout);

    info->setWidget(infoLabel);

    connect(aggiungi, SIGNAL(clicked()), this, SLOT(choose()));
    connect(text, SIGNAL(itemSelectionChanged()), this, SLOT(display()));
    connect(save,SIGNAL(triggered(bool)),this,SLOT(saveData()));
    connect(exit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(rimuovi,SIGNAL(clicked(bool)),this,SLOT(remove()));
    connect(calcolo,SIGNAL(clicked(bool)),this,SLOT(calcoloStipendi()));
    connect(ordineAlfa,SIGNAL(clicked(bool)),this,SLOT(ordineAlfa()));
    connect(cerca,SIGNAL(textChanged(QString)),this,SLOT(search()));
    connect(cerca,SIGNAL(textEdited(QString)),text,SLOT(clearSelection()));
    connect(modifica,SIGNAL(clicked(bool)),this,SLOT(modify()));
    connect(about,SIGNAL(triggered(bool)),this,SLOT(about()));
    connect(rimozione,SIGNAL(clicked(bool)),this,SLOT(removeOptions()));
}

Vista::~Vista(){
    if(model) delete model;
}

void Vista::loadData(){
    model->loadFromFile();
    for(int i = 0; i < model->sizeModel(); ++i)
        text->addItem(QString::fromStdString(model->getItem(i)->getCognome()));

    if(text->count() > 0 && text->item(0)->isSelected() == false){
        text->item(0)->setSelected(true);
        display();
    }
}

void Vista::saveData(){
    try {
        model->saveToFile();
    }
    catch (std::exception) {
        QMessageBox box(QMessageBox::Warning, "Errore di salvataggio", "Impossibile scrivere sul file", QMessageBox::Ok);
        box.exec();
    }
}

void Vista::choose(){
    if(text->count() == 0){
        Aggiungi *add = new Aggiungi(text,info,model,this);
        add->exec();
        text->item(0)->setSelected(true);
        display();
    }
    else{
        Aggiungi *add = new Aggiungi(text,info,model,this);
        add->exec();
    }
}

void Vista::display(){
    if(model->sizeModel() > 0)
        infoLabel->setText( QString::fromStdString(model->getItem(text->currentRow())->info()));
    else
        infoLabel->setText("");
}

void Vista::remove(){
    int index = 0;
    QList<QListWidgetItem*> items = text->selectedItems();

    if(items.size()){
        foreach(QListWidgetItem *item, items)
        {
            index = text->row(item);
            delete text->takeItem(text->row(item));
        }
        delete model->getItem(index);
        model->remove(index);

        if(text->count() > 0 && text->item(0)->isSelected() == false){
            if(index == 0)
                text->item(0)->setSelected(true);
            else
                text->item(index-1)->setSelected(true);
        }
        display();
    }
}

void Vista::calcoloStipendi() {
    QMessageBox *popup = new QMessageBox(this);
    popup->setText("Il calcolo totale degli stipendi per il mese corrente è " + QString::number(model->calcoloStip(),'g',10) + "€");
    popup->exec();
}

void Vista::ordineAlfa(){
    text->sortItems();
    model->ordAlfa();
}

void Vista::search() const{
    std::string c = cerca->text().toStdString();
    std::regex rx("[a-zA-Z]*" + c + "[a-zA-Z]*", std::regex_constants::icase);

    for(int i = 0; i < text->count(); i++){
        std::string x = text->item(i)->text().toStdString();
        if(std::regex_match(x,rx) && cerca->text() != 0){
            text->item(i)->setBackgroundColor("#00FF00");
        }
        else
            text->item(i)->setBackground(Qt::white);
    }

    int index = 0;
    while( index < text->count() && text->item(index)->background() == Qt::white )
        index++;

    if(index <= text->count()){
        text->scrollToItem(text->item(index));
    }
}

void Vista::modify(){
    if(text->selectedItems().size() > 0){
        int i = text->row(text->selectedItems().first());
        if(dynamic_cast<Calciatore*>(model->getItem(i))){
            Modifica_Calciatore *window = new Modifica_Calciatore(text,info,model,i,this);
            window->exec();
        }
        else{
            if(dynamic_cast<Nuotatore*>(model->getItem(i))){
                Modifica_Nuotatore *window = new Modifica_Nuotatore(text,info,model,i,this);
                window->exec();
            }
            else{
                if(dynamic_cast<Pugile*>(model->getItem(i))){
                    Modifica_Pugile *window = new Modifica_Pugile(text,info,model,i,this);
                    window->exec();
                }
                else{
                    if(dynamic_cast<Dirigente*>(model->getItem(i))){
                        Modifica_Dirigente *window = new Modifica_Dirigente(text,info,model,i,this);
                        window->exec();
                    }
                    else{
                        if(dynamic_cast<Allenatore*>(model->getItem(i))){
                            Modifica_Allenatore *window = new Modifica_Allenatore(text,info,model,i,this);
                            window->exec();
                        }
                    }
                }
            }
        }
    }
    display();
}

void Vista::about(){
    QMessageBox *about = new QMessageBox(this);
    about->setText("Progetto di Programmazione ad Oggetti\n"
                   "Corso di Studi: Informatica(UniPd)\n"
                   "Anno Accademico 2018/19\n"
                   "Sviluppato da Matteo Infantino");
    about->exec();
}

void Vista::removeOptions(){
    QDialog *rem = new QDialog(this);
    QHBoxLayout *remLayout1 =new QHBoxLayout();
    QVBoxLayout *remLayout2 = new QVBoxLayout();
    QVBoxLayout *remLayout3 = new QVBoxLayout();
    rem->setLayout(remLayout1);
    remLayout1->addLayout(remLayout2);
    remLayout1->addLayout(remLayout3);
    QPushButton *removeCalc = new QPushButton("Rimuovi tutti i calciatori");
    QPushButton *removeNuot = new QPushButton("Rimuovi tutti i nuotatori");
    QPushButton *removePug = new QPushButton("Rimuovi tutti i pugili");
    QPushButton *removeDir = new QPushButton("Rimuovi tutti i dirigente");
    QPushButton *removeAll = new QPushButton("Rimuovi tutti gli allenatori");
    remLayout2->addWidget(removeCalc);
    remLayout2->addWidget(removeNuot);
    remLayout2->addWidget(removePug);
    remLayout2->addWidget(removeDir);
    remLayout2->addWidget(removeAll);

    remLayout3->setSpacing(0);
    date->setObjectName("edit");
    date->setDisplayFormat("dd.MM.yyyy");
    QPushButton *removeDate = new QPushButton("Rimuovi nati dopo il");
    remLayout3->addWidget(removeDate);
    remLayout3->addWidget(date);

    stip->setObjectName("edit");
    stip->setMaximum(100000000.0);
    QPushButton *removeStip = new QPushButton("Rimuovi chi guadagna più di");
    remLayout3->addWidget(removeStip);
    remLayout3->addWidget(stip);

    scad->setObjectName("edit");
    scad->setDisplayFormat("dd.MM.yyyy");
    QPushButton *removeScad = new QPushButton("Rimuovi atleti con scadenza\n"
                                              "certificato prima del");
    remLayout3->addWidget(removeScad);
    remLayout3->addWidget(scad);

    removeCalc->setObjectName("removeButtons");
    removeNuot->setObjectName("removeButtons");
    removePug->setObjectName("removeButtons");
    removeDir->setObjectName("removeButtons");
    removeAll->setObjectName("removeButtons");
    removeDate->setObjectName("removeButtons");
    removeStip->setObjectName("removeButtons");
    removeScad->setObjectName("removeButtons");

    connect(removeCalc,SIGNAL(clicked(bool)),this,SLOT(removeCalc()));
    connect(removeNuot,SIGNAL(clicked(bool)),this,SLOT(removeNuot()));
    connect(removePug,SIGNAL(clicked(bool)),this,SLOT(removePug()));
    connect(removeDir,SIGNAL(clicked(bool)),this,SLOT(removeDir()));
    connect(removeAll,SIGNAL(clicked(bool)),this,SLOT(removeAll()));
    connect(removeDate,SIGNAL(clicked(bool)),this,SLOT(removeDate()));
    connect(removeStip,SIGNAL(clicked(bool)),this,SLOT(removeStip()));
    connect(removeScad,SIGNAL(clicked(bool)),this,SLOT(removeScad()));

    rem->exec();
}

void Vista::removeCalc(){
    for(int index = 0; index < model->sizeModel(); index++){
        if(dynamic_cast<Calciatore*>(model->getItem(index))){
            delete text->takeItem(index);
            delete model->getItem(index);
            model->remove(index);
            index--;
        }
    }

    if(text->count() > 0 && text->item(0)->isSelected() == false){
        text->item(0)->setSelected(true);
    }
    display();
}

void Vista::removeNuot(){
    for(int index = 0; index < model->sizeModel(); index++){
        if(dynamic_cast<Nuotatore*>(model->getItem(index))){
            delete text->takeItem(index);
            delete model->getItem(index);
            model->remove(index);
            index--;
        }
    }

    if(text->count() > 0 && text->item(0)->isSelected() == false){
        text->item(0)->setSelected(true);
    }
    display();
}

void Vista::removePug(){
    for(int index = 0; index < model->sizeModel(); index++){
        if(dynamic_cast<Pugile*>(model->getItem(index))){
            delete text->takeItem(index);
            delete model->getItem(index);
            model->remove(index);
            index--;
        }
    }

    if(text->count() > 0 && text->item(0)->isSelected() == false){
        text->item(0)->setSelected(true);
    }
    display();
}

void Vista::removeDir(){
    for(int index = 0; index < model->sizeModel(); index++){
        if(dynamic_cast<Dirigente*>(model->getItem(index))){
            delete text->takeItem(index);
            delete model->getItem(index);
            model->remove(index);
            index--;
        }
    }

    if(text->count() > 0 && text->item(0)->isSelected() == false){
        text->item(0)->setSelected(true);
    }
    display();
}

void Vista::removeAll(){
    for(int index = 0; index < model->sizeModel(); index++){
        if(dynamic_cast<Allenatore*>(model->getItem(index))){
            delete text->takeItem(index);
            delete model->getItem(index);
            model->remove(index);
            index--;
        }
    }

    if(text->count() > 0 && text->item(0)->isSelected() == false){
        text->item(0)->setSelected(true);
    }
    display();
}

void Vista::removeDate(){
    for(int index = 0; index < model->sizeModel(); index++){
        if(model->getItem(index)->getDataNascita() > date->date()){
            delete text->takeItem(index);
            delete model->getItem(index);
            model->remove(index);
            index--;
        }
    }

    if(text->count() > 0 && text->item(0)->isSelected() == false){
        text->item(0)->setSelected(true);
    }
    display();
}

void Vista::removeStip(){
    for(int index = 0; index < model->sizeModel(); index++){
        if(model->getItem(index)->stipendio() > stip->value()){
            delete text->takeItem(index);
            delete model->getItem(index);
            model->remove(index);
            index--;
        }
    }

    if(text->count() > 0 && text->item(0)->isSelected() == false){
        text->item(0)->setSelected(true);
    }
    display();
}

void Vista::removeScad(){
    for(int index = 0; index < model->sizeModel(); index++){
        Atleta* q = dynamic_cast<Atleta*>(model->getItem(index));
        if(q && q->getScadenzaCertificato() < scad->date()){
            delete text->takeItem(index);
            delete model->getItem(index);
            model->remove(index);
            index--;
        }
    }

    if(text->count() > 0 && text->item(0)->isSelected() == false){
        text->item(0)->setSelected(true);
    }
    display();
}
