#ifndef QSPICE_WIDGET_H
#define QSPICE_WIDGET_H

#include <QTimer>
#include <QScrollArea>
#include <QLabel>
#include <QHBoxLayout>

#define  QSPICE_WIDGET_H_INSIDE

#include "qspice-session.h"
#include "qspice-audio.h"
#include "qspice-cursor-channel.h"
#include "qspice-display-channel.h"
#include "qspice-inputs-channel.h"
#include "qspice-main-channel.h"
#include "qspice-playback-channel.h"
#include "qspice-record-channel.h"
#include "qspice-smartcard-channel.h"
#include "qspice-smartcard-manager.h"
#include "qspice-usbredir-channel.h"
#include "qspice-usbdevice-manager.h"
#include "qspice-webdav-channel.h"

class QSpiceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QSpiceWidget(QWidget *parent = nullptr);
    virtual ~QSpiceWidget();

    /*
     *  Connect to SPICE source by uri, start spice-session.
     */
    bool connectToSpiceSource(QString &uri);

    /*
     * Disconnect from SPICE source, stop spice-session.
     */
    void disconnectFromSpiceSource();

    /*
     * Send key sequience to guest.
     */
    void sendKeySequience(Qt::Key);

    /*
     * Send files to guest.
     */
    void fileCopyAsync(QStringList&);

    /*
     * Copy guest Clipboard data to client Clipboard.
     */
    void copyClipboardDataFromGuest();

    /*
     * Send client Clipboard data to guest Clipboard.
     */
    void sendClipboardDataToGuest(quint32, const uchar*, size_t);

signals:
    /*
     * Emitted, when display resize event occurred.
     */
    void displayResized(const QSize&);

    /*
     * Emitted, when new portion of files will downloaded to guest.
     */
    void downloaded(int, int);

    /*
     * Emitted the state, when channel will initiated.
     * true is success.
     */
    void cursorChannelChanged(bool);

    /*
     * Emitted the state, when channel will initiated.
     * true is success.
     */
    void inputsChannelChanged(bool);

    /*
     * Emitted the state, when channel will initiated.
     * true is success.
     */
    void displayChannelChanged(bool);

    /*
     * Emitted the state, when channel will initiated.
     * true is success.
     */
    void usbredirChannelChanged(bool);

    /*
     * Emitted the state, when channel will initiated.
     * true is success.
     */
    void smartcardChannelChanged(bool);

    /*
     * Emitted the state, when channel will initiated.
     * true is success.
     */
    void webdavChannelChanged(bool);

    /*
     * Emitted the state, when channel will initiated.
     * true is success.
     */
    void playbackChannelChanged(bool);

    /*
     * Emitted the state, when channel will initiated.
     * true is success.
     * true is success.
     */
    void recordChannelChanged(bool);

    /*
     * Emitted, when error occured.
     */
    void errMsg(QString&);

    /*
     * In develop.
     * Emitted, when guest/client clipboards released.
     */
    void clipboardsReleased(bool);

private:
    QString                  guestName;
    Qt::TransformationMode   tr_mode;
    QImage                  *img;
    QScrollArea             *scrolled;
    QLabel                  *m_Image;
    QTimer                   resizeTimer;
    QHBoxLayout             *commonLayout;
    int                      _height, _width,
                             init_h, init_w;
    qreal                    zoom;

protected:
    QSpiceSession           *spiceSession;
    QSpiceMainChannel       *main;
    QSpiceDisplayChannel    *display;
    QSpiceInputsChannel     *inputs;
    QSpiceCursorChannel     *cursor;
    QSpiceSmartcardChannel  *smartcard;
    QSpiceUSBRedirChannel   *usbredir;
    QSpiceWebDAVChannel     *webdav;
    QSpicePlaybackChannel   *playback;
    QSpiceRecordChannel     *record;
    QSpiceUsbDeviceManager  *usbDevManager;
    QSpiceSmartcardManager  *smartcardManager;
    QSpiceAudio             *spiceAudio;

private slots:
    void setChannel(QSpiceChannel *channel);
    void obstructChannel(int);

    void mainAgentUpdate();
    void mainClipboardSelection(uint, void*, uint);
    void clipboardSelectionGrab();
    void guestClipboardSelectionRelease(uint);
    void clientClipboardSelectionRequest(uint, uint);
    void mainMouseUpdate();

    void usbDevAutoConnectFailed(QString&, QString&);
    void usbDevAdded(QString&);
    void usbDevError(QString&, QString&);
    void usbDevRemoved(QString&);

    void cardInserted(QString&);
    void cardRemoved(QString&);
    void readerAdded(QString&);
    void readerRemoved(QString&);

    void displayPrimaryCreate(
         int                 format,
         int                 width,
         int                 height,
         int                 stride,
         int                 shmid,
         void*               imgdata);

    void displayInvalidate(
        int                  x,
        int                  y,
        int                  width,
        int                  height);

    void displayPrimaryDestroy();

    void displayMark(int mark);

    void setClientCursor(
            int              width,
            int              height,
            int              hot_x,
            int              hot_y,
            void*            rgba);

    void reloadUsbDevList(void*);
    void reloadSmartcardList(void*);

    bool eventFilter(QObject *object, QEvent *event);
    void resizeEvent(QResizeEvent *event);
    void resizeDone();

public slots:
    /*
     * Set basic name for shapshots.
     */
    void setGuestName(QString&);

    /*
     * Set new widget size (width, height).
     */
    void setNewSize(int, int);
    void updateSize(int, int);

    /*
     * Show up USB Device widget.
     */
    void showUsbDevWidget();

    /*
     * Show up Smartcard widget.
     */
    void showSmartCardWidget();

    /*
     * Get and save Screenshot (pixbuff) from guest.
     */
    void getScreenshot();

    /*
     * Set transformation mode for display.
     */
    void setTransformationMode(Qt::TransformationMode);
};

#undef QSPICE_WIDGET_H_INSIDE

#endif // QSPICE_WIDGET_H
