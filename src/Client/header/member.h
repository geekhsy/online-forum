#ifndef MEMBER_H
#define MEMBER_H

#include "user.h"

class Member : public User
{
public:
    Member(QString id,QString username,QString password,int type = 1);
    bool deletePost(QString id,QString board);
};

#endif // MEMBER_H
