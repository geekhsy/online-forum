#include "comment.h"

Comment::Comment(QString contents, QString author_id, QString postId, QString id)
{
    this->contents = contents;
    this->authorId = author_id;
    this->postId = postId;
    this->id = id;
    time_t now = time(0);
    creationTime = asctime(localtime(&now));
    creationTime.chop(1);
}

QString Comment::getAuthorId()
{
    return authorId;
}

QString Comment::getContents()
{
    return contents;
}

QString Comment::getPostedTime()
{
    return creationTime;
}

Comment::~Comment()
{
    ;
}
