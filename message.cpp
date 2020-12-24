#include "message.h"
#include <QPainter>

Message::Message(int x, int y, int w, int h, QGraphicsItem *parent)
    : StaticItem(x, y, w, h, parent)
{
}

void Message::setText(const char *text)
{
    mText = QString(text);
}

void Message::setText(std::string text)
{
    mText = QString(text.c_str());
}

void Message::setLevel(const unsigned &level)
{
    mLevel = level;
}

void Message::setAlign(const unsigned &align)
{
    mAlign = align;
}

void Message::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen;
    pen.setWidth(2);
    pen.setBrush(QBrush(QColor(195, 219, 237)));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);

    QPainterPath path;
    path.addRect(mx, my, mw, mh);
    painter->fillPath(path, QBrush(QColor(225, 236, 244)));
    painter->drawPath(path);

    pen.setBrush(QBrush(QColor(9, 126, 207)));
    painter->setPen(pen);
    painter->setFont(QFont("Times", 14, QFont::Normal));

    if (mAlign == 1)
    {
        painter->drawText(QRect(mx + 14, my + 14, mw - 14, mh - 14), Qt::TextWordWrap, mText);
    }
    else
    {
        painter->drawText(QPoint(mx + 14, my + (mh / 2) + 7), mText);
    }
}
