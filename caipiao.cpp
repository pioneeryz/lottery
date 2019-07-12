#include "caipiao.h"
#include <iostream>
#include <time.h>
#include <string.h>
using namespace std;


yzcaipiao::yzcaipiao()
{
    cout << "初始化彩票程序中..."<<endl;
}

yzcaipiao::~yzcaipiao()
{

}

/**
 * @func  :初始化变量
 * @author:pioneeryz
 * @date  :2019/7/11
 */
void yzcaipiao::init(){

    memset(username,0,sizeof(username));
    memset(passwd,0,sizeof(passwd));
    _map_.insert(pair<string,string>("pioneer","123456"));
    _map_.insert(pair<string,string>("yanzhen","111111"));
    _map_.insert(pair<string,string>("viki","222222"));
    _map_.insert(pair<string,string>("root","123456"));
    _map_.insert(pair<string,string>("admin","123456"));
    _map_.insert(pair<string,string>("zzz","111111"));
}

/**
 * @func  :对已知数组从小到大排序
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :num[] --数组
 *         n     --大小
 */
void yzcaipiao::paixu(int num[],int n)
{
    int i,j,tmp;
	for(i = 0;i<n-1;i++)
	{
		for(j = i+1;j<n;j++)
		{
			if(num[i] > num[j])
			{
				tmp = num[i];
				num[i] = num[j];
				num[j] = tmp;
			}
		}
	}
}

/**
 * @func  :打印已知数组
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :num[] --数组
 *         n     --大小
 */
void yzcaipiao::displaySSQ(int num[],int n,int blue){
    for(int k=0;k<n;++k){
        printf(" %02d ",num[k]);
	}
	printf("(%02d)   ",blue);
}

/**
 * @func  :打印已知数组
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :red[] --红球数组
 *         n     --大小
 *         blue[]--篮球数组
 *         m     --大小
 */
void yzcaipiao::displayDLT(int red[], int n, int blue[], int m){
    for(int k = 0; k < n; ++k){
        printf(" %02d ", red[k]);
	}

	cout<<"(";
	for(int l = 0; l < m; ++l){
        printf(" %02d ",blue[l]);
	}
	cout<<")";
}

/**
 * @func  :判断当前数组是否有重数
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :num[] --数组
 *         n     --大小
 * @return:int   --非0 --有重复
 */
int yzcaipiao::deChong(int num[],int n){
    for(int i=0;i<n-1;++i){
        if(num[i+1] == num[i])
            return -1;
    }
    return 0;
}

/**
 * @func  :判断当前红球的奇偶，012路，小中大比
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :num[] --数组
 *         n     --大小
 */
void yzcaipiao::judge(int num[],int n)
{
    int oddNum = 0;     //奇数
    int evenNum = 0;    //偶数

    int num0 = 0;       //0路
    int num1 = 0;       //1路
    int num2 = 0;       //2路

    int smallNum = 0;   //1-11
    int middleNum = 0;  //2-22
    int bigNum = 0;     //3-33
    int sum = 0;        //红球和值

    for(int i = 0; i < n; ++i){

        //统计奇偶
        if(num[i]%2 == 0){
            evenNum++;
        }else{
            oddNum++;
        }

        //统计012路
        if(num[i]%3 == 0){
            num0++;
        }else if(num[i]%3 ==1){
            num1++;
        }else if(num[i]%3 ==2){
            num2++;
        }

        //统计小中大号
        if(num[i]>=1 && num[i]<=11){
            smallNum++;
        }
        if(num[i]>=12 && num[i]<=22){
            middleNum++;
        }
        if(num[i]>=23 && num[i]<=33){
            bigNum++;
        }
        sum += num[i];
    }
    printf(" %d:%d  %d:%d:%d  %d:%d:%d   %d\n\n",oddNum,evenNum,num0,num1,num2,smallNum,middleNum,bigNum,sum);
}

/**
 * @func  :双色球玩法
 * @author:pioneeryz
 * @date  :2019/7/10
 */
void yzcaipiao::shuangSeQiu(){
    int redNum[32]= {0};
    int blueNum = 0;
    int ret_val=-1;
    int input=0;
    printf("请输入随机注数:");
    scanf("%d",&input);
    cout <<endl<< "序号             选号              奇偶  012路  小中大  红和值"<<endl<<endl;
    for(int j = 0; j < input; ++j){
        for(int i = 0; i < 6; ++i)
        {
            redNum[i] = rand()%33+1;
        }
        blueNum = rand()%16 + 1;
        paixu(redNum,6);
        ret_val = deChong(redNum,6);
        if(ret_val != 0){
            j--;
            continue;
        }
        printf("%04d",j+1);
        displaySSQ(redNum,6,blueNum);
        judge(redNum,6);
    }

}

/**
 * @func  :大乐透玩法
 * @author:pioneeryz
 * @date  :2019/7/10
 */
void yzcaipiao::daLeTou(){
    int redNum[32] = {0};
    int blueNum[4] = {0};
    int ret_val=-1;
    int input=0;
    printf("请输入随机注数:");
    scanf("%d",&input);
    cout <<endl<< "序号             选号              奇偶  012路  小中大  红和值"<<endl<<endl;
    for(int j = 0; j < input; ++j){
        for(int i = 0; i < 5; ++i)
        {
            redNum[i] = rand()%35+1;
        }

        paixu(redNum,5);
        ret_val = deChong(redNum,6);
        if(ret_val != 0){
            j--;
            continue;
        }

        for(int k = 0; k < 2; ++k){
            blueNum[k] = rand()%12 + 1;
        }
        paixu(blueNum,2);
        ret_val = deChong(blueNum,2);
        if(ret_val != 0){
            j--;
            continue;
        }

        printf("%04d",j+1);
        displayDLT(redNum,5,blueNum,2);
        judge(redNum,5);
    }


}

/**
 * @func  :标题头打印
 * @author:pioneeryz
 * @date  :2019/7/10
 */
void yzcaipiao::displayTitle(){
    char time_temp[32] = {0};
    getTimeString(time_temp);
    cout << "**********************欢迎来到彩票世界***********************" << endl;
    cout << "****     *            "<<time_temp<<"        *       ****" << endl;
    cout << "****    * *           开发者：pioneer           * *      ****" << endl;
    cout << "****   *   *          双色球,大乐透玩法        *   *     ****" << endl;
    cout << "****    * *           6+1，5+2                  * *      ****" << endl;
    cout << "****     *            彩票模拟软件，仅供娱乐     *       ****" << endl;
    cout << "**********************500W大奖等着你*************************" << endl;
    cout << endl;
}

/**
 * @func  :登录认证
 * @author:pioneeryz
 * @date  :2019/7/10
 */
 void yzcaipiao::loginIn(){
    int count = 0;
    bool flag = false;
    while(1){
        cout << "请输入用户名:";
        cin >> username;
        cout << endl << "请输入密码:";
        cin >> passwd;
        map<string,string>::iterator it;

        for(it = _map_.begin(); it != _map_.end(); it++){
            if(string(username) == it->first && string(passwd) == it->second){
                flag = true;
                break;
            }
        }
        if(flag){
            cout << endl;
            cout << username <<"登录成功,开始你的旅行！" << endl;
            break;
        }else{
            cout << "您输入的用户名或密码错误!" << endl;
            count ++;
            if(count >= 3){
                cout << "连续三次输入错误,即将退出程序！" << endl;
                exit(0);
            }
            continue;
        }
    }
 }

 /**
 * @func  :退出登录
 * @author:pioneeryz
 * @date  :2019/7/11
 */
void  yzcaipiao::loginOut(){
    cout<<username<<"退出登录，欢迎下次再来"<<endl;
}

/**
 * @func  :获取当前格式化时间
 * @author:pioneeryz
 * @date  :2019/7/11
 */
int yzcaipiao::getTimeString(char* timeStr){
    time_t times = time(NULL);
    struct tm* utcTime = gmtime(&times);
    int timeStrLen = sprintf(timeStr, "%04d/%02d/%02d %02d:%02d:%02d", utcTime->tm_year+1900, utcTime->tm_mon+1, utcTime->tm_mday, utcTime->tm_hour+8, utcTime->tm_min, utcTime->tm_sec);
    return timeStrLen;
}
