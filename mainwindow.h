#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "etiket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QList<etiket*> etiketListesi;
    bool kontrolEtiketDuzeni();
    QList<QString> imagePaths1;

private:
    Ui::MainWindow *ui;
    QLabel *label;
    int moveNumber;
    void updateLabel();

private slots:
    void increaseCount();
};
#endif // MAINWINDOW_H
