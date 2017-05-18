/////////////////////////////////////////////////////////////////////////////
// Name:    pieplot.h
// Purpose: pie plot declarations
// Author:    Moskvichev Andrey V.
// Created:    2008/11/07
// Copyright:    (c) 2008-2010 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef PIEPLOT_H_
#define PIEPLOT_H_

#include <wx/plot/plot.h>
#include <wx/legend.h>
#include <wx/render/categoryrenderer.h>
#include <wx/render/xyarearenderer.h>

#include <wx/colorscheme.h>

const int shift3D = 20;

/**
 * Pie plot.
 * TODO: initial quick and dirty, must be cleaned up or rewritten.
 */
class WXDLLIMPEXP_FREECHART PiePlot : public Plot
{
public:
    PiePlot();
    virtual ~PiePlot();

    void SetDataset(UniDataSet *dataset);

    void SetUsedSerie(size_t serie)
    {
        m_serie = serie;
    }

    void SetColorScheme(ColorScheme *cs);

    void Set3DView(bool use3DView)
    {
        if (m_use3DView != use3DView)
            m_use3DView = use3DView;
    }

    void SetEllipticAspect(float ellipticAspect)
    {
        if (m_ellipticAspect != ellipticAspect && ellipticAspect > 0 && ellipticAspect <= 1)
            m_ellipticAspect = ellipticAspect;
    }

    void SetLegend(Legend *legend);

    //
    // DatasetObserver
    //
    virtual void DatasetChanged(Dataset *dataset);

protected:
    virtual bool HasData();

    virtual void DrawData(ChartDC& cdc, wxRect rc);
    
    virtual void DrawBackground(ChartDC& cdc, wxRect rc) {}; // Does nothing in a pie plot?

private:

    bool m_use3DView;
    float m_ellipticAspect;

    wxFont m_labelsFont;
    wxPen m_outlinePen;

    UniDataSet* m_dataset;

    ColorScheme m_colorScheme;

    size_t m_serie;

    wxCoord m_legendPlotGap; // distance between plot and legend

    Legend *m_legend;
};

#endif /*PIEPLOT_H_*/