#include "mainwindow.h"
#include "menuitemstyle.h"
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
    batteryTimer = new QTimer(this);
    timeTimer = new QTimer(this);
    hrSensor = new HeartRateSensor();
    currentSession = NULL;
    menuHistory.clear();

    ui->menuButton->setEnabled(true);
    ui->backButton->setEnabled(true);
    ui->selectButton->setEnabled(true);
    ui->upButton->setEnabled(true);
    ui->rightButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    ui->leftButton->setEnabled(true);
    ui->battery->setText(QString::number(battery) + "%");

    disconnect(ui->powerButton, SIGNAL(clicked(bool)), 0, 0);
    connect(ui->powerButton, SIGNAL(clicked(bool)), this, SLOT(shutdown()));
    connect(batteryTimer, SIGNAL(timeout()), this, SLOT(updateBattery()));
    connect(timeTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(ui->menuButton, SIGNAL(clicked(bool)), this, SLOT(showMainMenu()));
    connect(ui->backButton, SIGNAL(clicked(bool)), this, SLOT(backButton()));
    connect(ui->upButton, SIGNAL(clicked(bool)), this, SLOT(upButton()));
    connect(ui->downButton, SIGNAL(clicked(bool)), this, SLOT(downButton()));
    connect(ui->rightButton, SIGNAL(clicked(bool)), this, SLOT(rightButton()));
    connect(ui->leftButton, SIGNAL(clicked(bool)), this, SLOT(leftButton()));
    connect(ui->selectButton, SIGNAL(clicked(bool)), this, SLOT(selectButton()));

    ui->battery->setVisible(true);
    ui->batteryIcon->setVisible(true);
    ui->time->setVisible(true);
    ui->line->setVisible(true);
    ui->coherenceLabel->setVisible(true);
    ui->coherence->setVisible(true);
    ui->lengthLabel->setVisible(true);
    ui->length->setVisible(true);
    ui->achievementLabel->setVisible(true);
    ui->achievement->setVisible(true);
    ui->hrIcon->setVisible(true);
    ui->graph->setVisible(true);
    ui->menu->setVisible(true);
    ui->menuLabel->setVisible(true);

    for (int i=1; i<BPTICKS; ++i) {
        findChild<QLabel*>(QString("bp%1").arg(i))->setVisible(true);
    }

    ui->screen->setStyleSheet(QString("background-color: " + ALTGRAY));
    ui->coherenceLed->setStyleSheet(QString("background-color: " + GRAY));
    ui->menu->setItemDelegate(new MenuItemStyle);

    showMainMenu();
    updateTime();
    batteryTimer->start(BATTERYLIFE * 60 * 1000 / 100);
    timeTimer->start(1000);
}

// Shuts down the device
void MainWindow::shutdown() {
    if (currentSession) { endSession(); }

    ui->menuButton->setEnabled(false);
    ui->backButton->setEnabled(false);
    ui->selectButton->setEnabled(false);
    ui->upButton->setEnabled(false);
    ui->rightButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->leftButton->setEnabled(false);

    disconnect(ui->powerButton, SIGNAL(clicked(bool)), 0, 0);
    connect(ui->powerButton, SIGNAL(clicked(bool)), this, SLOT(startup()));
    disconnect(batteryTimer, SIGNAL(timeout()), 0, 0);
    disconnect(timeTimer, SIGNAL(timeout()), 0, 0);
    disconnect(ui->menuButton, SIGNAL(clicked(bool)), 0, 0);
    disconnect(ui->backButton, SIGNAL(clicked(bool)), 0, 0);
    disconnect(ui->upButton, SIGNAL(clicked(bool)), 0, 0);
    disconnect(ui->downButton, SIGNAL(clicked(bool)), 0, 0);
    disconnect(ui->rightButton, SIGNAL(clicked(bool)), 0, 0);
    disconnect(ui->leftButton, SIGNAL(clicked(bool)), 0, 0);
    disconnect(ui->selectButton, SIGNAL(clicked(bool)), 0, 0);

    batteryTimer->stop();
    timeTimer->stop();

    ui->battery->setVisible(false);
    ui->batteryIcon->setVisible(false);
    ui->time->setVisible(false);
    ui->line->setVisible(false);
    ui->coherenceLabel->setVisible(false);
    ui->coherence->setVisible(false);
    ui->lengthLabel->setVisible(false);
    ui->length->setVisible(false);
    ui->achievementLabel->setVisible(false);
    ui->achievement->setVisible(false);
    ui->hrIcon->setVisible(false);
    ui->graph->setVisible(false);
    ui->menu->setVisible(false);
    ui->menuLabel->setVisible(false);

    for (int i=1; i<BPTICKS; ++i) {
        findChild<QLabel*>(QString("bp%1").arg(i))->setVisible(false);
    }

    ui->screen->setStyleSheet(QString("background-color: " + GRAY));
    ui->coherenceLed->setStyleSheet(QString("background-color: " + GRAY));

    delete batteryTimer;
    delete timeTimer;
    delete hrSensor;
    delete ui->menu->itemDelegate();
}

// Shows the main menu
void MainWindow::showMainMenu() {
    menuIndex = 0;
    menuItemIndex = 0;
    menuHistory.append(menuIndex);

    ui->menu->setVisible(true);
    ui->menu->clear();
    ui->menu->addItem("Start new session");
    ui->menu->addItem("View history");
    ui->menu->addItem("Settings");
    ui->menu->setCurrentRow(menuItemIndex);
    ui->menuLabel->setText("Main Menu");

    ui->upButton->setEnabled(true);
    ui->rightButton->setEnabled(false);
    ui->downButton->setEnabled(true);
    ui->leftButton->setEnabled(false);

    if (currentSession) { endSession(); }
}

// Shows the session display
void MainWindow::showSessionDisplay() {
    menuIndex = 3;
    menuHistory.append(menuIndex);

    ui->menu->setVisible(false);
    ui->upButton->setEnabled(false);
    ui->rightButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->leftButton->setEnabled(false);
    ui->menuLabel->setText("Session");

    ui->graph->setBackground(QBrush(QColor(ALTGRAY)));
    ui->graph->replot();

    if (!currentSession) { startSession(); }
}

// Shows the history menu
void MainWindow::showHistoryMenu() {
    menuIndex = 1;
    menuItemIndex = 0;
    menuHistory.append(menuIndex);

    ui->menu->setVisible(true);
    ui->menu->clear();
    ui->upButton->setEnabled(true);
    ui->rightButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    ui->leftButton->setEnabled(true);
    ui->menuLabel->setText("History");

    for(int i=0; i<sessionHistory.count(); ++i) {
        // TODO: For each session add an item
        // ui->menu->addItem(sessionHistory[i]->getName());
    }

    ui->menu->setCurrentRow(menuItemIndex);
}

// Shows the settings menu
void MainWindow::showSettingsMenu() {
    menuIndex = 2;
    menuItemIndex = 0;
    menuHistory.append(menuIndex);

    ui->menu->setVisible(true);
    ui->menu->clear();
    ui->upButton->setEnabled(true);
    ui->rightButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    ui->leftButton->setEnabled(true);
    ui->menuLabel->setText("Settings");

    if (challengeLevelSetting == 1) {
        ui->menu->addItem("Challenge level: <b>Beginner</b>");
    } else if (challengeLevelSetting == 2) {
        ui->menu->addItem("Challenge level: <b>Novice</b>");
    } else if (challengeLevelSetting == 3) {
        ui->menu->addItem("Challenge level: <b>Intermediate</b>");
    } else if (challengeLevelSetting == 4) {
        ui->menu->addItem("Challenge level: <b>Advanced</b>");
    }

    ui->menu->addItem("Breath Pacer interval: <b>" + QString::number(breathPacerSetting) + "s</b>");
    ui->menu->addItem("Reset device");
    ui->menu->setCurrentRow(menuItemIndex);
}

// Up button is clicked
void MainWindow::upButton() {
    menuItemIndex = (menuItemIndex - 1);
    if (menuItemIndex < 0) { menuItemIndex = ui->menu->count() - 1; }
    ui->menu->setCurrentRow(menuItemIndex);
}

// Down button is clicked
void MainWindow::downButton() {
    menuItemIndex = (menuItemIndex + 1);
    if (menuItemIndex > ui->menu->count() - 1) { menuItemIndex = 0; }
    ui->menu->setCurrentRow(menuItemIndex);
}

// Right button is clicked
void MainWindow::rightButton() {
    if (menuIndex == 2) {
        if (menuItemIndex == 0) {
            challengeLevelSetting += 1;
            if (challengeLevelSetting > 4) { challengeLevelSetting = 1; }

            if (challengeLevelSetting == 1) {
                ui->menu->item(0)->setText("Challenge level: <b>Beginner</b>");
            } else if (challengeLevelSetting == 2) {
                ui->menu->item(0)->setText("Challenge level: <b>Novice</b>");
            } else if (challengeLevelSetting == 3) {
                ui->menu->item(0)->setText("Challenge level: <b>Intermediate</b>");
            } else if (challengeLevelSetting == 4) {
                ui->menu->item(0)->setText("Challenge level: <b>Advanced</b>");
            }
        } else if (menuItemIndex == 1) {
            breathPacerSetting += 1;
            if (breathPacerSetting > 30) { breathPacerSetting = 1; }

            if (challengeLevelSetting == 1) {
                ui->menu->item(1)->setText("Breath Pacer interval: <b>" + QString::number(breathPacerSetting) + "s</b>");
            } else if (challengeLevelSetting == 2) {
                ui->menu->item(1)->setText("Breath Pacer interval: <b>" + QString::number(breathPacerSetting) + "s</b>");
            } else if (challengeLevelSetting == 3) {
                ui->menu->item(1)->setText("Breath Pacer interval: <b>" + QString::number(breathPacerSetting) + "s</b>");
            } else if (challengeLevelSetting == 4) {
                ui->menu->item(1)->setText("Breath Pacer interval: <b>" + QString::number(breathPacerSetting) + "s</b>");
            }
        }
    }
}

// Left button is clicked
void MainWindow::leftButton() {
    if (menuIndex == 2) {
        if (menuItemIndex == 0) {
            challengeLevelSetting -= 1;
            if (challengeLevelSetting < 1) { challengeLevelSetting = 4; }

            if (challengeLevelSetting == 1) {
                ui->menu->item(0)->setText("Challenge level: <b>Beginner</b>");
            } else if (challengeLevelSetting == 2) {
                ui->menu->item(0)->setText("Challenge level: <b>Novice</b>");
            } else if (challengeLevelSetting == 3) {
                ui->menu->item(0)->setText("Challenge level: <b>Intermediate</b>");
            } else if (challengeLevelSetting == 4) {
                ui->menu->item(0)->setText("Challenge level: <b>Advanced</b>");
            }
        } else if (menuItemIndex == 1) {
            breathPacerSetting -= 1;
            if (breathPacerSetting < 1) { breathPacerSetting = 30; }

            if (challengeLevelSetting == 1) {
                ui->menu->item(1)->setText("Breath Pacer interval: <b>" + QString::number(breathPacerSetting) + "s</b>");
            } else if (challengeLevelSetting == 2) {
                ui->menu->item(1)->setText("Breath Pacer interval: <b>" + QString::number(breathPacerSetting) + "s</b>");
            } else if (challengeLevelSetting == 3) {
                ui->menu->item(1)->setText("Breath Pacer interval: <b>" + QString::number(breathPacerSetting) + "s</b>");
            } else if (challengeLevelSetting == 4) {
                ui->menu->item(1)->setText("Breath Pacer interval: <b>" + QString::number(breathPacerSetting) + "s</b>");
            }
        }
    }
}

// Select button is clicked
void MainWindow::selectButton() {
    if (menuIndex == 0) {
        if (menuItemIndex == 0) {
            showSessionDisplay();
        } else if (menuItemIndex == 1) {
            showHistoryMenu();
        } else if (menuItemIndex == 2) {
            showSettingsMenu();
        }
    } else if (menuIndex == 1) {
        // TODO: select corresponding history log with sessionHistory[menuItemIndex]
    } else if (menuIndex == 2) {
        if (menuItemIndex == 2) {
            reset();
        }
    } else if (menuIndex == 3) {
        if (currentSession) { endSession(); }
    }
}

// Back button is clicked
void MainWindow::backButton() {
    if (menuHistory.size() >= 2) {
        if (menuHistory.last() == 3) {
            if (currentSession) { endSession(); }
        }

        menuHistory.removeLast();

        if (menuIndex == menuHistory.last()) { return; }

        menuIndex = menuHistory.last();
        menuHistory.removeLast();

        if (menuIndex == 0) {
            showMainMenu();
        } else if (menuIndex == 1) {
            showHistoryMenu();
        } else if (menuIndex == 2) {
            showSettingsMenu();
        } else if (menuIndex == 3) {
            showSessionDisplay();
        }
    }
}

// Starts a new session
void MainWindow::startSession() {
    breathPacerTimer = new QTimer(this);
    breathPacerIndex = 0;
    connect(breathPacerTimer, SIGNAL(timeout()), this, SLOT(breathPacerTick()));
    breathPacerTick();
    breathPacerTimer->start(breathPacerSetting * 1000 / (BPTICKS * 2));

    sessionTimer = new QTimer(this);
    sessionTime = 0;
    connect(sessionTimer, SIGNAL(timeout()), this, SLOT(sessionTick()));
    currentSession = new Session();
    sessionTick();
    sessionTimer->start(1000);
}

// End the current session
void MainWindow::endSession() {
    sessionTimer->stop();
    breathPacerTimer->stop();

    delete sessionTimer;
    delete breathPacerTimer;

    if (currentSession) {
        sessionHistory.append(currentSession);
        currentSession = NULL;
    }
    sessionTime = 0;
    menuHistory.pop_back();
    showHistoryMenu();
}

// Runs a session loop
void MainWindow::sessionTick() {
    int heartrate = hrSensor->getHeartRate(sessionTime);
    if (heartrate == -1) {
        return endSession();
    }
    currentSession->addHeartRate(heartrate);
    displaySessionMetrics();
    sessionTime++;
}

// Shows the end of session metrics
void MainWindow::displaySessionMetrics() {
    setLength(sessionTime);
    currentSession->plotCurrentData(ui->graph);
    if (sessionTime % 5 == 0) {
        setCoherenceScore(currentSession->calculateCoherence());
        setAchievement(currentSession->getAchievement());
    }
}

// Updates the breath pacer by incrementing/decrementing the lights
void MainWindow::breathPacerTick() {
    for (int i=1; i<BPTICKS; ++i) {
        QLabel* led;
        bool on;

        if (breathPacerIndex < BPTICKS){
            led = findChild<QLabel*>(QString("bp%1").arg(i));
            on = (i <= breathPacerIndex);
        } else {
            led = findChild<QLabel*>(QString("bp%1").arg(BPTICKS - i));
            on = (i > breathPacerIndex - BPTICKS);
        }

        if (on) {
            led->setStyleSheet(QString("background-color: " + GREEN));
        } else {
            led->setStyleSheet(QString("background-color: " + GRAY));
        }
    }

    breathPacerIndex = (breathPacerIndex + 1) % (BPTICKS * 2);
}

// Takes a float [0-1] and updates the coherence score on the UI
void MainWindow::setCoherenceScore(float c) {
    ui->coherence->setText(QString::number(c));

    int lower, upper;
    if (challengeLevelSetting == 1) {
        lower = 0.5;
        upper = 0.9;
    } else if (challengeLevelSetting == 2) {
        lower = 0.6;
        upper = 2.1;
    } else if (challengeLevelSetting == 3) {
        lower = 1.8;
        upper = 4;
    } else if (challengeLevelSetting == 4) {
        lower = 4;
        upper = 6;
    }

    if (c >= lower && c <= upper) {
        ui->coherenceLed->setStyleSheet(QString("background-color: " + BLUE));
    } else if (c > upper) {
        ui->coherenceLed->setStyleSheet(QString("background-color: " + GREEN));
    } else if (c < lower) {
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

// Decrements the battery and updates the UI
void MainWindow::updateBattery() {
    battery -= 1;

    if (battery <= 0) {
        shutdown();
    } else {
        ui->battery->setText(QString::number(battery) + "%");
    }
}

// Updates the time and UI
void MainWindow::updateTime() {
    time_t currentTime;
    char timeString[100];

    time(&currentTime);
    strftime(timeString, 50, "%I:%M %P", localtime(&currentTime));

    ui->time->setText(timeString);
}

// Resets the device to factory settings
void MainWindow::reset() {
    breathPacerSetting = 10;
    challengeLevelSetting = 1;

    menuHistory.clear();
    sessionHistory.clear();

    qDeleteAll(sessionHistory);

    showMainMenu();
}
