# Heartwave

### Video demo:

https://www.youtube.com/watch?v=xdZD85LBHXs

### Folder Layout:

**docs:** contains the use cases, use case diagram, traceability matrix, class diagram, and sequence diagrams.

**src:** contains the source code for the project.

**images:** contains images of the UI.

**data:** contains the data sets of heart rate data used in the code.

### Team Members' Contributions:

**Michael Bradley:** Use cases 5,6; Sequence diagrams 5,6; Heart rate graphing functions (session and summary); Worked on: traceability matrix, class diagram, bug fixes (including memory leaks), heart rate sensor and session functionality.

**Zachary Call:** Use Cases: 1,3,4; Sequence diagrams: 1,3,4; receiving/not receiving heartrate data implementation; collection of real life heartrate data (3 samples); design and implementation of coherence score algorithm; bug fixes.

**Taha Rhidouani:** UI design & menu interface logic; startup & shutdown routine; undo button logic; history menu; settings menu; bug fixes.

**Jared Tarnocai:** Use Cases: 2,7,8; Sequence diagrams: 2,7,8, Battery Low, Sensor Interruption; session summary view implementation; Worked on: traceability matrix, class diagram, coherence score algorithm, bug fixes.

### Classes:

**mainwindow:** The main window of the application, acts as the control of the application

**heartratesensor:** Simulator of an actual heart rate sensor, holds heart rate dataset

**session:** Handles calculations of session informations (e.g., coherence score, data plotting, etc)

**qcustomplot:** widget for plotting and data visualization

**menuitemstyle:** item delegate class to paint HTML into the menu list items

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
