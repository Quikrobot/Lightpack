/*
 * LightpackMath.cpp
 *
 *  Created on: 29.09.2011
 *     Project: Lightpack
 *
 *  Copyright (c) 2011 Mike Shatohin, mikeshatohin [at] gmail.com
 *
 *  Lightpack a USB content-driving ambient lighting system
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

#include "LightpackMath.hpp"
#include "debug.h"

void LightpackMath::gammaCorrection(double gamma, const QList<QRgb> & colors, QList<StructRgb> & result)
{
    DEBUG_HIGH_LEVEL << Q_FUNC_INFO << gamma;

    //
    // Convert 8-bit 'colors' to 12-bit 'result' with gamma correction
    //
    for (int i = 0; i < colors.count(); i++)
    {
        StructRgb rgbResult;

        QRgb rgb = colors[i]; // color depth -- 8-bit

        // 256  == 2^8 : This is color depth of 'colors'
        // 4096 == 2^12: This is color depth of 'result'

        rgbResult.r = 4096.0 * pow(qRed(rgb) / 256.0, gamma);
        rgbResult.g = 4096.0 * pow(qGreen(rgb) / 256.0, gamma);
        rgbResult.b = 4096.0 * pow(qBlue(rgb) / 256.0, gamma);

        result[i] = rgbResult;
    }
}

void LightpackMath::brightnessCorrection(int brightness, QList<StructRgb> & result)
{
    DEBUG_HIGH_LEVEL << Q_FUNC_INFO << brightness;

    // brightness -- must be in percentage (0..100%)

    for (int i = 0; i < result.count(); i++)
    {
        result[i].r = (brightness / 100.0) * result[i].r;
        result[i].g = (brightness / 100.0) * result[i].g;
        result[i].b = (brightness / 100.0) * result[i].b;
    }
}
