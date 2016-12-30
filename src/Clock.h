
#ifndef EX4_CLOCK_H
#define EX4_CLOCK_H

class Clock {

private:
    unsigned int time; // The time of the clock

public:
    Clock();
    void increaseTime(); // Increases the clock time by 1
    unsigned int getTime(); // Returns the time of the clock

};

#endif //EX4_CLOCK_H
