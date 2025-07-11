/**
 * SPDX-FileCopyrightText: Thomas Duckworth <tduck@filotimoproject.org>
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <QDBusPendingCallWatcher>

#include "RpmOstreeDbusInterfaces.h"
#include "RpmOstreeInterface.h"
#include "RpmOstreeInterfaceTypes.h"

using namespace Qt::Literals::StringLiterals;

RpmOstreeInterface::RpmOstreeInterface(QObject *parent)
    : QObject(parent)
{
    registerDbusTypes();

    m_rpmOstreeSysrootInterface =
        new OrgProjectatomicRpmostree1SysrootInterface(RPM_OSTREE_SERVICE_NAME, RPM_OSTREE_SYSROOT_OBJECT_PATH, QDBusConnection::systemBus(), this);

    // Register the client with rpm-ostree.
    m_clientId[QLatin1String("id")] = QVariant{QStringLiteral("hephaestus")};

    auto pendingCall = m_rpmOstreeSysrootInterface->RegisterClient(m_clientId);

    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pendingCall, this);

    QObject::connect(watcher, &QDBusPendingCallWatcher::finished, [](QDBusPendingCallWatcher *localWatcher) {
        QDBusPendingReply<> reply = *localWatcher;
        localWatcher->deleteLater();
        if (reply.isError()) {
            qWarning() << "Failed to register client with rpm-ostree:" << qPrintable(QDBusConnection::systemBus().lastError().message());
        }
    });
}

RpmOstreeInterface::~RpmOstreeInterface()
{
    // Unregister the client when the interface is destroyed.
    auto pendingCall = m_rpmOstreeSysrootInterface->UnregisterClient(m_clientId);

    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pendingCall, this);

    QObject::connect(watcher, &QDBusPendingCallWatcher::finished, [](QDBusPendingCallWatcher *localWatcher) {
        QDBusPendingReply<> reply = *localWatcher;
        localWatcher->deleteLater();
        if (reply.isError()) {
            qWarning() << "Failed to unregister client with rpm-ostree -- this may cause the daemon to stay open indefinitely:"
                       << qPrintable(QDBusConnection::systemBus().lastError().message());
        }
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

OrgProjectatomicRpmostree1TransactionInterface *RpmOstreeInterface::transaction(QDBusConnection peerConnection)
{
    return new OrgProjectatomicRpmostree1TransactionInterface(RPM_OSTREE_SERVICE_NAME, u"/"_s, peerConnection, this);
}

RpmOstreeInterface *sharedRpmOstreeInterface()
{
    static RpmOstreeInterface instance;
    return &instance;
}
