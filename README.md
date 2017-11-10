# Deepin DreamScene

This is a project that I have a whim to help improve my ability to write code.

## Dependencies

### Build dependencies

* qmake (>= 5.3)
* [deepin-tool-kit](https://github.com/linuxdeepin/deepin-tool-kit) (developer package)
* xcb-ewmh (developer package)
* libmpv (developer package)

### Runtime dependencies

* [deepin-tool-kit](https://github.com/linuxdeepin/deepin-tool-kit)
* Qt5 (>= 5.6)
  * Qt5-DBus
  * Qt5-X11extras
* xcb-ewmh
* libmpv

If you use Deepin, just add my ppa. see [here](https://blog.mkacg.com/2017/07/24/PPA/)

If you use Arch, you can install deepin-dreamscene with aur.

## Installation

### Build from source code

1. Make sure you have installed all dependencies.

2. Build:
```
$ cd deepin-dreamscene
$ mkdir Build
$ cd Build
$ qmake ..
$ make
```

3. Install:
```
$ sudo make install
```

The executable binary file could be found at `/usr/bin/deepin-dreamscene` after the installation is finished.

## Getting help

You can create a issue, I will help you.

You may also find these channels useful if you encounter any other issues:

* [deepin community](https://bbs.deepin.org) Topbar is also the community software that you can post for help.

## License

DreamScene is licensed under [GPLv3](LICENSE).