/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

class ColorEditor;

class Window : public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

private:
    ColorEditor *mBgEditor;
    ColorEditor *mFgEditor;
};

#endif // WINDOW_H
