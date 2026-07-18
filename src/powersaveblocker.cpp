/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2020 Raspberry Pi Ltd | Copyright (C) 2026 Jupiter4 foundation
 */

#include "powersaveblocker.h"
#include <QDebug>
#include <string>

PowerSaveBlocker::PowerSaveBlocker(QObject *parent) :
    QObject(parent), _stayingAwake(false)
{
}

PowerSaveBlocker::~PowerSaveBlocker()
{
    if (_stayingAwake)
        removeBlock();
}

void PowerSaveBlocker::applyBlock(const QString &reason)
{
    if (_stayingAwake)
        return;

#ifdef Q_OS_WIN
    REASON_CONTEXT rc;
    std::wstring wreason = reason.toStdWString();
    rc.Version = POWER_REQUEST_CONTEXT_VERSION;
    rc.Flags = POWER_REQUEST_CONTEXT_SIMPLE_STRING;
    // PowerCreateRequest's REASON_CONTEXT wants a non-const wchar_t*, but never
    // mutates it - the API just isn't const-correct. const_cast documents that
    // explicitly instead of hiding it behind an old-style cast.
    rc.Reason.SimpleReasonString = const_cast<wchar_t *>(wreason.c_str());
    _powerRequest = PowerCreateRequest(&rc);

    if (_powerRequest == INVALID_HANDLE_VALUE)
    {
        qDebug() << "Error creating power request:" << GetLastError();
        return;
    }

    _stayingAwake = PowerSetRequest(_powerRequest, PowerRequestDisplayRequired);
    if (!_stayingAwake)
    {
        qDebug() << "Error running PowerSetRequest():" << GetLastError();
    }
#endif
}

void PowerSaveBlocker::removeBlock()
{
    if (!_stayingAwake)
        return;

#ifdef Q_OS_WIN
    PowerClearRequest(_powerRequest, PowerRequestDisplayRequired);
    CloseHandle(_powerRequest);
#endif
}
