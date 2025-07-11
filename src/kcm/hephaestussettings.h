/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "DeveloperOptions.h"
#include <KQuickConfigModule>

class HephaestusSettings : public KQuickConfigModule
{
    Q_OBJECT
    Q_PROPERTY(DeveloperOptions *developerOptions READ developerOptions CONSTANT)

public:
    HephaestusSettings(QObject *parent, const KPluginMetaData &data);

    DeveloperOptions *developerOptions() const
    {
        return m_developerOptions;
    }

private:
    DeveloperOptions *m_developerOptions;
};
