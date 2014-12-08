#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <QTextStream>
#include <QFile>
#include <QtDebug>

void logMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString message;
    QString currentDT = QDateTime::currentDateTime().toString("yyyy/mm/dd hh:mm:ss");
    switch (type) {
    case QtDebugMsg:
        message = QString("%1 - DEBUG - %2\n").arg(currentDT, msg);
        break;
    case QtWarningMsg:
        message = QString("%1 - WARNING - %2\n").arg(currentDT, msg);
        break;
    case QtCriticalMsg:
        message = QString("%1 - CRITICAL - %2\n").arg(currentDT, msg);
        break;
    case QtFatalMsg:
        message = QString("%1 - FATAL - %2\n").arg(currentDT, msg);
    }
    QFile logFile("QuickFolderCloner.log");
    logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream stream(&logFile);
    stream << message;
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(logMessageHandler);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
