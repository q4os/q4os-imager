#ifndef DRIVELISTMODEL_H
#define DRIVELISTMODEL_H

/*
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2020 Raspberry Pi Ltd | Copyright (C) 2026 Jupiter4 foundation
 */

#include <QAbstractItemModel>
#include <QMap>
#include <QHash>
#include "drivelistitem.h"
#include "drivelistmodelpollthread.h"

class DriveListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    DriveListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void startPolling();
    void stopPolling();

    enum driveListRoles {
        deviceRole = Qt::UserRole + 1, descriptionRole, sizeRole, isUsbRole, isScsiRole, isReadOnlyRole, mountpointsRole
    };

public slots:
    void processDriveList(std::vector<Drivelist::DeviceDescriptor> l);

protected:
    QMap<QString,DriveListItem *> _drivelist;
    QHash<int, QByteArray> _rolenames;
    DriveListModelPollThread _thread;
};

#endif // DRIVELISTMODEL_H
