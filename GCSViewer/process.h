#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QThread>
#include "dbmanager.h"

class Process : public QObject
{
    Q_OBJECT
public:

    explicit Process(QObject *parent = nullptr);

    DBManager dbManager;

    float valPitch;
    float valRoll;
    float valAirspeed;
    float valAltitude;
    short valHeading;
    QString valMode;
    float valTurn;
    float valVSpeed;

    void setUp(QThread &thread);

public slots:
    void doWork();
};

#endif // PROCESS_H
