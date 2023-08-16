/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#include "imagegradientselector.h"

#include <QPainter>

ImageGradientSelector::ImageGradientSelector(QWidget *parent)
    : KSelector(parent)
{
}

void ImageGradientSelector::setImage(const QImage &image)
{
    mImage = image;
    update();
}

void ImageGradientSelector::drawContents(QPainter *painter)
{
    painter->drawImage(contentsRect(), mImage);
}
