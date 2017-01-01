
#ifndef EX4_CLOCK_H
#define EX4_CLOCK_H

/**
 * The class represents the Clock of the taxi center.
 * Used to determine the time of the trips.
 */
class Clock {

private:
    // The time of the clock
    unsigned int time;

public:

    /**
     * Constructor
     */
    Clock();

    /**
     * @brief increases the clock time by one.
     */
    void increaseTime();

    /**
     * @brief returns the time.
     * @return unsigned int
     */
    unsigned int getTime();
};

#endif //EX4_CLOCK_H
