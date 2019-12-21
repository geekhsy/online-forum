#ifndef SOCKET_H
#define SOCKET_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QTcpSocket>
#include "post.h"
#include "comment.h"

class Post;
class Comment;

class Socket
{
public:
    static Socket* getInstance();//获取单例
    bool addUsers(QString username,QString password,QString id,int type);//添加用户
    bool isMatched(QString username,QString password);//判断用户名、密码是否匹配
    QString getUserId(QString username);//根据用户名获取ID
    QString getUserManagement(QString username);//获取版主管理的版块名称
    QString getUserName(QString id);//根据ID获取用户名
    int getUserType(QString username);//获取用户类型
    bool convertToModerator(QString id,QString boardName);//提升为版主
    bool convertToMember(QString id);//降为普通用户
    QString getAllUserNames();//获取所有用户名
    bool addComments(QString id,QString contents,QString postId,QString authorId);//添加评论
    QStringList getComments(QString postId);//获取帖子下的ID
    bool hasComment(QString postId);//判断帖子是否有评论
    bool addPost(QString id,QString title,QString contents,QString authorId,QString boardName);//发布新帖
    bool deletePost(QString id);//根据帖子ID删除帖子
    QList<QString> getAllPostTitles(QString boardName);//获取某板块下所有帖子名称
    QStringList getPostInfo(QString id);//根据帖子ID获取帖子的详细信息
    bool rewritePost(QString id,QString title,QString contents);//修改帖子
    bool convertToAnonymity(QString username);//以匿名方式登录
    bool logIn(QString username);//登录
    bool logOut(QString username);//注销

private:
    Socket();
    Socket(const Socket& other);

    QTcpSocket *socket;
};

#endif // SOCKET_H
