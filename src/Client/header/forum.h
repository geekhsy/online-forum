#ifndef FORUM_H
#define FORUM_H

#include "board.h"
#include <fstream>

class Forum
{
public:
    static Forum* getInstance();
    Board* getCurrentBoard();
    QString getBoardNames();
    bool switchBoard(QString boardName);
    ~Forum();
    friend fstream & operator <<(fstream &out,Forum &myForum);
    friend fstream & operator >>(fstream &in,Forum &myForum);
private:
    Forum();
    Forum(const Forum& other);
    void addBoard(QString boardName);

    vector<Board*> forum;
    Board* currentBoard = nullptr;
};

#endif // FORUM_H
