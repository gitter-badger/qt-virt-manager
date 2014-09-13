#ifndef CREATE_POOL_H
#define CREATE_POOL_H

#include "_create_storage_widgets/_create_storage.h"
#include "_create_storage_widgets/dir_pool_stuff.h"
#include "_create_storage_widgets/fs_pool_stuff.h"
#include "_create_storage_widgets/netfs_pool_stuff.h"
#include "_create_storage_widgets/logical_pool_stuff.h"
#include "_create_storage_widgets/disk_pool_stuff.h"
#include "_create_storage_widgets/iscsi_pool_stuff.h"
#include "_create_storage_widgets/scsi_pool_stuff.h"
#include "_create_storage_widgets/mpath_pool_stuff.h"
#include "_create_storage_widgets/rbd_pool_stuff.h"
#include "_create_storage_widgets/sheepdog_pool_stuff.h"
#include "_create_storage_widgets/gluster_pool_stuff.h"
#include "_create_storage_widgets/zfs_pool_stuff.h"

class CreatePool : public _CreateStorage
{
    Q_OBJECT
public:
    explicit CreatePool(QWidget *parent = 0);

signals:

private:
    QLabel          *uuidLabel;
    QLineEdit       *uuid;
    QHBoxLayout     *uuidLayout;
    QWidget         *uuidWdg;
    _Pool_Stuff     *info = NULL;

public slots:
    QString getStorageXMLDescFileName() const;

private slots:
    void typeChanged(int);
};

#endif // CREATE_POOL_H
