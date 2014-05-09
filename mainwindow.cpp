#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "personwidget.h"

#include <QInputDialog>
#include <QFile>

#include <stdlib.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    load();
}

void MainWindow::addPerson() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                             tr("User name:"), QLineEdit::Normal,
                                             "", &ok);

    PersonWidget *p = new PersonWidget();
    p->setName(text);
    people_vector.push_back(p);
    ui->frame->layout()->addWidget(p);
    store();
    QObject::connect(p, &PersonWidget::changed, this, &MainWindow::store);
}

void MainWindow::removePerson() {
    for (size_t i=0; i<people_vector.size();) {
        if (!people_vector[i]->isChecked()) {
            i++;
            continue;
        } else {
            delete people_vector[i];
            people_vector.erase(people_vector.begin()+i);
        }
    }
    store();
}

void MainWindow::clear_vector() {
    for (size_t i=0; i< people_vector.size();i++) {
        delete people_vector[i];
    }
    people_vector.clear();

}

void MainWindow::load() {
    clear_vector();
#ifdef Q_OS_ANDROID
    QString savedfile = QString(STORAGE_FILE);
#else
    QString savedfile = QString(getenv("HOME")) + QString("/") + QString(STORAGE_FILE);
#endif

    QFile file(savedfile);
    file.open(QIODevice::ReadOnly | QIODevice::Truncate);

    PackedPerson data;
    while (file.read((char*)&data,sizeof(PackedPerson))==sizeof(PackedPerson)) {
        PersonWidget *p = new PersonWidget();

        p->setPacked(data);
        people_vector.push_back(p);
        ui->frame->layout()->addWidget(p);
        QObject::connect(p, &PersonWidget::changed, this, &MainWindow::store);
    }
    file.close();
}

void MainWindow::store() {

#ifdef Q_OS_ANDROID
    QString savedfile = QString(STORAGE_FILE);
#else
    QString savedfile = QString(getenv("HOME")) + QString("/") + QString(STORAGE_FILE);
#endif

    QFile file(savedfile);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);

    for (size_t i=0; i< people_vector.size(); i++) {

        PackedPerson data = people_vector[i]->getPacked();
        char* ptr = (char*)(&data);
        if (file.write(ptr,sizeof(PackedPerson)) != sizeof(PackedPerson)) {
            //TODO Do something about it?
            break;
        }

    }
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

