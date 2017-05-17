/////////////////////////////////////////////////////////////////////////////
// Name:        dataeet.h
// Purpose:     Default data set classes
// Author:      wxFreeChart team
// Created:     06.05.2017
// Copyright:   (c) 2017 wxFreeChart team
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifndef DATASET1_H_
#define DATASET1_H_

#include <wx/wxfreechartdefs.h>

#include <wx/dataset.h>
#include <wx/dataseries.h>

// TODO: Renderers should be assocated with plots and not data sets.
class XYRenderer;

enum DataTypeTrait
{
    TypeUndefined,
    TypeTraitNominal,
    TypeTraitOrdinal,
    TypeTraitInterval,
    TypeTraitRatio
};


/**
 * Helper class to assist clients of data sets in interpreting the content of
 * the dataset.
 * This class is designed to be overidden in order to extend the list of types that
 * are able to be stored in a data set and plotted on a chart. The default version
 * of this class provides interpretation of int, float, double and wxDateTime types.
 */
class WXDLLIMPEXP_FREECHART DataInterpreter
{
public:

    DataInterpreter();
    virtual ~DataInterpreter();
    
    /**
     * Re-interprets a value representation of the data back to its wxAny format. This is of limited
     * use for complex data types, but is useful for data types that are able to be represented by a 
     * rational value.
     * @param value The internal representation of the wxAny object.
     * @param dimension The dimension of the object to be interpreted. This is necessary because
     * two or more dimensions may use the same data type, but it is necessary to differentiate 
     * them because they may have different interpretations (see Julian date axis example).
     * @param options Possible options to modify how a particular data object is re-interpreted.
     * This is not used in the default class, but can be used by subclasses along with
     * specialised Axis and Renderer classes to fine tune the part of the data that is
     * treated as being ordinal.
     * @return The typed data.
     */
    virtual wxAny AsAny(double value, size_t dimension, int options = 0) const;

    /**
     * Re-interprets an object representation to a different wxAny format.
     * @param data The internal representation of the wxAny object.
     * @param dimension The dimension of the object to be interpreted. This is necessary because
     * two or more dimensions may use the same data type, but it is necessary to differentiate 
     * them because they may have different interpretations (see Julian date axis example).
     * @param options Possible options to modify how a particular data object is re-interpreted.
     * This is not used in the default class, but can be used by subclasses along with
     * specialised Axis and Renderer classes to fine tune the part of the data that is
     * treated as being ordinal.
     * @return The typed data.
     */
    virtual wxAny AsAny(const wxAny& data, size_t dimension, int options = 0) const;

    /**
     * Interprets the content of the data contained within the wxAny container in an
     * ordinal way and returns the coresponding value.
     * @param data The wxAny object to be interpreted. The object must contain one of
     * the known types otherwise an error (assert) will be raised.
     * @param dimension The dimension of the object to be interpreted. This is necessary because
     * two or more dimensions may use the same data type, but it is necessary to differentiate 
     * them because they may have different interpretations (see Julian date axis example).
     * @param options Possible options to modify how a particular data object is interpreted.
     * This is not used in the default class, but can be used by subclasses along with
     * specialised Axis and Renderer classes to fine tune the part of the data that is
     * treated as being ordinal.
     * @return The interpreted value of the data.
     */
    virtual double AsValue(const wxAny& data, size_t dimension, int options = 0) const;
    
    /**
     * Get the trait for the data type that is being interpreted.
     * @param data
     * @return The type trait for this object. If the object is not recognised by this
     * class then TypeUndefined is returned. This provides an application with an opportunity
     * to gracefully manage the situation rather than an assert being raised later.
     */
    virtual DataTypeTrait GetTrait(const wxAny& data, size_t dimension) const;
};

/***************************************
 * DATA SET
 ***************************************/

/**
 * Base class for all objects representing a data set.
 *
 * A data set is a collection of data series that can be plotted against a
 * common set of axis. Therefore, all data points within all series of a data
 * set must be of a common type.
 * 
 * 
 */
class WXDLLIMPEXP_FREECHART DataSet : public Dataset
{
public:

    /**
     * Default constructor that creates an empty data set with the option to provide a
     * name.
     * Currently dataset names are not used.
     * @param name The name that can be used to describe this data set.
     */
    DataSet (const wxString& name = wxEmptyString);

    /**
     * Default destructor.
     */
    virtual ~DataSet();
    
    /**
     * Add a data series to this data set. All series must contain data points with the same
     * number of dimensions and with data that is essentially the same type (i.e. that can 
     * be plotted against a common axis).
     * @param series
     */
    virtual void AddSeries(DataSeries* series);
    
    virtual DataInterpreter* GetInterpreter() const;

    virtual const wxString& GetName() const;

    virtual const wxSharedPtr<DataPoint> GetPoint(size_t series, size_t index, size_t dimension) const;

    virtual const wxAny& GetPointData(size_t series, size_t index, size_t dimension) const;

    virtual const double GetPointValue(size_t series, size_t index, size_t dimension) const;

    virtual const wxSharedPtr<DataSeries> GetSeries(size_t index) const;

    virtual const size_t GetSeriesCount() const;

    virtual void SetInterpreter(DataInterpreter* interpreter);

    virtual void SetName(const wxString& name);
    
    virtual const wxAny InterpretDataAsAny(size_t series, size_t index, size_t dimension) const;
    
    virtual const wxAny InterpretValueAsAny(size_t series, size_t index, size_t dimension) const;
    
    virtual double InterpretDataAsValue(size_t series, size_t index, size_t dimension) const;
    
    
    // Implement or defer all pure virtual methods from original Dataset class.

    virtual bool AcceptRenderer (Renderer* r);

    virtual size_t GetCount (size_t serie) const;

    virtual double GetMaxValue(bool vertical) const = 0;

    virtual double GetMinValue(bool vertical) const = 0;

    virtual size_t GetSerieCount() const;

    virtual wxString GetSerieName (size_t serie) const;

protected:
    wxString m_name;
    DataInterpreter* m_interpreter;
    wxVector<wxSharedPtr<DataSeries> > m_series;
};

/***************************************
 * UNI DATA SET
 ***************************************/

class WXDLLIMPEXP_FREECHART UniDataSet : public DataSet
{
public:
    UniDataSet (const wxString& name = wxEmptyString);

    virtual ~UniDataSet();
    
    void AddCategory(const wxAny& category);

    virtual size_t GetBaseCount();
    
    virtual const wxVector<wxAny>& GetBaseSeries() const;

    virtual const wxAny& GetBaseValue(size_t index) const;

    virtual double GetValue(size_t series, size_t index) const;
    
    // Abstract Data Set method implementations.   

    virtual double GetMaxValue(bool vertical) const;
    
    virtual double GetMinValue(bool vertical) const;

private:
    wxVector<wxAny> m_baseSeries;
};

/***************************************
 * BI DATA SET
 ***************************************/

class WXDLLIMPEXP_FREECHART BiDataSet : public DataSet
{
public:
    BiDataSet (const wxString& name = wxEmptyString);

    virtual ~BiDataSet();
    
    virtual double GetFirst(size_t series, size_t index);
    
    virtual double GetSecond(size_t series, size_t index);
    
    virtual const XYRenderer* GetRenderer() const;

    virtual XYRenderer* GetRenderer();
    
    // Abstract Data Set method implementations.   

    virtual double GetMaxValue(bool vertical) const;
    
    virtual double GetMinValue(bool vertical) const;
};

/***************************************
 * NARY DATA SET
 ***************************************/

class WXDLLIMPEXP_FREECHART NaryDataSet : public DataSet
{
public:
    NaryDataSet (const wxString& name = wxEmptyString);

    virtual ~NaryDataSet();

};


#endif // DATASET1_H_