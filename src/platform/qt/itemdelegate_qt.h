//
// Created by nightrider on 06.04.24.
//

#ifndef LATEX_ITEMDELEGATE_QT_H
#define LATEX_ITEMDELEGATE_QT_H

#include "latex.h"
#include <QTableWidget>

class TeXItemDelegate: public QAbstractItemDelegate
{
    //Q_OBJECT
public:
    using render_ptr = std::shared_ptr<tex::TeXRender>;
    int padding=4;
    int text_size=20;

private:
    render_ptr create_render(QString latex, int width) const
    {
        tex::TeXRender* raw = tex::LaTeX::parse(
                latex.toStdWString(),
                width - padding * 2,
                text_size,
                text_size / 3.f,
                0xff424242);
        return render_ptr(raw);
    }
public:
    render_ptr get_render(const QModelIndex& index, int width) const
    {
        render_ptr render = index.data(Qt::UserRole).value<render_ptr>();
        if (render==nullptr) {
            QString latex = index.data(Qt::DisplayRole).toString();
            render = create_render(latex, width);
            QAbstractItemModel* model = const_cast<QAbstractItemModel*>(index.model());
            QVariant vrender = QVariant::fromValue<TeXItemDelegate::render_ptr>(render);
            model->setData(index, vrender, Qt::UserRole);
        }
        render->setWidth(width,tex::Alignment::left);
        return render;
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        //painter->drawText(option.rect.left(),option.rect.bottom(),text);
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setClipRect(option.rect);

        tex::Graphics2D_qt g2(painter);
        render_ptr render = get_render(index,option.rect.width());
        render->draw(g2, option.rect.left()+padding, option.rect.top()+padding);
        painter->setClipping(false);
    }

    QSize sizeHint(int width, const QModelIndex &index) const {
        render_ptr render = get_render(index,width);
        width = render->getWidth();
        int height = render->getHeight();
        return QSize(width+2*padding,height+2*padding);
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        return sizeHint(option.rect.width(),index);
    }
};

#endif //LATEX_ITEMDELEGATE_QT_H
