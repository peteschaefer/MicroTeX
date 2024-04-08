/*  Created by schaefer on 08.04.24. */

#include "graphic_view_qt.h"
#include "latex.h"
#include "render.h"

#include <QtWidgets/QGraphicsPathItem>

using namespace tex;

void TeXGraphicsItem::setupRender(tex::TeXRender *render, int padding) {
  Graphics2D_qt_view g2(this);
  render->draw(g2, padding, padding);
}

void TeXGraphicsItem::setupText(const std::wstring &latex, int width,
                                    int padding, float text_size) {
  TeXRender* render = tex::LaTeX::parse(
      latex,
      width - padding * 2,
      text_size,
      text_size / 3.f,
      0xff424242);
  setupRender(render,padding);
  delete render;
}

void TeXGraphicsItem::setRender(tex::TeXRender *render, int padding) {
  setupRender(render,padding);
}

void TeXGraphicsItem::setLaTeX(const std::wstring &latex, int width,
                                   int padding, float text_size) {
  setupText(latex,width,padding,text_size);
}

void Graphics2D_qt_view::drawRoundRect(float x, float y, float w, float h,
                                       float rx, float ry, QPen pen,
                                       QBrush brush) {
  //  is a bit more involved. We need the help of a QPaintPath
  QPainterPath path;
  path.addRoundedRect(x,y,w,h,rx,ry);
  QGraphicsPathItem* item = new QGraphicsPathItem(path,_group);
  item->setPen(pen);
  item->setBrush(brush);
  item->setTransform(_tf);
  _group->addToGroup(item);
}

void Graphics2D_qt_view::drawRect(float x, float y, float w, float h, QPen pen,
                                  QBrush brush) {
  QGraphicsRectItem* rect = new QGraphicsRectItem(x,y,w,h);
  rect->setPen(pen);
  rect->setBrush(brush);
  rect->setTransform(_tf);
  _group->addToGroup(rect);
}

void Graphics2D_qt_view::fillRoundRect(float x, float y, float w, float h,
                                       float rx, float ry) {
  drawRoundRect(x, y, w, h, rx, ry, makePen(), getQBrush());
}

void Graphics2D_qt_view::drawRoundRect(float x, float y, float w, float h,
                                       float rx, float ry) {
  drawRoundRect(x, y, w, h, rx, ry, makePen());
}

void Graphics2D_qt_view::fillRect(float x, float y, float w, float h) {
  drawRect(x,y,w,h,makePen(), getQBrush());
}

void Graphics2D_qt_view::drawRect(float x, float y, float w, float h) {
  drawRect(x,y,w,h,makePen());
}

void Graphics2D_qt_view::drawLine(float x, float y1, float x2, float y2) {
  QGraphicsLineItem* line = new QGraphicsLineItem(x,y1,x2,y2, _group);
  line->setPen(makePen());
  line->setTransform(_tf);
  _group->addToGroup(line);
}

void Graphics2D_qt_view::drawTextItem(QFont font, QFontMetricsF *metrics,
                                      QPointF pos, QString qtext) {
  QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(qtext, _group);
  text->setFont(font);

  QPointF posf (pos.x(), pos.y() - metrics->ascent()*_tf.m22());
  //  note: y = baseline
  text->setTransform(_tf);
  text->setPos(posf);
  text->setBrush(getQBrush());
  _group->addToGroup(text);
}

void Graphics2D_qt_view::drawText(const std::wstring &t, float x, float y) {
  drawTextItem(_font->getQFont(), _font->getQFontMetrics(), QPointF(x,y), QString::fromStdWString(t));
}

void Graphics2D_qt_view::rotate(float angle, float px, float py)
{
  translate( px, py);
  rotate(angle);
  translate(-px,-py);
}

void Graphics2D_qt_view::rotate(float angle) {
  _tf.rotateRadians(angle);
}

void Graphics2D_qt_view::translate(float dx, float dy) {
  _tf.translate(dx,dy);
}

void Graphics2D_qt_view::scale(float sx, float sy) {
  _sx *= sx;
  _sy *= sy;
  _tf.scale(sx,sy);
}

void Graphics2D_qt_view::reset() {
  _tf.reset();
  _sx = _sy = 1.f;
}
