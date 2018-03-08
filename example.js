const WindowsDisplayRotate = require("./");

function spinClockwise() {
    setTimeout(() => WindowsDisplayRotate.clockwise(), 0);
    setTimeout(() => WindowsDisplayRotate.clockwise(), 2000);
    setTimeout(() => WindowsDisplayRotate.clockwise(), 4000);
    setTimeout(() => WindowsDisplayRotate.clockwise(), 6000);
}

function spinCounterClockwise() {
    setTimeout(() => WindowsDisplayRotate.counterClockwise(), 0);
    setTimeout(() => WindowsDisplayRotate.counterClockwise(), 2000);
    setTimeout(() => WindowsDisplayRotate.counterClockwise(), 4000);
    setTimeout(() => WindowsDisplayRotate.counterClockwise(), 6000);
}

console.log("Availible screens: " + WindowsDisplayRotate.size());
console.log("All screens : " + WindowsDisplayRotate.size(true));

spinClockwise();
