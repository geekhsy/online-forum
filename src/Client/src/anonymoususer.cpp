#include "anonymoususer.h"

AnonymousUser::AnonymousUser(QString id, QString username, QString password, int type):
    User(id,username,password,type){}

bool AnonymousUser::deletePost(QString id, QString board)
{
    return false;
}

bool AnonymousUser::addPost(QString title, QString contents)
{
    return false;
}

bool AnonymousUser::addComment(QString contents, QString board, QString postId)
{
    return false;
}

