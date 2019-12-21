#include "board.h"
#include "guid.h"
#include "usermanager.h"
#include <map>
#include "Socket.h"
#include <QDebug>
#include <QList>

Board::Board(QString name)
{
    this->name = name;
}

bool Board::addPost(QString title, QString contents)
{
    QString id = QString::fromStdString(generateGuid());
//    time_t now = time(0);
//    QString creationTime = asctime(localtime(&now));
//    creationTime.chop(1);
//    Post temp(id,title,contents,UserManager::getInstance()->getCurrentUser()->getId(),this->name,false,creationTime);
    Socket::getInstance()->addPost(id,title,contents,UserManager::getInstance()->getCurrentUser()->getId(),this->name);
//    Socket::getInstance() << temp;
    return true;
}

bool Board::deletePost(QString id)
{
    return Socket::getInstance()->deletePost(id);
}

QList<QString> Board::getPostsTitles()
{
    return Socket::getInstance()->getAllPostTitles(this->getName());
}

QString Board::getName()
{
    return this->name;
}

Board::~Board()
{
}
