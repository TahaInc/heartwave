#ifndef HEARTRATESENSOR_H
#define HEARTRATESENSOR_H

#include <QVector>
#include <ctime>

class HeartRateSensor
{
public:
    HeartRateSensor(int ds=-1);

    int getHeartRate(int);

private:
    QVector<int> data;
};

#endif // HEARTRATESENSOR_H
