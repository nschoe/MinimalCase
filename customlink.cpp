#include "customlink.h"

#include <QPainter>
#include <QDebug>
#include <QCursor>
#include <math.h>

CustomLink::CustomLink(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsObject *parent)
    : QGraphicsObject(parent),
      m_line(this),
      m_label(&m_line)
{
	m_line.setLine(x1, y1, x2, y2);

	setAcceptHoverEvents(true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemIsMovable, true);

	// The only way to center the text, is to use setHtml with <center> **and** set a text width
	m_label.setHtml(QString("<center>some text</center>"));
	qreal a = x2 - x1;
	qreal b = y2 - y1;
	m_label.setTextWidth(m_line.line().length());
	m_label.setRotation(22); // Rotate the link so it's parallel to the line
	m_label.setPos(x1, y1);  // Set position to first point, so that text is centered on the line

	// Now we need to translate the text so it's above the line and not beneath it
	QLineF nV = m_line.line().normalVector();
	nV.setLength(30);
	m_label.setPos(nV.p2());
}

QRectF CustomLink::boundingRect() const
{
	return m_line.boundingRect();
}

QPainterPath CustomLink::shape() const
{
	QPainterPathStroker *stroke = new QPainterPathStroker;
	stroke->setWidth(12.0);
	stroke->setJoinStyle(Qt::RoundJoin);


	return stroke->createStroke(m_line.shape());
}

void CustomLink::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	// We don't have much to do here: the QGraphicsLineItem will paint itself, since this is a child

	// We do paint the boundingRect and the shape though, to illustrate the issue
	painter->setPen(Qt::red);
	painter->drawRect(boundingRect());

	painter->setPen(Qt::blue);
	painter->drawPath(shape());

	painter->setPen(Qt::green);
	painter->drawPath(m_label.shape());
}

void CustomLink::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	Q_UNUSED(event);
	qDebug() << "Entering";
	setOpacity(0.3);
	setCursor(QCursor(Qt::PointingHandCursor));
}

void CustomLink::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	Q_UNUSED(event);
	qDebug() << "Leaving";
	setOpacity(1.0);
	setCursor(QCursor(Qt::ArrowCursor));
}
