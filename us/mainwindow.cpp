#include "mainwindow.h"
#include <QMenuBar>
#include <QGraphicsView>
#include <QFileDialog>
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
}

void MainWindow::saveImageToSharedMemory(QImage &image) {
    SharedMemory sharedmemory;
    sharedmemory.saveImage(image);
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

