# Q4OS Imager

Q4OS Imager is a graphical utility for writing operating system images to USB
flash drives and SD cards. It is the recommended way to create bootable Q4OS
installation media, and it can also write arbitrary local disk images.

It is a friendly fork of [Raspberry Pi Imager](https://github.com/raspberrypi/rpi-imager)
by Raspberry Pi Ltd, rebranded and configured for the [Q4OS](https://q4os.org)
operating system. See [PROVENANCE.md](PROVENANCE.md) for the exact upstream
baseline and a summary of the changes made in this fork.

- Website: <https://q4os.org>
- Contact: <devteam@q4os.org>

## Features

- Downloads the current Q4OS image list and writes the selected image in one step
- Writes local images (`.img`, or compressed `.zip`, `.gz`, `.xz`, ...)
- Verifies the written medium after flashing
- Advanced options dialog (press <kbd>CTRL</kbd>+<kbd>SHIFT</kbd>+<kbd>X</kbd>)
  for hostname, SSH, Wi-Fi and locale presets
- Runs on Linux and Windows

## Installation

### Q4OS / Debian

```
sudo apt update && sudo apt install q4os-imager
```

### Windows

Download `imager-<version>.exe` from the releases page and run it. The Windows
installer is built from the source code in this repository by the public GitHub
Actions workflow [`.github/workflows/windows.yml`](.github/workflows/windows.yml);
see [PROVENANCE.md](PROVENANCE.md) and the code signing policy below.

## Building from source

### Debian/Ubuntu

Install the build dependencies:

```
sudo apt install --no-install-recommends build-essential devscripts debhelper cmake git libarchive-dev libcurl4-gnutls-dev \
    qtbase5-dev qtbase5-dev-tools qtdeclarative5-dev libqt5svg5-dev qttools5-dev libgnutls28-dev \
    qml-module-qtquick2 qml-module-qtquick-controls2 qml-module-qtquick-layouts qml-module-qtquick-templates2 qml-module-qtquick-window2 qml-module-qtgraphicaleffects
```

Build the Debian package and install it:

```
git clone https://github.com/q4os/q4os-imager
cd q4os-imager
debuild -uc -us
sudo apt install ../q4os-imager*.deb
```

An icon is created in the start menu under "Utilities" or "Accessories".
The application runs as a regular user and calls udisks2 over DBus for
privileged operations like opening the disk device for writing. If udisks2 is
not functional on your distribution, it can alternatively be started as root
with sudo.

### Fedora/RHEL/CentOS

```
sudo yum install git gcc gcc-c++ make cmake libarchive-devel libcurl-devel openssl-devel qt5-qtbase-devel qt5-qtquickcontrols2-devel qt5-qtsvg-devel qt5-linguist
git clone https://github.com/q4os/q4os-imager
cd q4os-imager
mkdir -p build
cd build
cmake ../src
make
sudo make install
```

### Windows

The canonical Windows build is the GitHub Actions workflow
[`.github/workflows/windows.yml`](.github/workflows/windows.yml), which anybody
can run on a fork of this repository (`workflow_dispatch`); it produces the NSIS
installer as a build artifact.

For a local build, install Qt 5.15 with the MinGW 32-bit toolchain and CMake
(from the Qt online installer) and [NSIS](https://nsis.sourceforge.io), build
`src/CMakeLists.txt` in Release mode (for example from Qt Creator), then compile
the generated `q4os-imager.nsi` script to create the installer. OpenSSL 1.1
runtime DLLs are required if your Qt build does not use schannel; the workflow
file shows a checksum-pinned way to obtain them.

## Privacy

Q4OS Imager does not collect or transmit any usage statistics by default. The
download-statistics telemetry present in the upstream project is disabled at
compile time in this fork (`ENABLE_TELEMETRY=OFF` in `src/CMakeLists.txt`) and
can only become active if a user explicitly enables it in the options dialog.

Network access is used solely for the application's core function: fetching the
OS image list and downloading the image selected by the user. This program will
not transfer any other information to any networked system unless approved by
the user.

## Code signing policy

Windows binaries are built from the source code in this repository by the public
GitHub Actions workflow [`.github/workflows/windows.yml`](.github/workflows/windows.yml).

Free code signing provided by [SignPath.io](https://about.signpath.io/),
certificate by [SignPath Foundation](https://signpath.org/).

Team roles:

- Committers and reviewers: [Q4OS Team](https://github.com/q4os) (<devteam@q4os.org>)
- Release approvers: Q4OS project lead

## Security

See [SECURITY.md](SECURITY.md) for supported versions and how to report
vulnerabilities privately.

## Other notes

### Debugging

On Linux the application prints debug messages to the console when started from
a console. On Windows, start the application with the `--debug` command-line
option to open a console window.

### Custom repository

If the application is started with `--repo <URL>`, it uses a custom image
repository, so a second start-menu shortcut with that parameter lets you use the
application with your own images.

## License

Q4OS Imager is licensed under the Apache License 2.0 — see [LICENSE](LICENSE).
[license.txt](license.txt) additionally summarizes the licenses of the bundled
third-party components (Qt, libarchive, libcurl, drivelist, mountutils and
others).

Copyright (C) 2020 Raspberry Pi Ltd (upstream). Copyright (C) 2026 Jupiter4 foundation.
