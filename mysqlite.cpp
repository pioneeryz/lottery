#include "mysqlite.h"
#include <time.h>
#include <string.h>
//构造函数
mydb::mydb()
{
    _dbname_ = "caipiao.db";
    memset(currentData,0,sizeof(currentData));
    getCurrentDate(currentData);
    count = 0;
}

//析构函数
mydb::~mydb()
{

}

/**
 * @func  :查询数据库
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :Dbname --数据库名字
 *         sql    --要执行的sql语句
 */
int mydb::QuerySQL(string DbName,string sql)
{
   sqlite3 *db;
   char *errmsg=NULL;
   char **dbResult; //是 char ** 类型，两个*号
   int nRow, nColumn;
   int rc;
   int index;
   rc = sqlite3_open((const char *)DbName.c_str(), &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return -1;
   }else{
      //fprintf(stderr, "Opened database successfully\n");
   }
   rc=sqlite3_get_table(db,sql.c_str(),&dbResult, &nRow, &nColumn, &errmsg);
   if(rc==0){
        index=nColumn;
        //printf("查询到%d条记录\n",nRow);
        count=nRow;
        for(int i=0;i<nRow;i++){
            //printf("第%d条记录\n",i+1);
            for(int j=0;j<nColumn;j++){
                //printf("%s = %s\n",dbResult[j],dbResult[index]);
                if(j==0){
                    m_user[i].UserName=dbResult[index];
                }
                if(j==1){
                    m_user[i].PassWd=dbResult[index];
                }
                ++index;
            }
            //printf("----------\n");
        }
   }else{
       printf("查询失败...\n");
   }
   sqlite3_free_table(dbResult);
   sqlite3_close(db);
   return 0;
}

/**
 * @func  :执行SQL语句
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :Dbname --数据库名字
 *         sql    --要执行的sql语句
 */
int mydb::ExcuteSQL(string DbName,string sql)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   char **dbResult; //是 char ** 类型，两个*号
   int nRow, nColumn;

   int rc;
   int index;
   rc = sqlite3_open((const char *)DbName.c_str(), &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return -1;
   }else{
      //fprintf(stderr, "Opened database successfully\n");
   }

   rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      //fprintf(stdout, "SQL successfully\n");
   }
   sqlite3_close(db);
   return 0;
}

/**
 * @func  :建表
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :Dbname --数据库名字
 *         sql    --要执行的sql语句
 */
int mydb::EstablishTable(TableType tt)
{
    string sql = "";
    char sql_tmp[1024]={0};
    switch(tt){
    case 0:
        sql = "CREATE TABLE user("  \
              "UserName  TEXT   NOT NULL," \
              "PassWd    TEXT   NOT NULL);";
          break;
    case 1:

        sql = "CREATE TABLE ssq%s("  \
              "SEQ_NUMBER  TEXT   NOT NULL," \
              "BLUE  TEXT   NOT NULL," \
              "ODD_EVEN  TEXT   NOT NULL," \
              "M_012  TEXT   NOT NULL," \
              "M_ABC  TEXT   NOT NULL," \
              "RED_SUM   INT   NOT NULL);";
          sprintf(sql_tmp,sql.c_str(),currentData);
          sql = string(sql_tmp);
          break;

    case 2:
          sql = "CREATE TABLE dlt%s("  \
                "SEQ_NUMBER  TEXT   NOT NULL," \
                "BLUE  TEXT   NOT NULL," \
                "ODD_EVEN  TEXT   NOT NULL," \
                "M_012  TEXT   NOT NULL," \
                "M_12345 TEXT   NOT NULL," \
                "RED_SUM   INT   NOT NULL);";
          sprintf(sql_tmp,sql.c_str(),currentData);
          sql = string(sql_tmp);
          break;
    default:
        break;
    }
    ExcuteSQL(_dbname_,sql);
    return 0;
}

/**
 * @func  :插入数据
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :Dbname --数据库名字
 *         sql    --要执行的sql语句
 */
int mydb::InsretData(string username, string password)
{
    char sql_tmp[1024]={0};
    string sql = "INSERT INTO user(UserName,PassWd) " \
                 "VALUES ('%s','%s');";
    sprintf(sql_tmp,sql.c_str(),username.c_str(),password.c_str());
    //cout<<"sql_tmp:"<<sql_tmp<<endl;
    sql=string(sql_tmp);
    int ret_val = ExcuteSQL(_dbname_,sql);
    return ret_val;
}

/**
 * @func  :插入数据
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :red     --红球
 *         blue    --篮球
 *         oddeven --奇偶比
 *         m012    --012路
 *         mabc    --小中大
 *         redsum  --红球和
 */
int mydb::InsertSSQData(string red, string blue,string oddeven, string m012, string mabc, int redsum)
{
    char sql_tmp[1024]={0};
    string sql = "INSERT INTO ssq%s(SEQ_NUMBER,BLUE,ODD_EVEN,M_012,M_ABC,RED_SUM) " \
                 "VALUES ('%s','%s','%s','%s','%s','%d');";
    sprintf(sql_tmp,sql.c_str(),currentData,red.c_str(),blue.c_str(),oddeven.c_str(),m012.c_str(),mabc.c_str(),redsum);
    //cout<<"sql_tmp:"<<sql_tmp<<endl;
    sql=string(sql_tmp);
    int ret_val = ExcuteSQL(_dbname_,sql);
    return ret_val;

}

/**
 * @func  :插入数据
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :red     --红球
 *         blue    --篮球
 *         oddeven --奇偶比
 *         m012    --012路
 *         m12345  --12345区
 *         redsum  --红球和
 */
int mydb::InsertDLTData(string red,string blue, string oddeven, string m012, string m12345, int redsum)
{
    char sql_tmp[1024]={0};
    string sql = "INSERT INTO dlt%s(SEQ_NUMBER,BLUE,ODD_EVEN,M_012,M_12345,RED_SUM) " \
                 "VALUES ('%s','%s','%s','%s','%s','%d');";
    sprintf(sql_tmp,sql.c_str(),currentData,red.c_str(),blue.c_str(),oddeven.c_str(),m012.c_str(),m12345.c_str(),redsum);
    //cout<<"sql_tmp:"<<sql_tmp<<endl;
    sql=string(sql_tmp);
    int ret_val = ExcuteSQL(_dbname_,sql);
    return ret_val;
}

/**
 * @func  :查询
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :Dbname --数据库名字
 *         sql    --要执行的sql语句
 */
int mydb::SearchData()
{
    string sql = "select * from user;";
    QuerySQL(_dbname_,sql);
    return 0;
}

/**
 * @func  :删除数据
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :Dbname --数据库名字
 *         sql    --要执行的sql语句
 */
int mydb::DeleteData(string username)
{
    char sql_tmp[1024]={0};
    string sql = "delete from user where Username = \'%s\';";
    sprintf(sql_tmp,sql.c_str(),username.c_str());
    cout<<"sql_tmp:"<<sql_tmp<<endl;
    sql=string(sql_tmp);
    int ret_val = ExcuteSQL(_dbname_,sql);
    return ret_val;
}

/**
 * @func  :删除表
 * @author:pioneeryz
 * @date  :2019/7/10
 * @param :Dbname --数据库名字
 *         sql    --要执行的sql语句
 */
int mydb::DeleteTable()
{


}

/**
 * @func  :获取当前格式化日期
 * @author:pioneeryz
 * @date  :2019/7/11
 */
int mydb::getCurrentDate(char* timeStr){
    time_t times = time(NULL);
    struct tm* utcTime = gmtime(&times);
    int timeStrLen = sprintf(timeStr, "%04d%02d%02d", utcTime->tm_year+1900, utcTime->tm_mon+1, utcTime->tm_mday);
    return timeStrLen;
}
