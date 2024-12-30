#include "dragdropevent.h"
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QDrag>
#include <QMouseEvent>
#include <QMimeData>
DragDropEvent::DragDropEvent(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(400, 300);
    setAcceptDrops(true);

    boatIcon = new QLabel(this);
    boatIcon->setPixmap(QPixmap(":/images/boat.png"));
    boatIcon->move(10, 10);
    boatIcon->show();
    boatIcon->setAttribute(Qt::WA_DeleteOnClose);

    carIcon = new QLabel(this);
    carIcon->setPixmap(QPixmap(":/images/car.png"));
    carIcon->move(100, 10);
    carIcon->show();
    carIcon->setAttribute(Qt::WA_DeleteOnClose);

    houseIcon = new QLabel(this);
    houseIcon->setPixmap(QPixmap(":/images/house.png"));
    houseIcon->move(10, 80);
    houseIcon->show();
    houseIcon->setAttribute(Qt::WA_DeleteOnClose);


}

DragDropEvent::~DragDropEvent()
{

}

void DragDropEvent::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
    {
        return;
    }
    QPixmap pixmap = *child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/Myitemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor (127, 127, 127, 127));
    painter.end();
    child->setPixmap (tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt:: MoveAction)
    {
        child->close();
    } else {
        child->show();
        child->setPixmap (pixmap);

    }
}
void DragDropEvent::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/Myitemdata"))
    {
        if (event->source () == this)
        {
            event->setDropAction (Qt:: MoveAction);
            event->accept();
        } else
        {
            event->acceptProposedAction();
        }
    }
    else
    {
        event->ignore();
    }
}
void DragDropEvent::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/Myitemdata")) {
        QByteArray itemData = event->mimeData()->data ("application/Myitemdata");
        QDataStream dataStream(&itemData, QIODevice:: ReadOnly);
        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap (pixmap);
        newIcon->move (event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute (Qt:: WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction (Qt:: MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}
