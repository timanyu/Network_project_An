#include"user.h"
#include"../../database/database.h"

#include<string.h>
#include<stdio.h>

int Login(UserInfo* user)
{
    //user->name;
    //user->passwd;
    char sql[128] = {0};
    sprintf(sql,"select passwd from user where 'name'=%s", user->name);
    MYSQL_RES *res = Query(sql);
    //获得结果集的行数
    int rows = GetRows(res);//获得个数
    if(res == 0)//没内容处理
    {
        FreeRes(res);
        return ERR_NOUSER;
    }

    MYSQL_ROW row = GetRow(res);//获得行数
    if(strcmp(row[0],user->passwd) != 0)
    {
        FreeRes(res);
        return ERR_PASSWD;
    }
    FreeRes(res);
    return SUCCESS;

}

int Signin(UserInfo* user)
{
    char sql[128] = {0};
    sprintf(sql,"select passwd from user where 'name'=%s", user->name);
    MYSQL_RES *res = Query(sql);
    //获得结果集的行数
    int rows = GetRows(res);//获得个数

    FreeRes(res);

    if(rows != 0)//判断有没有东西
    { 
        return ERR_USEREXISTS;
    }

    memset(sql,0,128);
    sprintf(sql,"insert into user values(%s,%s)",user->name,user->passwd);
    if(0 != UpData(sql))
    {
        return ERR_UPDATA;
    }

    return SUCCESS;


}