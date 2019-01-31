#include "vista.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file("../ProjectP2/style.css");
    file.open(QFile::ReadOnly);
    QString style = QLatin1String(file.readAll());
    a.setStyleSheet(style);
    file.close();

    Vista w;
    w.setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    w.show();

    return a.exec();
}
