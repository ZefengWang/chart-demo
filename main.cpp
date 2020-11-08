#include "chart.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Chart w(nullptr);
    w.show();
    return a.exec();
}
