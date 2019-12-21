#ifndef BOARD_H
#define BOARD_H

#include "post.h"
#include <map>
#include <vector>
#include <QString>
using namespace std;

class Board
{
public:
    Board(QString name);
    bool addPost(QString title,QString contents);
    bool deletePost(QString id);
    QList<QString> getPostsTitles();
    QString getName();
    ~Board();
private:
    QString name;
};

#endif // BOARD_H
