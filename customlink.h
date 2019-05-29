#ifndef CUSTOMLINK_H
#define CUSTOMLINK_H

#include <QGraphicsObject>
#include <QGraphicsLineItem>
#include <QPainterPath>
#include <QGraphicsTextItem>

class CustomLink : public QGraphicsObject
{
public:
	CustomLink(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsObject *parent = nullptr);

	QRectF boundingRect() const;
	QPainterPath shape() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

	QGraphicsLineItem m_line;
	QGraphicsTextItem m_label;
};

#endif // CUSTOMLINK_H
