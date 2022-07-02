#include "dbmanager.h"
#include <hiredis/hiredis.h>

#include <QApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <unistd.h>
#include <QThreadStorage>

#include <QQmlApplicationEngine>
#include <QObject>
#include "mainwindow.h"


using namespace std;
float latInternal,longInternal;

QJsonDocument doc;
QJsonObject obj;

DBManager::DBManager(QObject *parent)
{
    connectDatabase();
}

void DBManager::connectDatabase() {
    db = redisConnect ((char*)"127.0.0.1", 6379);
    if (db == NULL || db->err)
    {
              if (db)
              {
                  qDebug() << "Hata: " << db->errstr;
              } else
              {
                    qDebug() <<"Redis bağlantısı başarısız oldu.";
              }
    }
}




double DBManager::getLon() const
{
    return longInternal;
}

void DBManager::setLon(double newLon)
{
    longInternal = newLon;
}

double DBManager::getLat() const
{
    return latInternal;
}

void DBManager::setLat(double newLat)
{
    latInternal = newLat;
}


void DBManager::setRoll(float newRoll) {
    valRoll = newRoll;
}
float DBManager::getRoll() const {
    return valRoll;
}

void DBManager::setPitch(float newPitch) {
    valPitch = newPitch;
}
float DBManager::getPitch() const {
    return valPitch;
}


void DBManager::setVSpeed(float newVSpeed) {
    valVSpeed = newVSpeed;
}
float DBManager::getVSpeed() const{
    return valVSpeed;
}

void DBManager::setAirspeed(float newAirspeed) {
    valAirspeed = newAirspeed;
}

float DBManager::getAirspeed() const{
    return valAirspeed;
}

void DBManager::setAltitude(float newAlt) {
    valAltitude = newAlt;
}

float DBManager::getAltitude() const {
    return valAltitude;
}

void DBManager::setHeading(short newHead) {
    valHeading = newHead;
}

short DBManager::getHeading() const {
    return valHeading;
}

void DBManager::setMode(QString newMode) {
    valMode = newMode;
}
QString DBManager::getMode() const {
    return valMode;
}

void DBManager::setTurn(float newTurn) {
    valTurn = newTurn;
}
float DBManager::getTurn() const {
    return valTurn;
}

void DBManager::getReply()
{
    replyData = (redisReply *)redisCommand (db,"GET %s","json_data");
    stringToJson (replyData->str);
}


void DBManager::stringToJson (QByteArray str)
{

    doc = QJsonDocument::fromJson (str);
    obj = doc.object ();



    valPitch = obj["att_pitch"].toString().toFloat();
    valRoll = obj["att_roll"].toString().toFloat();
    valAirspeed = obj["ais"].toString().toFloat();
    valAltitude = obj["alt"].toString().toFloat();
    valHeading = obj["head"].toString().toFloat();
    latInternal = obj["lat"].toString().toFloat();
    longInternal = obj["lon"].toString().toFloat();
    valMode = obj["mode"].toString();
    valTurn = obj["turn"].toString().toFloat();
    valVSpeed = obj["vs"].toString().toFloat();




//    qDebug() << valVSpeed;

    setPitch(valPitch);
    setRoll(valRoll);
    setAirspeed(valAirspeed);
    setAltitude(valAltitude);
    setHeading(valHeading);
    setVSpeed(valVSpeed);
    setMode(valMode);
    setTurn(valTurn);
    setLat(latInternal);
    setLon(longInternal);
/*
    process.valPitch = valPitch;
    process.valRoll = valRoll;
    process.valAirspeed = valAirspeed;
    process.valAltitude = valAltitude;
    process.valHeading = valHeading;
    process.latInternal = latInternal;
    process.longInternal = longInternal;
    process.valMode = valMode;
    process.valTurn = valTurn;
    process.valVSpeed = valVSpeed;*/

}
