#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QtDBus>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();
    void createActions();
    void saveImageToSharedMemory(QImage &image);

private:
    QMenu *fileMenu;
    QGraphicsScene *imageScene;
    QGraphicsView *imageView;
    QAction *openAction;
    QAction *sendAction;

private slots:
    void showImage(QString);
    void openImage();
    int sendMessageToImg();
    void callFinishedSlot(QDBusPendingCallWatcher *call);
};

#endif // MAINWINDOW_H
