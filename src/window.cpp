/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#include "window.h"
#include "coloreditor.h"
#include "contrastpreview.h"

#include <QVBoxLayout>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    ContrastPreview *preview = new ContrastPreview;
    mBgEditor = new ColorEditor;
    mFgEditor = new ColorEditor;

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(QMargins());
    layout->addWidget(mBgEditor);
    layout->addWidget(mFgEditor);
    layout->addWidget(preview);

    connect(mBgEditor, &ColorEditor::colorChanged, preview, &ContrastPreview::setBackgroundColor);
    connect(mFgEditor, &ColorEditor::colorChanged, preview, &ContrastPreview::setForegroundColor);

    mBgEditor->setColor(Qt::white);
    mFgEditor->setColor(Qt::black);
}
