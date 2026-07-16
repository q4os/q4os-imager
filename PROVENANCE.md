# Build provenance

This document describes where the Q4OS Imager source code comes from and how
the released binaries are produced, so that anyone can verify that a published
binary corresponds to this source.

## Source origin

Q4OS Imager is a fork of
[Raspberry Pi Imager](https://github.com/raspberrypi/rpi-imager) by
Raspberry Pi Ltd, licensed under the Apache License 2.0.

- Upstream baseline: commit `b49408781a3c347bd6f6c057c68bb34d6c06ad10` (2023-05-22)
- Changes relative to upstream:
  - project renamed and rebranded (names, URLs, artwork) for the Q4OS
    operating system
  - built-in image repository points to the Q4OS OS image list
  - download-statistics telemetry disabled at compile time
    (`ENABLE_TELEMETRY=OFF`)
  - upstream `embedded/` netboot build and upstream CI configuration removed
  - Windows code-signing invocations (signtool) removed from the build files;
    signing is performed outside the build, see below
  - Debian packaging adjusted for Q4OS

## Linux (Debian) packages

The `q4os-imager` Debian package is built from this tree with standard Debian
tooling (`dpkg-buildpackage` in a clean build chroot) and published in the
Q4OS apt repositories, which are signed with the Q4OS repository key.

## Windows installer

The Windows installer (`imager-<version>.exe`) is built exclusively by the
public GitHub Actions workflow
[`.github/workflows/windows.yml`](.github/workflows/windows.yml) on
GitHub-hosted runners, from the exact source in this repository:

1. Qt 5.15.2 (MinGW 8.1, 32-bit) is installed with `jurplel/install-qt-action`.
2. OpenSSL 1.1.1w runtime DLLs are downloaded from FireDaemon and verified
   against a SHA-256 checksum pinned in the workflow file.
3. The application is configured and compiled with CMake, Ninja and MinGW gcc.
4. The installer is packed with NSIS.
5. The unsigned installer is uploaded as a build artifact.
6. Code signing, when enabled, is performed by a SignPath.io signing request
   submitted from the same workflow; release-signing requests are approved
   manually.

No pre-built binaries are stored in this repository; all third-party build
inputs are fetched from their official distribution points and are
checksum-pinned where the origin does not provide signed downloads.

## Verifying a release

To reproduce a Windows build, fork the repository and run the
`windows-installer` workflow (`workflow_dispatch`) on the release tag, then
compare the produced installer contents with the published one.
