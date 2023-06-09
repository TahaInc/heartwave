#include "mainwindow.h"
#include "menuitemstyle.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    startup();
}

MainWindow::~MainWindow()
{
    // Deallocate all memory
    qDeleteAll(sessionHistory);
    if (currentSession) {
        delete currentSession;
        if (sessionTimer){ delete sessionTimer; }
        if (breathPacerTimer){ delete breathPacerTimer; }
        if (hrSensor){ delete hrSensor; }
    }
    if (batteryTimer){ delete batteryTimer; }
    if (timeTimer){ delete timeTimer; }
    if (ui->menu->itemDelegate()) { delete ui->menu->itemDelegate(); }
    delete ui;
}

// Starts up the device
void MainWindow::startup() {
    // Initialize device variables
    battery = 100;
    batteryTimer = new QTimer(this);
    timeTimer = new QTimer(this);
    currentSession = NULL;
    menuHistory.clear();

    // Enable UI buttons
    ui->menuButton->setEnabled(true);
    ui->backButton->setEnabled(true);
    ui->selectButton->setEnabled(true);
    ui->upButton->setEnabled(true);
    ui->rightButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    ui->leftButton->setEnabled(true);

    // Connect UI buttons and timers to corresponding slots
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

    // Show screen elements
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
    ui->sumView->setVisible(false);
    ui->battery->setText(QString::number(battery) + "%");

    for (int i=1; i<BPTICKS; ++i) {
        findChild<QLabel*>(QString("bp%1").arg(i))->setVisible(true);
    }

    ui->screen->setStyleSheet(QString("background-color: " + ALTGRAY));
    ui->coherenceLed->setStyleSheet(QString("background-color: " + GRAY));
    ui->menu->setItemDelegate(new MenuItemStyle); // Set the style for the menu elements

    // Show main menu and start timers
    showMainMenu();
    updateTime();
    batteryTimer->start(BATTERYLIFE * 60 * 1000 / 100);
    timeTimer->start(1000);
}

// Shuts down the device
void MainWindow::shutdown() {
    if (currentSession) { endSession(); } // End session if session is running

    // Disable UI buttons
    ui->menuButton->setEnabled(false);
    ui->backButton->setEnabled(false);
    ui->selectButton->setEnabled(false);
    ui->upButton->setEnabled(false);
    ui->rightButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->leftButton->setEnabled(false);

    // Disconnect buttons and timers
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

    // Stop battery and timer button
    batteryTimer->stop();
    timeTimer->stop();

    // Turn off screen
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
    ui->sumView->setVisible(false);

    for (int i=1; i<BPTICKS; ++i) {
        findChild<QLabel*>(QString("bp%1").arg(i))->setVisible(false);
    }

    ui->screen->setStyleSheet(QString("background-color: " + GRAY));
    ui->coherenceLed->setStyleSheet(QString("background-color: " + GRAY));

    // Deallocate device variables
    delete batteryTimer;
    batteryTimer = nullptr;
    delete timeTimer;
    timeTimer = nullptr;
    delete ui->menu->itemDelegate();
}

// Shows the main menu
void MainWindow::showMainMenu() {
    // Set menu variables and add to history
    menuIndex = 0;
    menuItemIndex = 0;
    menuHistory.append(menuIndex);

    // Show menu elements
    ui->menu->setVisible(true);
    ui->sumView->setVisible(false);
    ui->menu->clear();
    ui->menu->addItem("Start new session");
    ui->menu->addItem("View history");
    ui->menu->addItem("Settings");
    ui->menu->setCurrentRow(menuItemIndex);
    ui->menuLabel->setText("Main Menu");

    // Enable corresponding UI buttons
    ui->upButton->setEnabled(true);
    ui->rightButton->setEnabled(false);
    ui->downButton->setEnabled(true);
    ui->leftButton->setEnabled(false);

    if (currentSession) { endSession(); } // End session if session is running
}

// Shows the session display
void MainWindow::showSessionDisplay() {
    // Set menu variables and add to history
    menuIndex = 3;
    menuHistory.append(menuIndex);

    // Change screen information and graph background color
    ui->menuLabel->setText("Session");
    ui->graph->setBackground(QBrush(QColor(ALTGRAY)));
    ui->graph->replot();

    // Enable corresponding UI buttons
    ui->menu->setVisible(false);
    ui->sumView->setVisible(false);
    ui->upButton->setEnabled(false);
    ui->rightButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->leftButton->setEnabled(false);

    if (!currentSession) { startSession(); } // Start session if session not running
}

// Displays the summary view for a session
void MainWindow::showSessionSummary(int sessionIndex){
    // Set menu variables and add to history
    menuIndex = 4;
    menuHistory.append(menuIndex);

    // Enable corresponding UI buttons
    ui->menu->setVisible(false);
    ui->upButton->setEnabled(false);
    ui->rightButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->leftButton->setEnabled(false);

    // Get the data to be displayed
    float achievement = sessionHistory[sessionIndex]->getAchievement();
    float averageCoherence = sessionHistory[sessionIndex]->getAverageCoherence();
    int sessionLength = sessionHistory[sessionIndex]->getSessionLength();
    int challengeLevel = sessionHistory[sessionIndex]->getChallengeLevel();
    QVector<float> coherenceSpread;
    sessionHistory[sessionIndex]->getCoherenceSpread(coherenceSpread);

    // Set the labels
    ui->menuLabel->setText("Session Summary");
    ui->sumViewAverageCoherence->setText("<b>Average Coherence:</b> " + QString::number(averageCoherence));
    if(coherenceSpread.length() >= 3){
        ui->sumViewCoherenceSpread->setText("<b>Coherence Spread:</b> Low: " + QString::number(coherenceSpread[0] * 100) + "%  Med: " + QString::number(coherenceSpread[1] * 100)+ "%  High: " + QString::number(coherenceSpread[2] * 100) + "%");
    }
    ui->sumViewSessionLength->setText("<b>Session length:</b> " + QString::number(sessionLength) + " seconds");
    if(challengeLevel == 1){
        ui->sumViewChallengeLevel->setText("<b>Challenge level:</b> Beginner");
    } else if(challengeLevel == 2){
        ui->sumViewChallengeLevel->setText("<b>Challenge level:</b> Novice");
    } else if(challengeLevel == 3){
        ui->sumViewChallengeLevel->setText("<b>Challenge level:</b> Intermediate");
    } else if(challengeLevel == 4){
        ui->sumViewChallengeLevel->setText("<b>Challenge level:</b> Advanced");
    }
    ui->sumViewAchievementScore->setText("<b>Achievment Score:</b> " + QString::number(achievement));

    // Make the summary screen visible
    ui->sumView->setStyleSheet(QString("background-color: " + ALTGRAY));
    ui->sumView->setVisible(true);

    // Display the entire HRV graph
    ui->sumViewGraph->setBackground(QBrush(QColor(ALTGRAY)));
    sessionHistory[sessionIndex]->plotAllData(ui->sumViewGraph);
}

// Shows the history menu
void MainWindow::showHistoryMenu() {
    // Set menu variables and add to history
    menuIndex = 1;
    menuItemIndex = 0;
    menuHistory.append(menuIndex);
    historyViewDelete = false;

    // Show menu elements
    ui->menu->setVisible(true);
    ui->sumView->setVisible(false);
    ui->menu->clear();
    ui->menuLabel->setText("History");

    for(int i=0; i<sessionHistory.count(); ++i) {
         if (i == 0) {
             ui->menu->addItem("<span style='white-space: pre;'><u>" + sessionHistory[i]->getName() + "</u>                   ⌫</span>");
         } else {
             ui->menu->addItem("<span style='white-space: pre;'>" + sessionHistory[i]->getName() + "                   ⌫</span>");
         }
    }

    ui->menu->setCurrentRow(menuItemIndex);

    // Enable corresponding UI buttons
    ui->upButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    ui->leftButton->setEnabled(false);
    if (sessionHistory.count() > 0) {  ui->rightButton->setEnabled(true); }
    else {  ui->rightButton->setEnabled(false); }
}

// Shows the settings menu
void MainWindow::showSettingsMenu() {
    // Set menu variables and add to history
    menuIndex = 2;
    menuItemIndex = 0;
    menuHistory.append(menuIndex);

    // Show menu elements
    ui->menu->setVisible(true);
    ui->sumView->setVisible(false);
    ui->menu->clear();
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

    // Enable corresponding UI buttons
    ui->upButton->setEnabled(true);
    ui->rightButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    ui->leftButton->setEnabled(true);
}

// Up button is clicked
void MainWindow::upButton() {
    // If inside session history menu, remove underline from view/delete buttons
    if (menuIndex == 1 && sessionHistory.count() > 1) {
        historyViewDelete = false;
        ui->menu->item(menuItemIndex)->setText("<span style='white-space: pre;'>" + sessionHistory[menuItemIndex]->getName() + "                   ⌫</span>");
    }

    // Increment and highlight menu item
    menuItemIndex = (menuItemIndex - 1);
    if (menuItemIndex < 0) { menuItemIndex = ui->menu->count() - 1; }
    ui->menu->setCurrentRow(menuItemIndex);

    // If inside session history menu, underline view history button
    if (menuIndex == 1 && sessionHistory.count() > 1) {
        ui->rightButton->setEnabled(true);
        ui->leftButton->setEnabled(false);
        ui->menu->item(menuItemIndex)->setText("<span style='white-space: pre;'><u>" + sessionHistory[menuItemIndex]->getName() + "</u>                   ⌫</span>");
    }

    // If inside settings menu, disable right/left arrows if "reset device" option is highlighted
    if (menuIndex == 2) {
        if (menuItemIndex == 2) {
            ui->rightButton->setEnabled(false);
            ui->leftButton->setEnabled(false);
        } else {
            ui->rightButton->setEnabled(true);
            ui->leftButton->setEnabled(true);
        }
    }
}

// Down button is clicked
void MainWindow::downButton() {
    // If inside session history menu, remove underline from view/delete buttons
    if (menuIndex == 1 && sessionHistory.count() > 1) {
        historyViewDelete = false;
        ui->menu->item(menuItemIndex)->setText("<span style='white-space: pre;'>" + sessionHistory[menuItemIndex]->getName() + "                   ⌫</span>");
    }

    // Decrement and highlight menu item
    menuItemIndex = (menuItemIndex + 1);
    if (menuItemIndex > ui->menu->count() - 1) { menuItemIndex = 0; }
    ui->menu->setCurrentRow(menuItemIndex);

    // If inside session history menu, underline view history button
    if (menuIndex == 1 && sessionHistory.count() > 1) {
        ui->rightButton->setEnabled(true);
        ui->leftButton->setEnabled(false);
        ui->menu->item(menuItemIndex)->setText("<span style='white-space: pre;'><u>" + sessionHistory[menuItemIndex]->getName() + "</u>                   ⌫</span>");
    }

    // If inside settings menu, disable right/left arrows if "reset device" option is highlighted
    if (menuIndex == 2) {
        if (menuItemIndex == 2) {
            ui->rightButton->setEnabled(false);
            ui->leftButton->setEnabled(false);
        } else {
            ui->rightButton->setEnabled(true);
            ui->leftButton->setEnabled(true);
        }
    }
}

// Right button is clicked
void MainWindow::rightButton() {
    // If inside settings menu, toggle between challenge level and breath pacer options
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

    // If inside history menu, underline delete button
    else if (menuIndex == 1 && sessionHistory.count() > 0) {
        historyViewDelete = true;
        ui->rightButton->setEnabled(false);
        ui->leftButton->setEnabled(true);
        ui->menu->item(menuItemIndex)->setText("<span style='white-space: pre;'>" + sessionHistory[menuItemIndex]->getName() + "                   <u>⌫</u></span>");
    }
}

// Left button is clicked
void MainWindow::leftButton() {
    // If inside settings menu, toggle between challenge level and breath pacer options
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

    // If inside history menu, underline select button
    else if (menuIndex == 1 && sessionHistory.count() > 0) {
        historyViewDelete = false;
        ui->rightButton->setEnabled(true);
        ui->leftButton->setEnabled(false);
        ui->menu->item(menuItemIndex)->setText("<span style='white-space: pre;'><u>" + sessionHistory[menuItemIndex]->getName() + "</u>                   ⌫</span>");
    }
}

// Select button is clicked
void MainWindow::selectButton() {
    // If inside main menu, select corresponding option
    if (menuIndex == 0) {
        if (menuItemIndex == 0) {
            showSessionDisplay();
        } else if (menuItemIndex == 1) {
            showHistoryMenu();
        } else if (menuItemIndex == 2) {
            showSettingsMenu();
        }
    }

    // If inside session history menu, delete session if delete button is underlined or select session if view button is underlined
    else if (menuIndex == 1 && sessionHistory.count() > 0) {
        if (historyViewDelete) {
            delete sessionHistory[menuItemIndex];
            sessionHistory.removeAt(menuItemIndex);
            ui->menu->takeItem(menuItemIndex);
            historyViewDelete = false;

            menuItemIndex = (menuItemIndex - 1);
            if (menuItemIndex < 0) { menuItemIndex = 0; }

            if (sessionHistory.count() > 0) {
                ui->rightButton->setEnabled(true);
                ui->leftButton->setEnabled(false);
                ui->menu->setCurrentRow(menuItemIndex);
                ui->menu->item(menuItemIndex)->setText("<span style='white-space: pre;'><u>" + sessionHistory[menuItemIndex]->getName() + "</u>                   ⌫</span>");
            } else {
                showMainMenu();
            }
        } else {
            showSessionSummary(menuItemIndex);
        }
    }

    // If inside settings menu, reset device if option is highlighted
    else if (menuIndex == 2) {
        if (menuItemIndex == 2) {
            reset();
        }
    }

    // If in a session, end it and show summary
    else if (menuIndex == 3) {
        if (currentSession) {
            endSession();
            showSessionSummary(0);
        } else {
            showHistoryMenu();
        }
    }

    // If viewing session summary, return to session history menu
    else if (menuIndex == 4) {
        showHistoryMenu();
    }
}

// Back button is clicked
void MainWindow::backButton() {
    if (menuHistory.size() >= 2) {

        // If we are in a session, end it
        if (menuHistory.last() == 3 && currentSession) {
            endSession();
        }

        // Remove current screen from history
        menuHistory.removeLast();

        // If we are already in the screen we need to go back to, return
        if (menuIndex == menuHistory.last()) { return; }

        // Get the screen we need to go back to and remove it from history
        menuIndex = menuHistory.last();
        menuHistory.removeLast();

        // Change to corresponding menu
        if (menuIndex == 0) {
            showMainMenu();
        } else if (menuIndex == 1) {
            showHistoryMenu();
        } else if (menuIndex == 2) {
            showSettingsMenu();
        } else if (menuIndex == 3 || menuIndex == 4) {
            showMainMenu();
        }
    }
}

// Starts a new session
void MainWindow::startSession() {
    // Create new heart rate sensor
    hrSensor = new HeartRateSensor();

    // Start breath pacer timer and setup animation
    breathPacerTimer = new QTimer(this);
    breathPacerIndex = 0;
    connect(breathPacerTimer, SIGNAL(timeout()), this, SLOT(breathPacerTick()));
    breathPacerTick();
    breathPacerTimer->start(breathPacerSetting * 1000 / (BPTICKS * 2));

    // Start session timer and create session class
    sessionTimer = new QTimer(this);
    sessionTime = 0;
    connect(sessionTimer, SIGNAL(timeout()), this, SLOT(sessionTick()));
    currentSession = new Session(challengeLevelSetting);
    sessionTick();
    sessionTimer->start(1000);
}

// End the current session
void MainWindow::endSession() {
    // Stop session and breath pacer timers
    sessionTimer->stop();
    breathPacerTimer->stop();

    // Deallocate timers and sensor from memory
    delete sessionTimer;
    delete breathPacerTimer;
    delete hrSensor;

    // If in a session, add it to the history
    if (currentSession) {
        sessionHistory.prepend(currentSession);
        currentSession = NULL;
    }

    // Reset coherence light and time variable
    setCoherenceScore(-1);
    sessionTime = 0;
}

// Runs a session loop
void MainWindow::sessionTick() {
    int heartrate = hrSensor->getHeartRate(sessionTime); // Get heart rate at current time

    // Update metrics in view if data is valid, disable heart label otherwise
    if (heartrate == -1) {
        noHeartData();
    } else {
        receivingHeartData();
        currentSession->addHeartRate(heartrate);
        displaySessionMetrics();
    }

    sessionTime++; // Increment time
}

// Shows the session metrics
void MainWindow::displaySessionMetrics() {
    // Update length and graph
    setLength(sessionTime);
    currentSession->plotCurrentData(ui->graph);

    // Update coherence score and achievement every 5 seconds
    if (sessionTime % 5 == 0) {
        float lastCoherence = currentSession->getLastCoherence();
        float newCoherence = currentSession->calculateCoherence();
        if (lastCoherence != -1 && getCoherenceLevel(lastCoherence) != getCoherenceLevel(newCoherence)) {
            std::cout << "BEEP!" << std::endl;
        }
        setCoherenceScore(newCoherence);
        setAchievement(currentSession->getAchievement());
    }
}

// Updates the breath pacer by incrementing/decrementing the lights
void MainWindow::breathPacerTick() {

    // For every breath pacer tick, enable the right amount depending on breathPacerIndex
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

    // Increment breathPacerIndex
    breathPacerIndex = (breathPacerIndex + 1) % (BPTICKS * 2);
}

// Calculate coherence level
int MainWindow::getCoherenceLevel(float c) {
    // Set lower and upper bounds based on challenge level settings
    float lower, upper;
    if (challengeLevelSetting == 1) {
        lower = 0.5;
        upper = 0.9;
    } else if (challengeLevelSetting == 2) {
        lower = 0.6;
        upper = 2.1;
    } else if (challengeLevelSetting == 3) {
        lower = 1.8;
        upper = 4;
    } else {
        lower = 4;
        upper = 6;
    }

    if (c < lower) {
        return 0;
    } else if (c < upper) {
        return 1;
    } else {
        return 2;
    }
}

// Takes a float [0-16] and updates the coherence score on the UI
void MainWindow::setCoherenceScore(float c) {

    // If coherence invalid, turn off light
    if (c < 0) {
        ui->coherenceLed->setStyleSheet(QString("background-color: " + GRAY));
        return;
    }

    // Update screen text
    ui->coherence->setText(QString::number(c));

    // Calculate coherence score and turn light to corresponding color
    int score = getCoherenceLevel(c);
    if (score == 0) {
        ui->coherenceLed->setStyleSheet(QString("background-color: " + RED));
    } else if (score == 1) {
        ui->coherenceLed->setStyleSheet(QString("background-color: " + BLUE));
    } else {
        ui->coherenceLed->setStyleSheet(QString("background-color: " + GREEN));
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

void MainWindow::receivingHeartData(){
    ui->hrIcon->setPixmap(QPixmap(":/resources/img/hr_on.png"));
}

void MainWindow::noHeartData(){
    ui->hrIcon->setPixmap(QPixmap(":/resources/img/hr.png"));
}

// Decrements the battery and updates the UI
void MainWindow::updateBattery() {
    battery -= 1; // Decrement battery level

    // Update battery label or shutdown if dead
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
