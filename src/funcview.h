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

class Tic : public QwtPlotMarker
{
public:
    Tic(unsigned short axis, double x, double y, const QwtSymbol &symbol);

    enum Axis {
        XAxis,
        YAxis
    };
};

class Axis : public QwtPlotMarker
{
public:
    Axis(QwtPlotMarker::LineStyle style, double x, double y, QString str);
    ~Axis(void);

    void setColor(const QColor &col);
    void setFont(QFont &font);
    void setLabel(bool on);
    void setLabel(QString str);
    void setLabel(QwtText str, bool formated);
    void setLabelSize(double size);
    void setStyle(int style);
    void setSymbol(bool on);
    void setWidth(int width);

private:
    QwtText m_label;
    QPen *m_pen;
    QwtSymbol *m_symbol;
    QPen *m_symbolPen;
};

class FuncView : public QWidget
{
    Q_OBJECT
public:
    FuncView(QWidget *parent = 0);
    ~FuncView(void);

    void initSettings(QSettings *settings);

    QwtPlotMagnifierEx* getMagnifier(void) const;
    QwtPlotPanner* getPanner(void) const;
    QwtPlot* getQwtPlot(void) const;

    enum AxisType {
        Hor,
        Ver
    };

    struct Symbol {
        QwtSymbol *m_TicsSymbol;
        int m_TicsSymbolLength;
        QPen *m_TicsSymbolPen;
        int m_TicsSymbolWidth;
    };

public slots:
    bool plot(GFunction *gfunc);

    inline void setHorAxisCol(const QColor &col) const { setAxisCol(Hor, col); }
    inline void setVerAxisCol(const QColor &col) const { setAxisCol(Ver, col); }

    inline void setHorArrowOn(bool on) const { setAxisArrowOn(Hor, on); }
    inline void setVerArrowOn(bool on) const { setAxisArrowOn(Ver, on); }

    inline void setHorAxisOn(bool on) { setAxisOn(Hor, on); }
    inline void setVerAxisOn(bool on) { setAxisOn(Ver, on); }

    inline void setHorStyle(int style) const { setAxisStyle(Hor, style); }
    inline void setVerStyle(int style) const { setAxisStyle(Ver, style); }

    inline void setHorWidth(int width) const { setAxisWidth(Hor, width); }
    inline void setVerWidth(int width) const { setAxisWidth(Ver, width); }

    inline void setHorLabel(const QString &str) const { setAxisLabel(Hor, str); }
    inline void setVerLabel(const QString &str) const { setAxisLabel(Ver, str); }

    inline void setHorLabelFont(QFont font) const { setAxisLabelFont(Hor, font); }
    inline void setVerLabelFont(QFont font) const { setAxisLabelFont(Ver, font); }

    inline void setHorLabelSize(double size) const { setAxisLabelSize(Hor, size); }
    inline void setVerLabelSize(double size) const { setAxisLabelSize(Ver, size); }

    inline void setHorLabelOn(bool on) const { setAxisLabelOn(Hor, on); }
    inline void setVerLabelOn(bool on) const { setAxisLabelOn(Ver, on); }

    inline void setHorTicsOn(bool on) { setAxisTicsOn(Hor, on); }
    inline void setVerTicsOn(bool on) { setAxisTicsOn(Ver, on); }

    inline void setHorTicsLength(int length) { setAxisTicsLength(Hor, length); }
    inline void setVerTicsLength(int length) { setAxisTicsLength(Ver, length); }

    void setBGCol(const QColor &col) const;

    void setCoordMouseOn(bool on) const;

    void setGridCol(const QColor &col) const;
    void setGridOn(bool on) const;
    void setGridStyle(int i) const;
    void setGridWidth(int width) const;

signals:
    void resized(void);

protected:
    void resizeEvent(QResizeEvent *ev);

private:
    QwtPlotGrid *m_grid;
    QPen *m_gridPen;
    bool m_horTicsOn;
    QwtPlotMagnifierEx *m_magnifier;
    QwtPlotPanner *m_panner;
    QwtPlotPicker *m_picker;
    double m_ratio;
    Ui::FuncView *m_ui;
    bool m_verTicsOn;
    Symbol *m_xTicsSymbol;
    Symbol *m_yTicsSymbol;
    QList<Tic*> m_xTicList;
    QList<Tic*> m_yTicList;
    Axis *m_xAxis;
    double m_xmax;
    double m_xmin;
    Axis *m_yAxis;
    double m_ymax;
    double m_ymin;

    void setAxisCol(unsigned short axis, const QColor &col) const;
    void setAxisArrowOn(unsigned short axis, bool on) const;
    void setAxisOn(unsigned short axis, bool on);
    void setAxisStyle(unsigned short axis, int style) const;
    void setAxisWidth(unsigned short axis, int width) const;

    void setAxisLabel(unsigned short axis, const QString &str) const;
    void setAxisLabelFont(unsigned short axis, QFont font) const;
    void setAxisLabelOn(unsigned short axis, bool on) const;
    void setAxisLabelSize(unsigned short axis, double size) const;

    void setAxisTicsOn(unsigned short axis, bool on, bool saveState = true);
    void setAxisTicsLength(unsigned short axis, int length);

    /* Not implemented yet.
     * void setAxisTicsSize(unsigned short axis, double size) const;
     * void setAxisTicsWidth(unsigned short axis, int width);
     * void setAxisTicsFont(unsigned short axis, QFont font) const;
     * void setAxisTicsCol(unsigned short axis, const QColor &col);
     */

    void updateAxes(void);
    void updateTics(void);

private slots:
    void updateBounds(void);
    void updateRatio(void);
};

#endif // FUNCVIEW_H
