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
    int DeleteTable();
public:
    int InsertSSQData(string red,string blue, string oddeven, string m012, string mabc, int redsum);
    int InsertDLTData(string red,string blue, string oddeven, string m012, string m12345, int redsum);
public:
    user m_user[100];
    string _dbname_;
    int count;
};


#endif // MYSQLITE_H_INCLUDED
