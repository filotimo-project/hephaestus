/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <KLocalizedContext>
#include <KLocalizedString>
#include <KMessageBox>
#include <qlogging.h>

#include "DeveloperMode.h"
#include "RpmOstreeInterface.h"

using namespace Qt::Literals::StringLiterals;

bool DeveloperMode::isEnabled() const
{
    auto os = m_rpmOstreeInterface->os(m_rpmOstreeInterface->sysroot()->booted());

    return os->bootedDeployment().value(u"unlocked"_s).toString() == u"development"_s;
}

void DeveloperMode::enable()
{
    // Use a Konsole command, because the experimental interface to do this doesn't integrate with Polkit policy.
    // TODO: use a KAuth helper at some point

    QProcess process;
    process.setProgram(u"pkexec"_s);
    process.setArguments({u"rpm-ostree"_s, u"usroverlay"_s});

    if (!process.startDetached()) {
        qWarning() << "Failed to enable developer mode: " << process.errorString();
        return;
    }

    Q_EMIT enabledChanged();
}
