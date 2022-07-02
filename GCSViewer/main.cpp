#include "mainwindow.h"
#include "dbmanager.h"
#include "process.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QObject>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);




    QThread cThread;
    Process cProcess;
    cProcess.setUp (cThread);
    cProcess.moveToThread (&cThread);
    cThread.start ();

    qmlRegisterType<DBManager>("database.package.qml",1,0,"DatabasePackage");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/map.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);


    engine.load (url);




    MainWindow w;
    w.setProcess(&cProcess);




    w.show();



    return app.exec();
}
