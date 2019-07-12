#ifndef MYSQLITE_H_INCLUDED
#define MYSQLITE_H_INCLUDED
#include "sqlite3.h"
#include <stdlib.h>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
typedef struct{
    string UserName;
    string PassWd;
}user;
class mydb{

public:
    mydb();
    ~mydb();

    //查询数据库
    int QuerySQL(string DbName,string sql);
    //执行SQL语句
    int ExcuteSQL(string DbName,string sql);
    //建表
    int EstablishTable();
    //插入数据
    int InsretData(string username, string password);
    //查询
    int SearchData();
    //删除数据
    int DeleteData(string username);
    //删除表
    int DeleteTable();
public:
    user m_user[100];
    string _dbname_;
    int count;
};


#endif // MYSQLITE_H_INCLUDED
