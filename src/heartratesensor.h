#ifndef HEARTRATESENSOR_H
#define HEARTRATESENSOR_H

#include <QVector>
#include <ctime>
#include <QDebug>

class HeartRateSensor
{
public:
    HeartRateSensor();

    int getHeartRate(int);

private:
    QVector<int> data;
};

#endif // HEARTRATESENSOR_H
