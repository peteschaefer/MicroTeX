/*  schaefer on 08.04.24.
 */

#include "svggenerator.h"

svgtool::SvgGenerator::SvgGenerator()
    : _delegate(), _engine(new SvgPaintEngine(_delegate.paintEngine()))
{
  assert(_delegate.paintEngine()!=nullptr);
}

QPaintEngine *svgtool::SvgGenerator::paintEngine() const {
  SvgPaintEngine *p = const_cast<SvgPaintEngine*>(&_engine);
  return dynamic_cast<QPaintEngine*>(p);
}

//  delegate QPaintDevice
int svgtool::SvgGenerator::devType() const { return _delegate.devType(); }
int svgtool::SvgGenerator::metric(
    QPaintDevice::PaintDeviceMetric metric) const {
  return _delegate.metric(metric);
}
void svgtool::SvgGenerator::initPainter(QPainter *painter) const {
  _delegate.initPainter(painter);
}
QPaintDevice *svgtool::SvgGenerator::redirected(QPoint *offset) const {
  return _delegate.redirected(offset);
}
QPainter *svgtool::SvgGenerator::sharedPainter() const {
  return _delegate.sharedPainter();
}

QString svgtool::SvgGenerator::title() const { return _delegate.title(); }
void svgtool::SvgGenerator::setTitle(const QString &title) { _delegate.setTitle(title); }
QString svgtool::SvgGenerator::description() const { return _delegate.description(); }
void svgtool::SvgGenerator::setDescription(const QString &description) { _delegate.setDescription(description); }
QSize svgtool::SvgGenerator::size() const { return _delegate.size(); }
void svgtool::SvgGenerator::setSize(const QSize &size) { _delegate.setSize(size); }
QRect svgtool::SvgGenerator::viewBox() const { return _delegate.viewBox(); }
QRectF svgtool::SvgGenerator::viewBoxF() const { return _delegate.viewBoxF(); }
void svgtool::SvgGenerator::setViewBox(const QRect &viewBox) { _delegate.setViewBox(viewBox); }
void svgtool::SvgGenerator::setViewBox(const QRectF &viewBox) { _delegate.setViewBox(viewBox); }
QString svgtool::SvgGenerator::fileName() const { return _delegate.fileName(); }
void svgtool::SvgGenerator::setFileName(const QString &fileName) { _delegate.setFileName(fileName); }
QIODevice *svgtool::SvgGenerator::outputDevice() const { return _delegate.outputDevice(); }
void svgtool::SvgGenerator::setOutputDevice(QIODevice *outputDevice) { _delegate.setOutputDevice(outputDevice); }
void svgtool::SvgGenerator::setResolution(int dpi) { _delegate.setResolution(dpi); }
int svgtool::SvgGenerator::resolution() const { return _delegate.resolution(); }

//  delegate QPaintEngine
QPaintEngine::Type svgtool::SvgPaintEngine::type() const { return _delegate->type(); }
void svgtool::SvgPaintEngine::drawPixmap(const QRectF &r, const QPixmap &pm,
                                         const QRectF &sr) { _delegate-> drawPixmap(r,pm,sr); }
void svgtool::SvgPaintEngine::updateState(const QPaintEngineState &state) {
  //  don't delegate. The state is only present in this->.
  const QPaintEngineState* astate = &state;
  const QPaintEngineState* mystate = &state;
  assert(astate==mystate);
  QPaintEngineState*& dstate = ((SvgPaintEngine*)_delegate)->state;
  if (!dstate) dstate = const_cast<QPaintEngineState*>(mystate);
  //  ugly hack, because engine->state is set from outside, by QPainter.
  //  Yes this is ugly, but that's the way it is. Thanks Qt.
  _delegate->updateState(state);
}
bool svgtool::SvgPaintEngine::end() { return _delegate->end(); }
bool svgtool::SvgPaintEngine::begin(QPaintDevice *pdev) {
  return _delegate->begin(pdev);
}
void svgtool::SvgPaintEngine::drawRects(const QRect *rects, int rectCount) {
  if (rectCount>0) _delegate->drawRects(rects, rectCount);
}
void svgtool::SvgPaintEngine::drawRects(const QRectF *rects, int rectCount) {
  if (rectCount>0) _delegate->drawRects(rects, rectCount);
}
void svgtool::SvgPaintEngine::drawLines(const QLine *lines, int lineCount) {
  if (lineCount>0) _delegate->drawLines(lines, lineCount);
}
void svgtool::SvgPaintEngine::drawLines(const QLineF *lines, int lineCount) {
  if (lineCount>0) _delegate->drawLines(lines, lineCount);
}
void svgtool::SvgPaintEngine::drawEllipse(const QRectF &r) {
  _delegate->drawEllipse(r);
}
void svgtool::SvgPaintEngine::drawEllipse(const QRect &r) {
  _delegate->drawEllipse(r);
}
void svgtool::SvgPaintEngine::drawPath(const QPainterPath &path) {
  _delegate->drawPath(path);
}
void svgtool::SvgPaintEngine::drawPoints(const QPointF *points, int pointCount) {
  if (pointCount>0) _delegate->drawPoints(points, pointCount);
}
void svgtool::SvgPaintEngine::drawPoints(const QPoint *points, int pointCount) {
  if (pointCount>0) _delegate->drawPoints(points, pointCount);
}
void svgtool::SvgPaintEngine::drawPolygon(const QPointF *points, int pointCount,
                                          QPaintEngine::PolygonDrawMode mode) {
  if (pointCount>0) _delegate->drawPolygon(points, pointCount, mode);
}
void svgtool::SvgPaintEngine::drawPolygon(const QPoint *points, int pointCount,
                                          QPaintEngine::PolygonDrawMode mode) {
  if (pointCount>0) _delegate->drawPolygon(points, pointCount, mode);
}
void svgtool::SvgPaintEngine::drawTextItem(const QPointF &p,
                                           const QTextItem &textItem) {
  _delegate->drawTextItem(p, textItem);
}
void svgtool::SvgPaintEngine::drawTiledPixmap(const QRectF &r,
                                              const QPixmap &pixmap,
                                              const QPointF &s) {
  _delegate->drawTiledPixmap(r, pixmap, s);
}
void svgtool::SvgPaintEngine::drawImage(const QRectF &r, const QImage &pm,
                                        const QRectF &sr,
                                        Qt::ImageConversionFlags flags) {
  _delegate->drawImage(r, pm, sr, flags);
}
QPoint svgtool::SvgPaintEngine::coordinateOffset() const {
  return _delegate->coordinateOffset();
}
svgtool::SvgPaintEngine::SvgPaintEngine(QPaintEngine *del) : _delegate(del) {
  assert(_delegate!=nullptr);
}
