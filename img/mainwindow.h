#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();
    void createActions();

private:
    QMenu *fileMenu;
    QGraphicsScene *imageScene;
    QGraphicsView *imageView;
    QAction *loadAction;

private slots:
    void loadImageFromSharedMemory();
    void showImage(const QPixmap &image);

public slots:
    Q_SCRIPTABLE QString handleDbusMessage(const QString &message);
};
#endif // MAINWINDOW_H
