#include <QtWidgets/QApplication>
#include <QDebug>
#include "source/mainWin/include/mainWindow.h"
#include "source/pyLibs/include/catchpystd.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    
    MainWindow w;
    w.show();
    

    qDebug() << "This hello qt5";

    return a.exec();

}