#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "personwidget.h"

#include <QInputDialog>
#include <QFile>
#include <QScroller>
#include <QGraphicsBlurEffect>

#include <stdlib.h>

union conv {
    PackedPerson person;
    char data[sizeof(PackedPerson)];
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    eff = new QGraphicsBlurEffect();

    this->setGraphicsEffect(eff);
    eff->setBlurRadius(0);

    QScroller::grabGesture(ui->scrollArea, QScroller::LeftMouseButtonGesture);

    load();
}

#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

void MainWindow::addPerson() {



    bool ok;
    QString text = QInputDialog::getText(this, tr("Insert new person"),
                                             tr("User name:"), QLineEdit::Normal,
                                             "", &ok);
    if (!ok) {
        return;
    }

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

    union conv record;
    while (file.read(record.data,sizeof(PackedPerson))==sizeof(PackedPerson)) {
        PersonWidget *p = new PersonWidget();

        p->setPacked(record.person);
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
        union conv record;
        record.person = people_vector[i]->getPacked();
        if (file.write(record.data,sizeof(PackedPerson)) != sizeof(PackedPerson)) {
            //TODO Do something about it?
            break;
        }

    }
    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete eff;
}

