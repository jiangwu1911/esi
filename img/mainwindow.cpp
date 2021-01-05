#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBuffer>
#include <QDebug>
#include "sharedmemory.h"

USE_NAMESPACE_ESI

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    initUI();
}

MainWindow::~MainWindow() {
}

void MainWindow::initUI() {
    this->resize(640, 480);

    fileMenu = menuBar()->addMenu("&Load");

    imageScene = new QGraphicsScene(this);
    imageView = new QGraphicsView(imageScene);
    setCentralWidget(imageView);

    createActions();
}

void MainWindow::createActions() {
    // create actions, add them to menus
    loadAction = new QAction("&Load", this);
    fileMenu->addAction(loadAction);
    connect(loadAction, SIGNAL(triggered(bool)), this, SLOT(loadImageFromSharedMemory()));
}

void MainWindow::loadImageFromSharedMemory() {
    QImage image;
    SharedMemoryForImage shm;
    shm.loadImage(image);
    showImage(QPixmap::fromImage(image));
}

void MainWindow::showImage(const QPixmap &image) {
    qDebug() << image.size();
    imageScene->clear();
    imageView->resetTransform();
    imageScene->addPixmap(image);
    imageScene->update();
    imageView->setSceneRect(image.rect());
}

Q_SCRIPTABLE QString MainWindow::handleDbusMessage(const QString &message) {
    qDebug() << "Got a message:" << message;
    if (message == "Image saved") {
        this->loadImageFromSharedMemory();
    }
    return QString("Image has been read");
}
