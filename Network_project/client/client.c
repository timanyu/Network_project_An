#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<assert.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#include"user/user.h"

int main()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    assert(sockfd != -1);

    struct sockaddr_in ser_addr;
    memset(&ser_addr,0,sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(6500);
    ser_addr.sin_addr.s_addr = inet_addr("192.168.150.128");

    int res = connect(sockfd,(struct sockaddr*)&ser_addr,sizeof(ser_addr));
    assert(res != -1);

    while(1)
    {
        ShowPage();
        int option;
        scanf("%d",&option);

        switch (option)
        {
        case 0:
            close(sockfd);
            exit(0);
            break;
            
        case 1:
            if(Signin(sockfd))
            {
                Login(sockfd);
                printf("登录失败，请重新选择\n");
            }
            else
            {
                printf("注册失败，请重新选择\n");
            }
            break;
            
        case 2:
            Login(sockfd);
            printf("登录失败，请重新选择\n");
            break;
        
        default:
            printf("选择错误，请重新选择\n");
            break;
        }
    }
}