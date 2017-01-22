
#include "Task.h"

Task::Task(void *(*func)(void *), void *arg) : func(func), arg(arg) {

}

void Task::execute() {

    func(arg);
}

Task::~Task() {

}
