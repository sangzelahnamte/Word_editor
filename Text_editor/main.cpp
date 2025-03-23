#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile stylesheetfile(":/theme/Combinear.qss");
    stylesheetfile.open(QIODevice::ReadOnly);
    QString styles = qUtf8Printable(stylesheetfile.readAll()); // or to latin 1 string
    a.setStyleSheet(styles);
    MainWindow w;
    w.show();
    return a.exec();
}
