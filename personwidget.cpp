#include "personwidget.h"
#include "ui_personwidget.h"

#include <string.h>
#include <QInputDialog>

PersonWidget::PersonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonWidget)
{
    ui->setupUi(this);
    ui->frame->setVisible(false);
}


void PersonWidget::setPacked(PackedPerson p) {
    QString name = QString::fromLocal8Bit(p.name);
    QString currency = QString::fromLocal8Bit(p.currency);
    ui->btnName->setText(name);
    ui->spnValue->setValue(p.value);
    ui->btnCurrency->setText(currency);
}

void PersonWidget::set_currency() {
    bool ok;
    QString currency = QInputDialog::getText(this, tr("Insert new currency"),tr("Currency"), QLineEdit::Normal, "", &ok);
    if (!ok) return;

    ui->btnCurrency->setText(currency);
    emit changed();
}



void PersonWidget::changeValue(bool increase) {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Insert Δ"),
                                             tr("Value"), QLineEdit::Normal,
                                             "", &ok);
    if (!ok) return;
    double mod = text.toDouble();

    if (! increase) {
        mod *= -1;
    }

    ui->spnValue->setValue( ui->spnValue->value() + mod);
}

void PersonWidget::increase() {
   this->changeValue(true);
}

void PersonWidget::decrease() {
    this->changeValue(false);
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
    r.value = ui->spnValue->value();

    QByteArray name = ui->btnName->text().toLocal8Bit();
    QByteArray currency = ui->btnCurrency->text().toLocal8Bit();

    memset(r.name, 0,sizeof(r.name));
    strncpy(r.name,name.data(),sizeof(r.name)-1);
    memset(r.currency,0, sizeof(r.currency));
    strncpy(r.currency,currency.data(),sizeof(r.currency));

    return r;
}
