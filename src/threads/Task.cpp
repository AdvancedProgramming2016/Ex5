
#include "Task.h"

Task::Task(void *(*func)(void *), void *arg) : func(func), arg(arg),
                                               finished(false) {

}

void Task::execute() {

    func(arg);
}

bool Task::isFinished() {

    return this->finished;
}

void Task::setFinished() {

    this->finished = true;
}
