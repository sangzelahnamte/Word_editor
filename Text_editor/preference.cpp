#include "preference.h"
#include "ui_preference.h"

Preference::Preference(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Preference)
{
    ui->setupUi(this);

}

Preference::~Preference()
{
    delete ui;
}

void Preference::on_buttonBox_accepted()
{
    QString selected_objs;
    QObjectList listobj = this->children(); // list of the dialog widget childrens
    foreach(QObject *obj, listobj)
    {
        if(obj->inherits("QCheckBox"))
        {
            QCheckBox *box = qobject_cast<QCheckBox*>(obj);
            if(box && box->isChecked())
            {
                selected_objs += box->text() + "\r\n";
            }
        }
    }
    QMessageBox::information(this, "Info settings", "You have selected\r\n" + selected_objs);
    accept();
}


void Preference::on_buttonBox_rejected()
{

}
