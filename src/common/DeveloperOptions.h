/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <QObject>

#include "RpmOstreeInterface.h"

class DeveloperOptions : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool developerModeEnabled READ developerModeEnabled NOTIFY developerModeEnabledChanged)

public:
    explicit DeveloperOptions(QObject *parent = nullptr);

    bool developerModeEnabled() const;

    // Enables "developer mode" by calling the LiveFs method on the experimental OS interface.
    // This is the same as `rpm-ostree usroverlay`.
    Q_SLOT void enableDeveloperMode();

    Q_SIGNAL void developerModeEnabledChanged();

private:
    class RpmOstreeInterface *m_rpmOstreeInterface;
};
