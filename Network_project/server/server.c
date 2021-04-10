#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<sys/epoll.h>
#include<semaphore.h>
#include<pthread.h>

#include"network/network.h"
#include"thread/thread.h"
#include"queue/queue.h"
#include"../public.h"
#include"database/database.h"

#define MAXEVENTS 100

sem_t sem; //主线程与工作线程同步的信号量
Que que;
pthread_mutex_t mutex;

MYSQL conn;

int main()
{
    MYSQL *p = LinkDataBase();//数据库链接
    assert(p != NULL);

    int listenfd = InitSocket();//初始化网络
    assert(listenfd != -1);

    int epfd = epoll_create(5);
    assert(epfd != -1);

    int res = InsertFdToEpoll(epfd,listenfd,EPOLLIN);//初始化epoll
    assert(res != -1);

    sem_init(&sem,0,0);
    InitQue(&que);
    pthread_mutex_init(&mutex,NULL);

    res = CreateThreadPool(5);//初始化线程池
    assert(res != -1);

    while(1)
    {
        struct epoll_event events[MAXEVENTS];
        int n = epoll_wait(epfd,events,MAXEVENTS,-1);
        if(n <= 0) continue;

        int i = 0;
        for(;i < n;++i)
        {
            int fd = events[i].data.fd;
            if(fd == listenfd)//新的客户端链接到达
            {
                GetNewClient(listenfd,epfd);
            }
            else
            {
                if(events[i].events & EPOLLRDHUP)
                {
                    CloseClient(fd,epfd);
                }
                else
                {
                    pthread_mutex_lock(&mutex);
                    Push(&que,fd);
                    pthread_mutex_unlock(&mutex);
                    sem_post(&sem);
                }
                
            }
            
        }

    }

    /* struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listenfd;

    int res = epoll_ctl();*/

    sem_destroy(&sem);
    pthread_mutex_destroy(&mutex);//释放锁
    Destroy(&que);//清空队列
    UnLinkDataBase();
    exit(0);
}