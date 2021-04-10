#include<pthread.h>
#include<semaphore.h>
#include<assert.h>

#include"../network/network.h"
#include"thread.h"
#include"../queue/queue.h"
#include"../io/io.h"

extern sem_t           sem;
extern Que             que;
extern pthread_mutex_t mutex;

void *work_thread(void *arg)
{
    while(1)
    {
        sem_wait(&sem);
        pthread_mutex_lock(&mutex);
        int fd = Pop(&que);
        pthread_mutex_unlock(&mutex);

        DealReadyEvent(fd);//io单元提供处理方法，处理就绪事件，即就是文件描述符上有数据到达
    }
}

int CreateThreadPool(int num)
{
    int i = 0;
    for(;i<num;i++)
    {
        pthread_t id;
        int res = pthread_create(&id,NULL,work_thread,NULL);
        assert(res == 0);
    }
}
