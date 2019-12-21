#include "mythread.h"
#include "mysql.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>

QString separator = "\1\9\9\8";

MyThread::MyThread(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
}

void MyThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

void MyThread::readyRead()
{
    //接收
    QDataStream inBound(socket);
    QByteArray Data;
    do{
        if(!socket->waitForReadyRead()){
            qDebug() << "fail to read!!!!!" << endl;
            return;
        }
        inBound.startTransaction();
        inBound >> Data;
    } while(!inBound.commitTransaction());

    // get the information
//    QByteArray Data = socket->readAll();
//    if((Data[5]-'0') == Data.size()){
        QStringList info = QString(Data).split(separator);
        qDebug() << socketDescriptor << " Data in: " << info << endl;
        int type = info[0].toInt();
        qDebug() << "type = " << type << endl;
        QByteArray feedback;
        feedback.clear();
        switch (type) {
        /*
         * length type username password id type
         * bool
         */
        case 0:{
            bool res = Mysql::getInstance()->addUsers(info[2],info[3],info[4],info[5].toInt());
            qDebug() << "res = " << res << endl;
            feedback.append(QString::number(res));
            qDebug() << "feedback  is " << feedback << endl;
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        /*
         * length type username password
         * bool
         */
        case 1:{
            bool res = Mysql::getInstance()->isMatched(info[2],info[3]);
            qDebug() << "res = " << res << endl;
            feedback.append(QString::number(res));
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 2:{
            QString res = Mysql::getInstance()->getUserId(info[2]);
            feedback.append(res);
            qDebug() << "res = " << res << endl;
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 3:{
            QString res = Mysql::getInstance()->getUserManagement(info[2]);
            feedback.append(res);
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 4:{
            QString res = Mysql::getInstance()->getUserName(info[2]);
            feedback.append(res);
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 5:{
            int res = Mysql::getInstance()->getUserType(info[2]);
            qDebug() << "res = " << res << endl;
            feedback.append(QString::number(res,10));
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 6:{
            bool res = Mysql::getInstance()->convertToModerator(info[2],info[3]);
            feedback.append(QString::number(res));
            qDebug() << "res = " << res << endl;
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 7:{
            bool res = Mysql::getInstance()->convertToMember(info[2]);
            feedback.append(QString::number(res));
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 8:{
            QString res = Mysql::getInstance()->getAllUserNames();
            feedback.append(res);
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 9:{
            bool res = Mysql::getInstance()->addComments(info[2],info[3],info[4],info[5]);
            feedback.append(QString::number(res));
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 10:{
            QString res = Mysql::getInstance()->getComments(info[2]);
            feedback.append(res);
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 11:{
            bool res = Mysql::getInstance()->hasComment(info[2]);
            feedback.append(QString::number(res));
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 12:{
            bool res = Mysql::getInstance()->addPost(info[2],info[3]
                    ,info[4],info[5],info[6]);
            feedback.append(QString::number(res));
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 13:{
            bool res = Mysql::getInstance()->deletePost(info[2]);
            feedback.append(QString::number(res));
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 14:{
            QString res = Mysql::getInstance()->getAllPostTitles(info[2]);
            feedback.append(res);
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 15:{
            QString res = Mysql::getInstance()->getPostInfo(info[2]);
            feedback.append(res);
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 16:{
            bool res = Mysql::getInstance()->rewritePost(info[2],info[3],info[4]);
            feedback.append(QString::number(res));
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 17:{
            bool res = Mysql::getInstance()->convertToAnonymity(info[2]);
            feedback.append(QString::number(res));
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 18:{
            bool res = Mysql::getInstance()->logIn(info[2]);
            qDebug() << "res = " << res << endl;
            feedback.append(QString::number(res));
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        case 19:{
            bool res = Mysql::getInstance()->logOut(info[2]);
            feedback.append(QString::number(res));
            socket->write(feedback);
            socket->waitForBytesWritten();
            break;
        }
        default:
            break;
        }
//    }

    // will write on server side window
//    qDebug() << socketDescriptor << " Data in: " << Data;
//    if(Data[0] == '0'){
//        socket->write("success\n");
//    }
//    socket->write(Data);
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}
