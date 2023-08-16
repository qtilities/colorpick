/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#ifndef HSVCOLORSPACE_H
#define HSVCOLORSPACE_H

#include "colorspace.h"

class HsvColorSpace : public ColorSpace
{
public:
    static HsvColorSpace *instance();

    QString name(int idx) const override;
    int value(const QColor &color, int idx) const override;
    int maximum(int idx) const override;

    QVector<int> values(const QColor &color) const override;
    QColor fromValues(const QVector<int> &values) const override;

private:
    HsvColorSpace();
};

#endif // HSVCOLORSPACE_H
