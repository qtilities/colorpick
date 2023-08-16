/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#ifndef CONTRASTPREVIEW_H
#define CONTRASTPREVIEW_H

#include <QWidget>

class QLabel;

/**
 * Shows a preview of what a text would look like with the given foreground and background colors
 */
class ContrastPreview : public QWidget
{
    Q_OBJECT
public:
    explicit ContrastPreview(QWidget *parent = 0);

    void setBackgroundColor(const QColor &color);
    void setForegroundColor(const QColor &color);

private:
    void updatePreview();
    void updateRatioLabel();
    void updateDemoLabel();

    QColor mBackgroundColor;
    QColor mForegroundColor;

    QLabel *mRatioLabel;
    QLabel *mDemoLabel;
};

#endif // CONTRASTPREVIEW_H
