#include "mysql.h"
#include <QDebug>
#include <time.h>
#include <QList>
#include <fstream>


using namespace std;

std::atomic<Mysql*> Mysql::m_instance;
std::mutex Mysql::m_mutex;

Mysql* Mysql::getInstance(){
    Mysql* tmp = m_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);//获取内存fence
    if (tmp == nullptr) {
        std::lock_guard<std::mutex> lock(m_mutex);
        tmp = m_instance.load(std::memory_order_relaxed);
        if (tmp == nullptr) {
            tmp = new Mysql;
            std::atomic_thread_fence(std::memory_order_release);//释放内存fence
            m_instance.store(tmp, std::memory_order_relaxed);
        }
    }
    return tmp;
//    static Mysql* m_instance = nullptr;
//    if(m_instance == nullptr){
//        m_instance = new Mysql();
//    }
//    return m_instance;
}

Mysql::Mysql()
{
    ifstream ptr("mysql.db");
    if(!ptr){
        qDebug() << "Fail to read from mysql.db" << endl
                 << "It has been initialized!" << endl;
//        QMessageBox msgBox;
//        msgBox.setText("Fail to read from mysql.db");
//        msgBox.setInformativeText("It has been initialized!");
//        msgBox.setStandardButtons(QMessageBox::Ok);
//        msgBox.exec();
    }
    else{
        ptr.close();
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mysql.db");
    if(!db.open()){
        qDebug() << "error" << endl;
    }
    else{
        query = new QSqlQuery(db);
        query->exec("create table user(username QString primary key,password QString,id QString,type int,isOnline bool)");
        query->exec("create table manage(username QString primary key,board QString)");
        query->exec("create table comment(id QString primary key,"
                    "contents QString,postId QString,authorId QString,creationTime QString)");
        query->exec("create table post(id QString primary key,title QString,contents QString,"
                    "authorId QString,boardName QString,isModify bool,creationTime QString)");
        query->exec("create table anonymity(username QString, type int)");
    }
}

bool Mysql::addUsers(QString username, QString password, QString id, int type)
{
    sql_mutex.lock();
    query->exec(QString("select * from user where username  = '%1'").arg(username));
    if(query->last()){
        sql_mutex.unlock();
        return false;
    }
    query->exec(QString("insert into user values ('%1','%2','%3','%4','%5')")
                .arg(username).arg(password).arg(id).arg(type).arg(false));
    sql_mutex.unlock();
    return true;
}

bool Mysql::isMatched(QString username, QString password)
{
    sql_mutex.lock();
    query->exec(QString("select * from user where username  = '%1'").arg(username));
    if(query->last()){
        if(query->value(1).toString() == password){
            sql_mutex.unlock();
            return true;
        }
    }
    sql_mutex.unlock();
    return false;
}

QString Mysql::getUserId(QString username)
{
    sql_mutex.lock();
    query->exec(QString("select * from user where username  = '%1'").arg(username));
    if(query->last()){
        QString temp = query->value(2).toString();
        sql_mutex.unlock();
        return temp;
    }
    sql_mutex.unlock();
    return "";
}

QString Mysql::getUserManagement(QString username)
{
    sql_mutex.lock();
    query->exec(QString("select * from manage where username  = '%1'").arg(username));
    if(query->last()){
        QString temp = query->value(1).toString();
        sql_mutex.unlock();
        return temp;
    }
    sql_mutex.unlock();
    return "";
}

QString Mysql::getUserName(QString id)
{
    sql_mutex.lock();
    query->exec(QString("select * from user where id  = '%1'").arg(id));
    if(query->last()){
        QString temp = query->value(0).toString();
        sql_mutex.unlock();
        return temp;
    }
    sql_mutex.unlock();
    return "";
}

int Mysql::getUserType(QString username)
{
    sql_mutex.lock();
    query->exec(QString("select * from user where username  = '%1'").arg(username));
    if(query->last()){
        int temp = query->value(3).toInt();
        sql_mutex.unlock();
        return temp;
    }
    sql_mutex.unlock();
    return -1;
}

bool Mysql::convertToModerator(QString id, QString boardName)
{
    sql_mutex.lock();
    query->exec(QString("select * from user where id = '%1'").arg(id));
    if(query->last()){
        if(query->value(3).toInt() == 1){
            query->exec(QString("update user set type = 2 where id = '%1'").arg(id));
            query->exec(QString("select * from user where id  = '%1'").arg(id));
            query->last();
            QString name = query->value(0).toString();
            query->exec(QString("insert into manage values ('%1','%2')").arg(name).arg(boardName));
            qDebug() << "after" << endl;
            sql_mutex.unlock();
            return true;
        }
    }
    sql_mutex.unlock();
    return false;
}

bool Mysql::convertToMember(QString id)
{
    sql_mutex.lock();
    query->exec(QString("select * from user where id = '%1'").arg(id));
    if(query->last()){
        if(query->value(3).toInt() == 2){
            query->exec(QString("update user set type = 1 where id = '%1'").arg(id));
            query->exec(QString("select * from user where id  = '%1'").arg(id));
            query->last();
            QString name = query->value(0).toString();
            query->exec(QString("delete from manage where id = '%1'").arg(name));
            sql_mutex.unlock();
            return true;
        }
    }
    sql_mutex.unlock();
    return false;
}

QString Mysql::getAllUserNames()
{
    sql_mutex.lock();
    QString name = "";
    query->exec(QString("select * from user"));
    while (query->next()) {
       name.append(query->value(0).toString());
       name.append("*");
    }
    if(name.length()){
        name.chop(1);
    }
    sql_mutex.unlock();
    return name;
}

bool Mysql::addComments(QString id, QString contents, QString postId, QString authorId)
{
    sql_mutex.lock();
    time_t now = time(0);
    QString creationTime = asctime(localtime(&now));
    creationTime.chop(1);
    query->exec(QString("insert into comment values ('%1','%2','%3','%4','%5')").arg(id)
                .arg(contents).arg(postId).arg(authorId).arg(creationTime));
    sql_mutex.unlock();
    return true;
}

//返回 作者名、评论内容、发表时间
QString Mysql::getComments(QString postId)
{
    sql_mutex.lock();
    QString comments;
    query->exec(QString("select * from comment where postId = '%1'").arg(postId));
    int i = 0;
    while(query->next()){
        i ++;
        comments.append(QString("\1\2\1\9") + query->value(1).toString()
                        + QString("\1\2\1\9") + query->value(3).toString()
                        + QString("\1\2\1\9") + query->value(4).toString());
    }
    comments = QString::number(i,10) + comments;
    sql_mutex.unlock();
    return comments;
}

bool Mysql::hasComment(QString postId)
{
    sql_mutex.lock();
    query->exec(QString("select * from comment where postId = '%1'").arg(postId));
    if(query->last()){
        sql_mutex.unlock();
        return true;
    }
    else{
        sql_mutex.unlock();
        return false;
    }
}

bool Mysql::addPost(QString id, QString title, QString contents, QString authorId, QString boardName)
{
    sql_mutex.lock();
    time_t now = time(0);
    QString creationTime = QString(asctime(localtime(&now)));
    creationTime.chop(1);
    query->exec(QString("insert into post values('%1','%2','%3','%4','%5','%6','%7')").arg(id)
                .arg(title).arg(contents).arg(authorId).arg(boardName).arg(false).arg(creationTime));
    sql_mutex.unlock();
    return true;
}

bool Mysql::deletePost(QString id)
{
    sql_mutex.lock();
    query->exec(QString("select * from post where id = '%1'").arg(id));
    if(!query->last()){
        sql_mutex.unlock();
        return false;
    }
    else{
        query->exec(QString("delete from post where id = '%1'").arg(id));
        sql_mutex.unlock();
        return true;
    }
}

QString Mysql::getAllPostTitles(QString boardName)
{
    sql_mutex.lock();

    QString names;
    query->exec(QString("select * from post where boardName = '%1'").arg(boardName));
    while(query->next()){
        names.append(query->value(0).toString());
        names.append(QString("\1\2\1\9"));
        names.append(query->value(1).toString());
        names.append(QString("\1\2\1\9"));
    }
    names.chop(QString("\1\2\1\9").size());
    sql_mutex.unlock();
    return names;
}

//id ,title ,contents ,authorId ,boardName ,isModify ,creationTime
QString Mysql::getPostInfo(QString id)
{
    sql_mutex.lock();
    QString info;
    query->exec(QString("select * from post where id = '%1'").arg(id));
    if(query->next()){
        for(int i = 0;i < 7;i ++){
            info.append(query->value(i).toString());
            info.append(QString("\1\2\1\9"));
        }
    }
    if(info.size()){
        info.chop(QString("\1\2\1\9").size());
    }
    else{
        info = " ";
    }
    sql_mutex.unlock();
    return info;
}

bool Mysql::rewritePost(QString id, QString title, QString contents)
{
    sql_mutex.lock();
    qDebug() << title << endl
         << contents << endl;
    query->exec(QString("update post set title = '%1', contents = '%2', isModify = '%3' where id = '%4'")
                .arg(title).arg(contents).arg(true).arg(id));
    sql_mutex.unlock();
    return true;
}

bool Mysql::convertToAnonymity(QString username)
{
    sql_mutex.lock();
    query->exec(QString("select type from user where username = '%1'").arg(username));
    query->next();
    int type = query->value(0).toInt();
    query->exec(QString("update user set type = '%1' where username = '%2'").arg(4).arg(username));
    query->exec(QString("insert into anonymity values ('%1','%2')").arg(username).arg(type));
    sql_mutex.unlock();
    return false;
}

bool Mysql::logIn(QString username)
{
    sql_mutex.lock();
    query->exec(QString("select isOnline from user where username = '%1'").arg(username));
    query->next();
    if(query->value(0).toInt()){ //若用户已经在线
        sql_mutex.unlock();
        return false;
    }
    else{ //记录该用户已经在线
        query->exec(QString("update user set isOnline = '%1' where username  = '%2'").arg(true).arg(username));
        sql_mutex.unlock();
        return true;
    }

}

bool Mysql::logOut(QString username)
{
    sql_mutex.lock();
    //得到用户类型
    query->exec(QString("select type from user where username = '%1'").arg(username));
    query->next();
    int type = query->value(0).toInt();

    //如果是匿名用户，注销时恢复原来的类型
    if(type == 4){
        query->exec(QString("select type from anonymity where username = '%1'").arg(username));
        query->next();
        type = query->value(0).toInt();
        query->exec(QString("delete from anonymity where username = '%1'").arg(username));
        query->exec(QString("update user set type = '%1' where username = '%2'").arg(type).arg(username));
    }
    query->exec(QString("update user set isOnline = '%1' where username  = '%2'").arg(false).arg(username));
    sql_mutex.unlock();
    return true;
}
