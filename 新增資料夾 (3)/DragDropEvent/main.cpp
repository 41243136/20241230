#include "dragdropevent.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a (argc, argv);
    DragDropEvent w1,w2;
    w1.setWindowTitle (QStringLiteral("滑鼠拖放事件處理第一視窗"));
    w2.setWindowTitle (QStringLiteral("滑鼠拖放事件處理第二視窗"));
    w1.move(100,100);
    w2.move(600,100);
    w1.show();
    w2.show();
    return a.exec();
}
