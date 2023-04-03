#ifndef SESSION_H
#define SESSION_H

#include "qcustomplot.h"
#include <QVector>

class Session
{
public:
    Session();

    inline void addHeartRate(float hr) { hrData.push_back(hr); }
    void plotCurrentData(QCPGraph *);
    void plotAllData(QCPGraph *);
    inline float getLastCoherenceScore() { return hrData.last(); }
    float getAchievement();

private:
    void calculateCoherence();

    QVector<int> hrData;
    QVector<float> coherenceScores;
};

#endif // SESSION_H
