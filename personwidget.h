#ifndef PERSONWIDGET_H
#define PERSONWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class PersonWidget;
struct PackedPerson;
}

struct PackedPerson {
    bool credit;
    char name[100];
    double value;
};

class PersonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PersonWidget(QWidget *parent = 0);
    PackedPerson getPacked();
    void setPacked(PackedPerson);
    void setName(QString);
    ~PersonWidget();
    bool isChecked();

private slots:
    void button_toggle(bool);
    void value_changed();
    void increase();
    void decrease();

signals:
    void changed();


private:
    Ui::PersonWidget *ui;
    void changeValue(bool);
};

#endif // PERSONWIDGET_H
