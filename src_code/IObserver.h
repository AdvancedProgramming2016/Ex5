
#ifndef EX2_IOBSERVER_H
#define EX2_IOBSERVER_H

/**
 * Observer interface, notifies the subject about an update that is made.
 */
class Taxi;

class IObserver {

public:
    /*
     * Sends update to the subject
     */
    virtual void update(Taxi *taxi) = 0;
};

#endif //EX2_IOBSERVER_H
