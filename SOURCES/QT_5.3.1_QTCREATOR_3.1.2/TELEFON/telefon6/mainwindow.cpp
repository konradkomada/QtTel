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

QString wsk_telefon = "wsk_telefon6.txt";
QString telefon = "telefon6.txt";
QString centralka = "centralka2.txt";
QString Wygrany = "centralka_wygrany.txt";


//Metoda monitorująca zmiany w plikach
void MainWindow::Monitoruj_plik(QString Filename) // <- constructor
{
fw = new QFileSystemWatcher(this);
connect( fw, SIGNAL(fileChanged(QString)), this, SLOT( fileChangedSlot(QString)) ); // <- never emit
//connect( fw, SIGNAL(directoryChanged(QString)), this, SLOT( fileChangedSlot(QString)) ); //emit but files() is empty, directories() is ok
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
            //QMessageBox::information(this,"test","Zmiana pliku2: "+Filename);
        }
        Ustaw_pole(wsk_telefon);
        if (Read_file(Wygrany) == "telefon1.txt" ||  Read_file(Wygrany) == "telefon2.txt" || Read_file(Wygrany) == "telefon3.txt" || Read_file(Wygrany) == "telefon4.txt" ||  Read_file(Wygrany) == "telefon5.txt" || Read_file(Wygrany) == "telefon6.txt") {
        ui->pushButton_2->hide();
        ui->lineEdit->setText("wygrał: "+Read_file(Wygrany));
        }
}




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
    //return dData;
    mFile.close();
}

void MainWindow::Ustaw_pole(QString Filename)
{

    dData=Read_file(Filename);

if (dData == "1.00") {
    ui->lineEdit_2->setText("Za mało");
    ui->pushButton_2->show();
} else if (dData == "2.00") {
    ui->lineEdit_2->setText("Za dużo");
    ui->pushButton_2->show();
} else if  (dData == "3.00") {
    ui->lineEdit_2->setText("Zgadłeś");
    ui->pushButton_2->hide();
} else if (dData == "0.00") {
    ui->lineEdit_2->setText("");
    ui->pushButton_2->show();
} else {
    ui->lineEdit_2->setText("");
    ui->pushButton_2->show();
}
}


//Metoda zapisująca do pliku
void MainWindow::Write_file(QString Filename, double WData)
{
    QFile mFile(Filename);
//    mFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!mFile.open(QFile::WriteOnly | QFile::Text))             //# Sprawdzenie czy czy można zapisywać do pliku
    {
        QMessageBox::information(this,"Debug: write file","Nie mogę otworzyć pliku: "+Filename+" do zapisu");
        return;
    }
    QTextStream out(&mFile);
    out <<  QString::number(WData,'f', 2);
    mFile.flush();
    mFile.close();
}

void MainWindow::on_pushButton_clicked()
{
    QString readed_amount_char=ui->lineEdit->text();
    readed_amount=readed_amount_char.toDouble();
    //QMessageBox::information(this,"Debug2",ui->lineEdit->text());
    Write_file(centralka,readed_amount);
    //Read_file(wsk_telefon);
    Ustaw_pole(wsk_telefon);
}

//Metoda określająca zadania po kliknięciu butonu losowania (oraz samo losowanie i zapis do pliku)
void MainWindow::on_pushButton_2_clicked()
{
     Losuj_i_zapisz();
}

void MainWindow::Losuj_i_zapisz()
{
    qsrand(qrand());
    //losowanie liczby kwoty i podstawienie jej do zmiennej "test"
    qsrand(QTime::currentTime().msec());
    random_amount = QString((QString::number(qrand() % ((High+1)-Low)+Low))+"."+(QString::number(qrand() % ((High2+1)-Low2)+Low2))).toDouble(&ok);
    ui->lineEdit->setText(QString::number(random_amount,'f', 2));
    Write_file(telefon,random_amount);
}

//metoda dla edycji pola tekstowego
void MainWindow::on_lineEdit_returnPressed()
{
    QString readed_amount_char=ui->lineEdit->text();
    readed_amount=readed_amount_char.toDouble();
    //QMessageBox::information(this,"Debug4",ui->lineEdit->text());
    Write_file(telefon,readed_amount);
}

//metoda dla zakończenia edycji pola tekstowego (gdyby wcześniejsza nie zadziałała - takie zabezpieczenie)
void MainWindow::on_lineEdit_editingFinished()
{
    QString readed_amount_char=ui->lineEdit->text();
    readed_amount=readed_amount_char.toDouble();
    //QMessageBox::information(this,"Debug3",ui->lineEdit->text());
    Write_file(telefon,readed_amount);
}

//konstruktor głównego okna główna metoda ustawiająca zmienne
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #00ffff;");
    ui->lineEdit->setStyleSheet("background-color: #ffffff;");
    ui->lineEdit_2->setStyleSheet("background-color: #ffffff;");
    ui->pushButton->setStyleSheet("background-color: #eeeeee;");
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setStyleSheet("background-color: #eeeeee;");
    ui->pushButton_3->setStyleSheet("background-color: #eeeeee;");
    ui->pushButton_3->setVisible(false);
    High =  99999;
    Low =  0;
    High2 = 99;
    Low2 = 0;
    Losuj_i_zapisz();
    Monitoruj_plik(wsk_telefon);
    Monitoruj_plik(Wygrany);
    Monitoruj_plik(centralka);
}

MainWindow::~MainWindow()
{
    delete ui;
}



//void MainWindow::on_pushButton_3_clicked()
//{
//    ui->pushButton_3->hide();
//    ui->pushButton_2->show();
//    ui->lineEdit->setText("");
//}
