#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <hiredis/hiredis.h>
#include <QString>
#include <QObject>
#include <QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QThread>
#include <QDebug>



class DBManager : public QObject
{
    Q_OBJECT

public:

    explicit DBManager(QObject *parent = nullptr);
 DBManager getDB();
    redisContext *db;
    QJsonDocument jsonDocument;

    redisReply *replyData;

    float valPitch;
    float valRoll;
    float valAirspeed;
    float valAltitude;
    short valHeading;
    QString valMode;
    float valTurn;
    float valVSpeed;


    void stringToJson(QByteArray str);

    void connectDatabase();
    void getReply();


    Q_INVOKABLE  float getPitch() const;
    void setPitch(float newPitch) ;

    Q_INVOKABLE float getRoll() const;
    void setRoll(float newRoll) ;

    Q_INVOKABLE float getAltitude() const;
    void setAltitude(float newAlt) ;

    Q_INVOKABLE float getAirspeed() const;
    void setAirspeed(float newAirspeed) ;

    Q_INVOKABLE QString getMode() const;
    void setMode(QString newMode) ;

    Q_INVOKABLE float getTurn() const;
    void setTurn(float newTurn) ;

    Q_INVOKABLE short getHeading() const;
    void setHeading(short newHead) ;

    Q_INVOKABLE float getVSpeed() const;
    void setVSpeed(float newVSpeed) ;

    Q_INVOKABLE double getLat() const;
    void setLat(double newLat) ;

    Q_INVOKABLE double getLon() const;
    void setLon(double newLon) ;

};


#endif // DBMANAGER_H
