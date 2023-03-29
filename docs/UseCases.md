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
3. The main window displays the following information: percentage of time spent in each coherence level, average coherence, challenge level, length of the session, achievement score, and the entire HRV graph.

Postcondition

* The information has been displayed correctly

Extensions

* 3a. The user selects another menu option while viewing the information
  * 3a1. The main window stops displaying the information.
  * 3a2. The newly selected option is run.

## Delete a Result (UC8)

