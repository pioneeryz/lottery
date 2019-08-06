#include "caipiao.h"
#include <iostream>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <windows.h>
using namespace std;


yzcaipiao::yzcaipiao()
{
    cout << "初始化彩票程序中..." << endl;
    _mydb_.EstablishTable(userTable);
    _mydb_.EstablishTable(ssqTable);
    _mydb_.EstablishTable(dltTable);
    _mydb_.SearchData();
    //pthread_mutex_init(&dblock, NULL);
}

yzcaipiao::~yzcaipiao()
{
    cout << "退出彩票程序中..." << endl;
    //pthread_mutex_destroy(&dblock);
}

/**
 * @func  :初始化变量
 * @author:pioneeryz
 * @date  :2019/7/11
 */
void yzcaipiao::init(){

    memset(username,0,sizeof(username));
    memset(passwd,0,sizeof(passwd));
    memset(constNumber,0,sizeof(constNumber));
    for(int j = 0; j < 105; ++j){
        constNumber[j] = j;
    }
    //可以考虑放进数据库中，增删改查
    /*
    _map_.insert(pair<string,string>("pioneer","123456"));
    _map_.insert(pair<string,string>("yanzhen","111111"));
    _map_.insert(pair<string,string>("viki","222222"));
    _map_.insert(pair<string,string>("root","123456"));
    _map_.insert(pair<string,string>("admin","123456"));
    _map_.insert(pair<string,string>("zzz","111111"));
    _map_.insert(pair<string,string>("zyq","123456"));
    */
    for(int i = 0; i<_mydb_.count;i++)
    {
        _map_.insert(pair<string,string>(_mydb_.m_user[i].UserName,_mydb_.m_user[i].PassWd));
    }
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
    char redtemp[32] = {0};
    char bluetemp[8] = {0};
    for(int k=0;k<n;++k){
        printf(" %02d ",num[k]);
	}
	printf("(%02d)   ",blue);
	sprintf(redtemp,"%02d %02d %02d %02d %02d %02d",num[0],num[1],num[2],num[3],num[4],num[5]);
	seqNumber = string(redtemp);
    sprintf(bluetemp,"%02d",blue);
    blueNumber = string(bluetemp);
	//cout <<"seqNumber :"<<seqNumber<<endl;
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
    char redtemp[32] = {0};
    char bluetemp[8] = {0};
    for(int k = 0; k < n; ++k){
        printf(" %02d ", red[k]);
	}

	cout<<"(";
	for(int l = 0; l < m; ++l){
        printf(" %02d ",blue[l]);
	}
	cout<<")";
    sprintf(redtemp,"%02d %02d %02d %02d %02d",red[0],red[1],red[2],red[3],red[4]);
	seqNumber = string(redtemp);
    sprintf(bluetemp,"%02d %02d",blue[0],blue[1]);
    blueNumber = string(bluetemp);
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
void yzcaipiao::judge(int num[],int n,LotteryType type)
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

    int range1 = 0;
    int range2 = 0;
    int range3 = 0;
    int range4 = 0;
    int range5 = 0;

    char oddEven_temp[32] = {0};
    char m_012_temp[32] = {0};
    char m_abc_temp[32] = {0};
    char m_12345_temp[32] = {0};
    char redSum_temp[16] = {0};

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
        else if(num[i]>=12 && num[i]<=22){
            middleNum++;
        }
        else if(num[i]>=23 && num[i]<=33){
            bigNum++;
        }

        //统计五区
        if(num[i]>=1 && num[i]<=7){
            range1++;
        }
        else if(num[i]>=8 && num[i]<=14){
            range2++;
        }
        else if(num[i]>=15 && num[i]<=21){
            range3++;
        }
        else if(num[i]>=22 && num[i]<=28){
            range4++;
        }
        else if(num[i]>=29 && num[i]<=35){
            range5++;
        }

        sum += num[i];
    }
    sprintf(oddEven_temp,"%d:%d",oddNum,evenNum);
    sprintf(m_012_temp,"%d:%d:%d",num0,num1,num2);
    redSum = sum;
    oddEven = string(oddEven_temp);
    m_012 = string(m_012_temp);
    switch(type)
    {
    case ssq:
        printf(" %d:%d  %d:%d:%d  %d:%d:%d   %d\n\n",oddNum,evenNum,num0,num1,num2,smallNum,middleNum,bigNum,sum);
        sprintf(m_abc_temp,"%d:%d:%d",smallNum,middleNum,bigNum);
        m_abc = string(m_abc_temp);
        break;
    case dlt:
        printf(" %d:%d   %d:%d:%d  %d:%d:%d:%d:%d   %d\n\n",oddNum,evenNum,num0,num1,num2,range1,range2,range3,range4,range5,sum);
        sprintf(m_12345_temp,"%d:%d:%d:%d:%d",range1,range2,range3,range4,range5);
        m_12345 = string(m_12345_temp);
        break;
    default:
        break;
    }
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
    int m_random = 0;
    printf("请输入随机注数:");
    scanf("%d",&input);
    cout <<endl<< "序号             选号              奇偶  012路  小中大  红和值"<<endl<<endl;
    for(int j = 0; j < input; ++j){
        //pthread_mutex_lock(&dblock);
        /*1.直接随机数赋值
        for(int i = 0; i < 6; ++i)
        {
            redNum[i] = rand()%33+1;
        }
        */
        for(int i = 0; i < 6; ++i)
        {
            m_random = rand()%98;
            redNum[i] = constNumber[m_random]%33 + 1;
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
        judge(redNum,6,ssq);
        _mydb_.InsertSSQData(seqNumber,blueNumber,oddEven,m_012,m_abc,redSum);

        Sleep(10);//200ms
        //pthread_mutex_unlock(&dblock);
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
    int ret_val = -1;
    int input = 0;
    int m_random = 0;
    printf("请输入随机注数:");
    scanf("%d",&input);
    cout <<endl<< "序号             选号              奇偶  012路  五区比      红和值"<<endl<<endl;
    for(int j = 0; j < input; ++j){
        /*
        for(int i = 0; i < 5; ++i)
        {
            redNum[i] = rand()%35+1;
        }
        */
        for(int i = 0; i < 5; ++i)
        {
            m_random = rand()%104;
            redNum[i] = constNumber[m_random]%35 + 1;
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
        judge(redNum,5,dlt);
        _mydb_.InsertDLTData(seqNumber,blueNumber,oddEven,m_012,m_12345,redSum);
        //Sleep(1);
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

int yzcaipiao::userOn(){
    bool flag = false;
    int count = 0;
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
            return 0;
        }else{
            cout << "您输入的用户名或密码错误!" << endl;
            count ++;
            if(count >= 3){
                cout << "连续三次输入错误,即将退出程序！" << endl;
                exit(0);
                return -1;
            }
            continue;
        }
    }
}

int  yzcaipiao::addUser(){
    string adminPass = "";
    string name = "";
    string pass = "";
    cout << "请输入管理员密码执行操作:";
    cin >> adminPass;
    if(adminPass != "038813"){
        return -1;
    }
    cout << "请输入增加的用户名:";
    cin >> name;
    cout << endl;
    cout << "请输入用户名的密码:";
    cin >> pass;
    cout << endl;

    map<string,string>::iterator it;

    for(it = _map_.begin(); it != _map_.end(); it++){
        if(string(name) == it->first){
            cout << "该用户已经存在." << endl;
            return -1;
        }
    }
    int ret_val = _mydb_.InsretData(name,pass);
    if(!ret_val){
        _map_.clear();
        _mydb_.SearchData();
        for(int i = 0; i<_mydb_.count;i++)
        {
            _map_.insert(pair<string,string>(_mydb_.m_user[i].UserName,_mydb_.m_user[i].PassWd));
        }
    }
    return ret_val;
}

int  yzcaipiao::deleteUser()
{
    int ret_val = -1;
    string name ="";
    string pass ="";
    cout << "请输入要删除的用户的名字:";
    cin >> name;
    cout << "请输入管理员密码:";
    cin >> pass;
    if(pass == "038813"){
        ret_val = _mydb_.DeleteData(name);
        if(!ret_val){
            _map_.clear();
            _mydb_.SearchData();
            for(int i = 0; i<_mydb_.count;i++)
            {
                _map_.insert(pair<string,string>(_mydb_.m_user[i].UserName,_mydb_.m_user[i].PassWd));
            }
        }
    }else{
        cout << "管理员密码错误，无法删除该用户"<<endl;
    }
    return ret_val;
}

/**
 * @func  :登录认证
 * @author:pioneeryz
 * @date  :2019/8/2
 */
int  yzcaipiao::queryUser(){
    string pass ="";
    cout << "请输入管理员密码:";
    cin >> pass;
    if(pass != "038813"){
        cout << "密码错误."<<endl;
        return -1;
    }
    cout << "----------------"<<endl;

    for(int i = 0; i < 100; i++){
        if(string(_mydb_.m_user[i].UserName) != "")
        cout << _mydb_.m_user[i].UserName << ":"<<_mydb_.m_user[i].PassWd<<endl;
    }
    cout << "----------------"<<endl;
    return 0;
}
/**
 * @func  :登录认证
 * @author:pioneeryz
 * @date  :2019/7/10
 */
 void yzcaipiao::loginIn(){
    int ret_val = -1;
    int count = 0;
    bool flag = false;
    int input;
    while(1){
        cout << "请选择要执行的操作(提示:(1.用户登录 2.增加用户 3.删除用户 4.查询当前用户)"<<endl;
        cin >> input;
        switch(input){
        case 1:
            ret_val=userOn();
            if(ret_val == 0)
                return;
            break;
        case 2:
            addUser();
            break;
        case 3:
            deleteUser();
            break;
        case 4:
            queryUser();
            break;

        default:
            break;
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
