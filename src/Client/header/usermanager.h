#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>
#include <map>
#include "moderator.h"
#include "administrator.h"
#include <QString>
using namespace std;

class UserManager
{
public:
    static UserManager* getInstance();
    int logIn(QString username, QString password, bool isAnonymous);
    bool logOut();
    bool Register(QString username,QString password);
    User *getCurrentUser();
    bool convertToModerator(QString id,QString boardName);
    bool convertToMember(QString id);
    QString getUserNames();
    QString getUserName(QString id);
    QString getUserInfo(QString username);
    ~UserManager();
private:
    UserManager();
    UserManager(const UserManager& other);

    User* currentUser = nullptr;
};

#endif // USERMANAGER_H
