#ifndef NETWORKMANAGERAPI_H
#define NETWORKMANAGERAPI_H

/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2022 Raspberry Pi Ltd | Copyright (C) 2026 Jupiter4 foundation
 */

#include "wlancredentials.h"

class NetworkManagerApi : public WlanCredentials
{
public:
    NetworkManagerApi();
    QByteArray getSSID() override;
    QByteArray getPSK() override;

protected:
    QByteArray _getSSIDofInterface(const QByteArray &iface);
};

#endif // NETWORKMANAGERAPI_H
