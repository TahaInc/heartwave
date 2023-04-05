#ifndef SESSION_H
#define SESSION_H

#include "qcustomplot.h"
#include <QVector>
#include <QtMath>

class Session
{
public:
    Session(int);

    inline void addHeartRate(int hr) { hrData.push_back(hr); }
    void plotCurrentData(QCustomPlot *);
    void plotAllData(QCustomPlot *);
    float getAchievement();
    float calculateCoherence();
    inline int getChallengeLevel() const { return challengeLevel; }
    float getAverageCoherence();
    int getChallengeLevel();
    int getSessionLength();
    void getCoherenceSpread(QVector<float>** intervals);

private:
    const int challengeLevel;

    QVector<int> hrData;
    QVector<float> coherenceScores;
};

#endif // SESSION_H
