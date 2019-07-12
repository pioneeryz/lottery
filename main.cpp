#include <iostream>
#include <time.h>
#include "caipiao.h"
using namespace std;

/**
 * @fun   :主测试程序
 * @author:pioneeryz
 * @date  :2019/7/10
 */
int main()
{
    yzcaipiao yz;
    int caipiao_type_=0;
    yz.init();
    loop:yz.loginIn();
    while(1){
        srand(time(NULL));
        yz.displayTitle();
        cout << "请选择玩法(提示:1(双色球玩法),2(大乐透玩法),3(退出当前用户),4(结束程序):" << endl;
        scanf("%d",&caipiao_type_);
        switch(caipiao_type_){
        case 1:
            yz.shuangSeQiu();
            break;
        case 2:
            yz.daLeTou();
            break;
        case 3:
            yz.loginOut();
            goto loop;
            break;
        case 4:
            exit(0);
            break;
        default:
            cout << "选择的彩种不存在，请重新选择!" << endl;
            break;
        }
    }
    return 0;
}
