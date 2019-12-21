#include "user.h"
#include "post.h"
#include "usermanager.h"
#include "forum.h"
#include "comment.h"
#include "guid.h"
#include "Socket.h"
#include <QStringList>

User::User(QString id, QString username, QString password, int type)
{
    this->id = id;
    this->username = username;
    this->password = password;
    this->type = type;
}

int User::getType()
{
    return this->type;
}

QString User::getUsername()
{
    return this->username;
}

QString User::getPassword()
{
    return this->password;
}

QString User::getId()
{
    return this->id;
}

void User::logIn(QString username, QString password,bool isAnonymous)
{
    UserManager::getInstance()->logIn(username,password,isAnonymous);
}

void User::logOut()
{
    UserManager::getInstance()->logOut();
}


bool User::addPost(QString title, QString contents)
{
    if(title.length() == 0 || contents.length() == 0){
        return false;
    }
    Forum::getInstance()->getCurrentBoard()->addPost(title,contents);
    return true;
}

bool User::addComment(QString contents, QString board, QString postId)
{
    if(!Forum::getInstance()->switchBoard(board)){
        return false;
    }
    QStringList info = Socket::getInstance()->getPostInfo(id);
    if(info.size() == 0 ||info.at(4) != board){
        return false;
    }
    QString id = QString::fromStdString(generateGuid());
    Socket::getInstance()->addComments(id,contents,postId,this->getId());
    return true;
}

User::~User()
{
    ;
}

