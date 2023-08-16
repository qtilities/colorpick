/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#ifndef COMPONENTEDITOR_H
#define COMPONENTEDITOR_H

#include <QWidget>

class ColorSpace;
class ImageGradientSelector;

class QSpinBox;

/**
 * Edit a color individual components, the edited components depend on the supplied colorspace
 */
class ComponentEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ComponentEditor(ColorSpace *colorSpace, QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

Q_SIGNALS:
    void colorChanged(const QColor &color);

private:
    void updateSelectorGradients();
    void updateFromSelectors();

    QImage createGradientImage(int idx) const;

    ColorSpace *mColorSpace;
    ImageGradientSelector *mComponentSelectors[3];
    QSpinBox *mComponentSpinBoxes[3];
};

#endif // COMPONENTEDITOR_H
