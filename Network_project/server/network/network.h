#pragma once
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <string.h> 
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int InitSocket();

int InsertFdToEpoll(int epfd,int fd,uint32_t event);

int GetNewClient(int listenfd,int epfd);

int CloseClient(int fd,int epfd);

int SetOneShot(int epfd, int fd);