#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <string>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <QFileSystemWatcher>

extern QString Centralka1;
extern QString Centralka2;
extern QString Wygrany;
extern QString wsk_telefon1;
extern QString wsk_telefon2;
extern QString wsk_telefon3;
extern QString wsk_telefon4;
extern QString wsk_telefon5;
extern QString wsk_telefon6;

namespace Ui {
class MainWindow;
}

//Deklaracja nagłówkowa klasy głównego okna (prototypy)
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_lineEdit_editingFinished();
    void on_lineEdit_returnPressed();
    void fileChangedSlot(QString Filename); //monitoring pliku centralki

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    void Write_file(QString Filename, double WData);
    QString Read_file(QString Filename);
    void Monitoruj_plik(QString Filename);
    void Clear_file(QString Filename);
    QFileSystemWatcher* fw;
    double Losuj();
    int High;
    int Low;
    int High2;
    int Low2;
    bool ok;
    double random_amount;
    char readed_amount_char;
    double readed_amount;
};


#endif // MAINWINDOW_H
