#ifndef POST_H
#define POST_H

#include <QString>
#include <vector>
#include <map>
#include <ctime>
#include "comment.h"
#include "Socket.h"

using namespace std;

class Socket;

class Post
{
public:
    Post(QString id, QString title, QString contents, QString authorId, QString boardName, bool isModify, QString creationTime);
    QString getTitle();
    QString getContents();
    QString getAuthorId();
    QString getId();
    QString getBoardName();
    QString getPostedTime();
    bool addComment(QString contents);//增加评论
    bool rewrite(QString title,QString contents);//重写帖子
    bool hasComment();//判断是否含有评论
    bool isPostModify();//判断帖子是否修改过
    ~Post();

    friend void operator <<(Socket *socket, Post& myPost);
private:
    QString title;//帖子的标题
    QString contents;//帖子的内容
    QString authorId;//帖子作者ID
    QString id;//帖子本身的ID
    QString boardName;//所在版块
    bool isModify;//是否修改
    QString creationTime;//创建时间
};

#endif // POST_H
