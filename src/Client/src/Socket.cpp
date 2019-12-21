#include "Socket.h"
#include <QMessageBox>
#include <QWidget>
#include <QDebug>
#include <time.h>
#include <QList>
#include <fstream>
#include <QByteArray>

QString separator = "\1\9\9\8";

Socket* Socket::getInstance(){
    static Socket* m_instance = nullptr;
    if(m_instance == nullptr){
        m_instance = new Socket();
    }
    return m_instance;
}

Socket::Socket()
{
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1",1234);

//    ifstream ptr("mysql.db");
//    if(!ptr){
//        QMessageBox msgBox;
//        msgBox.setText("Fail to read from mysql.db");
//        msgBox.setInformativeText("It has been initialized!");
//        msgBox.setStandardButtons(QMessageBox::Ok);
//        msgBox.exec();
//    }
//    else{
//        ptr.close();
//    }
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("mysql.db");
//    if(!db.open()){
//        qDebug() << "error" << endl;
//    }
//    else{
//        query = new QSqlQuery(db);
//        query->exec("create table user(username QString primary key,password QString,id QString,type int,isOnline bool)");
//        query->exec("create table manage(username QString primary key,board QString)");
//        query->exec("create table comment(id QString primary key,"
//                    "contents QString,postId QString,authorId QString,creationTime QString)");
//        query->exec("create table post(id QString primary key,title QString,contents QString,"
//                    "authorId QString,boardName QString,isModify bool,creationTime QString)");
//        query->exec("create table anonymity(username QString, type int)");
//    }
}
//length type username password id type
bool Socket::addUsers(QString username, QString password, QString id, int type)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("0%1%2%3%4%5%6%7%8%9").arg(separator+'0').arg(separator).arg(username).arg(separator)
               .arg(password).arg(separator).arg(id).arg(separator).arg(type));
//    cmd[5] = cmd.size();
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();

//    query->exec(QString("select * from user where username  = '%1'").arg(username));
//    if(query->last()){
//        return false;
//    }
//    query->exec(QString("insert into user values ('%1','%2','%3','%4','%5')")
//                .arg(username).arg(password).arg(id).arg(type).arg(false));
//    return true;
}

bool Socket::isMatched(QString username, QString password)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("1%1%2%3%4%5").arg(separator+'0').arg(separator).arg(username).arg(separator)
               .arg(password));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();

//    query->exec(QString("select * from user where username  = '%1'").arg(username));
//    if(query->last()){
//        if(query->value(1).toString() == password){
//            return true;
//        }
//    }
//    return false;
}

QString Socket::getUserId(QString username)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("2%1%2%3").arg(separator+'0').arg(separator).arg(username));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return QString(feedback);


//    query->exec(QString("select * from user where username  = '%1'").arg(username));
//    if(query->last()){
//        return query->value(2).toString();
//    }
//    return "";
}

QString Socket::getUserManagement(QString username)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("3%1%2%3").arg(separator+'0').arg(separator).arg(username));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return QString(feedback);



//    query->exec(QString("select * from manage where username  = '%1'").arg(username));
//    if(query->last()){
//        return query->value(1).toString();
//    }
//    return "";
}

QString Socket::getUserName(QString id)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("4%1%2%3").arg(separator+'0').arg(separator).arg(id));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return QString(feedback);

//    query->exec(QString("select * from user where id  = '%1'").arg(id));
//    if(query->last()){
//        return query->value(0).toString();
//    }
//    return "";
}

int Socket::getUserType(QString username)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("5%1%2%3").arg(separator+'0').arg(separator).arg(username));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();



//    query->exec(QString("select * from user where username  = '%1'").arg(username));
//    if(query->last()){
//        return query->value(3).toInt();
//    }
//    return -1;
}

bool Socket::convertToModerator(QString id, QString boardName)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("6%1%2%3%4%5").arg(separator+'0').arg(separator).arg(id)
               .arg(separator).arg(boardName));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();


//    query->exec(QString("select * from user where id = '%1'").arg(id));
//    if(query->last()){
//        if(query->value(3).toInt() == 1){
//            query->exec(QString("update user set type = 2 where id = '%1'").arg(id));
//            query->exec(QString("insert into manage values ('%1','%2')").arg(getUserName(id)).arg(boardName));
//        }
//    }
//    return false;
}

bool Socket::convertToMember(QString id)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("7%1%2%3").arg(separator+'0').arg(separator).arg(id));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();

//    query->exec(QString("select * from user where id = '%1'").arg(id));
//    if(query->last()){
//        if(query->value(3).toInt() == 2){
//            query->exec(QString("update user set type = 1 where id = '%1'").arg(id));
//            query->exec(QString("delete from manage where id = '%1'").arg(getUserName(id)));
//        }
//    }
//    return false;
}

QString Socket::getAllUserNames()
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("8%1").arg(separator+'0'));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return QString(feedback);

//    QString name = "";
//    query->exec(QString("select * from user"));
//    while (query->next()) {
//       name.append(query->value(0).toString());
//       name.append("*");
//    }
//    if(name.length()){
//        name.chop(1);
//    }
//    return name;
}

bool Socket::addComments(QString id, QString contents, QString postId, QString authorId)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("9%1%2%3%4%5%6%7%8%9").arg(separator+'0').arg(separator).arg(id).arg(separator)
               .arg(contents).arg(separator).arg(postId).arg(separator).arg(authorId));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();


//    time_t now = time(0);
//    QString creationTime = asctime(localtime(&now));
//    creationTime.chop(1);
//    query->exec(QString("insert into comment values ('%1','%2','%3','%4','%5')").arg(id)
//                .arg(contents).arg(postId).arg(authorId).arg(creationTime));
//    return true;
}

//返回 作者名、评论内容、发表时间
QStringList Socket::getComments(QString postId)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("10%1%2%3").arg(separator+'0').arg(separator).arg(postId));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return QString(feedback).split("\1\2\1\9");




//    QStringList comments;
//    query->exec(QString("select * from comment where postId = '%1'").arg(postId));
//    comments << "0";
//    int i = 0;
//    while(query->next()){
//        i ++;
//        comments << query->value(1).toString() << query->value(3).toString() << query->value(4).toString();
//    }
//    *comments.begin() = QString::number(i,10);
//    return comments;
}

bool Socket::hasComment(QString postId)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("11%1%2%3").arg(separator+'0').arg(separator).arg(postId));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();



//    query->exec(QString("select * from comment where postId = '%1'").arg(postId));
//    if(query->last()){
//        return true;
//    }
//    else
//        return false;
}

bool Socket::addPost(QString id, QString title, QString contents, QString authorId, QString boardName)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("12%1%2%3%4%5%6%7%8%9%10%11").arg(separator+'0').arg(separator).arg(id).arg(separator)
               .arg(title).arg(separator).arg(contents).arg(separator).arg(authorId).arg(separator).arg(boardName));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();

//    //发送
//    QString requestBody = QString("12%1%2%3%4%5%6%7%8%9%10%11").arg(separator+'0').arg(separator).arg(id).arg(separator)
//                          .arg(title).arg(separator).arg(contents).arg(separator).arg(authorId).arg(separator).arg(boardName);
//    QByteArray outBlock;
//    QDataStream outBound(&outBlock, QIODevice::WriteOnly);
//    outBound << requestBody.toUtf8();
//    socket.write(outBlock);

//    //接收
//    QDataStream inBound(&socket);
//    QByteArray res;
//    do{
//        if(!socket.waitForReadyRead(TIMEOUT)){
//            emit error(socket.error(), socket.errorString());
//            return;
//        }

//        inBound.startTransaction();
//        inBound >> res;
//    } while(!inBound.commitTransaction());



//    time_t now = time(0);
//    QString creationTime = QString(asctime(localtime(&now)));
//    creationTime.chop(1);
//    query->exec(QString("insert into post values('%1','%2','%3','%4','%5','%6','%7')").arg(id)
//                .arg(title).arg(contents).arg(authorId).arg(boardName).arg(false).arg(creationTime));
//    return true;
}

bool Socket::deletePost(QString id)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("13%1%2%3").arg(separator+'0').arg(separator).arg(id));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();



//    query->exec(QString("select * from post where id = '%1'").arg(id));
//    if(!query->last()){
//        return false;
//    }
//    else{
//        query->exec(QString("delete from post where id = '%1'").arg(id));
//        return true;
//    }
}

QList<QString> Socket::getAllPostTitles(QString boardName)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("14%1%2%3").arg(separator+'0').arg(separator).arg(boardName));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    QStringList info = QString(feedback).split("\1\2\1\9");
    QList<QString> names;
    for(int i = 0;i < info.size();i ++){
        names.append(info[i]);
    }
    return names;


//    QList<QString> names;
//    query->exec(QString("select * from post where boardName = '%1'").arg(boardName));
//    while(query->next()){
//        names.append(query->value(0).toString());
//        names.append(query->value(1).toString());
//    }
//    return names;
}

//id ,title ,contents ,authorId ,boardName ,isModify ,creationTime
QStringList Socket::getPostInfo(QString id)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("15%1%2%3").arg(separator+'0').arg(separator).arg(id));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return QString(feedback).split("\1\2\1\9");


//    QStringList info;
//    query->exec(QString("select * from post where id = '%1'").arg(id));
//    if(query->next()){
//        for(int i = 0;i < 7;i ++){
//            info << query->value(i).toString();
//        }
//    }
//    return info;
}

bool Socket::rewritePost(QString id, QString title, QString contents)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("16%1%2%3%4%5%6%7").arg(separator+'0').arg(separator).arg(id).arg(separator)
               .arg(title).arg(separator).arg(contents));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();


//    qDebug() << title << endl
//         << contents << endl;
//    query->exec(QString("update post set title = '%1', contents = '%2', isModify = '%3' where id = '%4'")
//                .arg(title).arg(contents).arg(true).arg(id));
//    return true;
}

bool Socket::convertToAnonymity(QString username)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("17%1%2%3").arg(separator+'0').arg(separator).arg(username));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();

//    query->exec(QString("select type from user where username = '%1'").arg(username));
//    query->next();
//    int type = query->value(0).toInt();
//    query->exec(QString("update user set type = '%1' where username = '%2'").arg(4).arg(username));
//    query->exec(QString("insert into anonymity values ('%1','%2')").arg(username).arg(type));
//    return false;
}

bool Socket::logIn(QString username)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("18%1%2%3").arg(separator+'0').arg(separator).arg(username));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();

//    query->exec(QString("select isOnline from user where username = '%1'").arg(username));
//    query->next();
//    if(query->value(0).toInt()){ //若用户已经在线
//        return false;
//    }
//    else{ //记录该用户已经在线
//        query->exec(QString("update user set isOnline = '%1' where username  = '%2'").arg(true).arg(username));
//        return true;
//    }
}

bool Socket::logOut(QString username)
{
    QByteArray cmd;
    cmd.clear();
    cmd.append(QString("19%1%2%3").arg(separator+'0').arg(separator).arg(username));
    socket->write(cmd);

    socket->waitForReadyRead();
    QByteArray feedback = socket->readAll();
    return feedback.toInt();


//    //得到用户类型
//    query->exec(QString("select type from user where username = '%1'").arg(username));
//    query->next();
//    int type = query->value(0).toInt();

//    //如果是匿名用户，注销时恢复原来的类型
//    if(type == 4){
//        query->exec(QString("select type from anonymity where username = '%1'").arg(username));
//        query->next();
//        type = query->value(0).toInt();
//        query->exec(QString("delete from anonymity where username = '%1'").arg(username));
//        query->exec(QString("update user set type = '%1' where username = '%2'").arg(type).arg(username));
//    }
//    query->exec(QString("update user set isOnline = '%1' where username  = '%2'").arg(false).arg(username));
//    return true;
}
