#include "member.h"
#include "user.h"
#include "forum.h"
#include "Socket.h"

Member::Member(QString id, QString username, QString password, int type) :
    User(id,username,password,type){}

bool Member::deletePost(QString id, QString board)
{
    if(!Forum::getInstance()->switchBoard(board)){
        return false;
    }
    QStringList info = Socket::getInstance()->getPostInfo(id);
    if(info.size() == 0 ||info.at(4) != board){
        return false;
    }
    QString authorId = info.at(3);
    if(authorId.length() == 0 || authorId != this->getId()){
        return false;
    }
    return Forum::getInstance()->getCurrentBoard()->deletePost(id);
}


