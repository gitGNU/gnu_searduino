#include <QApplication>
#include "searduino.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Searduino w;
    w.show();
    
    return a.exec();
}
