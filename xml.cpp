#include "xml.h"

#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

XML::XML(QString filepath) : filename(filepath) {}

Qontainer<Tesserato *> XML::read() const{

    Qontainer<Tesserato*> list;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Errore nell'apertura del file" << file.errorString();
        return  list;
    }

    // Lettura da file XML
    QXmlStreamReader reader(&file);
    if(reader.readNextStartElement()) {
        if(reader.name() == "root") {
            while(reader.readNextStartElement()) {
                if(reader.name() == "Tesserato") {
                    const QXmlStreamAttributes attributes = reader.attributes();
                    const QString type = attributes.hasAttribute("type") ? attributes.value("type").toString() : "";

                    if(type == "calciatore"){
                        Tesserato* x = new Calciatore();
                        list.push_back(x);
                        while(reader.readNextStartElement()){
                            if(reader.name() == "nome"){
                                const QString textValue = reader.readElementText();
                                x->setNome(textValue.toStdString());
                            }
                            if(reader.name() == "cognome"){
                                const QString textValue = reader.readElementText();
                                x->setCognome(textValue.toStdString());

                                qDebug() << "Letto " + type + ": " + textValue;
                            }
                            if(reader.name() == "nascita"){
                                int anno = 0, mese = 0, giorno = 0;
                                while(reader.readNextStartElement()){
                                    if(reader.name() == "anno"){
                                        anno = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "mese"){
                                        mese = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "giorno"){
                                        giorno = reader.readElementText().toInt();
                                    }
                                    QDate nasc(anno,mese,giorno);
                                    x->setDataNascita(QDate(nasc));
                                }
                            }
                            if(reader.name() == "stipendio"){
                                double value = reader.readElementText().toDouble();
                                dynamic_cast<Calciatore*>(x)->setStipendioBase(value);
                            }
                            if(reader.name() == "scadenza"){
                                int anno = 0, mese = 0, giorno = 0;
                                while(reader.readNextStartElement()){
                                    if(reader.name() == "anno"){
                                        anno = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "mese"){
                                        mese = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "giorno"){
                                        giorno = reader.readElementText().toInt();
                                    }

                                    QDate scad(anno,mese,giorno);
                                    dynamic_cast<Calciatore*>(x)->setScadenzaCertificato(scad);
                                }
                            }
                            if(reader.name() == "presenze"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Calciatore*>(x)->setPresenze(value);
                            }
                            if(reader.name() == "bonus"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Calciatore*>(x)->setBonus(value);
                            }
                            if(reader.name() == "malus"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Calciatore*>(x)->setMalus(value);
                            }
                            if(reader.name() == "chiave"){
                                const QString& textValue = reader.readElementText();
                                if(textValue == "si")
                                    dynamic_cast<Calciatore*>(x)->setGiocatoreChiave(true);
                                else
                                    dynamic_cast<Calciatore*>(x)->setGiocatoreChiave(false);
                            }
                        }
                    }

                    if(type == "nuotatore"){
                        Tesserato* x = new Nuotatore();
                        list.push_back(x);
                        while(reader.readNextStartElement()){
                            if(reader.name() == "nome"){
                                const QString textValue = reader.readElementText();
                                x->setNome(textValue.toStdString());
                            }
                            if(reader.name() == "cognome"){
                                const QString textValue = reader.readElementText();
                                x->setCognome(textValue.toStdString());

                                qDebug() << "Letto " + type + ": " + textValue;
                            }
                            if(reader.name() == "nascita"){
                                int anno = 0, mese = 0, giorno = 0;
                                while(reader.readNextStartElement()){
                                    if(reader.name() == "anno"){
                                        anno = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "mese"){
                                        mese = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "giorno"){
                                        giorno = reader.readElementText().toInt();
                                    }
                                    QDate nasc(anno,mese,giorno);
                                    x->setDataNascita(QDate(nasc));
                                }
                            }
                            if(reader.name() == "stipendio"){
                                double value = reader.readElementText().toDouble();
                                dynamic_cast<Nuotatore*>(x)->setStipendioBase(value);
                            }
                            if(reader.name() == "scadenza"){
                                int anno = 0, mese = 0, giorno = 0;
                                while(reader.readNextStartElement()){
                                    if(reader.name() == "anno"){
                                        anno = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "mese"){
                                        mese = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "giorno"){
                                        giorno = reader.readElementText().toInt();
                                    }

                                    QDate scad(anno,mese,giorno);
                                    dynamic_cast<Nuotatore*>(x)->setScadenzaCertificato(scad);
                                }
                            }
                            if(reader.name() == "sponsor"){
                                double value = reader.readElementText().toDouble();
                                dynamic_cast<Nuotatore*>(x)->setSponsor(value);
                            }
                            if(reader.name() == "ori"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Nuotatore*>(x)->setOri(value);
                            }
                            if(reader.name() == "argenti"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Nuotatore*>(x)->setArgenti(value);
                            }
                            if(reader.name() == "bronzi"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Nuotatore*>(x)->setBronzi(value);
                            }
                        }
                    }
                    if(type == "pugile"){
                        Tesserato* x = new Pugile();
                        list.push_back(x);
                        while(reader.readNextStartElement()){
                            if(reader.name() == "nome"){
                                const QString textValue = reader.readElementText();
                                x->setNome(textValue.toStdString());
                            }
                            if(reader.name() == "cognome"){
                                const QString textValue = reader.readElementText();
                                x->setCognome(textValue.toStdString());

                                qDebug() << "Letto " + type + ": " + textValue;
                            }
                            if(reader.name() == "nascita"){
                                int anno = 0, mese = 0, giorno = 0;
                                while(reader.readNextStartElement()){
                                    if(reader.name() == "anno"){
                                        anno = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "mese"){
                                        mese = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "giorno"){
                                        giorno = reader.readElementText().toInt();
                                    }
                                    QDate nasc(anno,mese,giorno);
                                    x->setDataNascita(QDate(nasc));
                                }
                            }
                            if(reader.name() == "stipendio"){
                                double value = reader.readElementText().toDouble();
                                dynamic_cast<Pugile*>(x)->setStipendioBase(value);
                            }
                            if(reader.name() == "scadenza"){
                                int anno = 0, mese = 0, giorno = 0;
                                while(reader.readNextStartElement()){
                                    if(reader.name() == "anno"){
                                        anno = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "mese"){
                                        mese = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "giorno"){
                                        giorno = reader.readElementText().toInt();
                                    }

                                    QDate scad(anno,mese,giorno);
                                    dynamic_cast<Pugile*>(x)->setScadenzaCertificato(scad);
                                }
                            }
                            if(reader.name() == "vittorie"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Pugile*>(x)->setVittorie(value);
                            }
                            if(reader.name() == "vittorieKO"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Pugile*>(x)->setVittorieKO(value);
                            }
                            if(reader.name() == "sconfitteKO"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Pugile*>(x)->setSconfitteKO(value);
                            }
                        }
                    }

                    if(type == "dirigente"){
                        Tesserato* x = new Dirigente();
                        list.push_back(x);
                        while(reader.readNextStartElement()){
                            if(reader.name() == "nome"){
                                const QString textValue = reader.readElementText();
                                x->setNome(textValue.toStdString());
                            }
                            if(reader.name() == "cognome"){
                                const QString textValue = reader.readElementText();
                                x->setCognome(textValue.toStdString());

                                qDebug() << "Letto " + type + ": " + textValue;
                            }
                            if(reader.name() == "nascita"){
                                int anno = 0, mese = 0, giorno = 0;
                                while(reader.readNextStartElement()){
                                    if(reader.name() == "anno"){
                                        anno = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "mese"){
                                        mese = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "giorno"){
                                        giorno = reader.readElementText().toInt();
                                    }
                                    QDate nasc(anno,mese,giorno);
                                    x->setDataNascita(QDate(nasc));
                                }
                            }
                            if(reader.name() == "salario"){
                                double value = reader.readElementText().toDouble();
                                dynamic_cast<Dirigente*>(x)->setPagaOraria(value);
                            }
                            if(reader.name() == "ore"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Dirigente*>(x)->setOreMese(value);
                            }
                            if(reader.name() == "commissioni"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Dirigente*>(x)->setCommisioni(value);
                            }
                            if(reader.name() == "master"){
                                const QString& textValue = reader.readElementText();
                                if(textValue == "si")
                                    dynamic_cast<Dirigente*>(x)->setMaster(true);
                                else
                                    dynamic_cast<Dirigente*>(x)->setMaster(false);
                            }
                        }
                    }

                    if(type == "allenatore"){
                        Tesserato* x = new Allenatore();
                        list.push_back(x);
                        while(reader.readNextStartElement()){
                            if(reader.name() == "nome"){
                                const QString textValue = reader.readElementText();
                                x->setNome(textValue.toStdString());
                            }
                            if(reader.name() == "cognome"){
                                const QString textValue = reader.readElementText();
                                x->setCognome(textValue.toStdString());

                                qDebug() << "Letto " + type + ": " + textValue;
                            }
                            if(reader.name() == "nascita"){
                                int anno = 0, mese = 0, giorno = 0;
                                while(reader.readNextStartElement()){
                                    if(reader.name() == "anno"){
                                        anno = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "mese"){
                                        mese = reader.readElementText().toInt();
                                    }
                                    if(reader.name() == "giorno"){
                                        giorno = reader.readElementText().toInt();
                                    }
                                    QDate nasc(anno,mese,giorno);
                                    x->setDataNascita(QDate(nasc));
                                }
                            }
                            if(reader.name() == "salario"){
                                double value = reader.readElementText().toDouble();
                                dynamic_cast<Allenatore*>(x)->setPagaOraria(value);
                            }
                            if(reader.name() == "ore"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Allenatore*>(x)->setOreMese(value);
                            }
                            if(reader.name() == "vittorie"){
                                int value = reader.readElementText().toInt();
                                dynamic_cast<Allenatore*>(x)->setVittorie(value);
                            }
                            if(reader.name() == "obiettivi"){
                                const QString& textValue = reader.readElementText();
                                if(textValue == "si")
                                    dynamic_cast<Allenatore*>(x)->setObiettivi(true);
                                else
                                    dynamic_cast<Allenatore*>(x)->setObiettivi(false);
                            }
                        }
                    }

                }
            }
        }
        else
            reader.skipCurrentElement();
    }
    file.close();
    return list;
}

void XML::write(Qontainer<Tesserato *> &list) const{

    QSaveFile file(filename);
    if(!file.open(QIODevice::WriteOnly)) {
        throw std::exception();
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeComment("File di salvataggio dell'applicazione. Non modificare a mano.");

    writer.writeStartElement("root");

    Qontainer<Tesserato*>::Iterator it = list.begin();

    while(it != list.end()) {
        writer.writeStartElement("Tesserato");

        Tesserato* tess = *it;
        string type;
        if(dynamic_cast<Calciatore*>(tess))
            type = "calciatore";
        if(dynamic_cast<Nuotatore*>(tess))
            type = "nuotatore";
        if(dynamic_cast<Pugile*>(tess))
            type = "pugile";
        if(dynamic_cast<Dirigente*>(tess))
            type = "dirigente";
        if(dynamic_cast<Allenatore*>(tess))
            type = "allenatore";

        writer.writeAttribute("type", QString::fromStdString(type));

        writer.writeStartElement("nome");
        writer.writeCharacters(QString::fromStdString(tess->getNome()));
        writer.writeEndElement();

        writer.writeStartElement("cognome");
        writer.writeCharacters(QString::fromStdString(tess->getCognome()));
        writer.writeEndElement();

        writer.writeStartElement("nascita");
        writer.writeStartElement("anno");
        writer.writeCharacters(QString::number(tess->getDataNascita().year()));
        writer.writeEndElement();
        writer.writeStartElement("mese");
        writer.writeCharacters(QString::number(tess->getDataNascita().month()));
        writer.writeEndElement();
        writer.writeStartElement("giorno");
        writer.writeCharacters(QString::number(tess->getDataNascita().day()));
        writer.writeEndElement();
        writer.writeEndElement();

        if(dynamic_cast<Atleta*>(tess)){
            Atleta* atl = static_cast<Atleta*>(tess);
            writer.writeStartElement("stipendio");
            writer.writeCharacters(QString::number(atl->getStipendioBase()));
            writer.writeEndElement();

            writer.writeStartElement("scadenza");
            writer.writeStartElement("anno");
            writer.writeCharacters(QString::number(atl->getScadenzaCertificato().year()));
            writer.writeEndElement();
            writer.writeStartElement("mese");
            writer.writeCharacters(QString::number(atl->getScadenzaCertificato().month()));
            writer.writeEndElement();
            writer.writeStartElement("giorno");
            writer.writeCharacters(QString::number(atl->getScadenzaCertificato().day()));
            writer.writeEndElement();
            writer.writeEndElement();
        }


        if(dynamic_cast<Calciatore*>(tess)){
            Calciatore* calc = static_cast<Calciatore*>(tess);

            writer.writeStartElement("presenze");
            writer.writeCharacters(QString::number(calc->getPresenze()));
            writer.writeEndElement();

            writer.writeStartElement("bonus");
            writer.writeCharacters(QString::number(calc->getBonus()));
            writer.writeEndElement();

            writer.writeStartElement("malus");
            writer.writeCharacters(QString::number(calc->getMalus()));
            writer.writeEndElement();

            writer.writeStartElement("chiave");
            if(calc->getGiocatoreChiave())
                writer.writeCharacters("si");
            else
                writer.writeCharacters("no");
            writer.writeEndElement();
        }

        if(dynamic_cast<Nuotatore*>(tess)){
            Nuotatore* nuot = static_cast<Nuotatore*>(tess);
            writer.writeStartElement("sponsor");
            writer.writeCharacters(QString::number(nuot->getSponsor()));
            writer.writeEndElement();

            writer.writeStartElement("ori");
            writer.writeCharacters(QString::number(nuot->getOri()));
            writer.writeEndElement();

            writer.writeStartElement("argenti");
            writer.writeCharacters(QString::number(nuot->getArgenti()));
            writer.writeEndElement();

            writer.writeStartElement("bronzi");
            writer.writeCharacters(QString::number(nuot->getArgenti()));
            writer.writeEndElement();
        }

        if(dynamic_cast<Pugile*>(tess)){
            Pugile* pug = static_cast<Pugile*>(tess);

            writer.writeStartElement("vittorie");
            writer.writeCharacters(QString::number(pug->getVittorie()));
            writer.writeEndElement();

            writer.writeStartElement("vittorieKO");
            writer.writeCharacters(QString::number(pug->getVittorieKO()));
            writer.writeEndElement();

            writer.writeStartElement("sconfitteKO");
            writer.writeCharacters(QString::number(pug->getSconfitteKO()));
            writer.writeEndElement();
        }

        if(dynamic_cast<Staff*>(tess)){
            Staff* st = static_cast<Staff*>(tess);
            writer.writeStartElement("salario");
            writer.writeCharacters(QString::number(st->getPagaOraria()));
            writer.writeEndElement();

            writer.writeStartElement("ore");
            writer.writeCharacters(QString::number(st->getOreMese()));
            writer.writeEndElement();
        }

        if(dynamic_cast<Dirigente*>(tess)){
            Dirigente* dir = static_cast<Dirigente*>(tess);
            writer.writeStartElement("commissioni");
            writer.writeCharacters(QString::number(dir->getCommisioni()));
            writer.writeEndElement();

            writer.writeStartElement("master");
            if(dir->getMaster())
                writer.writeCharacters("si");
            else
                writer.writeCharacters("no");
            writer.writeEndElement();
        }

        if(dynamic_cast<Allenatore*>(tess)){
            Allenatore* all = static_cast<Allenatore*>(tess);
            writer.writeStartElement("vittorie");
            writer.writeCharacters(QString::number(all->getVittorie()));
            writer.writeEndElement();

            writer.writeStartElement("obiettivi");
            if(all->getObiettivi())
                writer.writeCharacters("si");
            else
                writer.writeCharacters("no");
            writer.writeEndElement();
        }

        writer.writeEndElement();

        if (writer.hasError())
            throw std::exception();

        it++;
    }

    writer.writeEndElement();
    writer.writeEndDocument();

    file.commit();
}

