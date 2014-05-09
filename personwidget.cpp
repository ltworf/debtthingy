#include "personwidget.h"
#include "ui_personwidget.h"

#include <string.h>

PersonWidget::PersonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonWidget)
{
    ui->setupUi(this);
    ui->frame->setVisible(false);
}

void PersonWidget::setPacked(PackedPerson p) {
    QString name = QString::fromLocal8Bit(p.name);
    ui->btnName->setText(name);

    ui->chkCredit->setChecked(p.credit);
    ui->spnValue->setValue(p.value);
}

PersonWidget::~PersonWidget()
{
    delete ui;
}

void PersonWidget::button_toggle(bool value) {
    ui->frame->setVisible(value);
}

void PersonWidget::setName(QString name) {
    ui->btnName->setText(name);
}

bool PersonWidget::isChecked() {
    return ui->btnName->isChecked();
}

void PersonWidget::value_changed() {
    emit changed();
}

PackedPerson PersonWidget::getPacked() {
    PackedPerson r;

    r.credit = ui->chkCredit->isChecked();
    r.value = ui->spnValue->value();

    QByteArray name = ui->btnName->text().toLocal8Bit();

    memset(r.name, 0,sizeof(r.name));
    strncpy(r.name,name.data(),sizeof(r.name)-1);

    return r;

}
