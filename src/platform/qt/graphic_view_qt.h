//
// Created by nightrider on 07.04.24.
//

#ifndef LATEX_GRAPHIC_VIEW_QT_H
#define LATEX_GRAPHIC_VIEW_QT_H

#include "graphic/graphic.h"
#include "platform/qt/graphic_qt.h"

#include <QGraphicsItemGroup>

namespace tex
{
    class Graphics2D_qt_view : public Graphics2D_qt
    {
    protected:
        QGraphicsItemGroup* _group;
        QTransform _transform;
        QPen _pen;

        void setPen() override { _pen = makePen(); }
    public:
        Graphics2D_qt_view() : Graphics2D_qt(nullptr) {
            _group = new QGraphicsItemGroup();
        }

        QGraphicsItem* result() const {
            return _group;
        }

//      re-implements Graphics2D
        void reset() override {
            _transform.reset();
            _sx = _sy = 1.f;
        }

        void scale(float sx, float sy) override {
            _sx *= sx;
            _sy *= sy;
            _transform.setMatrix(
                    _sx, _transform.m12(), _transform.m13(),
                    _transform.m21(), _sy, _transform.m23(),
                    _transform.m31(), _transform.m32(), _transform.m33() );
        }

        void translate(float dx, float dy) override {
            _transform.setMatrix(
                    _sx, _transform.m12(), _transform.m13(),
                    _transform.m21(), _sy, _transform.m23(),
                    _transform.m31()+dx*_sx, _transform.m32()+dy*_sy, _transform.m33() );
        }

        void rotate(float angle) override {
            //_painter->rotate(qRadiansToDegrees(angle));
            _transform.setMatrix(
                    _sx, _transform.m12(), _transform.m13(),
                    _transform.m21(), _sy, _transform.m23(),
                    _transform.m31(), _transform.m32(), _transform.m33() );
        }

        void rotate(float angle, float px, float py) override {
            //_painter->translate(px, py);
            //_painter->rotate(qRadiansToDegrees(angle));
            //_painter->translate(-px, -py);
            _transform.setMatrix(
                    _sx, _transform.m12(), _transform.m13(),
                    _transform.m21(), _sy, _transform.m23(),
                    _transform.m31(), _transform.m32(), _transform.m33() );
        }

        void drawText(const wstring &t, float x, float y) override {
            QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::fromStdWString(t), _group);
            //QFontMetricsF fmtx(_font->getQFont());
            text->setFont(_font->getQFont());
            text->setPos(x,y-_font->getAscent()*_sy);
            //  note: y = baseline
            text->setTransform(_transform);
            text->setBrush(getQBrush());
            _group->addToGroup(text);
        }

        void drawLine(float x, float y1, float x2, float y2) override {
            QGraphicsLineItem* line = new QGraphicsLineItem(x,y1,x2,y2, _group);
            line->setPen(makePen());
            line->setTransform(_transform);
            _group->addToGroup(line);
        }

        void drawRect(float x, float y, float w, float h) override {
            drawRect(x,y,w,h,makePen());
        }

        void fillRect(float x, float y, float w, float h) override {
            drawRect(x,y,w,h,makePen(), getQBrush());
        }

        void drawRoundRect(float x, float y, float w, float h, float rx, float ry) override {
            drawRoundRect(x, y, w, h, rx, ry, makePen());
        }

        void fillRoundRect(float x, float y, float w, float h, float rx, float ry) override {
            drawRoundRect(x, y, w, h, rx, ry, makePen(), getQBrush());
        }

    private:
        void drawRect(float x, float y, float w, float h, QPen pen, QBrush brush = QBrush())
        {
            QGraphicsRectItem* rect = new QGraphicsRectItem(x,y,w,h);
            rect->setPen(pen);
            rect->setBrush(brush);
            rect->setTransform(_transform);
            _group->addToGroup(rect);
        }
        void drawRoundRect(float x, float y, float w, float h, float rx, float ry, QPen pen, QBrush brush = QBrush())
        {
            //  is a bit more involved. We need the help of a QPaintPath
            QPainterPath path;
            path.addRoundedRect(x,y,w,h,rx,ry);
            QGraphicsPathItem* item = new QGraphicsPathItem(path,_group);
            item->setPen(pen);
            item->setBrush(brush);
            item->setTransform(_transform);
            _group->addToGroup(item);
        }
    };
}
#endif //LATEX_GRAPHIC_VIEW_QT_H
