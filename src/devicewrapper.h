#ifndef DEVICEWRAPPER_H
#define DEVICEWRAPPER_H

/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2022 Raspberry Pi Ltd | Copyright (C) 2026 Jupiter4 foundation
 */

#include <QObject>
#include <QMap>
#include <QFile>

class DeviceWrapperBlockCacheEntry;
class DeviceWrapperFatPartition;

#ifdef Q_OS_WIN
#include "windows/winfile.h"
using DeviceWrapperFile = WinFile;
#elif defined(Q_OS_DARWIN)
#include "mac/macfile.h"
using DeviceWrapperFile = MacFile;
#else
using DeviceWrapperFile = QFile;
#endif


class DeviceWrapper : public QObject
{
    Q_OBJECT
public:
    explicit DeviceWrapper(DeviceWrapperFile *file, QObject *parent = nullptr);
    virtual ~DeviceWrapper();
    void sync();
    void pwrite(const char *buf, quint64 size, quint64 offset);
    void pread(char *buf, quint64 size, quint64 offset);
    DeviceWrapperFatPartition *fatPartition(int nr);

protected:
    bool _dirty;
    QMap<quint64,DeviceWrapperBlockCacheEntry *> _blockcache;
    DeviceWrapperFile *_file;

    void _readIntoBlockCacheIfNeeded(quint64 offset, quint64 size);
    void _seekToBlock(quint64 blockNr);

signals:

};

#endif // DEVICEWRAPPER_H
