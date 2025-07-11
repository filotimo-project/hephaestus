/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "hephaestussettings.h"
#include "CurrentTransactionWatcher.h"
#include "DeveloperMode.h"

#include <KPluginFactory>

using namespace Qt::Literals::StringLiterals;

K_PLUGIN_CLASS_WITH_JSON(HephaestusSettings, "kcm_hephaestus.json")

HephaestusSettings::HephaestusSettings(QObject *parent, const KPluginMetaData &data)
    : KQuickConfigModule(parent, data)
    , m_developerMode(new DeveloperMode(this))
    , m_transactionWatcher(new CurrentTransactionWatcher(this))
{
    qmlRegisterAnonymousType<DeveloperMode>("org.kde.hephaestus", 1);
    qmlRegisterAnonymousType<CurrentTransactionWatcher>("org.kde.hephaestus", 1);
    qmlRegisterAnonymousType<Transaction>("org.kde.hephaestus", 1);
}

#include "hephaestussettings.moc"
