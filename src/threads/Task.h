
#ifndef EX4_TASK_H
#define EX4_TASK_H

/**
 * The class represents a task which will be executed in the pool thread.
 */
class Task {

private:

    void *arg;

    void *(*func)(void *arg);

public:

    Task(void *(*func)(void *arg), void *arg);

    void execute();

    virtual ~Task();

};


#endif //EX4_TASK_H
