
#ifndef EX4_THREADPOOL_H
#define EX4_THREADPOOL_H

#include "Task.h"
#include <queue>
#include <pthread.h>

/*
 * The class implements the thread pool pattern.
 * Executes given tasks.
 */
class ThreadPool {

private:

    std::queue<Task *> tasksQueue;
    int                threads_num;
    pthread_t          *threads;
    bool               stop;
    pthread_mutex_t    lock;
    unsigned int       taskCounter;
    pthread_mutex_t    taskCounterMutex;

public:

    ThreadPool(int threads_num);

    void executeTasks();

    void addTask(Task *job);

    void terminate();

    bool isEmpty();

    pthread_mutex_t &getTaskCounterMutex();

    void decreaseTaskCounter();

   // void waitForThreads();

    virtual ~ThreadPool();
};


#endif //EX4_THREADPOOL_H
