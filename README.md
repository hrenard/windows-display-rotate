# windows-display-rotate

A Node.js native module wich  can set the orientation of your display(s) on Windows only.

## Installation

```
npm install windows-display-rotate
```

```
yarn add windows-display-rotate
```

## Usage

Start by require the module.

```
const WindowsDisplayRotate = require("windows-display-rotate");
```

### Get the number of screen

```
// Get only active displays
let activeDisplays = WindowsDisplayRotate.size();

// Get all displays
let allDisplays = WindowsDisplayRotate.size(true);
```

### Turn a display

```
WindowsDisplayRotate.clockwise(); // Successful => true
WindowsDisplayRotate.counterClockwise(); // Successful => true

// Optionally precise the displayId (< WindowsDisplayRotate.size())
WindowsDisplayRotate.clockwise(2); // Successful => true
WindowsDisplayRotate.counterClockwise(0); // Successful => true
```

### Set the orientation of a display

```
WindowsDisplayRotate.doDefault(); // Successful => true
WindowsDisplayRotate.do90(); // Successful => true
WindowsDisplayRotate.do180(); // Successful => true
WindowsDisplayRotate.do270(); // Successful => true

// Optionally precise the displayId (< WindowsDisplayRotate.size())
WindowsDisplayRotate.doDefault(0); // Successful => true
WindowsDisplayRotate.do90(1); // Successful => true
WindowsDisplayRotate.do180(2); // Successful => true
WindowsDisplayRotate.do270(3); // Successful => true
```