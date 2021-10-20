#include "GUI/include/fmt_mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fmt_mainWindow w;
    w.show();
    return a.exec();
}
