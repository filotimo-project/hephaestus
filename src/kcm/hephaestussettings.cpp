/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "hephaestussettings.h"
#include "DeveloperOptions.h"

#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(HephaestusSettings, "kcm_hephaestus.json")

HephaestusSettings::HephaestusSettings(QObject *parent, const KPluginMetaData &data)
    : KQuickConfigModule(parent, data)
    , m_developerOptions(new DeveloperOptions(this))
{
    qmlRegisterAnonymousType<DeveloperOptions>("org.kde.hephaestus", 1);
}

#include "hephaestussettings.moc"
