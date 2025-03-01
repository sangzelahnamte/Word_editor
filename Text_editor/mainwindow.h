#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void new_file();
    void open_file();
    void save_file();
    void save_as();
    void select_none();
    void toolbar_top();
    void toolbar_left();
    void toolbar_right();
    void toolbar_bottom();
    void toolbar_moveable(); // move able toolbar
    void toolbar_floatable(); // floatable

private:
    Ui::MainWindow *ui;
    QString m_file_name;
    bool m_save;
};
#endif // MAINWINDOW_H
