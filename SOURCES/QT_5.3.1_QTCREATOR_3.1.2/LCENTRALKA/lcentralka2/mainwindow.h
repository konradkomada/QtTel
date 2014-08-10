#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemWatcher>

extern QString centralka;
extern QString telefon1;
extern QString telefon2;
extern QString telefon3;
extern QString Semafor;
extern QString Wygrany;
extern QString Telefon;
extern QString wsk_telefon1;
extern QString wsk_telefon2;
extern QString wsk_telefon3;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void fileChangedSlot(QString Filename); //monitoring pliku centralki
    //void fileChangedSlot_tel(QString Filename); //monitoring pliku telefonu

private:
    Ui::MainWindow *ui;
    void Monitoruj_plik(QString Filename);
    //void Monitoruj_plik_tel(QString Filename);
    void Write_file(QString Filename, double WData);
    void Write_semafor(QString Telefon);
    void Write_wygrany(QString Wygrany, QString Telefon);
    void Clear_file(QString Filename);
    QString Read_file(QString Filename);
    QString Read_file_tel(QString Filename);
    void Read_clear_file(QString Filename);
    QString Data;
    //QString centralka,telefon1,telefon2,telefon3;
    //QString Semafor,Wygrany,Telefon;
    double dData,centralka_amount,telefon_amount;
    QFileSystemWatcher* fw;
    char centralka_amount_char,telefon_amount_char;


};

#endif // MAINWINDOW_H
