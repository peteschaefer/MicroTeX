//
// Created by nightrider on 07.04.24.
//

#ifndef LATEX_QT_TEXGRAPHICSVIEW_H
#define LATEX_QT_TEXGRAPHICSVIEW_H

#include <QGraphicsView>
#include "platform/qt/graphic_view_qt.h"

namespace qt_graphics
{
    QGraphicsItem* makeGraphicsViewItem(const std::wstring& latex,
                                               int width, int padding=4,
                                               float text_size=20.0);

    inline void setLaTeX(QGraphicsView* view, const std::wstring& latex, float text_size=20.0) {
        QGraphicsScene* scene = new QGraphicsScene(view);
        QGraphicsItem* item = makeGraphicsViewItem(latex,view->width(), 0, text_size);
        QRectF bounds = item->boundingRect();
        //  scale to view
        qreal rescale = std::max(view->width()/bounds.width(),view->height()/bounds.height());
        item->setScale(rescale);
        scene->addItem(item);
        view->setScene(scene);
    }

    inline void setTextSize(QGraphicsView* view, float size) {
        //  not implemented
    }

    inline void savePDF(QGraphicsView* view, QString fileName) {
        //  not yet implemented
    }

    inline QGraphicsItem* makeGraphicsViewItem(const std::wstring& latex,
                                               int width, int padding,
                                               float text_size)
    {
        using namespace tex;
        TeXRender* render = LaTeX::parse(
                latex,
                width - padding * 2,
                text_size,
                text_size / 3.f,
                0xff424242);

        Graphics2D_qt_view g2;
        render->draw(g2, padding, padding);
        delete render;
        return g2.result();
    }
}

#endif //LATEX_QT_TEXGRAPHICSVIEW_H
