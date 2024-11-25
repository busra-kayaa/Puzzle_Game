#include "etiket.h"
#include "mainwindow.h"
#include <QMimeData>
#include <QDrag>
#include <QMessageBox>
#include <QDebug>

etiket::etiket(QWidget *parent) : QLabel(parent)
{
    setScaledContents(true);
    setFrameShape(QFrame::Box);
    setAcceptDrops(true); // Sürükle bırak özelliği verilir
}

void etiket::dragEnterEvent(QDragEnterEvent *event) {
    event->accept(); // Sürükleme kabul ediliyor
}

void etiket::setDragEnabled(bool enabled)
{
    dragEnabled = enabled; // Sürükleme özelliğini aç/kapat
}

void etiket::dropEvent(QDropEvent *event) {
    if (!dragEnabled) return;

    etiket *gelen = qobject_cast<etiket*>(event->source());
    if (gelen && gelen != this && !pixmap()->isNull()) { // Boş bir etikete düşürmeyi engelle
        int mesafeKriteriX = width();  // Yatay mesafe kriteri
        int mesafeKriteriY = height(); // Dikey mesafe kriteri

        QPoint gelenPos = gelen->pos();
        QPoint thisPos = pos();

        int deltaX = qAbs(gelenPos.x() - thisPos.x());
        int deltaY = qAbs(gelenPos.y() - thisPos.y());

        // Yatay, dikey ve çapraz hareket kontrolü
        if ((deltaX <= mesafeKriteriX && deltaY == 0) || // Yatay
            (deltaY <= mesafeKriteriY && deltaX == 0) || // Dikey
            (deltaX <= mesafeKriteriX && deltaY <= mesafeKriteriY)) { // Çapraz

            // Etiketlerin görsellerini değiştir
            QImage birakilan(pixmap()->toImage());
            setPixmap(QPixmap::fromImage(gelen->pixmap()->toImage()));
            gelen->setPixmap(QPixmap::fromImage(birakilan));

            // MainWindow'dan düzen kontrolü
            MainWindow *mainWindow = qobject_cast<MainWindow*>(topLevelWidget());
            if (mainWindow && mainWindow->kontrolEtiketDuzeni()) {
                QMessageBox::information(topLevelWidget(), "Oyun Kazanıldı", "Tebrikler! Oyun bitti.");
                return;
            }

            emit Count(); // Hamle sayısını artır
        }
    }
}


void etiket::mouseMoveEvent(QMouseEvent *event) {
    if (!dragEnabled) return; // Eğer sürükleme devre dışıysa işlem yapma

    QMimeData *mdata = new QMimeData();
    mdata->setImageData(pixmap()->toImage());
    QDrag *suruklenen = new QDrag(this);
    suruklenen->setMimeData(mdata);
    suruklenen->setPixmap(mdata->imageData().value<QPixmap>());
    suruklenen->exec(Qt::MoveAction);
}
