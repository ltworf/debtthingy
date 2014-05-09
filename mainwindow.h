#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <vector>

#include "personwidget.h"

#ifdef Q_OS_ANDROID
    #define STORAGE_FILE "/sdcard/.lolwut.data.txt"
#else
    #define STORAGE_FILE ".lolwut.data.txt"
#endif



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
    void addPerson();
    void removePerson();
    void load();
    void store();

private:
    Ui::MainWindow *ui;
    std::vector<PersonWidget*> people_vector;

    void clear_vector();
};

#endif // MAINWINDOW_H
