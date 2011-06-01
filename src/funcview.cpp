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

FuncView::FuncView(QWidget *parent) :
    QWidget(parent),
    m_grid(new QwtPlotGrid()),
    m_gridPen(new QPen()),
    m_ui(new Ui::FuncView),
    m_xmax(10),
    m_xmin(-10),
    m_xScaleItem(new QwtPlotScaleItem(QwtScaleDraw::BottomScale, 0.0)),
    m_ymax(10),
    m_ymin(-10),
    m_yScaleItem(new QwtPlotScaleItem(QwtScaleDraw::LeftScale, 0.0))
{
    m_ui->setupUi(this);
    m_ui->m_qwtPlot->setCanvasBackground(Qt::white);
    m_ui->m_qwtPlot->enableAxis(QwtPlot::yLeft, false);
    m_ui->m_qwtPlot->enableAxis(QwtPlot::xBottom, false);

    updateRatio();

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
        gfunc->setXMax(m_xmax + 1);
    if (!gfunc->getMinOn())
        gfunc->setXMin(m_xmin - 1);
    if (!gfunc->getPrecUser())
        gfunc->setPrecision((abs(m_xmax - m_xmin) + 1) / 400);

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

void FuncView::setAxisOn(bool on) const
{
    m_xScaleItem->setVisible(on);
    m_yScaleItem->setVisible(on);
    m_ui->m_qwtPlot->replot();
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

void FuncView::setGridWidth(double width) const
{
    m_gridPen->setWidth(width);
    m_grid->setPen(*m_gridPen);
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
}

void FuncView::updateRatio(void)
{
    m_ratio = size().width() / abs(m_xmax - m_xmin);
}
