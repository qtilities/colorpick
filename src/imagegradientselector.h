/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#ifndef IMAGEGRADIENTSELECTOR_H
#define IMAGEGRADIENTSELECTOR_H

#include <KSelector>

/**
 * A KSelector which displays a stretched image instead of a gradient. Useful to create gradients which are not
 * RGB-based.
 */
class ImageGradientSelector : public KSelector
{
public:
    ImageGradientSelector(QWidget *parent = nullptr);

    void setImage(const QImage &image);

protected:
    void drawContents(QPainter *painter) override;

private:
    QImage mImage;
};

#endif // IMAGEGRADIENTSELECTOR_H
