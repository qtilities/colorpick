/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#include "rgbcolorspace.h"

#include <QCoreApplication>

RgbColorSpace *RgbColorSpace::instance()
{
    static RgbColorSpace obj;
    return &obj;
}

RgbColorSpace::RgbColorSpace()
{
}

QString RgbColorSpace::name(int idx) const
{
    static QString names[3] = {
        QCoreApplication::translate("RgbColorSpace", "R"),
        QCoreApplication::translate("RgbColorSpace", "G"),
        QCoreApplication::translate("RgbColorSpace", "B"),
    };
    return names[idx];
}

int RgbColorSpace::value(const QColor &color, int idx) const
{
    if (idx == 0) {
        return color.red();
    } else if (idx == 1) {
        return color.green();
    } else if (idx == 2) {
        return color.blue();
    } else {
        return color.alpha();
    }
}

int RgbColorSpace::maximum(int idx) const
{
    return 255;
}

QVector<int> RgbColorSpace::values(const QColor &color) const
{
    return { color.red(), color.green(), color.blue() };
}

QColor RgbColorSpace::fromValues(const QVector<int> &values) const
{
    return QColor(values.at(0), values.at(1), values.at(2));
}
