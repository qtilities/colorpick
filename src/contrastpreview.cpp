/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#include "contrastpreview.h"
#include "hcycolorspace.h"

#include <QLabel>
#include <QLocale>
#include <QVBoxLayout>

// As per http://www.w3.org/TR/WCAG20/#visual-audio-contrast
static constexpr qreal ACCEPTABLE_CONTRAST_RATIO = 3;
static constexpr qreal GOOD_CONTRAST_RATIO = 4.5;

ContrastPreview::ContrastPreview(QWidget *parent) : QWidget(parent)
{
    mRatioLabel = new QLabel;

    mDemoLabel = new QLabel(tr("Contrast Example Text"));
    mDemoLabel->setAutoFillBackground(true);
    mDemoLabel->setFrameStyle(QFrame::Box);
    mDemoLabel->setMargin(6);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mRatioLabel);
    layout->addWidget(mDemoLabel);
}

void ContrastPreview::setBackgroundColor(const QColor &color)
{
    if (mBackgroundColor != color) {
        mBackgroundColor = color;
        updatePreview();
    }
}

void ContrastPreview::setForegroundColor(const QColor &color)
{
    if (mForegroundColor != color) {
        mForegroundColor = color;
        updatePreview();
    }
}

void ContrastPreview::updatePreview()
{
    updateRatioLabel();
    updateDemoLabel();
}

void ContrastPreview::updateRatioLabel()
{
    hcy::color_comp_t lumaBg = hcy::luminance(mBackgroundColor.redF(),
                                              mBackgroundColor.greenF(),
                                              mBackgroundColor.blueF());
    hcy::color_comp_t lumaFg = hcy::luminance(mForegroundColor.redF(),
                                              mForegroundColor.greenF(),
                                              mForegroundColor.blueF());
    qreal ratio = hcy::contrast_ratio(lumaBg, lumaFg);

    QString level;
    if (ratio < ACCEPTABLE_CONTRAST_RATIO) {
        level = tr("Bad");
    } else if (ratio < GOOD_CONTRAST_RATIO) {
        level = tr("Acceptable");
    } else {
        level = tr("Good");
    }
    QString text = tr("Contrast Ratio");
    text = text + QString(": %1:1 (%2)").arg(QLocale::system().toString(ratio, 'g', 2), level);
    mRatioLabel->setText(text);
}

void ContrastPreview::updateDemoLabel()
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, mBackgroundColor);
    pal.setColor(QPalette::WindowText, mForegroundColor);
    mDemoLabel->setPalette(pal);
}
