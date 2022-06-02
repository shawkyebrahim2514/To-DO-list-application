#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QFile stylefile(":/essential files/stylesheet.qss");
    stylefile.open(QFile::ReadOnly);
    QString style = stylefile.readAll();
    stylefile.close();

    QApplication a(argc, argv);
    a.setStyleSheet(style);
    MainWindow w;
    w.show();
    return a.exec();
}
