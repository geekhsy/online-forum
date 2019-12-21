#include "administrator.h"
#include "user.h"
#include "forum.h"
#include "Socket.h"

Administrator::Administrator(QString id, QString username, QString password,int type) :
    User(id,username,password,type){}

bool Administrator::deletePost(QString id, QString board)
{
    if(!Forum::getInstance()->switchBoard(board)){
        return false;
    }
    QStringList info = Socket::getInstance()->getPostInfo(id);
    if(info.size() == 0 ||info.at(4) != board){
        return false;
    }
    //当前版块可能不是所需要操作的版块（存在切换）
    return Forum::getInstance()->getCurrentBoard()->deletePost(id);
}
