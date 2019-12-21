#ifndef COMMENT_H
#define COMMENT_H

#include <QString>
#include <ctime>
#include "Socket.h"

class Socket;

class Comment
{
public:
    Comment(QString contents,QString authorId,QString postId,QString id);
    QString getAuthorId();
    QString getContents();
    QString getPostedTime();
    ~Comment();

    friend void operator <<(Socket* socket, Comment &myComment);
private:
    QString postId;
    QString id;
    QString contents;
    QString authorId;
    QString creationTime;
};


#endif // COMMENT_H
