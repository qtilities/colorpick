/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#include "imagegradientselector.h"

#include <QPainter>
#include <QStyleOption>
#include <QWheelEvent>

static constexpr int arrowSize{7};

#ifdef QT_DEBUG
static void drawDebugLine(ImageGradientSelector *selector, QPainter *painter, int arrowPosition)
{
    QLineF line;
    selector->orientation() == Qt::Horizontal
        ? line = QLineF(arrowPosition, arrowSize, arrowPosition, selector->height() - arrowSize)
        : line = QLineF(0, arrowPosition, selector->width() - arrowSize, arrowPosition);
    painter->drawLines(&line, 1);
}
#endif

static constexpr QStyle::PrimitiveElement arrowElement(Qt::Orientation orientation)
{
    return orientation == Qt::Horizontal ? QStyle::PE_IndicatorArrowUp
                                         : QStyle::PE_IndicatorArrowLeft;
}

ImageGradientSelector::ImageGradientSelector(QWidget *parent)
    : QAbstractSlider(parent)
{
    setOrientation(Qt::Horizontal);
}

void ImageGradientSelector::setImage(const QImage &image)
{
    mImage = image;
    update();
}

void ImageGradientSelector::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QStyleOption arrowOption;
    QPen previousPen = painter.pen();
    QBrush previousBrush = painter.brush();

    painter.drawImage(imageRect(), mImage, QRectF());

    arrowOption.rect = arrowRect().toRect();
    painter.setPen(QPen());
    painter.setBrush(Qt::NoBrush);
    style()->drawPrimitive(arrowElement(orientation()), &arrowOption, &painter, this);
    painter.setPen(previousPen);
    painter.setBrush(previousBrush);

#ifdef QT_DEBUG
    drawDebugLine(this, &painter, arrowPosition());
#endif
}

void ImageGradientSelector::mousePressEvent(QMouseEvent *event)
{
    setArrowPosition(event->pos());
}

void ImageGradientSelector::mouseMoveEvent(QMouseEvent *event)
{
    setArrowPosition(event->pos());
}

void ImageGradientSelector::wheelEvent(QWheelEvent *event)
{
    int v = value() + event->angleDelta().y() / 120;
    setValue(v);
}

int ImageGradientSelector::arrowPosition() const
{
    QRectF rct = imageRect();
    int val = value(), max = maximum();
    int pos = (orientation() == Qt::Horizontal) ? val * rct.width() / max + arrowSize
                                                : val * rct.height() / max + arrowSize;
    return pos;
}

void ImageGradientSelector::setArrowPosition(const QPoint &pos)
{
    int w = width(), h = height(), min = minimum(), max = maximum();
    int v = (orientation() == Qt::Horizontal)
                ? (max - min) * (pos.x() - arrowSize) / (w - arrowSize * 2) + min
                : (max - min) * (h - pos.y() - arrowSize) / (h - arrowSize * 2) + min;
    setValue(v);
    update();
}

QRectF ImageGradientSelector::arrowRect() const
{
    int w = width(), h = height(), arrowPos = arrowPosition();
    return orientation() == Qt::Horizontal
               ? QRectF(arrowPos - arrowSize / 2, h - arrowSize, arrowSize, arrowSize)
               : QRectF(w - arrowSize, h - arrowPos - arrowSize / 2, arrowSize, arrowSize);
}

QRectF ImageGradientSelector::imageRect() const
{
    return QRectF(arrowSize,
                  arrowSize,
                  rect().width() - arrowSize * 2,
                  rect().height() - arrowSize * 2);
}
