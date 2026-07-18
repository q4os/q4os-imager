#ifndef WINWLANCREDENTIALS_H
#define WINWLANCREDENTIALS_H

/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2023 Q4OS Ltd
 */

#include "wlancredentials.h"

class WinWlanCredentials : public WlanCredentials
{
public:
    WinWlanCredentials();
    QByteArray getSSID() override;
    QByteArray getPSK() override;

protected:
    QByteArray _ssid, _psk;
};

#endif // WINWLANCREDENTIALS_H
