#ifndef MESSAGE_H
#define MESSAGE_H

#include "staticitem.h"

class Message : public StaticItem
{
public:
    Message(int x, int y, int w, int h, QGraphicsItem *parent = nullptr);
    void setText(const char* text);
    void setText(std::string text);
    void setLevel(const unsigned& level);
    void setAlign(const unsigned& align);

protected:
    QString mText {"-"};
    unsigned mLevel {0};
    unsigned mAlign {0};
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
};

#endif // MESSAGE_H
