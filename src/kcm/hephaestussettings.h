/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "CurrentTransactionWatcher.h"
#include "DeveloperMode.h"
#include <KQuickConfigModule>

class HephaestusSettings : public KQuickConfigModule
{
    Q_OBJECT
    Q_PROPERTY(DeveloperMode *developerMode READ developerMode CONSTANT)
    Q_PROPERTY(CurrentTransactionWatcher *currentTransactionWatcher READ currentTransactionWatcher CONSTANT)

public:
    HephaestusSettings(QObject *parent, const KPluginMetaData &data);

    DeveloperMode *developerMode() const
    {
        return m_developerMode;
    }

    CurrentTransactionWatcher *currentTransactionWatcher() const
    {
        return m_transactionWatcher;
    }

private:
    DeveloperMode *m_developerMode;
    CurrentTransactionWatcher *m_transactionWatcher;
};
