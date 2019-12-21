#include "moderator.h"
#include "member.h"
#include "user.h"
#include "forum.h"
#include "Socket.h"

Moderator::Moderator(QString id, QString username, QString password, QString management, int type) :
    Member(id,username,password,type)
{
    this->management = management;
}

QString Moderator::getManagementName()
{
    return management;
}

bool Moderator::deletePost(QString id, QString board)
{
    if(!Forum::getInstance()->switchBoard(board)){
        return false;
    } 
    QStringList info = Socket::getInstance()->getPostInfo(id);
    if(info.size() == 0 ||info.at(4) != board){
        return false;
    }
    QString authorId = info.at(3);
    if(authorId != this->getId() && board != this->management){
        return false;
    }
    return Forum::getInstance()->getCurrentBoard()->deletePost(id);
}

