#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->text_area);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::new_file); // new file
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open_file); // open file
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save_file); // save file
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::save_as); // save as
    connect(ui->actionSelect_All, &QAction::triggered, ui->text_area, &QTextEdit::selectAll); // select all
    connect(ui->actionSelect_none, &QAction::triggered, this, &MainWindow::select_none);
    connect(ui->actionCut, &QAction::triggered, ui->text_area, &QTextEdit::cut);
    connect(ui->actionCopy, &QAction::triggered, ui->text_area, &QTextEdit::copy);
    connect(ui->actionPaste, &QAction::triggered, ui->text_area, &QTextEdit::paste);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);

    new_file();
    m_save = true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::new_file()
{
    ui->text_area->clear();
    m_file_name.clear();
    m_save = false;
    ui->statusbar->showMessage("New file");
}

void MainWindow::open_file() // OPEN
{
    QString file_path = QFileDialog::getOpenFileName(this, "Open file", QString(),
                                                     "Text files(*txt);;All files(*,*)");
    if(file_path.isEmpty()) return; // engmah a select loh chuan
    m_file_name = file_path; // setting file name to member variable
    QFile file(m_file_name);
    if(file.open(QIODevice::ReadOnly)) // a hawn theih chuan file thar hawng rawhse
    {
        QTextStream text_stream(&file);
        while (!text_stream.atEnd())
        {
            ui->text_area->setText(text_stream.readLine());
        }
        file.close();
        m_save = true;
        ui->statusbar->showMessage(m_file_name);
    }
    else // a hawn theih loh chuan file thar a hawng ang
    {
        new_file();
        QMessageBox::critical(this, "ERROR!!!", file.errorString());
        return;
    }
}

void MainWindow::save_file() // SAVE
{
    if(m_file_name.isEmpty())
    {
        save_as();
        return;
    }
    QFile file(m_file_name);
    if(file.open(QIODevice::WriteOnly)) // a hawn theih chuan file a save theih
    {
        QTextStream text_stream(&file);
        text_stream << ui->text_area->toPlainText();
        file.close();
        m_save = true;
        ui->statusbar->showMessage(m_file_name);
    }
    else // a hawn theih loh chuan file error message
    {
        QMessageBox::critical(this, "ERROR!!!", file.errorString());
        return;
    }
}

void MainWindow::save_as()
{
    QString file_path = QFileDialog::getSaveFileName(this, "Save file", QString(), "Text files(*txt);;All files(*,*)");
    if(file_path.isEmpty()) return;
    m_file_name = file_path;
    save_file();
}

void MainWindow::select_none()
{
    QTextCursor cursor = ui->text_area->textCursor(); // initializing text cursor
    cursor.setPosition(0, QTextCursor::MoveMode::KeepAnchor); // move anchor at the beginning
    ui->text_area->setTextCursor(cursor);// setting the text cursor to text area
}
