#include "mysqlite.h"

mydb::mydb()
{
    _dbname_ = "caipiao.db";
    count = 0;
}
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
      fprintf(stderr, "Opened database successfully\n");
   }
   rc=sqlite3_get_table(db,sql.c_str(),&dbResult, &nRow, &nColumn, &errmsg);
   if(rc==0){
        index=nColumn;
        printf("查询到%d条记录\n",nRow);
        count=nRow;
        for(int i=0;i<nRow;i++){
            printf("第%d条记录\n",i+1);
            for(int j=0;j<nColumn;j++){
                printf("%s = %s\n",dbResult[j],dbResult[index]);
                if(j==0){
                    m_user[i].UserName=dbResult[index];
                }
                if(j==1){
                    m_user[i].PassWd=dbResult[index];
                }
                ++index;
            }
            printf("----------\n");
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
      fprintf(stdout, "SQL successfully\n");
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
int mydb::EstablishTable()
{
    string sql = "";
    sql = "CREATE TABLE user("  \
          "UserName  TEXT   NOT NULL," \
          "PassWd    TEXT   NOT NULL);";
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
                 "VALUES (\'%s'\,\'%s\');";
    sprintf(sql_tmp,sql.c_str(),username.c_str(),password.c_str());
    cout<<"sql_tmp:"<<sql_tmp<<endl;
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
