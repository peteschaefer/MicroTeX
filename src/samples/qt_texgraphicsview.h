//
// Created by nightrider on 07.04.24.
//

#ifndef LATEX_QT_TEXGRAPHICSVIEW_H
#define LATEX_QT_TEXGRAPHICSVIEW_H

#include <QGraphicsView>
#include "platform/qt/graphic_view_qt.h"

namespace qt_graphics
{
/**
 * Convenience method for setting up a QGraphicsView with a single item
 * @param view
 * @param latex
 * @param text_size
 */
   inline void setLaTeX(QGraphicsView* view, const std::wstring& latex, float text_size=20.0) {
        QGraphicsScene* scene = new QGraphicsScene(view);
        tex::TeXGraphicsItem* item = new tex::TeXGraphicsItem();
        item->renderLaTeX(latex, view->width(), 4, text_size);

        QRectF bounds = item->boundingRect();
        //  scale to view
        qreal rescale = std::min(view->width()/bounds.width(),view->height()/bounds.height());
        item->setScale(0.9*rescale);
        scene->addItem(item);
        view->setScene(scene);
    }

    inline void setTextSize(QGraphicsView* view, float size) {
        //  not implemented
    }

    inline void savePDF(QGraphicsView* view, QString fileName) {
        //  not yet implemented
    }

    inline void saveSVG(QGraphicsView* view, QString fileName) {
      //  not yet implemented
    }
}

#endif //LATEX_QT_TEXGRAPHICSVIEW_H
