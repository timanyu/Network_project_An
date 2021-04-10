#include"../../public.h"
#include"user.h"
#include<stdio.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#define SIGIN 1

void ShowPage()
{
    printf("*************************************************\n");
    printf("*********    0         退出             *********\n");
    printf("*********    1         注册             *********\n");
    printf("*********    2         登录             *********\n");
    printf("*************************************************\n");
}

static UserInfo GetUserInfo()
{
    UserInfo user;
    memset(&user,0,sizeof(user));
    printf("请输入用户名\n");
    fgets(user.name,20,stdin);
    user.name[strlen(user.name)-1] = 0;
    printf("请输入用户密码\n");
    fgets(user.passwd,20,stdin);
    user.passwd[strlen(user.passwd)-1] = 0;

    return user;
}

//简单的用户协议：每次发送用户数据之前，需要在前面加上4个字节的选项部分
int Login(int sockfd)
{
    UserInfo user_info = GetUserInfo();

    int option = SIGIN;
    send(sockfd,&option,4,0);

    send(sockfd,&user_info,sizeof(user_info),0);

    int res = 0;
    recv(sockfd,&res,4,0);

    switch (res)
    {
    case ERR_NOUSER:
        printf("没有该用户\n");
        return 0;
    case ERR_PASSWD:
        printf("密码不正确\n");
        return 0;

    default:
        break;
    }
    //进入主业务界面
    printf("%s 登录成功了\n",user_info.name);
    return 1;
}

int Signin(int sockfd)
{
    UserInfo user_info = GetUserInfo();

    int option = SIGIN;
    send(sockfd,&option,4,0);

    send(sockfd,&user_info,sizeof(user_info),0);

    int res = 0;
    recv(sockfd,&res,4,0);

    switch(res)
    {
    case ERR_USEREXISTS:
        printf("%s已存在\n",user_info.name);
        return 0;
    case ERR_UPDATA:
        printf("插入失败\n");
        return 0;
    }
    printf("注册成功，请登录\n");
    return 1;
}