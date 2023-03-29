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

1. User presses the power button
2. The interface stops displaying information (such as graphs and lights)
3. The interface locks
4. The device turns off

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

## Delete a Result (UC8)

