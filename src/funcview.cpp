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

Tic::Tic(unsigned short axis, double x, double y, const QwtSymbol &symbol)
{
    setXValue(x);
    setYValue(y);

    QString str;
    if (axis == Tic::XAxis) {
        str.setNum(x);
        setLabelAlignment(Qt::AlignBottom);
    } else {
        str.setNum(y);
        setLabelAlignment(Qt::AlignLeft);
    }
    setSymbol(symbol);
    setLabel(QwtText(str));
}

Axis::Axis(QwtPlotMarker::LineStyle style, double x, double y, QString str) :
    m_label(str),
    m_pen(new QPen())
{
    setLineStyle(style);

    if (style == QwtPlotMarker::HLine) {
        m_symbol = new QwtSymbol(QwtSymbol::RTriangle, QBrush(Qt::SolidPattern), QPen(Qt::black), QSize(10, 10));
        setLabel(m_label, false);
        setLabelAlignment(Qt::AlignRight);
    } else {
        m_symbol = new QwtSymbol(QwtSymbol::Triangle, QBrush(Qt::SolidPattern), QPen(Qt::black), QSize(10, 10));
        setLabel(m_label, false);
        setLabelAlignment(Qt::AlignTop);
    }

    QwtPlotMarker::setSymbol(*m_symbol);

    setXValue(x);
    setYValue(y);
}

Axis::~Axis(void)
{
    delete m_symbol;
    delete m_pen;
}

void Axis::setColor(const QColor &col)
{
    m_pen->setColor(col);
    setLinePen(*m_pen);
}

void Axis::setFont(QFont &font)
{
    font.setPointSizeF(m_label.font().pointSizeF());
    m_label.setFont(font);
    setLabel(m_label, true);
}

void Axis::setLabel(bool on)
{
    if (on)
        setLabel(m_label, true);
    else
        QwtPlotMarker::setLabel(QString());
}

void Axis::setLabel(QString str)
{
    QFont font = m_label.font();
    QString qstr = str;
    if (lineStyle() == QwtPlotMarker::HLine)
        qstr.insert(0, "\n\n\n");
    else if (lineStyle() == QwtPlotMarker::VLine)
        qstr += "\t\t\t\t\t\t\t\t\t\t";

    m_label.setText(qstr);
    m_label.setFont(font);

    QwtPlotMarker::setLabel(m_label);
}

void Axis::setLabel(QwtText str, bool formated)
{
    if (!formated) {
        QString qstr = str.text();
        if (lineStyle() == QwtPlotMarker::HLine)
            qstr.insert(0, "\n\n\n");
        else if (lineStyle() == QwtPlotMarker::VLine)
            qstr += "\t\t\t\t\t\t\t\t";

        m_label = qstr;
        m_label.setFont(str.font());
    }

    QwtPlotMarker::setLabel(m_label);
}

void Axis::setLabelSize(double size)
{
    QFont font = m_label.font();
    font.setPointSizeF(size);
    m_label.setFont(font);
    setLabel(m_label, true);
}

void Axis::setStyle(int style)
{
    m_pen->setStyle((Qt::PenStyle) (style + 1));
    setLinePen(*m_pen);
}

void Axis::setSymbol(bool on)
{
    if (on)
        QwtPlotMarker::setSymbol(*m_symbol);
    else
        QwtPlotMarker::setSymbol(QwtSymbol());
}

void Axis::setWidth(int width)
{
    m_pen->setWidth(width);
    setLinePen(*m_pen);
}

FuncView::FuncView(QWidget *parent) :
    QWidget(parent),
    m_grid(new QwtPlotGrid()),
    m_gridPen(new QPen()),
    m_ui(new Ui::FuncView),
    m_xTicsSymbol(new Symbol),
    m_yTicsSymbol(new Symbol),
    m_xmax(10),
    m_xmin(-10),
    m_ymax(10),
    m_ymin(-10)
{
    m_ui->setupUi(this);
    m_ui->m_qwtPlot->setCanvasBackground(Qt::white);
    m_ui->m_qwtPlot->enableAxis(QwtPlot::yLeft, false);
    m_ui->m_qwtPlot->enableAxis(QwtPlot::xBottom, false);

    m_xAxis = new Axis(QwtPlotMarker::HLine, 10, 0, "X");
    m_yAxis = new Axis(QwtPlotMarker::VLine, 0, 10, "Y");
    m_xAxis->attach(m_ui->m_qwtPlot);
    m_yAxis->attach(m_ui->m_qwtPlot);

    updateRatio();

    m_gridPen->setColor(Qt::gray);
    m_gridPen->setStyle(Qt::DashLine);
    m_grid->setPen(*m_gridPen);
    m_grid->attach(m_ui->m_qwtPlot);

    m_magnifier = new QwtPlotMagnifierEx(m_ui->m_qwtPlot->canvas());

    m_panner = new QwtPlotPanner(m_ui->m_qwtPlot->canvas());
    m_panner->setMouseButton(Qt::LeftButton);

    m_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, m_ui->m_qwtPlot->canvas());
    m_picker->setTrackerMode(QwtPicker::AlwaysOn);

    m_xTicsSymbol->m_TicsSymbol = new QwtSymbol(QwtSymbol::VLine, QBrush(Qt::SolidPattern), QPen(Qt::black), QSize(10, 10));
    m_xTicsSymbol->m_TicsSymbolPen = new QPen(Qt::black);
    m_xTicsSymbol->m_TicsSymbolLength = 10;
    m_xTicsSymbol->m_TicsSymbolWidth = 10;

    m_yTicsSymbol->m_TicsSymbol = new QwtSymbol(QwtSymbol::HLine, QBrush(Qt::SolidPattern), QPen(Qt::black), QSize(10, 10));
    m_yTicsSymbol->m_TicsSymbolPen = new QPen(Qt::black);
    m_yTicsSymbol->m_TicsSymbolLength = 10;
    m_yTicsSymbol->m_TicsSymbolWidth = 10;

    m_horTicsOn = true;
    m_verTicsOn = true;

    connect(m_magnifier, SIGNAL(rescaleEvent()), this, SLOT(updateRatio()));
    connect(m_magnifier, SIGNAL(rescaleEvent()), this, SLOT(updateBounds()));
    connect(m_panner, SIGNAL(panned(int, int)), this, SLOT(updateBounds()));
}

FuncView::~FuncView(void)
{
    unsigned short xTicSize = m_xTicList.size();
    for (unsigned short i = 0; i < xTicSize; ++i)
        delete m_xTicList[i];
    m_xTicList.clear();

    unsigned short yTicSize = m_yTicList.size();
    for (unsigned short i = 0; i < yTicSize; ++i)
        delete m_yTicList[i];
    m_yTicList.clear();

    delete m_grid;
    delete m_gridPen;
    delete m_magnifier;
    delete m_panner;
    delete m_picker;
    delete m_ui;
    delete m_xTicsSymbol;
    delete m_yTicsSymbol;
    delete m_xAxis;
    delete m_yAxis;
}

void FuncView::initSettings(QSettings *settings)
{
    settings->beginGroup("Settings");

    setBGCol(settings->value("BGColor", Qt::white).toString());
    setCoordMouseOn(settings->value("CoordinatesMouseOn", true).toBool());

    // Grid.
    bool gridOn = settings->value("GridOn", true).toBool();
    setGridCol(settings->value("GridColor", Qt::gray).toString());
    setGridStyle(settings->value("GridStyle", 2).toInt());
    setGridWidth(settings->value("GridWidth", 1).toInt());
    setGridOn(gridOn);

    // Horizontal Axis.
    setHorArrowOn(settings->value("HorArrowOn", true).toBool());
    setHorWidth(settings->value("HorAxisWidth", 1).toInt());
    setHorAxisCol(settings->value("HorAxisColor", Qt::black).toString());

    m_xAxis->setLabel(QwtText(settings->value("HorLabel", "X").toString()), false);
    m_xAxis->setLabelSize(settings->value("HorLabelSize", 10).toDouble());
    setHorLabelOn(settings->value("HorLabelOn", true).toBool());

    setHorTicsLength(settings->value("HorTicsLength", 10).toInt());
    setHorTicsOn(settings->value("HorTicsOn", true).toBool());

    setHorAxisOn(settings->value("HorAxisOn", true).toBool());

    // Vertical Axis.
    setVerArrowOn(settings->value("VerArrowOn", true).toBool());
    setVerWidth(settings->value("VerAxisWidth", 1).toInt());
    setVerAxisCol(settings->value("VerAxisColor", Qt::black).toString());

    m_yAxis->setLabel(QwtText(settings->value("VerLabel", "Y").toString()), false);
    m_yAxis->setLabelSize(settings->value("VerLabelSize", 10).toDouble());
    setVerLabelOn(settings->value("VerLabelOn", true).toBool());

    setVerTicsLength(settings->value("VerTicsLength", 10).toInt());
    setVerTicsOn(settings->value("VerTicsOn", true).toBool());

    setVerAxisOn(settings->value("VerAxisOn", true).toBool());

    settings->endGroup();
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
        gfunc->setMinNum(m_xmin - 1);
    if (!gfunc->getPrecOn())
        gfunc->setPrecNum((abs(m_xmax - m_xmin) + 1) / 400);

    if (gfunc->getShow()) {
        if (gfunc->setData()) {
            gfunc->getCurve()->attach(m_ui->m_qwtPlot);
            m_ui->m_qwtPlot->replot();
            return true;
        } else
            return false;
    }
    return true;
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

void FuncView::setAxisCol(unsigned short axis, const QColor &col) const
{
    switch (axis) {
    case Hor:    m_xAxis->setColor(col);
                 break;

    case Ver:    m_yAxis->setColor(col);
                 break;
    }
    m_ui->m_qwtPlot->replot();
}

void FuncView::setAxisArrowOn(unsigned short axis, bool on) const
{
    switch (axis) {
    case Hor:    m_xAxis->setSymbol(on);
                 break;

    case Ver:    m_yAxis->setSymbol(on);
                 break;
    }
    m_ui->m_qwtPlot->replot();
}

void FuncView::setAxisOn(unsigned short axis, bool on)
{
    switch (axis) {
    case Hor:   m_xAxis->setVisible(on);
                if (!on)
                    setAxisTicsOn(Hor, on, false);
                else
                    setAxisTicsOn(Hor, m_horTicsOn);
                break;

    case Ver:   m_yAxis->setVisible(on);
                if (!on)
                    setAxisTicsOn(Ver, on, false);
                else
                    setAxisTicsOn(Ver, m_verTicsOn);
                break;
    }
    m_ui->m_qwtPlot->replot();
}

void FuncView::setAxisStyle(unsigned short axis, int style) const
{
    switch (axis) {
    case Hor:    m_xAxis->setStyle(style);
                 break;

    case Ver:    m_yAxis->setStyle(style);
                 break;
    }
    m_ui->m_qwtPlot->replot();
}

void FuncView::setAxisWidth(unsigned short axis, int width) const
{
    switch (axis) {
    case Hor:    m_xAxis->setWidth(width);
                 break;

    case Ver:    m_yAxis->setWidth(width);
                 break;
    }
    m_ui->m_qwtPlot->replot();
}

void FuncView::setAxisLabel(unsigned short axis, const QString &str) const
{
    switch (axis) {
    case Hor:    m_xAxis->setLabel(str);
                 break;

    case Ver:    m_yAxis->setLabel(str);
                 break;
    }
    m_ui->m_qwtPlot->replot();
}

void FuncView::setAxisLabelFont(unsigned short axis, QFont font) const
{
    switch (axis) {
    case Hor:    m_xAxis->setFont(font);
                 break;

    case Ver:    m_yAxis->setFont(font);
                 break;
    }
    m_ui->m_qwtPlot->replot();
}

void FuncView::setAxisLabelOn(unsigned short axis, bool on) const
{
    switch (axis) {
    case Hor:    m_xAxis->setLabel(on);
                 break;

    case Ver:    m_yAxis->setLabel(on);
                 break;
    }
    m_ui->m_qwtPlot->replot();
}

void FuncView::setAxisLabelSize(unsigned short axis, double size) const
{
    switch (axis) {
    case Hor:    m_xAxis->setLabelSize(size);
                 break;

    case Ver:    m_yAxis->setLabelSize(size);
                 break;
    }
    m_ui->m_qwtPlot->replot();
}

void FuncView::setAxisTicsLength(unsigned short axis, int length)
{
    switch (axis) {
    case Hor:   m_xTicsSymbol->m_TicsSymbolLength = length;
                m_xTicsSymbol->m_TicsSymbol->setSize(QSize(m_xTicsSymbol->m_TicsSymbolWidth, length));
                break;

    case Ver:   m_yTicsSymbol->m_TicsSymbolLength = length;
                m_yTicsSymbol->m_TicsSymbol->setSize(QSize(length, m_yTicsSymbol->m_TicsSymbolWidth));
                break;
    }
    updateTics();
    m_ui->m_qwtPlot->replot();
}

void FuncView::setAxisTicsOn(unsigned short axis, bool on, bool saveState)
{
    unsigned short i;
    unsigned short lengthList;
    switch (axis) {
    case Hor:   lengthList = m_xTicList.size();
                for(i = 0; i < lengthList; ++i)
                    m_xTicList[i]->setVisible(on);

                if (saveState)
                    m_horTicsOn = on;
                break;

    case Ver:   lengthList = m_yTicList.size();
                for(i = 0; i < lengthList; ++i)
                    m_yTicList[i]->setVisible(on);

                if (saveState)
                    m_verTicsOn = on;
                break;
    }
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

void FuncView::setGridWidth(int width) const
{
    m_gridPen->setWidth(width);
    m_grid->setPen(*m_gridPen);
    m_ui->m_qwtPlot->replot();
}

void FuncView::updateAxes(void)
{
    m_xAxis->setXValue(m_xmax);
    m_yAxis->setYValue(m_ymax);

    updateTics();

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

void FuncView::updateTics(void)
{
    unsigned short xTicSize = m_xTicList.size();
    for (unsigned short i = 0; i < xTicSize; ++i)
        delete m_xTicList[i];
    m_xTicList.clear();

    QList<double> xList = m_ui->m_qwtPlot->axisScaleDiv(QwtPlot::xBottom)->ticks(QwtScaleDiv::MajorTick);
    unsigned short xSize = xList.size();
    for (unsigned short i = 0; i < xSize; ++i) {
        Tic *t = new Tic(Tic::XAxis, xList[i], 0, *m_xTicsSymbol->m_TicsSymbol);
        t->setVisible(m_horTicsOn);
        t->attach(m_ui->m_qwtPlot);
        m_xTicList.push_back(t);
    }

    unsigned short yTicSize = m_yTicList.size();
    for (unsigned short i = 0; i < yTicSize; ++i)
        delete m_yTicList[i];
    m_yTicList.clear();

    QList<double> yList = m_ui->m_qwtPlot->axisScaleDiv(QwtPlot::yLeft)->ticks(QwtScaleDiv::MajorTick);
    unsigned short ySize = yList.size();
    for (unsigned short i = 0; i < ySize; ++i) {
        Tic *t = new Tic(Tic::YAxis, 0, yList[i], *m_yTicsSymbol->m_TicsSymbol);
        t->setVisible(m_verTicsOn);
        t->attach(m_ui->m_qwtPlot);
        m_yTicList.push_back(t);
    }
}
