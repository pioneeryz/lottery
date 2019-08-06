#ifndef CAIPIAO_H_INCLUDED
#define CAIPIAO_H_INCLUDED
#include <iostream>
#include <map>
#include "mysqlite.h"
#include <pthread.h>
using namespace std;

typedef enum{
    ssq=0,
    dlt
}LotteryType;

class yzcaipiao{

public:
    //构造函数
    yzcaipiao();
    //析构函数
    ~yzcaipiao();
    //初始化
    void init();
    //排序
    void paixu(int num[],int n);
    //打印双色球
    void displaySSQ(int num[],int n,int blue);
    //打印大乐透
    void displayDLT(int red[], int n, int blue[], int m);
    //排重
    int  deChong(int num[],int n);
    //计算
    void judge(int num[],int n, LotteryType type);
    //双色球玩法
    void shuangSeQiu();
    //大乐透玩法
    void daLeTou();
    //打印标题
    void displayTitle();
    //获取当前格式化时间
    int getTimeString(char* timeStr);
    //用户密码登录
    int  userOn();
    //增加用户
    int  addUser();
    //删除用户
    int  deleteUser();
    //查询用户
    int  queryUser();
    //初始登录界面
    void  loginIn();
    //退出
    void loginOut();

private:
    map<string,string> _map_;
    char username[32];
    char passwd[32];
    mydb _mydb_;
    //数据库锁
    pthread_mutex_t dblock;

private:
    //选号(红球)
    string seqNumber;
    //篮球
    string blueNumber;
    //奇偶比
    string oddEven;
    //012路比
    string m_012;
    //小中大
    string m_abc;
    //五区比
    string m_12345;
    //红和值
    int redSum;

    char constNumber[128];
};

#endif // CAIPIAO_H_INCLUDED
