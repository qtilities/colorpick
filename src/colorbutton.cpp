/*
    MIT License

    Copyright (c) 2023 Andrea Zanellato <redtid3@gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/
#include "colorbutton.h"
#include <QPainter>

static constexpr int padding{6};

ColorButton::ColorButton(QWidget *parent)
    : QToolButton(parent)
    , mColor(Qt::black)
{
    setAutoFillBackground(true);
}

void ColorButton::setColor(const QColor &color)
{
    mColor = color;
    update();
}

QColor ColorButton::color() const
{
    return mColor;
}

void ColorButton::paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event);
    mColorRect = QRect(padding,
                       padding,
                       rect().width() - padding * 2,
                       rect().height() - padding * 2);
    QPen pen(mColor);
    QBrush brush(mColor);
    QPainter painter(this);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(mColorRect);
}
