#include "forum.h"
#include <string>
#include <set>
#include <QDebug>
#include <QMessageBox>
#include <QString>

Forum *Forum::getInstance()
{
    static Forum* m_instance = nullptr;
    if(m_instance == nullptr){
        m_instance = new Forum();
    }
    return m_instance;
}

Board *Forum::getCurrentBoard()
{
    return currentBoard;
}

QString Forum::getBoardNames()
{
    QString names = "";
    for(unsigned int i = 0;i < forum.size();i ++){
        names.append(forum[i]->getName());
        names.append("*");
    }
    names.chop(1);//去掉结束的换行符
    return names;
}

Forum::~Forum()
{
    fstream ptr("forum.txt",ios::in|ios::out);
    ptr << *this;
    for(unsigned int i = 0;i < forum.size();i ++){
        delete forum[i];
    }
    currentBoard = nullptr;
    forum.clear();
}

Forum::Forum()
{
    fstream ptr("forum.txt",ios::in);
    ptr >> *this;
//    Board* temp = new Board("first board");
//    temp->addPost("test1","this is test1");
//    temp->addPost("test2","this is test2");

//    temp->getPost(0)->addComment("hello world!");
//    temp->getPost(0)->addComment("above is a comment!");
//    currentBoard = temp;
//    forum.push_back(temp);
//    temp = new Board("second board");
//    temp->addPost("test3","this is test3");
//    temp->addPost("test4","this is test4");
//    forum.push_back(temp);
}

/*
 * 函数功能：根据板块名切换板块
 */
bool Forum::switchBoard(QString boardName)
{
    for(auto& board : forum){
        if(board->getName() == boardName){//根据板块名选择版块
            currentBoard = board;
            return true;
        }
    }
    return false;
}

void Forum::addBoard(QString boardName)
{
    //添加新版块
    Board* temp = new Board(boardName);
    forum.push_back(temp);
}

fstream & operator <<(fstream &out,Forum &myForum)
{
    if(!out){
        //若文件不存在提示
        QMessageBox msgBox;
        msgBox.setText("Fail to write in forum.txt.");
        msgBox.setInformativeText("Do you want to initialize it?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        switch (ret) {
            case QMessageBox::Yes:
                out.close();
                //创建文件
                out.open("forum.txt",ios::out|ios::trunc);
                break;
            case QMessageBox::No:
                break;
            default:
                break;
        }
    }
    if(out){
        out.close();
        out.open("forum.txt",ios::out|ios::trunc);
        out.clear();
        out.seekp(0);
        //将每个板块的名称写入文件
        for(unsigned int i = 0;i < myForum.forum.size();i ++){
            out << myForum.forum[i]->getName().toStdString() << endl;
        }
    }
    return out;
}

fstream & operator >>(fstream &in,Forum &myForum)
{
    if(!in){
        //提示文件不存在
        QMessageBox msgBox;
        msgBox.setText("Fail to read from forum.txt.");
        msgBox.setInformativeText("Do you want to initialize it?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        std::string s;
        switch (ret) {
            case QMessageBox::Yes://初始化帖子
                in.open("forum.txt",ios::out);
                in.close();
                in.open("forum.txt",ios::in|ios::out);
                //写入初始化信息
                s = "first board\nsecond board";
                in << s << endl;
                break;
            case QMessageBox::No:
                break;
            default:
                break;
        }
    }
    if(in){
        in.clear();
        in.seekg(0);
        std::string s;
        std::set<QString> rec;
        rec.clear();
        while(std::getline(in,s)){//获取每行的帖子名称
            if(s.length()){//若帖子名称非空
                qDebug() << "s " << QString::fromStdString(s) << endl;
                rec.insert(QString::fromStdString(s));
            }
        }
        //在内存中初始化各个板块
        for(std::set<QString>::iterator i = rec.begin();i != rec.end();i ++){
            Board* temp = new Board(*i);
            myForum.forum.push_back(temp);
        }
    }
    return in;
}
