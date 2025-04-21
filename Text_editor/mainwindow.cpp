#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "preference.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->text_area);
    // SIGNALS and SLOTS here!!!
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::new_file); // new file
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open_file); // open file
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save_file); // save file
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::save_as); // save as
    // CUT COPY PASTE.....
    connect(ui->actionSelect_All, &QAction::triggered, ui->text_area, &QTextEdit::selectAll); // select all
    connect(ui->actionSelect_none, &QAction::triggered, this, &MainWindow::select_none);
    connect(ui->actionCut, &QAction::triggered, ui->text_area, &QTextEdit::cut);
    connect(ui->actionCopy, &QAction::triggered, ui->text_area, &QTextEdit::copy);
    connect(ui->actionPaste, &QAction::triggered, ui->text_area, &QTextEdit::paste);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionClear, &QAction::triggered, ui->text_area, &QTextEdit::clear);
    connect(ui->actionPreference, &QAction::triggered, this, &MainWindow::preference);
    // TOOL BAR VIEW
    connect(ui->actionToolbar_top, &QAction::triggered, this, &MainWindow::toolbar_top);
    connect(ui->actionToolbar_left, &QAction::triggered, this, &MainWindow::toolbar_left);
    connect(ui->actionToolbar_right, &QAction::triggered, this, &MainWindow::toolbar_right);
    connect(ui->actionToolbar_bottom, &QAction::triggered, this, &MainWindow::toolbar_bottom);
    connect(ui->actionToolbar_moveable, &QAction::toggled, this, &MainWindow::toolbar_moveable);
    connect(ui->actionToolbar_floatable, &QAction::toggled, this, &MainWindow::toolbar_floatable);
    // TEXT FONT BOLD ITALIC UNDERLINE....
    connect(ui->actionBold, &QAction::triggered, this, &MainWindow::set_bold);
    connect(ui->actionItalic, &QAction::triggered, this, &MainWindow::set_italic);
    connect(ui->actionUnderline, &QAction::triggered, this, &MainWindow::set_underline);
    connect(ui->actionStrikeout, &QAction::triggered, this, &MainWindow::set_strikeout);
    // UNDO REDO
    connect(ui->actionUndo, &QAction::triggered, ui->text_area, &QTextEdit::undo);
    connect(ui->actionRedo, &QAction::triggered, ui->text_area, &QTextEdit::redo);
    // ZOOM IN AND OUT
    connect(ui->actionZoom_In, &QAction::triggered, this, &MainWindow::set_zoom_in);
    connect(ui->actionZoom_Out, &QAction::triggered, this, &MainWindow::set_zoom_out);

    // FONT
    connect(ui->actionFont, &QAction::triggered, this, &MainWindow::set_font);
    // COLOUR
    connect(ui->actionColour, &QAction::triggered, this, &MainWindow::set_colour);
    // ALIGNMENT
    connect(ui->actionAlign_center, &QAction::triggered, this, &MainWindow::set_align_center);
    connect(ui->actionAlign_Justify, &QAction::triggered, this, &MainWindow::set_align_justify);
    connect(ui->actionAlign_left, &QAction::triggered, this, &MainWindow::set_align_left);
    connect(ui->actionAlign_right, &QAction::triggered, this, &MainWindow::set_align_right);

    // PRINTER
    connect(ui->actionPrint, &QAction::triggered, this, &MainWindow::print_dialog);
    connect(ui->actionPrint_preview, &QAction::triggered, this, &MainWindow::preview_print_dialog);


    setup_statusbar();
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
    //ui->statusbar->showMessage("New file");
    update_status("New file");
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
        //ui->statusbar->showMessage(m_file_name);
    }
    else // a hawn theih loh chuan file thar a hawng ang
    {
        new_file();
        QMessageBox::critical(this, "ERROR!!!", file.errorString());
        return;
    }
    update_status(m_file_name);
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
        //ui->statusbar->showMessage(m_file_name);
    }
    else // a hawn theih loh chuan file error message
    {
        QMessageBox::critical(this, "ERROR!!!", file.errorString());
        return;
    }
    update_status(m_file_name);
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
    int cursor_position = cursor.position();
    cursor.clearSelection();
    cursor.setPosition(cursor_position, QTextCursor::MoveMode::KeepAnchor); // move anchor at the beginning
    ui->text_area->setTextCursor(cursor);// setting the text cursor to text area
}

void MainWindow::toolbar_top() // add toolbar to top
{
    addToolBar(Qt::ToolBarArea::TopToolBarArea, ui->toolBar);
}

void MainWindow::toolbar_left()
{
    addToolBar(Qt::ToolBarArea::LeftToolBarArea, ui->toolBar);
}

void MainWindow::toolbar_right()
{
    addToolBar(Qt::ToolBarArea::RightToolBarArea, ui->toolBar);
}

void MainWindow::toolbar_bottom()
{
    addToolBar(Qt::ToolBarArea::BottomToolBarArea, ui->toolBar);
}

void MainWindow::toolbar_moveable(bool arg)
{
    ui->toolBar->setMovable(arg);
}

void MainWindow::toolbar_floatable(bool arg)
{
    ui->toolBar->setFloatable(arg);
}

void MainWindow::preference() // PREFERENCES
{
    Preference *preference_dialog = new Preference(this);
    preference_dialog->exec();
}

void MainWindow::setup_statusbar() // sets up the status bar display
{
    // displays the icon on the status bar
    QLabel *label_icon = new QLabel(this);
    label_icon->setPixmap(QPixmap("qrc:/image/image/new.png"));
    ui->statusbar->addWidget(label_icon);

    // displays a text on the status bar
    QLabel *label_message = new QLabel(this);
    label_message->setText("Not saved:");
    ui->statusbar->addWidget(label_message);

    // displays a file status on the status bar
    QLabel *label_fileStatus = new QLabel(this);
    label_fileStatus->setText("New");
    ui->statusbar->addWidget(label_fileStatus);
}

void MainWindow::update_status(QString message)
{
    foreach(QObject *obj, ui->statusbar->children()) // display the info of status in console
    {
        qDebug() << "debug status: " << obj;
    }

    QLabel *label_icon = qobject_cast<QLabel*>(ui->statusbar->children().at(1));
    QLabel *label_message = qobject_cast<QLabel*>(ui->statusbar->children().at(2));
    QLabel *label_fileName = qobject_cast<QLabel*>(ui->statusbar->children().at(4));
    if(m_save)
    {
        label_icon->setPixmap(QPixmap("qrc:/image/image/save.png"));
        label_message->setText("Saved:");
    }
    else
    {
        label_icon->setPixmap(QPixmap("qrc:/image/image/new.png"));
        label_message->setText("Not Saved:");
    }

    label_fileName->setText(m_file_name);
}

void MainWindow::on_text_area_textChanged()
{
    m_save = false;
    if(m_file_name.isEmpty())
    {
        update_status("New file");
    }
    else
    {
        update_status(m_file_name);
    }
}

void MainWindow::set_font()
{
    bool ok = true;
    QFont current = ui->text_area->currentCharFormat().font();
    QFont font = QFontDialog::getFont(&ok, current, this, "Choose font");
    ui->text_area->setCurrentFont(font);
}

void MainWindow::set_colour()
{
    QColor current = ui->text_area->currentCharFormat().foreground().color();
    QColor colour = QColorDialog::getColor(current, this, "Choose colour");
    ui->text_area->setTextColor(colour);
    m_save = true;
}

void MainWindow::set_bold() // BOLD
{
    QFont font = ui->text_area->currentFont();
    font.bold() ? font.setBold(false) : font.setBold(true);
    ui->text_area->setCurrentFont(font);
}

void MainWindow::set_italic() // ITALIC
{
    QFont font = ui->text_area->currentFont();
    font.italic() ? font.setItalic(false) : font.setItalic(true);
    ui->text_area->setCurrentFont(font);
}

void MainWindow::set_underline() // UNDERLINE
{
    QFont font = ui->text_area->currentFont();
    font.underline() ? font.setUnderline(false) : font.setUnderline(true);
    ui->text_area->setCurrentFont(font);
}

void MainWindow::set_strikeout() // STRIKEOUT
{
    QFont font = ui->text_area->currentFont();
    font.strikeOut() ? font.setStrikeOut(false) : font.setStrikeOut(true);
    ui->text_area->setCurrentFont(font);
}

void MainWindow::set_align_center()
{
    ui->text_area->setAlignment(Qt::AlignCenter);
}

void MainWindow::set_align_justify()
{
    ui->text_area->setAlignment(Qt::AlignJustify);
}

void MainWindow::set_align_left()
{
    ui->text_area->setAlignment(Qt::AlignLeft);
}

void MainWindow::set_align_right()
{
    ui->text_area->setAlignment(Qt::AlignRight);
}

void MainWindow::set_zoom_out()
{
    ui->text_area->zoomOut(1);
}

void MainWindow::set_zoom_in()
{
    ui->text_area->zoomIn(1);
}

void MainWindow::print_dialog() // print method
{
    QPrinter myPrinter;
    myPrinter.setPrinterName("Extreme printer 1000");
    QPrintDialog dialog(&myPrinter, this);
    if(dialog.exec() == QPrintDialog::Rejected) return;
    ui->text_area->print(&myPrinter);
}

void MainWindow::preview_print_dialog() // preview print method
{
    QPrintPreviewDialog dialog;
    connect(&dialog, &QPrintPreviewDialog::paintRequested, ui->text_area, &QTextEdit::print);
    dialog.exec();
}

