#include "session.h"

Session::Session(const int challengeLevel) : challengeLevel(challengeLevel)
{

}

void Session::plotCurrentData(QCustomPlot *plot) {
    // Size the plot appropriately
    // -63 seconds ago to 0 (just now)
    plot->xAxis->setRangeLower(-63);
    plot->xAxis->setRangeUpper(0);
    //plot->xAxis->setLabel("Time (s)");
    //plot->yAxis->setRangeLower(60);
    //plot->yAxis->setRangeUpper(100);
    //plot->yAxis->setLabel("Heart Rate (BPM)");

    // Ensure that the plot has only one, empty graph
    plot->clearGraphs();
    QCPGraph *graph = plot->addGraph();
    graph->setLineStyle(QCPGraph::lsLine);

    // Graph the data
    int dataStartIndex = qMax(0, hrData.size() - 64);
    for (int i = dataStartIndex; i < hrData.size(); ++i) {
        graph->addData(i - hrData.size(), hrData[i]);
    }

    // Rescale the Y axis to fit the input data.
    //plot->graph()->rescaleValueAxis(true);
    graph->rescaleValueAxis(false);

    // Stretch the y axis a little to give the data some room to breathe
    plot->yAxis->scaleRange(1.1, plot->yAxis->range().center());
    // Update the UI
    plot->replot();
}

void Session::plotAllData(QCustomPlot *plot) {
    // Ensure that the plot has only one, empty graph
    plot->clearGraphs();
    QCPGraph *graph = plot->addGraph();
    graph->setLineStyle(QCPGraph::lsLine);

    // Graph the data
    for (int i = 0; i < hrData.size(); ++i) {
        graph->addData(i, hrData[i]);
    }

    // Set the graph's axes to fit the bounds if the input data
    graph->rescaleAxes();

    // Stretch the y axis a little to give the data some room to breathe
    plot->yAxis->scaleRange(1.1, plot->yAxis->range().center());
    // Update the UI
    plot->replot();
}

float Session::getAchievement() {
    float achievement = 0;

    for (int i = 0; i < coherenceScores.size(); ++i) {
        achievement += coherenceScores[i];
    }

    return achievement;
}

float Session::calculateCoherence() {
    //For smaller amounts of data points, the score will vary wildly

    int maxIndex = 0;
    int previous = hrData[0];
    QVector<int> periods; //These are partial periods

    //Find the periods (assuming the maximums are the only values greater than both adjacent values, and same for minimums)
    for(int data = qMax(1, hrData.length() - 64); data < (hrData.length() - 1); data++){
        if(maxIndex == 0){
            if(hrData[data] > previous && hrData[data] > hrData[data+1]){
                maxIndex = data;
            }
            if(hrData[data] != hrData[data+1]){
                previous = hrData[data];
            }
        }else{
            if(hrData[data] > previous && hrData[data] > hrData[data+1]){
                periods.push_back(data - maxIndex);
                maxIndex = data;
            }
            if(hrData[data] != hrData[data+1]){
                previous = hrData[data];
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
    return score;
}

//Calculates the average coherence score
float Session::getAverageCoherence(){
    float total = 0;
    for(int i = 0; i < coherenceScores.length(); i++){
        total += coherenceScores[i];
    }

    return (total / coherenceScores.length());
}

//Returns the challenge level
int Session::getChallengeLevel(){
    return challengeLevel;
}

//Gets the number of hrData readings (the size of the Vector)
int Session::getSessionLength(){
    return hrData.length();
}

//Returns the percentage of time spent in each coherence level
void Session::getCoherenceSpread(QVector<float>** intervals){
    float lowTime = 0;
    float medTime = 0;
    float highTime = 0;

    for(int i = 0; i < coherenceScores.length(); i++){
        //The following 2 if-statements of code has been taken from the setCoherenceScore() function in mainwindow.cpp (modified slightly)
        //Get the bounds for the coherence levels based on the challenge level
        int lower, upper;
        if (challengeLevel == 1) {
            lower = 0.5;
            upper = 0.9;
        } else if (challengeLevel == 2) {
            lower = 0.6;
            upper = 2.1;
        } else if (challengeLevel == 3) {
            lower = 1.8;
            upper = 4;
        } else {
            lower = 4;
            upper = 6;
        }

        //Count the coherence score for the corresponding coherence level
        if (coherenceScores[i] >= lower && coherenceScores[i] <= upper) {
            medTime += 1;
        } else if (coherenceScores[i] > upper) {
            highTime += 1;
        } else {
            lowTime += 1;
        }
    }

    //Create the vector to be returned
    QVector<float>* spread = new QVector<float>();
    if(coherenceScores.length() > 0){
        spread->append(lowTime / coherenceScores.length());
        spread->append(medTime / coherenceScores.length());
        spread->append(highTime / coherenceScores.length());
    }

    //Return the vector (contains the percentage of time spent in each coherence level)
    *intervals = spread;
}
