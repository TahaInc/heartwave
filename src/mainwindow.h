#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QString>

#define GRAY (QString("rgb(186, 189, 182)"))
#define GREEN (QString("rgb(115, 210, 22)"))
#define RED (QString("rgb(204, 0, 0)"))
#define BLUE (QString("rgb(44, 98, 203)"))

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
    QTimer *timer;
    int battery;
    void setBreathPacer(float v);
    void setCoherenceScore(float c);
    void setLength(float l);
    void setAchievement(float a);
    int decrementBattery();

private slots:
    void startup();
    void shutdown();
    void loop();
};
#endif // MAINWINDOW_H
