#ifndef DRAGDROPEVENT_H
#define DRAGDROPEVENT_H

#include <QWidget>
#include <QLabel>
class DragDropEvent : public QWidget
{
    Q_OBJECT

public:
    DragDropEvent(QWidget *parent = nullptr);
    ~DragDropEvent();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    QLabel *boatIcon;
    QLabel *carIcon;
    QLabel *houseIcon;
};
#endif // DRAGDROPEVENT_H
