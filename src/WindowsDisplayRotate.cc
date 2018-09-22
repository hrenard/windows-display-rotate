#include <nan.h>
#include <windows.h>
#include <iostream>

using namespace Nan;
using namespace std;

bool getDevmode(int id, DEVMODE *dm);
bool setOrientation(int id, DWORD displayOrientation);
bool isLandscape(DWORD displayOrientation);
bool isPortrait(DWORD displayOrientation);

bool getDevmode(int id, DEVMODE *dm)
{
    DISPLAY_DEVICE lpDisplayDevice;
    lpDisplayDevice.cb = sizeof(DISPLAY_DEVICE);
    bool exist = EnumDisplayDevices(NULL, id, &lpDisplayDevice, EDD_GET_DEVICE_INTERFACE_NAME);
    if (exist)
    {

        if (lpDisplayDevice.StateFlags & DISPLAY_DEVICE_ACTIVE)
        {
            return EnumDisplaySettings(lpDisplayDevice.DeviceName, ENUM_CURRENT_SETTINGS, dm);
        }
    }

    return false;
}

bool setOrientation(int id, DWORD displayOrientation)
{
    DEVMODE dm;
    dm.dmSize = sizeof(DEVMODE);

    if (getDevmode(id, &dm))
    {

        if ((isLandscape(dm.dmDisplayOrientation) && isPortrait(displayOrientation)) || (isPortrait(dm.dmDisplayOrientation) && isLandscape(displayOrientation)))
        {
            DWORD dwTemp = dm.dmPelsHeight;
            dm.dmPelsHeight = dm.dmPelsWidth;
            dm.dmPelsWidth = dwTemp;
        }

        dm.dmDisplayOrientation = displayOrientation;

        cout << dm.dmDeviceName << endl;

        int res = ChangeDisplaySettings(&dm, 0);
        cout << res << endl;
        return res == DISP_CHANGE_SUCCESSFUL;
    }

    return false;
}

bool isLandscape(DWORD displayOrientation)
{
    return (displayOrientation == DMDO_DEFAULT || displayOrientation == DMDO_180);
}

bool isPortrait(DWORD displayOrientation)
{
    return (displayOrientation == DMDO_90 || displayOrientation == DMDO_270);
}

NAN_METHOD(size)
{
    bool all = Nan::To<bool>(info[0]).FromMaybe(false);
    bool loop = true;
    int size = 0;

    DISPLAY_DEVICE lpDisplayDevice;
    lpDisplayDevice.cb = sizeof(DISPLAY_DEVICE);

    for (int i = 0; loop == true; i++)
    {
        loop = EnumDisplayDevices(NULL, i, &lpDisplayDevice, EDD_GET_DEVICE_INTERFACE_NAME);

        if (all || lpDisplayDevice.StateFlags & DISPLAY_DEVICE_ACTIVE)
        {
            size++;
        }
    }

    info.GetReturnValue().Set(Nan::New<v8::Integer>(size));
}

NAN_METHOD(doDefault)
{
    int id = Nan::To<int>(info[0]).FromMaybe(0);

    bool success = setOrientation(id, DMDO_DEFAULT);

    info.GetReturnValue().Set(Nan::New<v8::Boolean>(success));
}

NAN_METHOD(do90)
{
    int id = Nan::To<int>(info[0]).FromMaybe(0);

    bool success = setOrientation(id, DMDO_90);

    info.GetReturnValue().Set(Nan::New<v8::Boolean>(success));
}

NAN_METHOD(do180)
{
    int id = Nan::To<int>(info[0]).FromMaybe(0);

    bool success = setOrientation(id, DMDO_180);

    info.GetReturnValue().Set(Nan::New<v8::Boolean>(success));
}

NAN_METHOD(do270)
{
    int id = Nan::To<int>(info[0]).FromMaybe(0);

    bool success = setOrientation(id, DMDO_270);

    info.GetReturnValue().Set(Nan::New<v8::Boolean>(success));
}

NAN_METHOD(clockwise)
{
    int id = Nan::To<int>(info[0]).FromMaybe(0);

    DEVMODE dm;
    dm.dmSize = sizeof(DEVMODE);
    int success = false;

    if (getDevmode(id, &dm))
    {
        DWORD displayOrientation;
        switch (dm.dmDisplayOrientation)
        {
        case DMDO_DEFAULT:
            displayOrientation = DMDO_270;
            break;
        case DMDO_90:
            displayOrientation = DMDFO_DEFAULT;
            break;
        case DMDO_180:
            displayOrientation = DMDO_90;
            break;
        case DMDO_270:
            displayOrientation = DMDO_180;
            break;
        default:
            displayOrientation = DMDO_DEFAULT;
            break;
        }

        success = setOrientation(id, displayOrientation);
    }

    info.GetReturnValue().Set(Nan::New<v8::Boolean>(success));
}

NAN_METHOD(counterClockwise)
{
    int id = Nan::To<int>(info[0]).FromMaybe(0);

    DEVMODE dm;
    dm.dmSize = sizeof(DEVMODE);
    int success = false;

    if (getDevmode(id, &dm))
    {
        DWORD displayOrientation;
        switch (dm.dmDisplayOrientation)
        {
        case DMDO_DEFAULT:
            displayOrientation = DMDO_90;
            break;
        case DMDO_90:
            displayOrientation = DMDO_180;
            break;
        case DMDO_180:
            displayOrientation = DMDO_270;
            break;
        case DMDO_270:
            displayOrientation = DMDO_DEFAULT;
            break;
        default:
            displayOrientation = DMDO_DEFAULT;
            break;
        }

        success = setOrientation(id, displayOrientation);
    }

    info.GetReturnValue().Set(Nan::New<v8::Boolean>(success));
}

/*
NAN_METHOD(getDisplay)
{
    v8::Isolate *isolate = info.GetIsolate();
    v8::Local<v8::String> result = v8::String::NewFromUtf8(isolate, "Hello world !");

    bool onlyActive = Nan::To<bool>(info[0]).FromMaybe(false);

    info.GetReturnValue().Set(Nan::New<v8::Boolean>(onlyActive));
}*/

NAN_MODULE_INIT(Init)
{
    NAN_EXPORT(target, size);
    NAN_EXPORT(target, doDefault);
    NAN_EXPORT(target, do90);
    NAN_EXPORT(target, do180);
    NAN_EXPORT(target, do270);
    NAN_EXPORT(target, clockwise);
    NAN_EXPORT(target, counterClockwise);
}

NODE_MODULE(WindowsDisplayRotate, Init);