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
    
    Kirigami.FormLayout {
        Controls.Button {
            enabled: !kcm.developerMode.enabled
            text: i18n("Enable Developer Mode")
            onClicked: {
                kcm.developerMode.enable();
            }
        }

        Controls.Label {
            visible: kcm.developerMode.enabled
            text: i18n("Developer mode enabled")
        }

        Controls.Label {
            visible: kcm.currentTransactionWatcher.transaction !== null && !kcm.currentTransactionWatcher.transaction.finished
            text: i18n("Ongoing transaction title: %1", kcm.currentTransactionWatcher.transaction.title)
        }
    }
}
