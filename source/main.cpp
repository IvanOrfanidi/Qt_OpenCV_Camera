#include <QApplication>
#include <cstdint>
#include <include/mainwindow.h>

int main(int argc, char* argv[])
{
    QApplication appl(argc, argv);
    MainWindow windows;
    windows.show();
    return appl.exec();
}