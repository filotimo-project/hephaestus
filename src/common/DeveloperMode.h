/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <QObject>

#include "RpmOstreeInterface.h"

class DeveloperMode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled NOTIFY enabledChanged)

public:
    explicit DeveloperMode(QObject *parent)
        : QObject(parent)
        , m_rpmOstreeInterface(sharedRpmOstreeInterface())
    {
    }

    bool isEnabled() const;

    // Enables "developer mode" by calling `rpm-ostree usroverlay`.
    Q_SLOT void enable();

    Q_SIGNAL void enabledChanged();

private:
    class RpmOstreeInterface *m_rpmOstreeInterface;
};
