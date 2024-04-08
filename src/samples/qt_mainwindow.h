#if (defined(BUILD_QT) || defined(BUILD_SKIA)) && !defined(MEM_CHECK)

#ifndef QT_MAINWINDOW_H
#define QT_MAINWINDOW_H

#include "samples.h"

#define QT_GRAPHICSVIEW 1
#ifdef BUILD_SKIA
  #include "qt_skiatexwidget.h"
#elif defined(QT_GRAPHICSVIEW)
  class QGraphicsView;
#else
  #include "qt_texwidget.h"
#endif

#include <QWidget>
#include <QTextEdit>
#include <QSpinBox>

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent=nullptr);

  //! \return file name, or empty string on cancel
  QString saveAsDialog();

protected slots:
  void nextClicked();
  void renderClicked();
  void saveClicked();
  void fontSizeChanged(int size);

protected:
#if defined(QT_GRAPHICSVIEW)
  QGraphicsView* _texwidget;
#else
  TeXWidget* _texwidget;
#endif
  QTextEdit* _textedit;
  QSpinBox* _sizespin;

  tex::Samples _samples;
};

#endif
#endif
