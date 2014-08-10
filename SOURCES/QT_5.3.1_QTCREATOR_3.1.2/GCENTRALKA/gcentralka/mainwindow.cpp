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

QString Centralka1 = "centralka1.txt";
QString Centralka2 = "centralka2.txt";
QString Wygrany = "centralka_wygrany.txt";
QString wsk_telefon1 = "wsk_telefon1.txt";
QString wsk_telefon2 = "wsk_telefon2.txt";
QString wsk_telefon3 = "wsk_telefon3.txt";
QString wsk_telefon4 = "wsk_telefon4.txt";
QString wsk_telefon5 = "wsk_telefon5.txt";
QString wsk_telefon6 = "wsk_telefon6.txt";


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
            //Read_clear_file(Filename); // some data inside
            //QMessageBox::information(this,"test","Zmiana pliku2: "+Filename);
            ui->lineEdit_2->setText(Read_file(Wygrany));
            ui->pushButton->hide();
            ui->pushButton_3->show();
        }
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

double MainWindow::Losuj(){
    qsrand(qrand());
    //losowanie liczby kwoty i podstawienie jej do zmiennej "test"
    qsrand(QTime::currentTime().msec());
    random_amount = QString((QString::number(qrand() % ((High+1)-Low)+Low))+"."+(QString::number(qrand() % ((High2+1)-Low2)+Low2))).toDouble(&ok);
    //wyświetlenie liczby w polu tekstowym w okienku
    ui->lineEdit->setText(QString::number(random_amount,'f', 2));
    Write_file(Centralka1,random_amount);
    Write_file(Centralka2,random_amount);
    return random_amount;
}

//Metoda określająca zadania po kliknięciu butonu losowania (oraz samo losowanie i zapis do pliku)
void MainWindow::on_pushButton_clicked()
{

    random_amount=Losuj();

}

//metoda dla drugi zapasowy buton do wysyłania danych - co się stanie po kliknięciu (butod domyślnie niewidoczny)
void MainWindow::on_pushButton_2_clicked()
{
    QString readed_amount_char=ui->lineEdit->text();
    readed_amount=readed_amount_char.toDouble();
    //QMessageBox::information(this,"Debug2",ui->lineEdit->text());
    Write_file(Centralka1,readed_amount);
    Write_file(Centralka2,readed_amount);
}

//metoda dla edycji pola tekstowego
void MainWindow::on_lineEdit_returnPressed()
{
    QString readed_amount_char=ui->lineEdit->text();
    readed_amount=readed_amount_char.toDouble();
    //QMessageBox::information(this,"Debug4",ui->lineEdit->text());
    Write_file(Centralka1,readed_amount);
    Write_file(Centralka2,readed_amount);
}

//metoda dla zakończenia edycji pola tekstowego (gdyby wcześniejsza nie zadziałała - takie zabezpieczenie)
void MainWindow::on_lineEdit_editingFinished()
{
    QString readed_amount_char=ui->lineEdit->text();
    readed_amount=readed_amount_char.toDouble();
    //QMessageBox::information(this,"Debug3",ui->lineEdit->text());
    Write_file(Centralka1,readed_amount);
    Write_file(Centralka2,readed_amount);
}

//konstruktor głównego okna główna metoda ustawiająca zmienne
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #00ff00;");
    ui->lineEdit->setStyleSheet("background-color: #ffffff;");
    ui->lineEdit_2->setStyleSheet("background-color: #ffffff;");
    ui->pushButton->setStyleSheet("background-color: #eeeeee;");
    ui->pushButton_2->setStyleSheet("background-color: #eeeeee;");
    ui->pushButton_3->setStyleSheet("background-color: #eeeeee;");
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    High =  99999;
    Low =  0;
    High2 = 99;
    Low2 = 0;

    Monitoruj_plik(Wygrany);
}

//Destruktor
MainWindow::~MainWindow()
{
    delete ui;
}

//Metoda dla przycisku resetu
void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit_2->setText("");
    Clear_file(Wygrany);
    Losuj();
    ui->pushButton->show();
    ui->pushButton_3->hide();
    Clear_file(wsk_telefon1);
    Clear_file(wsk_telefon2);
    Clear_file(wsk_telefon3);
    Clear_file(wsk_telefon4);
    Clear_file(wsk_telefon5);
    Clear_file(wsk_telefon6);
}
