#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "process.h"

#include <QThread>
#include <QObject>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mapWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));



    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(repaintSlot()));
    timer->start();


}

void MainWindow::setProcess(Process *process) {
    this->prc = process;
}

void MainWindow::repaintSlot()  {

    repaintGraphics(prc->dbManager.getRoll(), prc->dbManager.getPitch(), prc->dbManager.getVSpeed(), prc->dbManager.getAltitude(), prc->dbManager.getAirspeed(), prc->dbManager.getTurn(), prc->dbManager.getHeading());

}

void MainWindow::repaintGraphics(float roll, float pitch, float vspeed, float alt, float airspeed, float turn, short head)
{
    ui->graphicsAI->setRoll(roll);
    ui->graphicsAI->setPitch(pitch);
    ui->graphicsAI->redraw();

    ui->graphicsALT->setAltitude(alt);
    ui->graphicsALT->redraw();

    ui->graphicsASI->setAirspeed(airspeed);
    ui->graphicsASI->redraw();

    ui->graphicsHI->setHeading(head);
    ui->graphicsHI->redraw();

    ui->graphicsVSI->setClimbRate(vspeed);
    ui->graphicsVSI->redraw();

    ui->graphicsTC->setTurnRate(turn);
    ui->graphicsTC->redraw();
}
MainWindow::~MainWindow()
{
    delete ui;
}
