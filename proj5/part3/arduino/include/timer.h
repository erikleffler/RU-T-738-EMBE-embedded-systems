#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    Timer();
    void start(int frequ);
    void stop();
private:
    int frequency;
};

#endif // TIMER_H
