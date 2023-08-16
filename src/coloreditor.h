/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#ifndef COLOREDITOR_H
#define COLOREDITOR_H

#include <QWidget>

class ComponentEditor;

class ColorButton;

class QLabel;
class QLineEdit;
class QMenu;
class QToolButton;

class ColorEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ColorEditor(const QIcon &icon, QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

Q_SIGNALS:
    void colorChanged(const QColor &color);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    void updateFromColor();
    void startPicking();
    void fillCopyMenu();

    ColorButton *mColorButton;
    QLineEdit *mLineEdit;
    QMenu *mCopyMenu;

    ComponentEditor *mRgbEditor;
    ComponentEditor *mHsvEditor;

    QColor mColor;

    bool mFromLineEdit = false;
    void setupCopyButton();
};

#endif // COLOREDITOR_H
