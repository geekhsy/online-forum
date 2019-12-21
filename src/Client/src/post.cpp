#include "post.h"
#include "usermanager.h"
#include "guid.h"

Post::Post(QString id, QString title, QString contents, QString authorId, QString boardName, bool isModify, QString creationTime)
{
    this->title = title;
    this->contents = contents;
    this->authorId = authorId;
    this->boardName = boardName;
    this->id = id;
    this->isModify = isModify;
    this->creationTime = creationTime;
}

QString Post::getTitle()
{
    return title;
}

QString Post::getContents()
{
    return contents;
}

QString Post::getAuthorId()
{
    return authorId;
}

QString Post::getId()
{
    return id;
}

QString Post::getBoardName()
{
    return boardName;
}

QString Post::getPostedTime()
{
    return creationTime;
}

bool Post::addComment(QString contents)
{
    if(contents.length() == 0){
        return false;
    }
    QString id = QString::fromStdString(generateGuid());
    QString authorId = UserManager::getInstance()->getCurrentUser()->getId();
    Socket::getInstance()->addComments(id,contents,this->id,authorId);
    return true;
//    if(contents.length() == 0){
//        return false;
//    }
//    QString id = QString::fromStdString(generateGuid());
//    QString authorId = UserManager::getInstance()->getCurrentUser()->getId();
//    Comment temp(contents,authorId,this->id,id);
//    Socket::getInstance() << temp;
//    return true;
}

bool Post::rewrite(QString title,QString contents)
{
    if(title.length() == 0){
        return false;
    }
    if(contents.length() == 0){
        return false;
    }
    this->title = title;
    this->contents = contents;
    this->isModify = true;
    return Socket::getInstance()->rewritePost(this->id,title,contents);
}

bool Post::hasComment()
{
    return Socket::getInstance()->hasComment(this->id);
}



bool Post::isPostModify()
{
    return isModify;
}

Post::~Post()
{
    ;
}
