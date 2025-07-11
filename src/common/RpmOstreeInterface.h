/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include <QDBusArgument>
#include <QList>
#include <QMap>
#include <QMetaType>
#include <QObject>
#include <QString>
#include <QVariant>
#include <qdbusconnection.h>

#include "RpmOstreeDbusInterfaces.h"

#define RPM_OSTREE_SERVICE_NAME u"org.projectatomic.rpmostree1"_s
#define RPM_OSTREE_SYSROOT_OBJECT_PATH u"/org/projectatomic/rpmostree1/Sysroot"_s

using namespace Qt::Literals::StringLiterals;

class RpmOstreeInterface : public QObject
{
    Q_OBJECT

    friend RpmOstreeInterface *sharedRpmOstreeInterface();

public:
    OrgProjectatomicRpmostree1SysrootInterface *sysroot() const
    {
        return m_rpmOstreeSysrootInterface;
    }

    // The following depend on dynamically determined object paths or DBus addresses that must be provided from the sysroot interface.
    //
    // Note: The object path for the currently booted OS interface is returned by the Booted property on the sysroot interface.
    OrgProjectatomicRpmostree1OSInterface *os(QDBusObjectPath objectPath);
    OrgProjectatomicRpmostree1OSExperimentalInterface *osExperimental(QDBusObjectPath objectPath);
    // Transaction connection addresses are returned by methods which start a transaction on the sysroot interface: e.g. Upgrade, Deploy, etc.
    OrgProjectatomicRpmostree1TransactionInterface *transaction(QDBusConnection peerConnection);

private:
    explicit RpmOstreeInterface(QObject *parent = nullptr);
    ~RpmOstreeInterface() override;

    OrgProjectatomicRpmostree1SysrootInterface *m_rpmOstreeSysrootInterface;
    QVariantMap m_clientId;
};

// This function returns a singleton instance of RpmOstreeInterface.
// This gets called in any class which needs access to it as a dependency.
RpmOstreeInterface *sharedRpmOstreeInterface();
