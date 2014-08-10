#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QtCore>
#include <QtGui>
#include <QString>
#include <QMessageBox>
#include <QGlobal.h>
#include <QTime>
#include <QFileSystemWatcher>

QString centralka = "centralka2.txt";
QString telefon1 = "telefon4.txt";
QString telefon2 = "telefon5.txt";
QString telefon3 = "telefon6.txt";
QString Semafor = "centralka2_semafor.txt";
QString Wygrany = "centralka_wygrany.txt";
QString Telefon;
QString wsk_telefon1 = "wsk_telefon4.txt";
QString wsk_telefon2 = "wsk_telefon5.txt";
QString wsk_telefon3 = "wsk_telefon6.txt";

//Metoda monitorująca zmiany w plikach
void MainWindow::Monitoruj_plik(QString Filename) // <- constructor
{
fw = new QFileSystemWatcher(this);
connect( fw, SIGNAL(fileChanged(QString)), this, SLOT( fileChangedSlot(QString)) ); // <- never emit
// connect( fw, SIGNAL(directoryChanged(QString)), this, SLOT( fileChangedSlot(QString)) ); //emit but files() is empty, directories() is ok
fw->addPath(Filename);
//qDebug() << fw->files() << fw->directories(); // outputs: () ("plik") in test ther are file
//QMessageBox::information(this,"test","Zmiana pliku: "+Filename);
}

//SLOT podejmujący akcję na zmianę w pliku, jeśli nastąpiłą zmiana pliku ale plik nie jest pusty to odpala metode  Read_clear_file
void MainWindow::fileChangedSlot(QString Filename)
{
//#ifdef QT_DEBUG
//qDebug() << "files watched: " << fw->files() << fw->directories();
//#endif
//QMessageBox::information(this,"test","Zmiana pliku2: "+Filename);
    QFile mFile(Filename);
    mFile.open( QIODevice::WriteOnly|QIODevice::Append);
        if (mFile.pos() != 0) {
            Read_clear_file(Filename); // some data inside
            //QMessageBox::information(this,"test","Zmiana pliku2: "+Filename);
        }
}

//Metoda zapisująca do pliku
void MainWindow::Write_file(QString Filename, double WData)
{
    QFile mFile(Filename);
//    mFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!mFile.open(QFile::WriteOnly | QFile::Text))             //# Sprawdzenie czy czy można zapisywać do pliku
    {
        QMessageBox::information(this,"Debug: write file","1Nie mogę otworzyć pliku: "+Filename+" do zapisu");
        return;
    }
    QTextStream out(&mFile);
    out <<  QString::number(WData,'f', 2);
    mFile.flush();
    mFile.close();
}

//Metoda zapisująca do pliku semafora
void MainWindow::Write_semafor(QString Telefon)
{
    QFile mFile(Semafor);
//    mFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!mFile.open(QFile::WriteOnly | QFile::Text))             //# Sprawdzenie czy czy można zapisywać do pliku
    {
        QMessageBox::information(this,"Debug: write file","2Nie mogę otworzyć pliku semafora: "+Semafor+" do zapisu");
        return;
    }
    QTextStream out(&mFile);
    out <<  Telefon;
    mFile.flush();
    mFile.close();
}

//Metoda zapisująca do pliku zwyciezcy lokalnego
void MainWindow::Write_wygrany(QString Wygrany, QString Telefon)
{
    QFile mFile(Wygrany);
//    mFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!mFile.open(QFile::WriteOnly | QFile::Text))             //# Sprawdzenie czy czy można zapisywać do pliku
    {
        QMessageBox::information(this,"Debug: write file","3Nie mogę otworzyć pliku wygranego: "+Wygrany+" do zapisu");
        return;
    }
    QTextStream out(&mFile);
    out <<  Telefon;
    mFile.flush();
    mFile.close();
}

//Metoda czyszcząca plik
void MainWindow::Clear_file(QString Filename)
{
    QFile mFile(Filename);
//    mFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!mFile.open(QFile::WriteOnly | QFile::Text))             //# Sprawdzenie czy czy można zapisywać do pliku
    {
        QMessageBox::information(this,"Debug: write file","4Nie mogę otworzyć pliku: "+Filename+" do zapisu");
        return;
    }
    QTextStream out(&mFile);
    out <<  QString ("");
    mFile.flush();
    mFile.close();
}

//Metoda odczytująca z pliku centralki
QString MainWindow::Read_file(QString Filename)
{
    QFile mFile(Filename);
//    mFile.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!mFile.open(QFile::ReadOnly | QFile::Text))             //# Sprawdzenie czy czy można zapisywać do pliku
    {
        QMessageBox::information(this,"Debug: open file","5Nie mogę otworzyć pliku: "+Filename+" do odczytu");
        //return;
    }
    QTextStream in(&mFile);
    QString mText = in.readAll();
    //dData = mText.toDouble();
    //ui->lineEdit->setText(QString::number(RData,'f', 2));
    return mText;
    mFile.close();
}

//Metoda odczytująca z plików telefonów
QString MainWindow::Read_file_tel(QString Filename)
{
    QFile mFile(Filename);
//    mFile.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!mFile.open(QFile::ReadOnly | QFile::Text))             //# Sprawdzenie czy czy można zapisywać do pliku
    {
        QMessageBox::information(this,"Debug: open file","6Nie mogę otworzyć pliku: "+Filename+" do odczytu");
        //return;
    }
    QTextStream in(&mFile);
    QString mText = in.readAll();
    //dData = mText.toDouble();
    //ui->lineEdit_3->setText(QString::number(RData,'f', 2));
    return mText;
    mFile.close();
}

//Metoda wykonująca operacje porównywania czytania i czyszczenia pliku dla potrzeb ciągłego monitorowania zmian w plikach i reagowania
void MainWindow::Read_clear_file(QString Filename)
{
    if (Filename=="centralka1.txt" || Filename=="centralka2.txt") {
    Data = MainWindow::Read_file(Filename);
    dData = Data.toDouble();
    //QMessageBox::information(this,"test","Test: "+Data);
    //ui->lineEdit->setText(QString::number(dData,'f', 2));
    //ui->lineEdit_2->setText(Filename);
    ui->lineEdit->setText(Data);
    //MainWindow::Write_file(filename,0);
    MainWindow::Clear_file(Filename);
    } else {
    Write_semafor(Filename);
    Telefon=Filename;
    Data = MainWindow::Read_file(Filename);
    dData = Data.toDouble();
    //QMessageBox::information(this,"test","Test: "+Data);
    //ui->lineEdit->setText(QString::number(dData,'f', 2));
    ui->lineEdit_2->setText(Filename);
    ui->lineEdit_3->setText(Data);
    //MainWindow::Write_file(filename,0);
    //MainWindow::Clear_file(Filename);
    }

    QString centralka_amount_char=ui->lineEdit->text();
    centralka_amount=centralka_amount_char.toDouble();
    QString telefon_amount_char=ui->lineEdit_3->text();
    telefon_amount=telefon_amount_char.toDouble();

    //if (Filename=="telefon1.txt") { QString telefon_wsk="telefon1_wsk.txt"; }
    //if (Filename=="telefon2.txt") { QString telefon_wsk="telefon2_wsk.txt"; }
    //if (Filename=="telefon3.txt") { QString telefon_wsk="telefon3_wsk.txt"; }

    if (centralka_amount > telefon_amount){
        //QMessageBox::information(this,"test","Test: >");
        Write_file("wsk_"+Filename,1);
        Clear_file(Semafor);
    }
    if (centralka_amount < telefon_amount){
        //QMessageBox::information(this,"test","Test: <");
        Write_file("wsk_"+Filename,2);
        Clear_file(Semafor);
    }
    if (centralka_amount == telefon_amount){
        //QMessageBox::information(this,"test","Test: =");
        Write_file("wsk_"+Filename,3);
        Write_wygrany(Wygrany, Telefon);
    }

}

//konstruktor głównego okna główna metoda ustawiająca zmienne
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #ff0000;");
    ui->lineEdit->setStyleSheet("background-color: #ffffff;");
    ui->lineEdit_2->setStyleSheet("background-color: #ffffff;");
    ui->lineEdit_3->setStyleSheet("background-color: #ffffff;");
    //QString centralka = "centralka1.txt";
    //QString telefon1 = "telefon1.txt";
    //QString telefon2 = "telefon2.txt";
    //QString telefon3 = "telefon3.txt";
    //QString Semafor = "centralka1_semafor.txt";
    //QString Wygrany = "centralka1_wygrany.txt";
    Read_clear_file(centralka);
    Monitoruj_plik(centralka);
    Read_file(telefon1);
    Monitoruj_plik(telefon1);
    Read_file(telefon2);
    Monitoruj_plik(telefon2);
    Read_file(telefon3);
    Monitoruj_plik(telefon3);
}

//destruktor głównego okna
MainWindow::~MainWindow()
{
    delete ui;
}
