# Device Use Cases

## Turn Device On (UC1)

Primary Actor

* Device user

Precondition

* User has a device

Main Success Scenario

1. User presses the power button.
2. The device turn on.

Postcondition

* The device has been turned on and is waiting on the main menu page.

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

## View Current Session Metrics (UC6)

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

* 1-7a. The device is out of battery
  * 1-7a1. The user charges the device, and tries again from step 1
