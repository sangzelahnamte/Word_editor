#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QDialog>
#include <QObjectList>
#include <QMessageBox>
#include <QDebug>
#include <QString>

namespace Ui {
class Preference;
}

class Preference : public QDialog
{
    Q_OBJECT

public:
    explicit Preference(QWidget *parent = nullptr);
    ~Preference();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::Preference *ui;
};

#endif // PREFERENCE_H
