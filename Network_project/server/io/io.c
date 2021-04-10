#include"io.h"
#include"../../public.h"
#include"../logic/user/user.h"

#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>



void DealReadyEvent(int fd)
{
    int option;
    recv(fd,&option,4,0);

    switch (option)
    {
    case LOGIN://登录
    {
      UserInfo user;
      recv(fd,&user,sizeof(user),0);
       
        break;
    }
    case SIGIN://注册
    {
      UserInfo user;
      recv(fd,&user,sizeof(user),0);
        break;
    }

    default:
        break;
    }
}