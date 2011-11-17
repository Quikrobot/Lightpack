/*
 * ILedDevice.hpp
 *
 *  Created on: 17.04.2011
 *      Author: Timur Sattarov && Mike Shatohin
 *     Project: Lightpack
 *
 *  Lightpack is very simple implementation of the backlight for a laptop
 *
 *  Copyright (c) 2011 Mike Shatohin, mikeshatohin [at] gmail.com
 *
 *  Lightpack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Lightpack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <QtGui>


class ILedDevice : public QObject
{
    Q_OBJECT
public:
    ILedDevice(QObject * parent) : QObject(parent) {}

signals:
    void openDeviceSuccess(bool isSuccess);
    void ioDeviceSuccess(bool isSuccess);
    void firmwareVersion(const QString & fwVersion);
    // Signal commandCompleted(bool) must be sent at the completion of each command
    // (setColors, setTimerOptions, setColorDepth, setSmoothSlowdown, etc.)
    void commandCompleted(bool ok);
    void setColors_VirtualDeviceCallback(QList<QRgb> colors);

public slots:
    virtual void setColors(const QList<QRgb> & colors) = 0;
    virtual void offLeds() = 0;
    virtual void setRefreshDelay(int value) = 0;
    virtual void setSmoothSlowdown(int value) = 0;
    virtual void setGamma(double value) = 0;
    virtual void setBrightness(int value) = 0;
    virtual void requestFirmwareVersion() = 0;

    // deprecated, but may be usable for lightpack hw <= 5.5
    virtual void setColorDepth(int value) = 0;

public:
    virtual void open() = 0;
};
