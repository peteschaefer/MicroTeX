#if (defined(BUILD_QT) || defined(BUILD_SKIA)) && !defined(MEM_CHECK)

#include "latex.h"
#include "samples.h"
#include "platform/qt/graphic_qt.h"
#include "platform/qt/itemdelegate_qt.h"
#include "qt_mainwindow.h"

#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

#ifdef BUILD_SKIA
  initGL();
#endif

  tex::LaTeX::init();
  MainWindow mainwin;
  mainwin.show();

#if 1
  QTableWidget table;
  table.setColumnCount(1);
  table.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  TeXItemDelegate* delegate = new TeXItemDelegate;
  table.setItemDelegateForColumn(0, delegate);

  const std::vector<std::wstring>& samples = mainwin._samples._samples;
  table.setRowCount(samples.size());
  for(int i=0; i < samples.size(); ++i) {
      QTableWidgetItem* item = new QTableWidgetItem;
      item->setText(QString::fromStdWString(samples[i]));
      table.setItem(i, 0, item);
      table.setRowHeight(i,80);
  }
    table.show();
  //    to properly adjust the row height, we call sizeHint() explicitly.
  //    would prefer to only call it on demand, i.e. when item is painted first (or so?!)
    for(int i=0; i < samples.size(); ++i) {
        QSize cellSize = delegate->sizeHint(table.width(),table.model()->index(i,0));
        table.setRowHeight(i,cellSize.height());
    }

    QObject::connect(table.model(),&QAbstractItemModel::dataChanged, delegate,
                     &TeXItemDelegate::updateModelData, Qt::UniqueConnection);
#endif


  int retn = app.exec();

  tex::LaTeX::release();
  return retn;
}

#endif
