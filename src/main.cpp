/*
    SPDX-License-Identifier: BSD-3-Clause-Clear

    This code is part of the Colorpick application and it's licensed under a BSD 3 clause clear license.
    You should have received a COPYING file along with the code. If not, contact the maintainers at
    https://github.com/qtilities/colorpick
*/
#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QScreen>
#include <QTranslator>

#include "window.h"

static QScreen *screenAt(const QPoint &pos)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
    return qApp->screenAt(pos);
#else
    const QList<QScreen*> screens = QGuiApplication::screens();
    for (QScreen *screen : screens) {
        if (screen->geometry().contains(pos))
            return screen;
    }
    return nullptr;
#endif
}
static void centerOnScreen(QWidget *widget)
{
    // Result is not correct but better than nothing
    if (const QScreen *screen = screenAt(QCursor::pos())) {
        widget->move(screen->geometry().center() - widget->frameGeometry().center());
    }
}
int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QTranslator qtTranslator, translator;

    // For some reason Qtc loads the wrong locale, force it for debugging.
#if PROJECT_TRANSLATION_TEST_ENABLED
    QLocale locale(QLocale("it"));
    QLocale::setDefault(locale);
#else
    QLocale locale = QLocale::system();
#endif
    // install the translations built-into Qt itself
    if (qtTranslator.load(QStringLiteral("qt_") + locale.name(),
#if QT_VERSION < 0x060000
                          QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
#else
                          QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
#endif
        app.installTranslator(&qtTranslator);

    // E.g. "<appname>_en"
    QString translationsFileName = QCoreApplication::applicationName().toLower() + '_'
                                   + locale.name();
    // Try first in the same binary directory, in case we are building,
    // otherwise read from system data
    QString translationsPath = QCoreApplication::applicationDirPath();

    bool isLoaded = translator.load(translationsFileName, translationsPath);
    if (!isLoaded) {
        // "/usr/share/<appname>/translations
        isLoaded = translator.load(translationsFileName,
                                   QStringLiteral(PROJECT_DATA_DIR)
                                       + QStringLiteral("/translations"));
    }
    if (isLoaded)
        app.installTranslator(&translator);

    QString iconName = QStringLiteral("/colorpick.svg");
    QString icoLocalPath = QCoreApplication::applicationDirPath() + iconName;
    QString icoSysPath = QStringLiteral(PROJECT_ICON_SYSTEM_PATH) + iconName;

    // Try first to find the app icon in the current/build directory
    QIcon appIcon = QIcon(icoLocalPath);
    if (appIcon.isNull())
        appIcon = QIcon(icoSysPath);

    app.setApplicationName(APPLICATION_NAME);
    app.setApplicationDisplayName(APPLICATION_DISPLAY_NAME);
    app.setOrganizationName(ORGANIZATION_NAME);
    app.setOrganizationDomain(ORGANIZATION_DOMAIN);
    app.setDesktopFileName(PROJECT_APPSTREAM_ID);
    app.setWindowIcon(appIcon);

    Window window;
    centerOnScreen(&window);
    window.show();

    return app.exec();
}
