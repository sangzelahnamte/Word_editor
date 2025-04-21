#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile stylesheetfile(":/theme/Combinear.qss");
    stylesheetfile.open(QIODevice::ReadOnly);
    QString styles = qUtf8Printable(stylesheetfile.readAll()); // or to latin 1 string
    a.setStyleSheet(styles);
    // added splash screen
    QPixmap image(":/image/image/qt_splashscreen.png");
    QSplashScreen splash(image);
    splash.show();
    QTimer::singleShot(3000, &splash, &QSplashScreen::close);
    MainWindow w;
    //w.show();
    QTimer::singleShot(2000, [&w]() {
        w.show();
    });
    return a.exec();
}
