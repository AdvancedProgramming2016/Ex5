
#include "ThreadPool.h"
#include <unistd.h>
#include <iostream>
//#include <boost/log/trivial.hpp>

static void *startTasks(void *arg) {

    ThreadPool *pool = (ThreadPool *) arg;
    pool->executeTasks();

    return NULL;
}

ThreadPool::ThreadPool(int threads_num) : threads_num(threads_num),
                                          stop(false) {

    threads = new pthread_t[threads_num];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < threads_num; i++) {

        pthread_create(threads + i, NULL, startTasks, this);
    }
}

ThreadPool::~ThreadPool() {

    delete[] threads;
    pthread_mutex_destroy(&this->lock);
}

void ThreadPool::executeTasks() {

    while (!stop) {

        pthread_mutex_lock(&lock);

        if (!tasksQueue.empty()) {

            Task *task = tasksQueue.front();
            tasksQueue.pop();
            pthread_mutex_unlock(&lock);
           // BOOST_LOG_TRIVIAL(trace) << "Executing task";
            task->execute();

        } else {

            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }

    pthread_exit(NULL);
}

void ThreadPool::addTask(Task *task) {

    tasksQueue.push(task);
}

void ThreadPool::terminate() {

    stop = true;
}
