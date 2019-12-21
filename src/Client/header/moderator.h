#ifndef MODERATOR_H
#define MODERATOR_H

#include "member.h"

class Moderator : public Member
{
public:
    Moderator(QString id, QString username, QString password,QString management,int type = 2);
    QString getManagementName();//获取管理的版块名称
    bool deletePost(QString id, QString board);
private:
    QString management;
};

#endif // MODERATOR_H
