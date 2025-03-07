#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QStatusBar>
#include <QDebug>
#include <QLabel>

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
    void toolbar_moveable(bool arg); // move able toolbar
    void toolbar_floatable(bool arg); // floatable

    void on_text_area_textChanged();

    void set_bold();
    void set_italic();
    void set_underline();
    void set_strikeout();

    void set_zoom_out();
    void set_zoom_in();

private:
    Ui::MainWindow *ui;
    QString m_file_name;
    bool m_save;
    void setup_statusbar();
    void update_status(QString message);
};
#endif // MAINWINDOW_H
