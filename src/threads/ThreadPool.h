
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

public:

    /*
     * Constructor.
     */
    ThreadPool(int threads_num);

    /*
     * Executes the tasks.
     */
    void executeTasks();

    /*
     * Adds a new task to the queue.
     */
    void addTask(Task *job);

    /*
     * Stops the thread pool.
     */
    void terminate();

    /*
     * Destructor.
     */
    virtual ~ThreadPool();
};


#endif //EX4_THREADPOOL_H
