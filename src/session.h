#ifndef SESSION_H
#define SESSION_H

#include "qcustomplot.h"
#include <QVector>
#include <QtMath>

class Session
{
public:
    Session();

    inline void addHeartRate(int hr) { hrData.push_back(hr); }
    void plotCurrentData(QCustomPlot *);
    void plotAllData(QCustomPlot *);
    float getAchievement();
    float calculateCoherence();

private:
    QVector<int> hrData;
    QVector<float> coherenceScores;
};

#endif // SESSION_H
