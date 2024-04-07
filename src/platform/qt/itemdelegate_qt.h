//
// Created by nightrider on 06.04.24.
//

#ifndef LATEX_ITEMDELEGATE_QT_H
#define LATEX_ITEMDELEGATE_QT_H

#include "latex.h"
#include <QTableWidget>
#include <QPainter>
#include <platform/qt/graphic_qt.h>

class TeXItemDelegate: public QAbstractItemDelegate
{
    Q_OBJECT
public:
    using render_ptr = std::shared_ptr<tex::TeXRender>;
    int padding=4;
    int text_size=20;

public slots:
    void updateModelData(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles)
    {
        if (!roles.contains(modelRole)) return;

        for(int row = topLeft.row(); row <= bottomRight.row(); ++row)
            for (int col = topLeft.column(); col <= bottomRight.column(); ++col)
            {
                QModelIndex index = topLeft.sibling(row,col);
                render_ptr old_render = index.data(modelRole).value<render_ptr>();
                if (old_render!=nullptr)
                    createModelData(index,old_render->getWidth());
            }
    };

private:
    int modelRole = Qt::UserRole;

    render_ptr createModelData(const QModelIndex& index, int width) const
    {
        QString latex = index.data(Qt::DisplayRole).toString();
        render_ptr render = create_render(latex,100);
        QVariant vrender = QVariant::fromValue<TeXItemDelegate::render_ptr>(render);
        QAbstractItemModel* model = const_cast<QAbstractItemModel*>(index.model());
        model->setData(index, vrender, modelRole);
        return render;
    }

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
        render_ptr render = index.data(modelRole).value<render_ptr>();
        if (render==nullptr)
            render = createModelData(index,width);
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
