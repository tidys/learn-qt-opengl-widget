#include "mainwindow.h"

#include <QApplication>
#include <qsurfaceformat.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat fmt;
    fmt.setVersion(2, 1);
    //    fmt.setProfile(QSurfaceFormat::CompatibilityProfile);
    QSurfaceFormat::setDefaultFormat(fmt);

    MainWindow w;
    w.show();
    return a.exec();
}
