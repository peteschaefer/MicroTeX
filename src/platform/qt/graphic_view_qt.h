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

        void drawText(const wstring &t, float x, float y) override {
            QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::fromStdWString(t), _group);
            QFontMetricsF fmtx(_font->getQFont());
            text->setFont(_font->getQFont());
            text->setPos(x,y-fmtx.ascent()*_sy);
            //  todo y = baseline. This is not yet precise.
            text->setTransform(_transform);
            _group->addToGroup(text);
        }
    };
}
#endif //LATEX_GRAPHIC_VIEW_QT_H
