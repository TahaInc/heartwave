#include "heartratesensor.h"

HeartRateSensor::HeartRateSensor()
{
    for(int i = 0; i < 60; ++i) {
        data.push_back(60.0f);
        data.push_back(65.0f);
        data.push_back(70.0f);
        data.push_back(65.0f);
    }
}

int HeartRateSensor::getHeartRate(int time) {
    if (0 <= time && time < data.size()) {
        return data[time];
    }
    return -1;
}
