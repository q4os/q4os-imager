/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2022 Raspberry Pi Ltd | Copyright (C) 2026 Jupiter4 foundation
 */

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls.Material 2.2

Button {
    font.family: roboto.name
    Material.background: activeFocus ? "#fbe7e7" : "#ffffff"
    Material.foreground: "#5d2d1B"
    Accessible.onPressAction: clicked()
    Keys.onEnterPressed: clicked()
    Keys.onReturnPressed: clicked()
}
