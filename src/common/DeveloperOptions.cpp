/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <KLocalizedContext>
#include <KLocalizedString>
#include <KMessageBox>
#include <qlogging.h>

#include "DeveloperOptions.h"
#include "RpmOstreeInterface.h"

using namespace Qt::Literals::StringLiterals;

DeveloperOptions::DeveloperOptions(QObject *parent)
    : QObject(parent)
    , m_rpmOstreeInterface(sharedRpmOstreeInterface())
{
}

bool DeveloperOptions::developerModeEnabled() const
{
    auto os = m_rpmOstreeInterface->os(m_rpmOstreeInterface->sysroot()->booted());

    return os->bootedDeployment().value(u"unlocked"_s).toString() == u"development"_s;
}

void DeveloperOptions::enableDeveloperMode()
{
    // FIXME: doens't work
    QDBusObjectPath osPath = m_rpmOstreeInterface->sysroot()->booted();
    auto reply = m_rpmOstreeInterface->osExperimental(osPath)->LiveFs({});
    reply.waitForFinished();

    Q_EMIT developerModeEnabledChanged();
}
