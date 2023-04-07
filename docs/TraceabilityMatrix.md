# Notes:

The user interface provided is a suggestion, and not a requirement. However, some elements of the provided interface are required.
This traceability matrix does not currently include details regarding the calculation of certain metrics (such as Achievement score).

# Traceability Matrix

| Requirement | Use Case | Implemented By | Tested By | Description |
| :---------- | :------- | :------------- | :-------- | :---------- |
| A light indicates an active pulse reading | 5 | MainWindow | Start a session and view the colour of the pulse indicator change. | When the device is reading apulse (in a session), the colour of the pulse light changes. |
| The UI contains a screen | 3,4,5,6,7,8 | MainWindow.ui | Run the app and look at the UI. | There is a scren on the device in which the menus and graphs are displayed. |
| The UI contains a menu | 3,4,7,8 | MainWindow.ui | Run the app and look at the UI. | The device opens up to the main *menu* by default. |
| The UI contains a 'Selector' button | 1,2,5,8 | MainWindow.ui | Run the app and look at the UI. | There is a selector button in the centre of the arrow buttons which is used to indicate that the currently selected menu item should perform an operation. |
| The menu has a 'Start Session' option listed first | 1,5 | MainWindow | Open the app and look at the UI. | When the app opens up to the main menu, the 'Start Session' button is at the top of the list and is selected by default. |
| The menu has a 'Settings' option | 3,4 | MainWindow | Open the app and look at the UI. | The 'Settings' option is a part of the Main Menu UI that opens by default. |
| The menu has a 'Log/History' option | 3,4,7,8 | MainWindow | Open the app and look at the UI. | The 'Log/History' option is a part of the Main Menu UI that opens by default. |
| There is a red/blue/green light indicating coherence level | 6 | MainWindow.ui | Start a session and wait for the Heart Rate Variance calculation to produce various coherence scores, reflected in the light at the top of the UI. | The light at the top of the UI changes based on the current coherence score. While in a session, it updates. |
| The 'Selector' button starts/stops sessions | 5 | MainWindow | Open the app, click the button to start a session, and then click the button again to stop it. | The app opens with the 'Start Session' button selected. Pressing the selector will start the session, and the pressing it again will end the session. |
| The device screen displays the menu by default | 1 | MainWindow | Open the app and look at the UI. | The device displays the main menu by default when it opens. |
| There are different challenge levels that affect coherence scores | 4,5,6,7,8 | MainWindow | CHange the challenge level, and then run through a session. | The challenge level changes the coherence score required to qualify as "good". |
| The screen displays the current coherence score | 6 | MainWindow | Start a session and look at the UI. | The session menu displays the current coherence score near the top. |
| The screen displays the length of the current session | 6 | MainWindow | Start a session and look at the UI. | The session displays the session time near the top, which updates every second. |
| The screen displays the current achievement score | 6 | MainWindow | Start a session and look at the UI. | The session menu displays the current achievement score at the top, which updates every 5 seconds. |
| The screen displays the HRV graph | 6 | MainWindow, Session | Start a session and look at the UI. | The session menu prominently displays a graph of the user heart rate, which is updated every second. |
| There is a 'Breath Pacer' as a progression of lights or a bar | 3,6 | MainWindow.ui | Open the app and look at the UI. | A series of lights representing the breath pacer are visible below the screen. |
| The default 'Breath Pacer' setting is 10 seconds | 3 | MainWindow | Open the app and check the 'Settings' menu. | The 'Settings' menu displays the breath pacer timing, which by default is 10 seconds. |
| The 'Settings' menu option allows modification of challenge level and breath pacer setting | 3,4 | MainWindow | Open the settings menu and click the left and right buttons when the challenge level or breath pacer timer are selected. | The challenge level and breath pacer setting can be adjusted using the left and right buttons in the UI when they are selected. |
| There are 4 challenge levels (Beginner -> Advanced) | 4 |MainWindow | Cycle through the challenge level options using the left and right buttons. | The challenge level options can be changed using the left and right buttons. Once all possible levels have been cycled through, it loops. |
| The breath pacer settings range from 1-30 seconds | 3 | MainWindow | Cycle through the breath pacer settings using the left and right buttons. | The left button decreases the breath pacer time and the right button increases it. Trying to go past 1 or 30 seconds loops around to the other side. |
| A session summary appears at the end of each session | 5 | MainWindow, Session | End a session and view the UI. | Once a session is completed, the history of past sessions is opened up, with the most recent session selecte. |
| Session summaries display challenge level, percentage of time in each coherence level, average coherence, length of session, achievement score, and the HRV graph | 5,6 | MainWindow, Session | Select a session summary and view the UI. | An individual session summary displays these statistics. By selecting one summary, you can see them displayed. |
| The 'Log/History' menu option shows previous sessions and dates | 7 | MainWindow | Select the 'Log/History' option in the main menu and enter it. | The 'Log/History' menu option is available in the main menu, and selecting it will show the session history. |
| When a logged session is selected, its summary is displayed alongside the ability to delete it | 7,8 | MainWindow, Session | Open the 'Log/History' menu and view the UI. | When a session is selected, its statistics are displayed and clicking the right arrow key will select the option to delete it. |
| The device can be reset to its intial state with no stored data | N/A | MainWindow | Select the 'Reset Device' button in the settings menu. | The 'Reset Device' option resets the device to factory defaults. |
| The session screen displays the current battery level | N/A | MainWindow | Open the app and view the UI. | The device battery level is visible near the top of the ui and changes over time. |
| There is a beep when coherence level changes | 6 | MainWindow, Session | Start a session and let the heart rate variability change. | When a new coherence level is reached, the word "BEEP" is printed to the console. |
| There's an on/off button that turns on/off the device | 1,2 | MainWindow | Press the power button to turn the device on, and then press it again to turn the device off. | The power button near the bottom of the UI toggles the power state and locks the device if it is off. |

