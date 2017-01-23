
#include "ThreadPool.h"
#include <unistd.h>
#include <iostream>
#include <boost/log/trivial.hpp>

static void *startTasks(void *arg) {

    ThreadPool *pool = (ThreadPool *) arg;
    pool->executeTasks();

    return NULL;
}

ThreadPool::ThreadPool(int threads_num) : threads_num(threads_num),
                                          stop(false), taskCounter(0) {

    pthread_mutex_init(&this->taskCounterMutex, NULL);
    threads = new pthread_t[threads_num];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < threads_num; i++) {

        pthread_create(threads + i, NULL, startTasks, this);
    }
}

ThreadPool::~ThreadPool() {

    delete[] threads;
    pthread_mutex_destroy(&this->lock);
    pthread_mutex_destroy(&this->taskCounterMutex);
}

void ThreadPool::executeTasks() {

    while (!stop) {

        pthread_mutex_lock(&lock);

        if (!tasksQueue.empty()) {

            Task *task = tasksQueue.front();
            tasksQueue.pop();
            pthread_mutex_unlock(&lock);
            BOOST_LOG_TRIVIAL(trace) << "Executing task";
            task->execute();
            task->setFinished();
            BOOST_LOG_TRIVIAL(trace) << "Set as finished";

        } else {

            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }

    pthread_exit(NULL);
}

void ThreadPool::addTask(Task *task) {

    tasksQueue.push(task);
    this->taskCounter++;
}

void ThreadPool::terminate() {

    stop = true;
}

bool ThreadPool::isEmpty() {

}

pthread_mutex_t &ThreadPool::getTaskCounterMutex() {
    return taskCounterMutex;
}

void ThreadPool::decreaseTaskCounter() {
    this->taskCounter--;
}

/*
void ThreadPool::waitForThreads() {

    BOOST_LOG_TRIVIAL(info) << "Waiting for trips to finish calculating";
    bool finished = false;

    while(!finished){

        if(this->taskCounter == 0){
            finished = true;
        }
    }
}
 */
