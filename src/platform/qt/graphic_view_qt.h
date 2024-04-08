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
    class TeXRender;

    class TeXGraphicsItem: public QGraphicsItemGroup
    {
    private:
      void setupRender(TeXRender* render,int padding);
      void setupText(const std::wstring& latex, int width, int padding, float text_size);

    public:
      TeXGraphicsItem(QGraphicsItem *parent = nullptr) : QGraphicsItemGroup() { }

      void setRender(TeXRender* render, int padding=0);
      void setLaTeX(const std::wstring& latex, int width, int padding=0, float text_size=20.0);
    };


    class Graphics2D_qt_view : public Graphics2D_qt
    {
    protected:
      TeXGraphicsItem* _group;
      QTransform _tf;
      QPen _pen;

      void setPen() override { _pen = makePen(); }
    public:
        Graphics2D_qt_view(TeXGraphicsItem* group) : Graphics2D_qt(nullptr), _group(group) { }

//      re-implements Graphics2D
        void reset() override;
        void scale(float sx, float sy) override;
        void translate(float dx, float dy) override;
        void rotate(float angle) override;
        void rotate(float angle, float px, float py) override;

        void drawText(const std::wstring &t, float x, float y) override;
        void drawTextItem(QFont font, QFontMetricsF* metrics, QPointF pos, QString qtext) override;
        void drawLine(float x, float y1, float x2, float y2) override;
        void drawRect(float x, float y, float w, float h) override;
        void fillRect(float x, float y, float w, float h) override;
        void drawRoundRect(float x, float y, float w, float h, float rx, float ry) override;
        void fillRoundRect(float x, float y, float w, float h, float rx, float ry) override;

    private:
        void drawRect(float x, float y, float w, float h, QPen pen, QBrush brush = QBrush());
        void drawRoundRect(float x, float y, float w, float h, float rx, float ry, QPen pen, QBrush brush = QBrush());
    };
}
#endif //LATEX_GRAPHIC_VIEW_QT_H
