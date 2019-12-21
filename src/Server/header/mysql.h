#ifndef MYSQL_H
#define MYSQL_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <mutex>

class Mysql
{
public:
    static Mysql* getInstance();//获取单例

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
    QString getComments(QString postId);//获取帖子下的ID
    bool hasComment(QString postId);//判断帖子是否有评论
    bool addPost(QString id,QString title,QString contents,QString authorId,QString boardName);//发布新帖
    bool deletePost(QString id);//根据帖子ID删除帖子
    QString getAllPostTitles(QString boardName);//获取某板块下所有帖子名称
    QString getPostInfo(QString id);//根据帖子ID获取帖子的详细信息
    bool rewritePost(QString id,QString title,QString contents);//修改帖子
    bool convertToAnonymity(QString username);//以匿名方式登录
    bool logIn(QString username);//登录
    bool logOut(QString username);//注销
private:
    static std::mutex m_mutex;
    static std::atomic<Mysql*> m_instance;

    std::mutex sql_mutex;
    Mysql();
    Mysql(const Mysql& other);

    QSqlQuery* query;
};

#endif // MYSQL_H
