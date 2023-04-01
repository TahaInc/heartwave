#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QString>
#include <QList>
#include <ctime>
#include "session.h"
#include "heartratesensor.h"

#define BLACK (QString("#000000"))
#define GRAY (QString("#BABDB6"))
#define ALTGRAY (QString("#D3D7CF"))
#define GREEN (QString("#73D216"))
#define RED (QString("#CC0000"))
#define BLUE (QString("#2C62CB"))
#define BPTICKS 17
#define BATTERYLIFE 30 // in minutes

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *sessionTimer;
    QTimer *breathPacerTimer;
    QTimer *batteryTimer;
    QTimer *timeTimer;
    QList<int> menuHistory;
    QList<Session*> sessionHistory;
    Session *currentSession;
    HeartRateSensor *hrSensor;
    int battery;
    int menuIndex;
    int menuItemIndex;
    int breathPacerIndex;
    int breathPacerSetting = 10;
    int challengeLevelSetting = 1;
    void setCoherenceScore(float c);
    void setLength(float l);
    void setAchievement(float a);
    void showHeartRateContact(bool h);
    void showSessionDisplay();
    void showHistoryMenu();
    void showSettingsMenu();
    void startSession();
    void endSession();
    void reset();

private slots:
    void startup();
    void shutdown();
    void upButton();
    void downButton();
    void rightButton();
    void leftButton();
    void selectButton();
    void backButton();
    void showMainMenu();
    void sessionTick();
    void breathPacerTick();
    void updateBattery();
    void updateTime();

};
#endif // MAINWINDOW_H
