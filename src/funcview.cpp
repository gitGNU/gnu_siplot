/* siplot -- simple graph plotter and math tool.
   Copyright (C) 2010 - 2011 David Jenni <dave.j@gmx.ch>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "funcview.h"
#include "ui_funcview.h"

QwtPlotMagnifierEx::QwtPlotMagnifierEx(QwtPlotCanvas *canvas) :
    QwtPlotMagnifier(canvas)
{
}

void QwtPlotMagnifierEx::rescale(double factor)
{
    QwtPlotMagnifier::rescale(factor);
    emit rescaleEvent();
}

void QwtPlotMagnifierEx::doRescale(double factor)
{
    QwtPlotMagnifier::rescale(factor);
}

Axis::Axis(QwtPlotMarker::LineStyle style, double x, double y, QString str) :
    m_label(str)
{
    setLineStyle(style);

    if (style == QwtPlotMarker::HLine) {
        m_symbol = new QwtSymbol(QwtSymbol::RTriangle, QBrush(Qt::SolidPattern), QPen(Qt::black), QSize(10, 10));
        setLabel(m_label);
        setLabelAlignment(Qt::AlignRight);
    } else {
        m_symbol = new QwtSymbol(QwtSymbol::Triangle, QBrush(Qt::SolidPattern), QPen(Qt::black), QSize(10, 10));
        setLabel(m_label);
        setLabelAlignment(Qt::AlignTop);
    }

    QwtPlotMarker::setSymbol(*m_symbol);

    setXValue(x);
    setYValue(y);
}

Axis::~Axis(void)
{
    delete m_symbol;
}

void Axis::setSymbol(bool on)
{
    if (on)
        QwtPlotMarker::setSymbol(*m_symbol);
    else
        QwtPlotMarker::setSymbol(QwtSymbol());
}

void Axis::setLabel(bool on)
{
    if (on)
        setLabel(m_label);
    else
        QwtPlotMarker::setLabel(QString());
}

void Axis::setLabel(QString str)
{
    m_label = str;
    if (lineStyle() == QwtPlotMarker::HLine) {
        str.insert(0, "\n\n\n\n\n");
        str += "\t\t\t\t";
    } else if (lineStyle() == QwtPlotMarker::VLine) {
        str.insert(0, "\n");
        str += "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
    }

    QwtPlotMarker::setLabel(QwtText(str));
}

FuncView::FuncView(QWidget *parent) :
    QWidget(parent),
    m_grid(new QwtPlotGrid()),
    m_gridPen(new QPen()),
    m_ui(new Ui::FuncView),
    m_xAxis(new Axis(QwtPlotMarker::HLine, 10, 0, "X")),
    m_xmax(10),
    m_xmin(-10),
    m_xScaleItem(new QwtPlotScaleItem(QwtScaleDraw::BottomScale, 0.0)),
    m_yAxis(new Axis(QwtPlotMarker::VLine, 0, 10, "Y")),
    m_ymax(10),
    m_ymin(-10),
    m_yScaleItem(new QwtPlotScaleItem(QwtScaleDraw::LeftScale, 0.0))
{
    m_ui->setupUi(this);
    m_ui->m_qwtPlot->setCanvasBackground(Qt::white);
    m_ui->m_qwtPlot->enableAxis(QwtPlot::yLeft, false);
    m_ui->m_qwtPlot->enableAxis(QwtPlot::xBottom, false);

    updateRatio();

    m_xAxis->attach(m_ui->m_qwtPlot);
    m_yAxis->attach(m_ui->m_qwtPlot);

    m_xScaleItem->setTitle("X");
    m_xScaleItem->attach(m_ui->m_qwtPlot);
    m_ui->m_qwtPlot->setAxisScale(QwtPlot::xBottom, m_xmin, m_xmax);
    m_yScaleItem->setTitle("Y");
    m_yScaleItem->attach(m_ui->m_qwtPlot);
    m_ui->m_qwtPlot->setAxisScale(QwtPlot::yLeft, m_ymin, m_ymax);

    m_gridPen->setColor(Qt::gray);
    m_gridPen->setStyle(Qt::DashLine);
    m_grid->setPen(*m_gridPen);
    m_grid->attach(m_ui->m_qwtPlot);

    m_magnifier = new QwtPlotMagnifierEx(m_ui->m_qwtPlot->canvas());

    m_panner = new QwtPlotPanner(m_ui->m_qwtPlot->canvas());
    m_panner->setMouseButton(Qt::LeftButton);

    m_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, m_ui->m_qwtPlot->canvas());
    m_picker->setTrackerMode(QwtPicker::AlwaysOn);

    connect(m_magnifier, SIGNAL(rescaleEvent()), this, SLOT(updateRatio()));
    connect(m_magnifier, SIGNAL(rescaleEvent()), this, SLOT(updateBounds()));
    connect(m_panner, SIGNAL(panned(int, int)), this, SLOT(updateBounds()));
}

FuncView::~FuncView(void)
{
    delete m_grid;
    delete m_gridPen;
    delete m_magnifier;
    delete m_panner;
    delete m_picker;
    delete m_ui;
    delete m_xScaleItem;
    delete m_yScaleItem;
}

QwtPlotMagnifierEx* FuncView::getMagnifier(void) const
{
    return m_magnifier;
}

QwtPlotPanner* FuncView::getPanner(void) const
{
    return m_panner;
}

QwtPlot* FuncView::getQwtPlot(void) const
{
    return m_ui->m_qwtPlot;
}

bool FuncView::plot(GFunction *gfunc)
{
    if (!gfunc->getMaxOn())
        gfunc->setMaxNum(m_xmax + 1);
    if (!gfunc->getMinOn())
        gfunc->setNumMin(m_xmin - 1);
    if (!gfunc->getPrecOn())
        gfunc->setPrecNum((abs(m_xmax - m_xmin) + 1) / 400);

    if (gfunc->getShow())
        if (gfunc->setData()) {
            gfunc->getCurve()->setRenderHint(QwtPlotItem::RenderAntialiased);
            gfunc->getCurve()->attach(m_ui->m_qwtPlot);
            m_ui->m_qwtPlot->replot();
            return true;
        }
    return false;
}

void FuncView::resizeEvent(QResizeEvent *ev)
{
    updateBounds();
    
    m_xmax = (ev->size().width() / m_ratio) + m_xmin;
    m_ymax = (ev->size().height() / m_ratio) + m_ymin;

    QwtPlot *plot = m_ui->m_qwtPlot;
    plot->axisScaleDiv(QwtPlot::xBottom)->setInterval(m_xmin, m_xmax);
    plot->axisScaleDiv(QwtPlot::yLeft)->setInterval(m_ymin, m_ymax);

    emit resized();
}

void FuncView::setBGCol(const QColor &col) const
{
    m_ui->m_qwtPlot->setCanvasBackground(col);
    m_ui->m_qwtPlot->replot();
}

void FuncView::setCoordMouseOn(bool on) const
{
    if (on)
        m_picker->setTrackerMode(QwtPicker::AlwaysOn);
    else
        m_picker->setTrackerMode(QwtPicker::AlwaysOff);
}

void FuncView::setGridCol(const QColor &col) const
{
    m_gridPen->setColor(col);
    m_grid->setPen(*m_gridPen);
    m_ui->m_qwtPlot->replot();
}

void FuncView::setGridOn(bool on) const
{
    if (on)
        m_grid->setPen(*m_gridPen);
    else
        m_grid->setPen(QPen(Qt::NoPen));
    m_ui->m_qwtPlot->replot();
}

void FuncView::setGridStyle(int i) const
{
    m_gridPen->setStyle((Qt::PenStyle) (i + 1));
    m_grid->setPen(*m_gridPen);
    m_ui->m_qwtPlot->replot();
}

void FuncView::setGridWidth(int width) const
{
    m_gridPen->setWidth(width);
    m_grid->setPen(*m_gridPen);
    m_ui->m_qwtPlot->replot();
}

void FuncView::setHorArrowOn(bool on) const
{
    m_xAxis->setSymbol(on);
    m_ui->m_qwtPlot->replot();
}

void FuncView::setHorAxisOn(bool on) const
{
    m_xAxis->setVisible(on);
    m_xScaleItem->setVisible(on);
    m_ui->m_qwtPlot->replot();
}

void FuncView::setHorLabel(const QString &str) const
{
    m_xAxis->setLabel(str);
    m_ui->m_qwtPlot->replot();
}

void FuncView::setHorLabelOn(bool on) const
{
    m_xAxis->setLabel(on);
    m_ui->m_qwtPlot->replot();
}

void FuncView::updateAxes(void) const
{
    m_xAxis->setXValue(m_xmax);
    m_yAxis->setYValue(m_ymax);

    m_ui->m_qwtPlot->replot();
}

void FuncView::updateBounds(void)
{
    QwtPlot *plot = m_ui->m_qwtPlot;
    QwtScaleDiv *xScale = plot->axisScaleDiv(QwtPlot::xBottom);
    QwtScaleDiv *yScale = plot->axisScaleDiv(QwtPlot::yLeft);

    m_xmax = xScale->upperBound();
    m_xmin = xScale->lowerBound();

    m_ymax = yScale->upperBound();
    m_ymin = yScale->lowerBound();

    updateAxes();
}

void FuncView::updateRatio(void)
{
    m_ratio = size().width() / abs(m_xmax - m_xmin);
}

void FuncView::setVerArrowOn(bool on) const
{
    m_yAxis->setSymbol(on);
    m_ui->m_qwtPlot->replot();
}

void FuncView::setVerAxisOn(bool on) const
{
    m_yScaleItem->setVisible(on);
    m_yAxis->setVisible(on);
    m_ui->m_qwtPlot->replot();
}

void FuncView::setVerLabel(const QString &str) const
{
    m_yAxis->setLabel(str);
    m_ui->m_qwtPlot->replot();
}

void FuncView::setVerLabelOn(bool on) const
{
    m_yAxis->setLabel(on);
    m_ui->m_qwtPlot->replot();
}
