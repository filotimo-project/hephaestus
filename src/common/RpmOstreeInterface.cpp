/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <QDBusPendingCallWatcher>

#include "RpmOstreeDbusInterfaces.h"
#include "RpmOstreeInterface.h"
#include "RpmOstreeInterfaceTypes.h"

#define RPM_OSTREE_SERVICE_NAME u"org.projectatomic.rpmostree1"_s

using namespace Qt::Literals::StringLiterals;

RpmOstreeInterface::RpmOstreeInterface(QObject *parent)
    : QObject(parent)
{
    registerDbusTypes();

    QString objectPath = u"/org/projectatomic/rpmostree1/Sysroot"_s;

    m_rpmOstreeSysrootInterface = new OrgProjectatomicRpmostree1SysrootInterface(RPM_OSTREE_SERVICE_NAME, objectPath, QDBusConnection::systemBus(), this);

    // Register the client with rpm-ostree
    // Ensures the daemon stays running while we are using it
    m_clientId = {{u"id"_s, u"hephaestus"_s}};
    auto pendingCall = m_rpmOstreeSysrootInterface->RegisterClient(m_clientId);

    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pendingCall, this);

    QObject::connect(watcher, &QDBusPendingCallWatcher::finished, [](QDBusPendingCallWatcher *localWatcher) {
        QDBusReply<void> reply = *localWatcher;
        if (reply.isValid()) {
            qWarning() << "Failed to register client with rpm-ostree:" << reply.error().message();
        }

        localWatcher->deleteLater();
    });
}

RpmOstreeInterface::~RpmOstreeInterface()
{
    // Unregister the client when the interface is destroyed
    auto pendingCall = m_rpmOstreeSysrootInterface->UnregisterClient(m_clientId);

    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pendingCall, this);

    QObject::connect(watcher, &QDBusPendingCallWatcher::finished, [](QDBusPendingCallWatcher *localWatcher) {
        QDBusReply<void> reply = *localWatcher;
        if (reply.isValid()) {
            qWarning() << "Failed to unregister client with rpm-ostree -- this may cause the daemon to stay open indefinitely:" << reply.error().message();
        }

        localWatcher->deleteLater();
    });

    delete m_rpmOstreeSysrootInterface;
}

OrgProjectatomicRpmostree1OSInterface *RpmOstreeInterface::os(QDBusObjectPath objectPath)
{
    return new OrgProjectatomicRpmostree1OSInterface(RPM_OSTREE_SERVICE_NAME, objectPath.path(), QDBusConnection::systemBus(), this);
}

OrgProjectatomicRpmostree1OSExperimentalInterface *RpmOstreeInterface::osExperimental(QDBusObjectPath objectPath)
{
    return new OrgProjectatomicRpmostree1OSExperimentalInterface(RPM_OSTREE_SERVICE_NAME, objectPath.path(), QDBusConnection::systemBus(), this);
}

OrgProjectatomicRpmostree1TransactionInterface *RpmOstreeInterface::transaction(QDBusObjectPath objectPath)
{
    return new OrgProjectatomicRpmostree1TransactionInterface(RPM_OSTREE_SERVICE_NAME, objectPath.path(), QDBusConnection::systemBus(), this);
}

RpmOstreeInterface *sharedRpmOstreeInterface()
{
    static RpmOstreeInterface instance;
    return &instance;
}
