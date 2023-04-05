#include "session.h"

Session::Session()
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
