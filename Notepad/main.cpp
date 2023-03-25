#include "mainwindow.h"

#include <QApplication>
#include <QAction>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setAttribute(Qt::WA_QuitOnClose, true);
    w.resize(800, 600);
    QObject::connect(&app, &QApplication::aboutToQuit, [](){
            // Prevent the application from quitting when any window is still open
            if (QApplication::topLevelWidgets().count() > 1) {
                Q_FOREACH (QWidget* widget, QApplication::topLevelWidgets()) {
                    if (widget != qApp->activeWindow() && widget->isVisible()) {
                        widget->close();
                    }
                }
            }
        });
    w.show();
    return app.exec();
}
