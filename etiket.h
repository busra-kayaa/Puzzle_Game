#ifndef ETIKET_H
#define ETIKET_H

#include <QWidget>
#include <QLabel>
#include <QMimeData>
#include <QDrag>
#include <QDragEnterEvent>

class etiket : public QLabel
{
    Q_OBJECT
public:
    explicit etiket(QWidget *parent = nullptr);
    void setDragEnabled(bool enabled);
    // Getter metodu
        QString getCurrentImagePath() const {
            return currentImagePath;
        }

        // Setter metodu
        void setCurrentImagePath(const QString &path) {
            currentImagePath = path;
        }

private:
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);
    void mouseMoveEvent(QMouseEvent *event);

    QString currentImagePath; // Etikete atanmış olan resmin yolu

    bool dragEnabled = true; // Varsayılan olarak sürükleme etkin

signals:
    void Count();
};

#endif // ETIKET_H
