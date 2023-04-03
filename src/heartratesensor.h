#ifndef HEARTRATESENSOR_H
#define HEARTRATESENSOR_H

#include <QVector>

class HeartRateSensor
{
public:
    HeartRateSensor();

    int getHeartRate(int);

private:
    QVector<float> data;
};

#endif // HEARTRATESENSOR_H
