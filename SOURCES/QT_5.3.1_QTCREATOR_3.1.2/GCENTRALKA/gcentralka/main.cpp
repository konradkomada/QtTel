//Autor Konrad Komada
//Oprogramowanie do losowania i zapisu wylosowanej kwoty w plikach dla centralek lokalnych

#include "mainwindow.h"
#include <QApplication>


//Główna funkcja programu

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
