#pragma once

typedef struct User
{
    char name[20];
    char passwd[20];
}UserInfo;

#include<../../../usr/local/mysql/include/mysql.h>

#define SIGIN 1//注册
#define LOGIN 2//登录

#define ERR_NOUSER 100//服务器上找不到名字
#define ERR_PASSWD 101//密码错误
#define ERR_USEREXISTS  150//用户已存在
#define ERR_UPDATA 102//插入失败，更新失败

#define SUCCESS    200//成功
