#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    // Resimlerin yolları
    QList<QString> imagePaths = {
        ":/res/images/0.png",
        ":/res/images/1.png",
        ":/res/images/2.png",
        ":/res/images/3.png",
        ":/res/images/4.png",
        ":/res/images/5.png",
        ":/res/images/6.png",
        ":/res/images/7.png",
        ":/res/images/8.png",
        ":/res/images/9.png",
        ":/res/images/10.png",
        ":/res/images/11.png",
        ":/res/images/12.png",
        ":/res/images/13.png",
        ":/res/images/14.png",
        ":/res/images/15.png",
        ":/res/images/16.png",
        ":/res/images/17.png",
        ":/res/images/18.png",
        ":/res/images/19.png",
        ":/res/images/20.png",
        ":/res/images/21.png",
        ":/res/images/22.png",
        ":/res/images/23.png",
        ":/res/images/24.png"
    };

    int X = 50, Y = 50;

    // Etiketler için listeyi hazırlama
    for (int i = 0; i < 5; ++i) {
        for (int k = 0; k < 5; ++k) {
            etiket *et = new etiket(this);
            et->setGeometry(X, Y, 200, 150);

            // Eğer resim listesi boş değilse rastgele bir resim seçelim
            if (!imagePaths.isEmpty()) {
                int randomIndex = QRandomGenerator::global()->bounded(imagePaths.size());

                QString selectedImage = imagePaths[randomIndex];

                QPixmap pixmap(selectedImage);
                if (!pixmap.isNull()) {
                    et->setPixmap(pixmap);
                }

                // Seçilen resmi listeden çıkaralım
                imagePaths.removeAt(randomIndex);

                // Etiketi listeye ekle
                etiketListesi.append(et);

                connect(et, &etiket::Count, this, &MainWindow::increaseCount);
            }
            et->show();
            X += 200;
        }
        X = 50;
        Y += 150;
    }

    QString puzzleImagePath = ":/res/images/puzzle.jpg";
    etiket *et1 = new etiket(this);
    et1->setGeometry(1200, 55, 650, 420);
    et1->setFrameShape(QFrame::NoFrame);
    et1->setAcceptDrops(false); // Varsayılan Qt işlevi
    QPixmap pixmap1(puzzleImagePath);
    et1->setPixmap(pixmap1);
    et1->setDragEnabled(false); // Özelleştirilmiş sürükleme kontrolü
    et1->show();

    label = new QLabel(this);
    label->setGeometry(1200, 440, 200, 200);
    label->setText("Hamle Sayısı:   0");

    QFont font = label->font();
    font.setPointSize(15);
    label->setFont(font);
    label->setStyleSheet("QLabel { color: #0000FF; }");
    label->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::increaseCount() {
    moveNumber++;
    updateLabel();
}

void MainWindow::updateLabel() {
    label->setText("Hamle Sayısı:   " + QString::number(moveNumber));
}

bool MainWindow::kontrolEtiketDuzeni()
{
    QList<QString> imagePaths1 = {
        ":/res/images/0.png",
        ":/res/images/1.png",
        ":/res/images/2.png",
        ":/res/images/3.png",
        ":/res/images/4.png",
        ":/res/images/5.png",
        ":/res/images/6.png",
        ":/res/images/7.png",
        ":/res/images/8.png",
        ":/res/images/9.png",
        ":/res/images/10.png",
        ":/res/images/11.png",
        ":/res/images/12.png",
        ":/res/images/13.png",
        ":/res/images/14.png",
        ":/res/images/15.png",
        ":/res/images/16.png",
        ":/res/images/17.png",
        ":/res/images/18.png",
        ":/res/images/19.png",
        ":/res/images/20.png",
        ":/res/images/21.png",
        ":/res/images/22.png",
        ":/res/images/23.png",
        ":/res/images/24.png"
    };

    // Resimlerin sayısı etiket sayısı ile aynı olmalı
    if (etiketListesi.size() != imagePaths1.size()) {
        return false;
    }

    // Her etiketi ve karşılık gelen resmi kontrol et
    for (int i = 0; i < imagePaths1.size(); ++i) {
        etiket *etiket = etiketListesi.at(i);

        // Etiketin resmi ile beklenen resmi karşılaştır
        QImage etiketResmi = etiket->pixmap()->toImage();
        QString resimAdi = imagePaths1.at(i);
        QImage beklenenResim(resimAdi);

        // Resimlerin formatlarını aynı yapalım
        etiketResmi = etiketResmi.convertToFormat(QImage::Format_ARGB32);
        beklenenResim = beklenenResim.convertToFormat(QImage::Format_ARGB32);

        // Karşılaştırma yapalım
        if (etiketResmi != beklenenResim) {
            qDebug() << "Resimler eşleşmiyor: Etiket #" << etiketResmi << " ve Beklenen resim: " << beklenenResim;
            return false;
        }
    }

    return true;
}
