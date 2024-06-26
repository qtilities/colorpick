/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QDialog>

class QTimer;

class ColorPicker : public QDialog
{
    Q_OBJECT
public:
    ColorPicker();
    ~ColorPicker();

Q_SIGNALS:
    void colorChanged(const QColor &);

protected:
    void showEvent(QShowEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void updatePosition();
    void emitColorChanged();

    QTimer *mTimer;
    QPixmap mPixmap;
    qreal mScaleFactor;
};

#endif // COLORPICKER_H
