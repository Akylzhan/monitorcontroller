#ifndef CAFFEINE_H
#define CAFFEINE_H

class Caffeine
{
public:
    Caffeine();
    ~Caffeine();

    void startDrinking();
    void stopDrinking();

    bool keepDisplayOn = true;
    bool isDrinking = false;
};

#endif // CAFFEINE_H
