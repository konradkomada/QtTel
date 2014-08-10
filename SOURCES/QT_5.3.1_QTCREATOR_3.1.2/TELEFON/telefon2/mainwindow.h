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

extern QString telefon;
extern QString wsk_telefon;
extern QString Wygrany;

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
    void fileChangedSlot(QString Filename);

    //void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    void Write_file(QString Filename, double WData);
    QString Read_file(QString Filename);
    void Monitoruj_plik(QString Filename);
    void Ustaw_pole(QString Filename);
    void Losuj_i_zapisz();
    int High;
    int Low;
    int High2;
    int Low2;
    bool ok;
    double random_amount;
    char readed_amount_char;
    double readed_amount;
    QFileSystemWatcher* fw;
    QString dData;
};

#endif // MAINWINDOW_H
