
#include "Clock.h"

Clock::Clock() {

    this->time = 0;

}

unsigned int Clock::getTime() {

    return this->time;

}

void Clock::increaseTime() {

    ++this->time;

}
