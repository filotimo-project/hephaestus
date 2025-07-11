/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

import QtQuick
import QtQuick.Controls as Controls

import org.kde.kirigami as Kirigami
import org.kde.kcmutils as KCMUtils

KCMUtils.SimpleKCM {
    id: root

    Controls.Label {
        visible: kcm.developerOptions.developerModeEnabled
        text: i18n("Developer mode enabled")
    }
    
    Kirigami.FormLayout {
        Controls.Button {
            text: i18n("Enable Developer Mode")
            onClicked: {
                kcm.developerOptions.enableDeveloperMode();
            }
        }
    }
}
