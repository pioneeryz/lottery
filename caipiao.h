#ifndef CAIPIAO_H_INCLUDED
#define CAIPIAO_H_INCLUDED
#include <iostream>
#include <map>
using namespace std;
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
    void judge(int num[],int n);
    //双色球玩法
    void shuangSeQiu();
    //大乐透玩法
    void daLeTou();
    //打印标题
    void displayTitle();
    //获取当前格式化时间
    int getTimeString(char* timeStr);
    //管理员密码登录
    void  loginIn();
    //退出
    void loginOut();

private:
    map<string,string> _map_;
    char username[32];
    char passwd[32];

};

#endif // CAIPIAO_H_INCLUDED
