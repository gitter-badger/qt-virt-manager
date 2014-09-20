#ifndef SCSI_POOL_STUFF_H
#define SCSI_POOL_STUFF_H

#include "_pool_stuff.h"

class SCSI_Pool_Stuff : public _Pool_Stuff
{
    Q_OBJECT
public:
    explicit SCSI_Pool_Stuff(QWidget *parent = 0);

signals:

public slots:
    QString getStorageXMLDescFileName() const;
};

#endif // SCSI_POOL_STUFF_H