#include "mainwindow.h"
#include <QMenuBar>
#include <QGraphicsView>
#include <QFileDialog>
#include <QtDBus/QtDBus>
#include "sharedmemory.h"

USE_NAMESPACE_ESI

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    initUI();
}

MainWindow::~MainWindow() {
}

void MainWindow::initUI() {
    this->resize(640, 480);
    // setup menubar
    fileMenu = menuBar()->addMenu("&File");

    imageScene = new QGraphicsScene(this);
    imageView = new QGraphicsView(imageScene);
    setCentralWidget(imageView);

    createActions();
}

void MainWindow::createActions() {

    // create actions, add them to menus
    openAction = new QAction("&Open", this);
    fileMenu->addAction(openAction);
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openImage()));

    sendAction = new QAction("&Send", this);
    fileMenu->addAction(sendAction);
    connect(sendAction, SIGNAL(triggered(bool)), this, SLOT(sendMessageToImg()));
}

void MainWindow::saveImageToSharedMemory(QImage &image) {
    SharedMemoryForImage shm;
    shm.saveImage(image);
}

void MainWindow::callFinishedSlot(QDBusPendingCallWatcher *call) {
    QDBusPendingReply<QString> reply = *call;
    if (reply.isError()) {
        qInfo() << "Reply was:" << reply.error().message();
    } else {
        qDebug() << "Reply was:" << reply.value();
    }
    call->deleteLater();
}

int MainWindow::sendMessageToImg() {
    QDBusInterface iface("com.esi.img", "/", "", QDBusConnection::sessionBus());
    if (iface.isValid()) {
        QDBusPendingCall async = iface.asyncCall("handleDbusMessage", "Image saved");
        QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(async, this);

        QObject::connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher *)),
                         this, SLOT(callFinishedSlot(QDBusPendingCallWatcher *)));
        return 0;
    } else {
        qCritical() << QDBusConnection::sessionBus().lastError().message();
        return 1;
    }
}

void MainWindow::openImage() {
    QFileDialog dialog(this);
    dialog.setWindowTitle("Open Image");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Images (*.png *.bmp *.jpg)"));

    QStringList filePaths;
    if (dialog.exec()) {
        filePaths = dialog.selectedFiles();
        showImage(filePaths.at(0));
    }
}

void MainWindow::showImage(QString path) {
    imageScene->clear();
    imageView->resetTransform();

    QImage image;
    image.load(path);
    saveImageToSharedMemory(image);

    QPixmap pixmap = QPixmap::fromImage(image);
    imageScene->addPixmap(pixmap);
    imageScene->update();
    imageView->setSceneRect(pixmap.rect());
}

