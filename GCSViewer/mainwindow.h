#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "dbmanager.h"
#include "process.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Process *prc;

    void setProcess(Process *process);

    void repaintGraphics(float roll, float pitch, float vspeed, float alt, float airspeed, float turn, short head);

public slots:
    void repaintSlot();
private:
    Ui::MainWindow *ui;
    QTimer * timer;
};
#endif // MAINWINDOW_H
