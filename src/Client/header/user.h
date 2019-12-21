#ifndef USER_H
#define USER_H

#include <QString>
#include <QStringList>

class User
{
public:
    User(QString id,QString username,QString password,int type = 0);
    int getType();

    QString getUsername();
    QString getPassword();
    QString getId();

    void logIn(QString username, QString password, bool isAnonymous);
    void logOut();
    virtual bool deletePost(QString id,QString board) = 0;
    bool addPost(QString title,QString contents);
    bool addComment(QString contents,QString board,QString postId);
    bool isAnonymous();
    virtual ~User();
private:
    QString username;//用户名
    QString password;//密码
    QString id;//用户ID
    int type;//用户类型
};

#endif // USER_H
