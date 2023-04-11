# Heartwave

### Folder Layout:
**Video demo:**<br/>
https://www.youtube.com/watch?v=xdZD85LBHXs
<br />**Folders:**<br/>
**docs:** contains the use cases, traceability matrix, and sequence diagrams. 
<br />**scr:** contains the source code for the project.
<br />**images:** contains images of the UI.
<br />**data:** contains the data sets of heart rate data used in the code.

### Project Information:
**Team Members' Contributions:**<br />

**Michael Bradley:** 
<br />**Zachary Call:** Use Cases: 1,3,4; Sequence diagrams: 1,3,4; receiving/not receiving heartrate data implementation; collection of real life heartrate data (3 samples); design and implementation of coherence score algorithm; bug fixes
<br />**Taha Rhidouani:**
<br />**Jared Tarnocai:** Use Cases: 2,7,8; Sequence diagrams: 2,7,8, Battery Low, Sensor Interruption; session summary view implementation; Worked on: traceability matrix, class diagram, coherence score algorithm, bug fixes.
<br />

**Classes:**<br />
**mainwindow:** The main window of the application, acts as the control of the application 
<br />**heartratesensor:** Simulator of an actual heart rate sensor, holds heart rate dataset
<br />**session:** Handles calculations of session informations (e.g., coherence score, data plotting, etc) 
<br />**qcustomplot:** widget for plotting and data visualization
<br />**menuitemstyle:** item delegate class to paint HTML into the menu list items
<br />
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
