# Heartwave

### Folder Layout:

- **docs:** contains the use cases, use case diagram, traceability matrix, class diagram, and sequence diagrams.
- **src:** contains the source code for the project.
- **images:** contains images of the UI.
- **data:** contains the data sets of heart rate data used in the code. <br> <br>

### Classes:

- **mainwindow:** The main window of the application, acts as the control of the application
- **heartratesensor:** Simulator of an actual heart rate sensor, holds heart rate dataset
- **session:** Handles calculations of session informations (e.g., coherence score, data plotting, etc)
- **qcustomplot:** widget for plotting and data visualization
- **menuitemstyle:** item delegate class to paint HTML into the menu list items <br><br>

### Main features:

- Measures, analyzes and displays HRV (Heart Rate Variability) patterns
- Provides users with real-time biofeedback on their coherence levels
- Customizable settings to change challenge level or breath pacer interval
- Keeps a history of all session logs

<br />

**Features a clean & easy user interface** <br><img src="./images/screenshot_1.png?raw=true" height="500">

**Extensive session view with live updates** <br><img src="./images/screenshot_2.png?raw=true" height="500">

**Allows to view or delete old sessions** <br><img src="./images/screenshot_3.png?raw=true" height="500">

**Provides detailed session information** <br><img src="./images/screenshot_4.png?raw=true" height="500">

**Customizable settings page** <br><img src="./images/screenshot_5.png?raw=true" height="500">
