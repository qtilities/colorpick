/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#ifndef COLORSPACE_H
#define COLORSPACE_H

#include <QColor>
#include <QString>
#include <QVector>

/**
 * Represents a color space (RGB, HSV...)
 *
 * Provides a uniform API to manipulate colors independently of the actual color space.
 * Implmentations should be lightweight objects since they have no state.
 */
class ColorSpace
{
public:
    virtual ~ColorSpace();
    virtual QString name(int idx) const = 0;
    virtual int value(const QColor &color, int idx) const = 0;
    virtual int maximum(int idx) const = 0;

    virtual QVector<int> values(const QColor &color) const = 0;
    virtual QColor fromValues(const QVector<int> &values) const = 0;
};


#endif // COLORSPACE_H
