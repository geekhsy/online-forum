#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "user.h"

class Administrator : public User
{
public:
    Administrator(QString id, QString username, QString password,int type = 3);
    bool deletePost(QString id, QString board);
};

#endif // ADMINISTRATOR_H
