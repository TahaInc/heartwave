#include "session.h"

Session::Session()
{

}

void Session::plotCurrentData(QCPGraph *) {

}

void Session::plotAllData(QCPGraph *) {

}

float Session::getAchievement() {
    return 0;
}

void Session::calculateCoherence() {
    //For smaller amounts of data points, the score will vary wildly

    int maxIndex = 0;
    int previous = hrData[0];
    QVector<int> periods; //These are partial periods

    //Find the periods (assuming the maximums are the only values greater than both adjacent values, and same for minimums)
    for(int i = 1; i < (hrData.length() - 1) && i < 65; i++){
        if(maxIndex == 0){
            if(hrData[i] > previous && hrData[i] > hrData[i+1]){
                maxIndex = i;
            }
            if(hrData[i] != hrData[i+1]){
                previous = hrData[i];
            }
        }else{
            if(hrData[i] > previous && hrData[i] > hrData[i+1]){
                periods.push_back(i - maxIndex);
                maxIndex = i;
            }
            if(hrData[i] != hrData[i+1]){
                previous = hrData[i];
            }
        }
    }

    //Calculate the standard deviation of the length of the periods
    float stdev = 0;
    //Make sure there is enough data to calculate the standard deviation (needed for a coherence score)
    if(periods.length() > 0){
        //Calculate the mean period length
        float totalLength = 0;
        for(int i = 0; i < periods.length(); i++){
            totalLength += periods[i];
        }
        float meanPeriod = totalLength / periods.length();

        //Calculate the sum of the squared difference from the mean
        float totalDifferences = 0;
        for(int i = 0; i < periods.length(); i++){
            totalDifferences += (periods[i] - meanPeriod)*(periods[i] - meanPeriod);
        }

        //Calculate the standard deviation
        stdev = qSqrt(totalDifferences / periods.length());
    }

    //Calculate the coherence score based on the standard deviation
    float zero = 0;
    int multiplier = qMin(5, periods.length());
    float score = qMax(zero, 16 - (multiplier * stdev));

    //Add the new coherence score to the list of coherence scores
    coherenceScores.push_back(score);
}
