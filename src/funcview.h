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

#ifndef FUNCVIEW_H
#define FUNCVIEW_H

#include <QtGui>
#include <qwt_plot_grid.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_scaleitem.h>
#include <qwt_symbol.h>

#include "gfunction.h"

namespace Ui {
    class FuncView;
}

class QwtPlotMagnifierEx : public QwtPlotMagnifier
{
    Q_OBJECT
public:
    explicit QwtPlotMagnifierEx(QwtPlotCanvas *canvas);

protected:
    virtual void rescale(double factor);

signals:
    void rescaleEvent(void);

public slots:
    void doRescale(double factor);
};

class Axis : public QwtPlotMarker
{
public:
    Axis(QwtPlotMarker::LineStyle style, double x, double y, QString str);
    ~Axis(void);

    void setSymbol(bool on);
    void setLabel(bool on);
    void setLabel(QString str);

private:
    QString m_label;
    QwtSymbol *m_symbol;
};

class FuncView : public QWidget
{
    Q_OBJECT
public:
    FuncView(QWidget *parent = 0);
    ~FuncView(void);

    QwtPlotMagnifierEx* getMagnifier(void) const;
    QwtPlotPanner* getPanner(void) const;
    QwtPlot* getQwtPlot(void) const;

public slots:
    bool plot(GFunction *gfunc);
    void setBGCol(const QColor &col) const;
    void setCoordMouseOn(bool on) const;
    void setGridCol(const QColor &col) const;
    void setGridOn(bool on) const;
    void setGridStyle(int i) const;
    void setGridWidth(int width) const;
    void setHorArrowOn(bool on) const;
    void setHorAxisOn(bool on) const;
    void setHorLabel(const QString &str) const;
    void setHorLabelOn(bool on) const;
    void updateAxes(void) const;
    void updateBounds(void);
    void updateRatio(void);
    void setVerArrowOn(bool on) const;
    void setVerAxisOn(bool on) const;
    void setVerLabel(const QString &str) const;
    void setVerLabelOn(bool on) const;


signals:
    void resized(void);

protected:
    void resizeEvent(QResizeEvent *ev);

private:
    QwtPlotGrid *m_grid;
    QPen *m_gridPen;
    QwtPlotMagnifierEx *m_magnifier;
    QwtPlotPanner *m_panner;
    QwtPlotPicker *m_picker;
    double m_ratio;
    Ui::FuncView *m_ui;
    Axis *m_xAxis;
    double m_xmax;
    double m_xmin;
    QwtPlotScaleItem *m_xScaleItem;
    Axis *m_yAxis;
    double m_ymax;
    double m_ymin;
    QwtPlotScaleItem *m_yScaleItem;
};

#endif // FUNCVIEW_H
