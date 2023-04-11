# Heartwave

### Folder Layout:
Video demo
https://www.youtube.com/watch?v=xdZD85LBHXs
Folders
docs: contains the use cases, traceability matrix, and sequence diagrams. scr: contains the source code for the project.
images: contains images of the UI.
data: contains the data sets of heart rate data used in the code.

### Project Information:
Team Members' Contributions:

Michael Bradley: 
Zachary Call:
Taha Rhidouani:
Jared Tarnocai: Use Cases: 2,7,8; Sequence diagrams: 2,7,8, Battery Low, Sensor Interruption; session summary view implementation; Worked on: traceability matrix, class diagram, coherence score algorithm, bug fixes.


Classes:
mainwindow: The main window of the application, acts as the control of the application heartratesensor: Simulator of an actual heart rate sensor, holds heart rate dataset
session: Handles calculations of session informations (e.g., coherence score, data plotting, etc) qcustomplot: widget for plotting and data visualization
menuitemstyle: item delegate class to paint HTML into the menu list items

### Main features:

- Measures, analyzes and displays HRV (Heart Rate Variability) patterns
- Provides users with real-time biofeedback on their coherence levels
- Customizable settings to change challenge level or breath pacer interval
- Keeps a history of all session logs

<br />

**Features a clean & easy user inteface** <br><img src="./images/screenshot_1.png?raw=true" height="500">

**Extensive session view with live updates** <br><img src="./images/screenshot_2.png?raw=true" height="500">

**Allows to view or delete old sessions** <br><img src="./images/screenshot_3.png?raw=true" height="500">

**Provides detailed session information** <br><img src="./images/screenshot_4.png?raw=true" height="500">

**Customizable settings page** <br><img src="./images/screenshot_5.png?raw=true" height="500">
