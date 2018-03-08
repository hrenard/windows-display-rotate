let WindowsDisplayRotate;

if (process.env.DEBUG) {
    WindowsDisplayRotate = require("./build/Debug/WindowsDisplayRotate.node");
} else {
    WindowsDisplayRotate = require("./build/Release/WindowsDisplayRotate.node");
}

module.exports = WindowsDisplayRotate;
