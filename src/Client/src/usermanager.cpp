#include "usermanager.h"
#include "user.h"
#include "member.h"
#include "moderator.h"
#include "administrator.h"
#include "anonymoususer.h"
#include "guid.h"
#include "Socket.h"
#include <QSqlQuery>

//单线程版本，尚未加互斥锁，获取单例指针
UserManager* UserManager::getInstance(){
    static UserManager* m_instance = nullptr;
    if(m_instance == nullptr){
        m_instance = new UserManager();
    }
    return m_instance;
}

UserManager::UserManager()
{   
//    QString id = QString::fromStdString(generateGuid());
//    Socket::getInstance()->addUsers("geekhsy","981219",id,3);
//    id = QString::fromStdString(generateGuid());
//    Socket::getInstance()->addUsers("wx","981219",id,3);
//    id = QString::fromStdString(generateGuid());
//    Socket::getInstance()->addUsers("123","123",id,1);
//    id = QString::fromStdString(generateGuid());
//    Socket::getInstance()->addUsers("王昕","123",id,1);
//    id = QString::fromStdString(generateGuid());
//    Socket::getInstance()->addUsers("pzy","123",id,4);
}

int UserManager::logIn(QString username,QString password,bool isAnonymous)
{
    if(Socket::getInstance()->isMatched(username,password)){//如果用户名、密码匹配
        if(!Socket::getInstance()->logIn(username)){
            //如果登录失败
            return -1;
        }
        if(isAnonymous){
            //如果是匿名登录
            Socket::getInstance()->convertToAnonymity(username);
        }
        QString id = Socket::getInstance()->getUserId(username);//获取用户ID
        int type = Socket::getInstance()->getUserType(username);//获取用户类型
        //根据类型生成对象
        if(type == 1){
            currentUser = new Member(id,username,password);
        }
        else if(type == 2){
            QString management = Socket::getInstance()->getUserManagement(username);
            currentUser = new Moderator(id,username,password,management);
        }
        else if(type == 3){
            currentUser = new Administrator(id,username,password);
        }
        else{
            currentUser = new AnonymousUser(id,username,password);
        }
        return 1;
    }
    return 0;
}

bool UserManager::logOut()
{
    //释放当前用户占用的内存空间
    delete currentUser;
    currentUser = nullptr;
    return true;
}

bool UserManager::Register(QString username, QString password)
{
    //生成全局唯一ID
    QString id = QString::fromStdString(generateGuid());
    //尝试进行注释
    return Socket::getInstance()->addUsers(username,password,id,1);
}

User *UserManager::getCurrentUser()
{
    //获取当前用户指针
    return currentUser;
}

/*
 * 功能：将普通用户提升为版主
 * 参数：用户ID、预管理版块名称
 * 返回值：是否成功转换
 */
bool UserManager::convertToModerator(QString id, QString boardName)
{
    if(currentUser->getType() != 3){
        return false;
    }
    return Socket::getInstance()->convertToModerator(id,boardName);
}

/*
 * 功能：将版主降为普通用户
 * 参数：用户ID
 * 返回值：是否成功转换
 */
bool UserManager::convertToMember(QString id)
{
    if(currentUser->getType() != 3){
        return false;
    }
    return Socket::getInstance()->convertToMember(id);
}

QString UserManager::getUserNames()
{
    return Socket::getInstance()->getAllUserNames();
}

QString UserManager::getUserName(QString id)
{
    return Socket::getInstance()->getUserName(id);
}

QString UserManager::getUserInfo(QString username)
{
    QString info = "";
    info.append(QString("username：") + QString(username));
    info.append("*");
    info.append(QString("type："));
    int type = Socket::getInstance()->getUserType(username);
    if(type == 1){
        info.append("普通会员");
    }
    else if(type == 2){
        info.append("版主");
    }
    else if(type == 3){
        info.append("管理员");
    }
    else{
        info.append("匿名用户");
    }
    info.append("*");
    info.append(QString("id：") + Socket::getInstance()->getUserId(username));
    if(type == 2){
        info.append("*");
        info.append(QString("管理板块：") + Socket::getInstance()->getUserManagement(username));
    }
    return info;
}

UserManager::~UserManager()
{
    currentUser = nullptr;
}
