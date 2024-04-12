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
    // connects to Model changes
    void updateModelData(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());;

private:
    int modelRole = Qt::UserRole;

    render_ptr createModelData(const QModelIndex& index, int width) const;
    render_ptr create_render(QString latex, int width) const;
public:
    render_ptr get_render(const QModelIndex& index, int width) const;
    //  implements QAbstractItemDelegate
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(int width, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

Q_DECLARE_METATYPE(TeXItemDelegate::render_ptr);

#endif //LATEX_ITEMDELEGATE_QT_H
