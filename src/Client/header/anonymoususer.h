#ifndef ANONYMOUSUSER_H
#define ANONYMOUSUSER_H

#include "user.h"

class AnonymousUser : public User
{
public:
    AnonymousUser(QString id,QString username,QString password,int type = 4);
    bool deletePost(QString id,QString board);
    bool addPost(QString title,QString contents);
    bool addComment(QString contents,QString board,QString postId);
};

#endif // ANONYMOUSUSER_H
