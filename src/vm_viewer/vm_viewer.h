#ifndef VM_VIEWER_H
#define VM_VIEWER_H

#include <QMainWindow>
#include <QStatusBar>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTime>
#include <QFileDialog>
#include <QSettings>
#include <QIcon>
#include <QVBoxLayout>
#include <QLabel>
#include "vm_viewer/viewer_toolbar.h"
#include "vm_state_widget.h"
#include "virt_objects/virt_entity_config.h"
#include "virt_objects/_virt_thread.h"
#include "create_widgets/snapshot/create_snapshot_dialog.h"
#include "create_widgets/snapshot/snapshot_action_dialog.h"
#include <QDebug>

#define PERIOD      333

class VM_Viewer : public QMainWindow
{
    Q_OBJECT
public:
    explicit VM_Viewer(
            QWidget        *parent     = nullptr,
            virConnectPtr*  connPtrPtr = nullptr,
            QString         arg1       = QString(),
            QString         arg2       = QString());
    virtual ~VM_Viewer();
    QString          connName, domain, TYPE;
    virConnectPtr*   ptr_ConnPtr;
    virErrorPtr      virtErrors = nullptr;
    QSettings        settings;
    ViewerToolBar   *viewerToolBar = nullptr;
    VM_State_Widget *vm_stateWdg = nullptr;
    uint             timerId = 0;
    uint             killTimerId = 0;
    uint             counter = 0;

    QVBoxLayout     *infoLayout = nullptr;
    QLabel          *icon = nullptr, *msg = nullptr;
    QWidget         *info = nullptr;

signals:
    void             finished(QString&);
    void             errorMsg(QString&);
    void             addNewTask(TASK);

public slots:
    virtual void     init();
    virtual void     closeEvent(QCloseEvent *ev);
    void             sendErrMsg(QString&);
    void             sendErrMsg(QString&, uint);
    void             sendConnErrors();
    void             sendGlobalErrors();
    void             resendExecMethod(const QStringList&);
    void             startCloseProcess();
    virtual void     reconnectToVirtDomain();
    virtual void     sendKeySeqToVirtDomain(Qt::Key);
    virtual void     getScreenshotFromVirtDomain();
    virtual void     copyFilesToVirtDomain();
    virtual void     copyToClipboardFromVirtDomain();
    virtual void     pasteClipboardToVirtDomain();
    void             showErrorInfo(QString&);
};

#endif // VM_VIEWER_H
