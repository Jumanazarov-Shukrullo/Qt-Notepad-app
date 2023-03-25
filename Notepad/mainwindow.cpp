#include "mainwindow.h"
#include "feedbackdialog.h"

bool new_triggered = false;
bool save_triggered = false;
bool open_triggered = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{    
    file_dir = "/home/shukrullo/qt/NotepadAppDirs";
    file_path = "";
    file_status = "";
    new_triggered = true;
    save_triggered = false;
    open_triggered = false;
    create_menus();
    create_actions();
    text_edit = new QTextEdit(this);
    setCentralWidget(text_edit);
    findDialog = new FindDialog(this);
    connect(findDialog, SIGNAL(findNext(const QString &, Qt::CaseSensitivity)),
            this, SLOT(findNext(const QString &, Qt::CaseSensitivity)));
    connect(findDialog, SIGNAL(findPrevious(const QString &, Qt::CaseSensitivity)),
            this,SLOT(findPrevious(const QString&, Qt::CaseSensitivity)));
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (this == QApplication::topLevelWidgets().first()) {
        QApplication::quit();
    } else {
        event->accept();
    }
}

MainWindow::~MainWindow() {

}

void MainWindow::create_menus() {
    QMenu* m1 = new QMenu(tr("&File"), this);
    QMenu* m2 = new QMenu(tr("&Edit"), this);
    QMenu* m3 = new QMenu(tr("&Format"), this);
    QMenu* m4 = new QMenu(tr("&View"), this);
    QMenu* m5 = new QMenu(tr("&Help"), this);
    std::initializer_list<QMenu*> list { m1, m2, m3, m4, m5 };
    menus = new QVector<QMenu*>(list);
    for(int i = 0; i < menus->size(); ++ i) {
        menuBar()->addMenu(menus->at(i));
    }
}

void MainWindow::create_actions() {
    /// 1st Menu
    actions = new QVector<QAction*>();

    QAction* action_new = new QAction(tr("&New"), this);
    action_new->setShortcut(QKeySequence::New);
    action_new->setIcon(QIcon(":/Images/new.png"));
    connect(action_new, SIGNAL(triggered()), this, SLOT(action_new()));

    QAction* action_new_window = new QAction(tr("&New Window"), this);
    action_new_window->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_N));
    connect(action_new_window, SIGNAL(triggered()), this, SLOT(action_new_window()), Qt::QueuedConnection);

    QAction* action_open = new QAction(tr("&Open"), this);
    action_open->setShortcut(QKeySequence::Open);
    action_open->setIcon(QIcon(":/Images/open.png"));
    connect(action_open, SIGNAL(triggered()), this, SLOT(action_open()));

    QAction* action_save = new QAction(tr("&Save"), this);
    action_save->setShortcut(QKeySequence::Save);
    action_save->setIcon(QIcon(":/Images/save.png"));
    connect(action_save, SIGNAL(triggered()), this, SLOT(action_save()));

    QAction* action_save_as = new QAction(tr("&Save As"), this);
    action_save_as->setShortcut(QKeySequence::SaveAs);
    action_save_as->setIcon(QIcon(":/Images/save_as.png"));
    connect(action_save_as, SIGNAL(triggered()), this, SLOT(action_save_as()));

    QAction* action_print = new QAction(tr("&Print"), this);
    action_print->setShortcut(QKeySequence::Print);
    action_print->setIcon(QIcon(":/Images/print.png"));
    connect(action_print, SIGNAL(triggered()), this, SLOT(action_print()));

    QAction* action_exit = new QAction(tr("&Exit"), this);
    action_exit->setShortcut(QKeySequence::Quit);
    action_exit->setIcon(QIcon(":/Images/exit.png"));
    connect(action_exit, SIGNAL(triggered()), this, SLOT(action_exit()));

    actions->append(action_new);
    actions->append(action_new_window);
    actions->append(action_open);
    actions->append(action_save);
    actions->append(action_save_as);
    actions->append(action_print);
    actions->append(action_exit);

    int counter = 0;
    for(int i = 0; i < actions->size();) {
        ++counter;
        if (counter == 6 || counter == 9) {
            menus->at(0)->addSeparator();
        } else {
            menus->at(0)->addAction(actions->at(i));
            ++i;
        }
    }

    actions->clear();
    /// 2nd Menu

    undo = new QAction(tr("&Undo"), this);
    undo->setShortcut(QKeySequence::Undo);
    undo->setDisabled(false);
    connect(undo, SIGNAL(triggered()), this, SLOT(action_undo()));

    cut = new QAction(tr("&Cut"), this);
    cut->setShortcut(QKeySequence::Cut);
//    cut->setDisabled(true);
    connect(cut, SIGNAL(triggered()), this, SLOT(action_cut()));

    copy = new QAction(tr("&Copy"), this);
    copy->setShortcut(QKeySequence::Copy);
//    copy->setDisabled(true);
    connect(copy, SIGNAL(triggered()), this, SLOT(action_copy()));

    paste = new QAction(tr("&Paste"), this);
    paste->setShortcut(QKeySequence::Paste);
//    paste->setDisabled(false);
    connect(paste, SIGNAL(triggered()), this, SLOT(action_paste()));

    dlte = new QAction(tr("&Delete"), this);
//    dlte->setDisabled(true);
    dlte->setShortcut(QKeySequence::Delete);
    connect(dlte, SIGNAL(triggered()), this, SLOT(action_delete()));

    fnd = new QAction(tr("&Find"), this);
    fnd->setShortcut(QKeySequence::Find);
//    fnd->setDisabled(true);
    connect(fnd, SIGNAL(triggered()), this, SLOT(action_find()));


    auto* action_select_all = new QAction(tr("&Select All..."), this);
    action_select_all->setShortcut(QKeySequence::SelectAll);
    connect(action_select_all, SIGNAL(triggered()), this, SLOT(action_select_all()));

    auto* action_date_time = new QAction(tr("&Date/Time"), this);
    action_date_time->setShortcut(QKeySequence(Qt::Key_F5));
    connect(action_date_time, SIGNAL(triggered()), this, SLOT(action_date_time()));

    actions->append(undo);
    actions->append(cut);
    actions->append(copy);
    actions->append(paste);
    actions->append(dlte);
    actions->append(fnd);
    actions->append(action_select_all);
    actions->append(action_date_time);

    counter = 0;
    for(int i = 0; i < actions->size();) {
        ++counter;
        if (counter == 2 || counter == 7 || counter == 13) {
            menus->at(1)->addSeparator();
        } else {
            menus->at(1)->addAction(actions->at(i));
            ++i;
        }
    }
    actions->clear();

    /// 3rd Menu
    QAction* action_font = new QAction(tr("&Font..."), this);
    connect(action_font, SIGNAL(triggered()), this, SLOT(action_font()));

    QAction* action_color = new QAction(tr("&Color..."), this);
    connect(action_color, SIGNAL(triggered()), this, SLOT(action_color()));
    QAction* action_background_color = new QAction(tr("&Background Color"), this);
    connect(action_background_color, SIGNAL(triggered()), this,
                                     SLOT(action_background_color()));
    QAction* action_backgroud_color_edit_text = new QAction(tr("&Set Palette"), this);
    connect(action_backgroud_color_edit_text, SIGNAL(triggered()), this,
                         SLOT(action_backgroud_color_edit_text()));
    actions->append(action_font);
    actions->append(action_color);
    actions->append(action_background_color);
    actions->append(action_backgroud_color_edit_text);
    for(int i = 0; i < actions->size(); ++ i) {
        menus->at(2)->addAction(actions->at(i));
    }
    actions->clear();

    /// 4th Menu
    QMenu* zoom = new QMenu(tr("&Zoom"), this);
    menus->at(3)->addMenu(zoom);

    QAction* action_zoom_in = new QAction(tr("&Zoom In"), this);
    action_zoom_in->setShortcut(QKeySequence::ZoomIn);
    connect(action_zoom_in, SIGNAL(triggered()), this, SLOT(action_zoom_in()));

    QAction* action_zoom_out = new QAction(tr("&Zoom Out"), this);
    action_zoom_out->setShortcut(QKeySequence::ZoomOut);
    connect(action_zoom_out, SIGNAL(triggered()), this, SLOT(action_zoom_out()));

    QAction* action_default_zoom = new QAction(tr("&Restore Default Zoom"), this);
    action_default_zoom->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_0));
    connect(action_default_zoom, SIGNAL(triggered()), this, SLOT(action_default_zoom()));

    zoom->addAction(action_zoom_in);
    zoom->addAction(action_zoom_out);
    zoom->addAction(action_default_zoom);
    status_bar = new QAction(tr("&Status Bar"), this);
    connect(status_bar, SIGNAL(triggered()), this, SLOT(action_status_bar()));
    status_bar->setCheckable(true);
    status_bar->setChecked(false);

    menus->at(3)->addAction(status_bar);

    /// 5th Menu
    QAction* action_view_help = new QAction(tr("&View Help"), this);
    connect(action_view_help, SIGNAL(triggered()), this, SLOT(action_view_help()));

    QAction* action_send_feedback = new QAction(tr("&Send Feedback"), this);
    connect(action_send_feedback, SIGNAL(triggered()), this, SLOT(action_send_feedback()));

    QAction* action_about_notepad = new QAction(tr("&About Notepad"), this);
    connect(action_about_notepad, SIGNAL(triggered()), this, SLOT(action_about_notepad()));

    actions->append(action_view_help);
    actions->append(action_send_feedback);
    actions->append(action_about_notepad);
    counter = 0;
    for(int i = 0; i < actions->size();) {
        ++counter;
        if (counter == 3) {
            menus->at(4)->addSeparator();
        } else {
            menus->at(4)->addAction(actions->at(i));
            ++i;
        }
    }
}


/// 1st menu
void MainWindow::action_new() {    
    if (!new_triggered || save_triggered) {
        new_triggered = true;
        text_edit->clear();
        return;
    } else {
        if (text_edit->document()->isModified()) {
            QMessageBox::StandardButton button = QMessageBox::question(this,
                                    "New", "Do you want to save changes?\n",
                                     QMessageBox::No | QMessageBox::Yes
                                     | QMessageBox::Cancel);
            if (button == QMessageBox::Yes) {
                action_save();
                text_edit->setText("");
            } else if (button == QMessageBox::Cancel) {
                return;
            } else {
                text_edit->clear();
            }
        }
        new_triggered = false;
    }
    open_triggered = false;
}


void MainWindow::action_new_window() {
    MainWindow* win = new MainWindow();
    win->setAttribute(Qt::WA_DeleteOnClose);
    win->show();
}

void MainWindow::action_open() {
    QString file_name = QFileDialog::getOpenFileName(this, "Open file", file_dir);
    QFile file(file_name);
    file_path = file_name;
    open_triggered = true;
    new_triggered = false;
    if (!file.open(QFile::ReadWrite)) {
        QMessageBox::critical(this, "Error", "Couldn't open file");
        return;
    }
    QTextStream out(&file);
    QString text = out.readAll();
    text_edit->setText(text);
    file.close();
}
void MainWindow::action_save() {
    qDebug() << open_triggered << new_triggered;
    QString file_name = "";
    if (new_triggered || (!open_triggered && !save_triggered)) {
        file_name = QFileDialog::getSaveFileName(this, "Save file as...", file_dir);
        file_path = file_name;
    } else {
        file_name = file_path;
    }
    save_triggered = true;
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Title", "Couldn't open file to save");
        return;
    }
    QTextStream out(&file);
    QString text = text_edit->toPlainText();
    out << text;
    file_status = text;
    file.flush();
    file.close();
}
void MainWindow::action_save_as() {
    QString file_name = QFileDialog::getSaveFileName(this, "Open file", file_dir);
    QFile file(file_name);
    file_path = file_name;
    if (!file.open(QFile::ReadWrite)) {
        QMessageBox::critical(this, "Error", "Couldn't open file");
        return;
    }
    QTextStream out(&file);
    QString text = text_edit->toPlainText();
    out << text;
    file.close();
}


void MainWindow::action_print() {
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QDialog::Rejected){
        return;
    }
    text_edit->print(&printer);
}

void MainWindow::action_exit() {
    qDebug() << text_edit->document()->isModified() << "\n" <<
                text_edit->document()->isEmpty() << "\n" <<
                new_triggered << "\n" << save_triggered;
    auto current_file_status = text_edit->toPlainText();
    if((!new_triggered || !save_triggered) && (file_status != current_file_status)) {
     QMessageBox::StandardButton button = QMessageBox::question(this,
                                         "Title",
                                         "Document was changed\n"
                                         "Do you want to save it before exitting?\n",
                                         QMessageBox::Yes | QMessageBox::No |
                                         QMessageBox::Cancel);
     if (button == QMessageBox::Yes) {
         action_save();
         QApplication::quit();
     } else if (button == QMessageBox::No) {
         QApplication::quit();
     } else {
         return;
     }
    } else  {
        QApplication::quit();
    }
}

/// 2nd menu
/// Till replace actions will in mode "disabled"
void MainWindow::action_undo() {
    text_edit->undo();
}
void MainWindow::action_cut() {
    QWidget* focused = QApplication::focusWidget();
    if(focused != 0) {
        cut->setDisabled(false);
        QApplication::postEvent(focused, new QKeyEvent(QEvent::KeyPress,
                             Qt::Key_X, Qt::ControlModifier));
    }
}
void MainWindow::action_copy() {
    QWidget* focused = QApplication::focusWidget();
    if(focused != 0) {
        QApplication::postEvent(focused, new QKeyEvent(QEvent::KeyPress,
                             Qt::Key_C, Qt::ControlModifier));
    }
}

void MainWindow::action_paste() {
#if QT_CONFIG(clipboard)
    text_edit->paste();
#endif
}
void MainWindow::action_delete() {
    QWidget* focused = QApplication::focusWidget();
    if(focused != 0) {
        QApplication::postEvent(focused, new QKeyEvent(QEvent::KeyPress,
                             Qt::Key_Delete, Qt::ControlModifier));
    }
}
void MainWindow::action_find() {
    findDialog->show();
}
void MainWindow::findNext(const QString &str, Qt::CaseSensitivity cs)
{
    QTextDocument::FindFlags flags;
    if (cs == Qt::CaseSensitive) {
        flags = QTextDocument::FindCaseSensitively;
    } else {
        flags = QTextDocument::FindWholeWords;
    }
    if (!text_edit->find(str, flags)) {
        QMessageBox::information(this, tr("Notepad"), tr("Cannot find \"%1\"").arg(str));
    }
}

void MainWindow::findPrevious(const QString &str, Qt::CaseSensitivity cs)
{
    QTextDocument::FindFlags flags;
    if (cs == Qt::CaseSensitive) {
        flags = QTextDocument::FindCaseSensitively | QTextDocument::FindBackward;
    } else {
        flags = QTextDocument::FindWholeWords | QTextDocument::FindBackward;
    }
    if (!text_edit->find(str, flags)) {
        QMessageBox::information(this, tr("Notepad"), tr("Cannot find \"%1\"").arg(str));
    }
}
void MainWindow::action_select_all() {
    QWidget* focused = QApplication::focusWidget();
    if(focused != 0) {
        QApplication::postEvent(focused, new QKeyEvent(QEvent::KeyPress,
                             Qt::Key_A, Qt::ControlModifier));
    }
}
void MainWindow::action_date_time() {
    QString time = QDateTime::currentDateTime().toString();;
    QMessageBox::information(this, "Date", time);
}

/// 3rd menu
void MainWindow::action_font() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        text_edit->setFont(font);
    } else {
        return;
    }
}
void MainWindow::action_color() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if(color.isValid()) {
        text_edit->setTextColor(color);
    }
}
void MainWindow::action_background_color() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color.isValid()) {
        QPalette pl = text_edit->palette();
        pl.setColor(QPalette::Base, color);
        text_edit->setPalette(pl);
    }
}
void MainWindow::action_backgroud_color_edit_text() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if(color.isValid()) {
        text_edit->setPalette(QPalette(color));
    }
}
/// 4th menu
void MainWindow::action_zoom_in() {
    text_edit->zoomIn(1);
}
void MainWindow::action_zoom_out() {
    text_edit->zoomOut(1);
}
void MainWindow::action_default_zoom() {
    QString styleSheet = "body { font-size: medium; }";  // Set the default font size
    text_edit->document()->setDefaultStyleSheet(styleSheet);
}

void MainWindow::action_status_bar(){
    if (status_bar->isChecked()) {
        statusBar()->show();
    } else {
        statusBar()->hide();
    }
}

/// 5th menu
void MainWindow::action_view_help() {
    QString text = "Need Help?\n"
                   "Something wrong happened?\n"
                   "Feel free to reach to me.\n"
                   "Telegram: @jumanazarov_shukrullo";
    QMessageBox::StandardButton button = QMessageBox::question(this, "Help", text);
    if (button == QMessageBox::Yes) {
        QDesktopServices::openUrl(QUrl("https://t.me/jumanazarov_shukrullo"));
    } else {
        return;
    }
}
void MainWindow::action_send_feedback(){
    FeedbackDialog *dialog = new FeedbackDialog(this);
    dialog->exec();
}
void MainWindow::action_about_notepad() {
    QString text = "Linux Notepad is a simple text editor for Linux.\n"
                   "It creates and edits plain text documents.\n"
                   "First released in 2023, no commercial use.\n"
                   "Notepad has been part of every version of Linux ever since.\n"
                   "Creator: Shukrullo\n";
    QMessageBox::information(this, "About Notepad", text);
}
