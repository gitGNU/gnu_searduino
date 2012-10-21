#ifndef SEARDUINO_H
#define SEARDUINO_H

#include <QMainWindow>

namespace Ui {
class Searduino;
}

class Searduino : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Searduino(QWidget *parent = 0);
    ~Searduino();
    
private:
    Ui::Searduino *ui;
};

#endif // SEARDUINO_H
