#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    startup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Starts up the device
void MainWindow::startup() {
    battery = 100;
    timer = new QTimer(this);

    ui->screen->setEnabled(true);
    ui->menu->setEnabled(true);
    ui->back->setEnabled(true);
    ui->up->setEnabled(true);
    ui->right->setEnabled(true);
    ui->down->setEnabled(true);
    ui->left->setEnabled(true);
    ui->battery->setText(QString::number(battery) + "%");

    disconnect(ui->power, SIGNAL(clicked(bool)), 0, 0);
    connect(ui->power, SIGNAL(clicked(bool)), this, SLOT(shutdown()));
    connect(timer, SIGNAL(timeout()), this, SLOT(loop()));

    timer->start(1000);

    // TODO: turn on display, initialize buttons/data, etc
}

void MainWindow::loop() {
    // TODO: Main loop
}

// Shuts down the device
void MainWindow::shutdown() {
    // Disable the display when the device is powered off
    ui->screen->setEnabled(false);
    ui->menu->setEnabled(false);
    ui->back->setEnabled(false);
    ui->up->setEnabled(false);
    ui->right->setEnabled(false);
    ui->down->setEnabled(false);
    ui->left->setEnabled(false);

    disconnect(ui->power, SIGNAL(clicked(bool)), 0, 0);
    connect(ui->power, SIGNAL(clicked(bool)), this, SLOT(startup()));

    timer->stop();

    // TODO: turn off display, clear data, etc
}

// Takes a float [0-1] and displays it on the breath pacer display
void MainWindow::setBreathPacer(float v) {
    int value = int(17 * v);

    for (int i=1; i<=17; ++i) {
        QLabel* led = findChild<QLabel*>(QString("bp%1").arg(i));

        if (i <= value) {
            led->setStyleSheet(QString("background-color: " + GREEN));
        } else {
            led->setStyleSheet(QString("background-color: " + GRAY));
        }
    }
}

// Takes a float [0-1] and updates the coherence score on the UI
void MainWindow::setCoherenceScore(float c) {
    ui->coherence->setText(QString::number(c));

    if (true) { // TODO: If coherence is medium
        ui->coherenceLed->setStyleSheet(QString("background-color: " + BLUE));
    } else if (true) { // TODO: If coherence is high
        ui->coherenceLed->setStyleSheet(QString("background-color: " + GREEN));
    } else { // TODO: If coherence is low
        ui->coherenceLed->setStyleSheet(QString("background-color: " + RED));
    }
}

// Takes a float [0-1] and updates the length score on the UI
void MainWindow::setLength(float l) {
    ui->length->setText(QString::number(l));
}

// Takes a float [0-1] and updates the coherence score on the UI
void MainWindow::setAchievement(float a) {
    ui->achievement->setText(QString::number(a));
}

// Decrements the battery, updates the UI and returns new value
int MainWindow::decrementBattery() {
    battery -= 1;
    ui->battery->setText(QString::number(battery) + "%");
    return battery;
}
