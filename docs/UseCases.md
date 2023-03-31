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
  * 2a1. The user plugs in the device to charge it, and then tries again.

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


## Change Power Level (UC3)

## Select a Challenge Level (UC4)

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
3. The device displays the current session metrics (see UC6).
4. The device repeats steps 3 and 4 until stopped by the user, waiting 1 second between each repetition.
5. The user presses the selector again to end the session.
6. The device saves the current session.
7. The device displays the results of the session (see UC7).

Postcondition

* The device is functional and displaying the session results.

Extensions

* 2a. There is no heart rate data available.
  * 2a1. The session is automatically ended.
  * 2a2. Steps 6 and 7 are executed.
* 4a. The device gets turned off.
  * 4a1. See UC2, extension 1a.

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
3. The device calculates and displays the coherence score.
4. If the session time elapsed is a multiple of 5, the device calculates and displays the achievement score.
5. The breath meter is updated. The meter is filled up based on the session time elapsed. One cycle of the meter (empty to empty) takes (by default) 10 seconds, and the meter is completely filled at the halfway point.
6. The device increments the session time elapsed by one second (the time between display updates).

Postcondition

* The data is displayed on the screen

Extensions

* 1a. Less than 64 seconds of data is available.
  * 1a1. All available data is presented, with a gap of no data on the left.
  * 1a2. The data is shifted to the left every time a new data point is collected until a full 64 seconds are available.
* 5a. The user selected a time between breaths other than the default of 10 seconds.
  * 5a1. The desired time between breaths will be stored in a variable available to the function that calculates how full the breath meter will be.
  * 5a1. The function takes the desired time between breaths into account.

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
  * 1-5a1. The user charges the device, and tries again

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
  * 1-7a1. The user charges the device, and tries again from step 1.
* 7a. There are no more sessions stored.
  * 7a1. The device screen resets, no longer displaying the log/history menu.
  * 7a2. The default menu is displayed (the arrow buttons now interact with this menu).

Related Information

* To leave this menu (step 3 or 7), the user could enter UC7 by selecting a session.
