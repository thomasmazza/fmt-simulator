#include "GUI/include/fmt_mainwindow.hpp"
#include <locale.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "C");
    QApplication a(argc, argv);
    fmt_mainWindow w;
    w.show();
    return a.exec();
}
