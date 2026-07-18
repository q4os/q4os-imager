#ifndef MACWLANCREDENTIALS_H
#define MACWLANCREDENTIALS_H

/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2023 Q4OS Ltd
 */

#include "wlancredentials.h"

class MacWlanCredentials : public WlanCredentials
{
public:
    QByteArray getSSID() override;
    QByteArray getPSK() override;

protected:
    QByteArray _ssid;
};

#endif // MACWLANCREDENTIALS_H
