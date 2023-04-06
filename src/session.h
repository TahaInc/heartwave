#ifndef SESSION_H
#define SESSION_H

#include "qcustomplot.h"
#include <QVector>
#include <QtMath>
#include <QString>
#include <ctime>

class Session
{
public:
    Session(int);

    inline void addHeartRate(int hr) { hrData.push_back(hr); }
    void plotCurrentData(QCustomPlot *);
    void plotAllData(QCustomPlot *);
    float getAchievement();
    float calculateCoherence();
    QString getName();
    inline int getChallengeLevel() const { return challengeLevel; }

private:
    const int challengeLevel;
    QString name;

    QVector<int> hrData;
    QVector<float> coherenceScores;
};

#endif // SESSION_H
