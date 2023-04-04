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
    void plotCurrentData(QCPGraph *);
    void plotAllData(QCPGraph *);
    inline float getLastCoherenceScore() { return coherenceScores.last(); }
    float getAchievement();

private:
    void calculateCoherence();

    QVector<int> hrData;
    QVector<float> coherenceScores;
};

#endif // SESSION_H
