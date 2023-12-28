# Colorpick: Color picker and contrast checker

[![CI]](https://github.com/qtilities/colorpick/actions/workflows/build.yml)

Colorpick is a color picker, which makes it easy to check text readability by
letting you pick a background and foreground color and computing the contrast
between them.

It lets you know if contrast is good enough according to
<http://www.w3.org/TR/WCAG20/#visual-audio-contrast>.

It also comes with a handy magnified-picker, which you can control with the
cursor keys, for precise picking.

Finally, it lets you adjust colors and copy them to the clipboard as different
formats.

**⚠ Currently, working only under X11 based systems;
under Wayland the contrast checker is working,
the color picker selector doesn't work yet. ⚠**

![Main window](resources/screenshot.png)

## Dependencies

### Runtime

- Qt 5/6 base

### Build

- CMake
- Qt Linguist Tools
- [Qtilitools] CMake modules
- Git (optional, to pull latest VCS checkouts)

## Build

`CMAKE_BUILD_TYPE` is usually set to `Release`, though `None` might be a valid [alternative].<br />
`CMAKE_INSTALL_PREFIX` has to be set to `/usr` on most operating systems.<br />
By default, Qt5 is used for build, otherwise change it by adding `-D PROJECT_QT_VERSION=6`.

```bash
cmake -B build -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr -W no-dev
cmake --build build --verbose
DESTDIR="$(pwd)/package" cmake --install build
```

Using `sudo make install` is discouraged, instead use the system package manager where possible.

## Packages

[![Packaging status]](https://repology.org/project/colorpick/versions)

## Translations

To contribute language translations, you can use Qt Linguist and/or manually:

- Copy `resource/translations/colorpick.ts` language template to
  `resource/translations/colorpick_<country-code>.ts`, e.g.: `colorpick_de.ts`
- Set the language in the file:
  from `<TS version="2.1">` to `<TS version="2.1" language="de">`
- Copy `resource/translations/colorpick.desktop.yaml` language template to
  `resource/translations/colorpick_<country-code>.desktop.yaml`, e.g.: `colorpick_de.desktop.yaml`
- Translate them (see the existing translations as reference)
- Create a Pull Request with your changes.

## Authors

See the [AUTHORS] file.

## License

[BSD-3-Clause-Clear]


[AUTHORS]:            AUTHORS
[alternative]:        https://wiki.archlinux.org/title/CMake_package_guidelines#Fixing_the_automatic_optimization_flag_override
[BSD-3-Clause-Clear]: https://spdx.org/licenses/BSD-3-Clause-Clear.html
[CI]:                 https://github.com/qtilities/colorpick/actions/workflows/build.yml/badge.svg
[Packaging status]:   https://repology.org/badge/vertical-allrepos/colorpick.svg
[Qtilitools]:         https://github.com/qtilities/qtilitools/
