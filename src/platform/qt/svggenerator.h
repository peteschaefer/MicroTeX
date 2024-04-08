/*  schaefer on 08.04.24.
 */

#ifndef LATEX_SVGGENERATOR_H
#define LATEX_SVGGENERATOR_H

#include <QPaintEngine>
#include <QPainterPath>
#include <QRawFont>
#include <QSvgGenerator>

/**
 *  A wrapper for QSvgGenerator.
 *  Replace text with paths.
 */
namespace svgtool
{
  namespace TextToPath
  {
    extern QHash<QString,QRawFont> _raw;
/*
    bool useFont(QString fileName, qreal pixelsize=20.0) {
      QRawFont rfont (fileName,pixelsize);
      _raw.insert(rfont.familyName(),rfont);
    }
*/
    QRawFont rawFont(QFont font);

    QPainterPath toPath(QFont font, QString text, QPointF pos);
    QPainterPath toPath(QTextItem item, QPointF pos={0,0});
  };

  class SvgPaintEngine: public QPaintEngine
  {
  private:
    //  the underlying QPaintEngine used for QSvgGenerator
    QPaintEngine* _delegate;
  public:
    SvgPaintEngine(QPaintEngine* del);
    virtual ~SvgPaintEngine() {}

    //  the only method that is actually re-implemented
    void drawTextItem(const QPointF &p, const QTextItem &item) override;

    //  delegate to QPaintEngine
    bool begin(QPaintDevice *pdev) override;
    bool end() override;
    void updateState(const QPaintEngineState &state) override;
    void drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr) override;
    Type type() const override;
    //
    void drawRects(const QRect *rects, int rectCount) override;
    void drawRects(const QRectF *rects, int rectCount) override;
    void drawLines(const QLine *lines, int lineCount) override;
    void drawLines(const QLineF *lines, int lineCount) override;
    void drawEllipse(const QRectF &r) override;
    void drawEllipse(const QRect &r) override;
    void drawPath(const QPainterPath &path) override;
    void drawPoints(const QPointF *points, int pointCount) override;
    void drawPoints(const QPoint *points, int pointCount) override;
    void drawPolygon(const QPointF *points, int pointCount, PolygonDrawMode mode) override;
    void drawPolygon(const QPoint *points, int pointCount, PolygonDrawMode mode) override;
    void drawTiledPixmap(const QRectF &r, const QPixmap &pixmap, const QPointF &s) override;
    void drawImage(const QRectF &r, const QImage &pm, const QRectF &sr, Qt::ImageConversionFlags flags) override;
    QPoint coordinateOffset() const override;


  };

  class PSvgGenerator : public QSvgGenerator
  {
  public:
    //  just make this one public:
    using QSvgGenerator::paintEngine;
    using QSvgGenerator::metric;
    using QSvgGenerator::initPainter;
    using QSvgGenerator::redirected;
    using QSvgGenerator::sharedPainter;
  };

  class SvgGenerator: public QPaintDevice
  {
  private:
    PSvgGenerator _delegate;
    SvgPaintEngine _engine;
  public:
    SvgGenerator();
    ~SvgGenerator() {}

    //  delegate to QSvgGenerator
    QString title() const;
    void setTitle(const QString &title);

    QString description() const;
    void setDescription(const QString &description);

    QSize size() const;
    void setSize(const QSize &size);

    QRect viewBox() const;
    QRectF viewBoxF() const;
    void setViewBox(const QRect &viewBox);
    void setViewBox(const QRectF &viewBox);

    QString fileName() const;
    void setFileName(const QString &fileName);

    QIODevice *outputDevice() const;
    void setOutputDevice(QIODevice *outputDevice);

    void setResolution(int dpi);
    int resolution() const;


    int devType() const override;
    QPaintEngine *paintEngine() const override;

  protected:
    int metric(PaintDeviceMetric metric) const override;
    void initPainter(QPainter *painter) const override;
    QPaintDevice *redirected(QPoint *offset) const override;
    QPainter *sharedPainter() const override;
  };
}
#endif // LATEX_SVGGENERATOR_H
