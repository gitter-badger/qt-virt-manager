#include "filesystems.h"

/*
 * http://libvirt.org/formatdomain.html#elementsFilesystems
 */

#define LXC_FS_TYPES QStringList()<<"Mount"<<"File"<<"Block"<<"RAM"<<"Bind"

#define QEMU_FS_TYPES QStringList()<<"Mount"

#define XEN_FS_TYPES QStringList()<<"None"

FileSystems::FileSystems(
        QWidget *parent, virConnectPtr *connPtrPtr) :
    _QWidget(parent, connPtrPtr)
{
    typeLabel = new QLabel("Type:", this);
    type = new QComboBox(this);
    QString connType;
    if ( nullptr!=ptr_ConnPtr && nullptr!=*ptr_ConnPtr ) {
        connType = QString(virConnectGetType(*ptr_ConnPtr)).toLower();
    } else
        emit ptrIsNull();
    if ( connType=="lxc" ) {
        type->addItems(LXC_FS_TYPES);
    } else if ( connType=="qemu" ) {
        type->addItems(QEMU_FS_TYPES);
    } else if ( connType=="xen" ) {
        type->addItems(XEN_FS_TYPES);
    };
    typeLayout = new QHBoxLayout(this);
    typeLayout->addWidget(typeLabel);
    typeLayout->addWidget(type);
    typeWdg = new QWidget(this);
    typeWdg->setLayout(typeLayout);

    info = new QStackedWidget(this);
    for (int i=0; i<type->count(); i++) {
        setWidgets(type->itemText(i));
    };

    commonLayout = new QVBoxLayout(this);
    commonLayout->addWidget(typeWdg);
    commonLayout->addWidget(info);
    commonLayout->addStretch(-1);
    setLayout(commonLayout);
    connect(type, SIGNAL(currentIndexChanged(int)),
            info, SLOT(setCurrentIndex(int)));
}

/* public slots */
QDomDocument FileSystems::getDataDocument() const
{
    QDomDocument doc;
    _QWidget *wdg = static_cast<_QWidget*>(info->currentWidget());
    if ( nullptr!=wdg ) doc = wdg->getDataDocument();
    return doc;
}

/* private slots */
void FileSystems::setWidgets(QString _type)
{
    if ( _type.toLower()=="mount" ) {
        info->addWidget(new MountFsType(this, connType));
    } else if ( _type.toLower()=="file" ) {
        info->addWidget(new FileFsType(this, connType));
    } else if ( _type.toLower()=="block" ) {
        info->addWidget(new BlockFsType(this, connType));
    } else if ( _type.toLower()=="ram" ) {
        info->addWidget(new RAMFsType(this, connType));
    } else if ( _type.toLower()=="bind" ) {
        info->addWidget(new BindFsType(this, connType));
    };
}
