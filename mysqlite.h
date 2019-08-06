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

typedef enum{
    userTable=0,
    ssqTable,
    dltTable
}TableType;

class mydb{

public:
    mydb();
    ~mydb();

    //查询数据库
    int QuerySQL(string DbName,string sql);
    //执行SQL语句
    int ExcuteSQL(string DbName,string sql);
    //建表
    int EstablishTable(TableType tt);
    //插入数据
    int InsretData(string username, string password);
    //查询
    int SearchData();
    //删除数据
    int DeleteData(string username);
    //删除表
    int DeleteTable(string table);
    //获取当前日期
    int getCurrentDate(char* timeStr);

public:
    //将双色球数据插入数据库
    int InsertSSQData(string red,string blue, string oddeven, string m012, string mabc, int redsum);
    //将大乐透数据插入数据库
    int InsertDLTData(string red,string blue, string oddeven, string m012, string m12345, int redsum);
public:
    user m_user[100];
    string _dbname_;
    int count;

    char ssqTable[32];
    char dltTable[32];
    char currentData[32];
};


#endif // MYSQLITE_H_INCLUDED
