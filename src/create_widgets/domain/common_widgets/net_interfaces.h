#ifndef NET_INTERFACES_H
#define NET_INTERFACES_H

#include <QStackedWidget>
#include "net_if_widgets/tcp_tunnel.h"
#include "net_if_widgets/multicast_tunnel.h"
#include "net_if_widgets/pci_passthrough.h"
#include "net_if_widgets/direct_attachment.h"
#include "net_if_widgets/generic_ethernet.h"
#include "net_if_widgets/userspace_slirp.h"
#include "net_if_widgets/bridge_to_lan.h"
#include "net_if_widgets/virtual_network.h"

class NetInterfaces : public _QWidget
{
    Q_OBJECT
public:
    explicit NetInterfaces(
            QWidget        *parent      = nullptr,
            virConnectPtr*  connPtrPtr  = nullptr);
    QComboBox       *type;
    QStackedWidget  *info;

private:
    QLabel          *typeLabel;
    QHBoxLayout     *typeLayout;
    QWidget         *typeWdg;
    QVBoxLayout     *commonLayout;

    QString          connType;

public slots:
    QDomDocument     getDataDocument() const;

private slots:
    void             setWidgets(QString);
};

#endif // NET_INTERFACES_H
