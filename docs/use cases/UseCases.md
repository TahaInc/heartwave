# Device Use Cases

## Turn Device On (UC1)

Primary Actor

* Device user

Precondition

* User has a device

Main Success Scenario

1. The user presses the power button.
2. The device turns on.
3. The device unlocks the interface.
4. The device displays the main menu.

Postcondition

* The device has been turned on.
* The device is waiting on the main menu page.
* The device interface is usable.

Extensions

* 2a. The device is out of battery
  * 2a1. Follow the use case for battery low (UC9).

## Turn Device Off (UC2)

Primary Actor

* Device user

Precondition

* User has the device
* The device is currently on

Main Success Scenario

1. User presses the power button.
2. The interface stops displaying information (such as graphs and lights).
3. The interface locks.
4. The device turns off.

Postcondition

* The device is off
* The interface (except for the power button) is not functional

Extensions

* 1a. The device is currently in a session
  * 1a1. The session terminates.
  * 1a2. The session data is stored to the device.

## Change Breath Pacer Level (UC3)

Primary Actor

* Device user

Precondition

* The user has the device
* The device is on
* The "settings" menu option is selected, but not yet pressed

Main Success Scenario

1. The user presses the selector to enter the settings menu.
2. The user navigates using the arrows buttons to the change breath pacer level setting and selects it.
3. The user selects their requested breath pacer interval, ranging from 1-30 seconds.

Postcondition

* The device updates the breath pacer level to the desired interval.

Extensions

* 1-3a. The device is out of battery.
  * 1-3a1. Follow the use case for battery low (UC9).
* 3a. An invalid value is selected
  * 3a1. The device defaults the breath pacer interval value to 10 seconds.
* 3b. The device has never been initialized or recently reset
  * 3b1. The device defaults the breath pacer interval value to 10 seconds.

## Select a Challenge Level (UC4)

Primary Actor

* Device user

Precondition

* The user has the device
* The device is on
* The "settings" menu option is selected, but not yet pressed

Main Success Scenario

1. The user presses the selector to enter the settings menu.
2. The user navigates using the arrows buttons to the change challenge level setting and selects it.
3. The user selects their requested challenge level, ranging from 1-4 (beginner to advanced).

Postcondition

* The device updates the challenge level to the desired value.

Extensions

* 1-3a. The device is out of battery.
  * 1-3a1. Follow the use case for battery low (UC9).
* 3a. An invalid value is selected
  * 3a1. The device defaults to level 1.
* 3b. The device has never been initialized or recently reset
  * 3b1. The device defaults to level 1.

## Run Through a Session With a User (UC5)

Primary Actor

* Device user

Precondition

* The user has the device
* The device is on
* The "start session" menu option is selected, but not yet pressed

Main Success Scenario

1. The user presses the selector to initiate a session.
2. The device reads the user's heart rate.
3. The device turns the "active pulse reading" light on or off, depending on whether it could read a heart rate.
4. The device displays the current session metrics (see UC6).
5. The device repeats steps 2 through 4 until stopped by the user, waiting 1 second between each repetition.
6. The user presses the selector again to end the session.
7. The device saves the current session.
8. The device displays the results of the session (see UC7).

Postcondition

* The device is functional and displaying the session results.

Extensions

* 4a. There is no new heart rate data available.
  * 4a1. The display doe not update.
* 5a. The device gets turned off.
  * 5a1. See UC2, extension 1a.
* 5b. The user presses the back button.
  * 5b1. The session is saved (step 7).
  * 5b2. The user is returned to the main menu (not the session results).

## View Current Session Metrics (UC6)

Primary Actor

* The device

Precondition

* The user has the device
* The device is on
* A session is currently running

Main Success Scenario

1. The device plots the most recent 64 seconds of heart rate data on the graph, with the last data point collected being the rightmost point displayed.
2. The device displays the time elapsed in the current session.
3. If the session time elapsed is a multiple of 5, the device calculates and displays the coherence score on the display and on the coloured lights.
4. If the session time elapsed is a multiple of 5, the device calculates and displays the achievement score.
5. The device increments the session time elapsed by one second (the time between display updates).
6. The breath meter is updated when breathPacerTick() is called by the breath timer. The meter is filled up based on the session time elapsed. One cycle of the meter (empty to empty) takes (by default) 10 seconds, and the meter is completely filled at the halfway point.

Postcondition

* The data is displayed on the screen

Extensions

* 1a. Less than 64 seconds of data is available.
  * 1a1. All available data is presented, with a gap of no data on the left.
  * 1a2. The data is shifted to the left every time a new data point is collected until a full 64 seconds are available.
* 6a. The user selected a time between breaths other than the default of 10 seconds.
  * 6a1. The desired time between breaths will be stored in a variable available to the function that calculates how full the breath meter will be.
  * 6a1. The function takes the desired time between breaths into account.

## View Results (UC7)

Primary Actor

* Device user

Precondition

* The user has the device
* There exists session data to be displayed
* The session data to be displayed has been selected (either from the log/history or at the end of a session)

Main Success Scenario

1. The percentage of time spent in each coherence level is calculated.
2. The average coherence is calculated.
3. The device screen displays the following information: percentage of time spent in each coherence level, average coherence, challenge level, length of the session, achievement score, and the entire HRV graph.
4. The user presses the selector button
5. The device screen stops displaying the information

Postcondition

* The information has been displayed correctly
* The information is no longer being displayed

Extensions

* 1-5a. The device is out of battery
  * 1-5a1. Follow the use case for battery low (UC9)

## Delete a Result (UC8)

Primary Actor

* Device user

Precondition

* The device is not currently in a session
* There exists session data to be deleted

Main Success Scenario

1. The user presses arrow buttons to navigate to the log/history menu option
2. The user presses the selector button
3. A list of previous sessions is displayed on the device screen
4. The user presses arrow buttons to navigate to the desired session
5. The user presses the side arrow button the navigate to the delete option
6. The session data is deleted
7. The list being displayed is updated to reflect the deletion

Postcondition

* The selected session's data has been deleted (it is no longer being stored)

Extensions

* 1-7a. The device is out of battery.
  * 1-7a1. Follow the use case for battery low (UC9).
* 7a. There are no more sessions stored.
  * 7a1. The device screen resets, no longer displaying the log/history menu.
  * 7a2. The default menu is displayed (the arrow buttons now interact with this menu).

Related Information

* To leave this menu (step 3 or 7), the user could enter UC7 by selecting a session.

## Battery Low (UC9)
Primary Actor

* The device

Precondition

* The device has no remaining battery
* The device is currently on

Main Success Scenario

1. The device checks the current battery level
2. The device shuts down
3. The device turns off the running timers
4. The device turns off the screen

Postcondition

* The device is off
* No timers are running

Extensions

* 2a. If the device is currently in a session
  * 2a1. The device ends the session

## Sensor Off (UC10)

Primary Actor

- Device user

Precondition

- The device is currently receiving data

Main Success Scenario

1. There's no more data being receiving in the sensor
2. Heartrate icon changes from green (on) to black (no data)

Postcondition

- Heartrate icon is black

Extensions

- 1-7a. The device is out of battery.
  - 1-7a1. The user charges the device, and tries again from step 1.
