/**********************************************************************
Copyright (c)
Audi Autonomous Driving Cup. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3.  All advertising materials mentioning features or use of this software must display the following acknowledgement: �This product includes software developed by the Audi AG and its contributors for Audi Autonomous Driving Cup.�
4.  Neither the name of Audi nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY AUDI AG AND CONTRIBUTORS �AS IS� AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL AUDI AG OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


**********************************************************************
* $Author:: spie#$  $Date:: 2017-05-12 09:34:53#$ $Rev:: 63109   $
**********************************************************************/
#ifndef _STOPLINE_FILTER_HEADER_
#define _STOPLINE_FILTER_HEADER_

#include "stdafx.h"
#include "ADTF_OpenCV_helper.h"


#define OID_ADTF_FILTER_DEF "adtf.user_Crossline" //unique for a filter
#define ADTF_FILTER_DESC "AADC User Crossline"  //this appears in the Component Tree in ADTF
#define ADTF_FILTER_VERSION_SUB_NAME "Crossline"//must match with accepted_version_...
#define ADTF_FILTER_VERSION_ACCEPT_LABEL "accepted_version"//sets the version entry
#define ADTF_FILTER_VERSION_STRING "1.0.0"//version string
#define ADTF_FILTER_VERSION_Major 1//this values will be compared, major version change - will not work
#define ADTF_FILTER_VERSION_Minor 0//change will work but notice
#define ADTF_FILTER_VERSION_Build 0//change will work but notice
//the detailed description of the filter
#define ADTF_FILTER_VERSION_LABEL "A small OpenCV Template Filter \n$Rev:: 62948"

/*! @defgroup STOPLINEFilter
*  @{
*
*  \image html User_STOPLINE.PNG "Plugin OpenCV Template Filter"
* This is a small OpenCV template which can be used by the AADC teams for their own filter implementations for image processing.
*
* This plugin needs the following libraries:
* \li OpenCV  v.3.2.0
*
* <b> Filter Properties</b>
* <table>
* <tr><th>Property<th>Description<th>Default
* </table>
*
* <b>Output Pins</b>
* <table>
* <tr><th>Pin<th>Description<th>MajorType<th>SubType
* <tr><td>Video_Output<td>Video Pin for data from camera<td>MEDIA_TYPE_VIDEO<td>MEDIA_SUBTYPE_VIDEO_UNCOMPRESSED
*</table>
*
* <b>Input Pins</b>
* <table>
* <tr><th>Pin<th>Description<th>MajorType<th>SubType
* <tr><td>Video_Input<td>Video Pin for data from camera<td>MEDIA_TYPE_VIDEO<td>MEDIA_SUBTYPE_VIDEO_UNCOMPRESSED
* </table>
*
* <b>Plugin Details</b>
* <table>
* <tr><td>Path<td>src/aadcUser/AADC_STOPLINE
* <tr><td>Filename<td>user_STOPLINE.plb
* <tr><td>Version<td>1.0.0
* </table>
*
*/

//!  Template filter for OpenCV Image Processing
/*!
* This class is the main class of the OpenCV Template Filter and can be used as template for user specific image processing filters
*/
class ccrossline : public adtf::cFilter
{
    /*! This macro does all the plugin setup stuff */
    ADTF_FILTER_VERSION(OID_ADTF_FILTER_DEF,
                        ADTF_FILTER_DESC,
                        adtf::OBJCAT_Auxiliary,
                        ADTF_FILTER_VERSION_SUB_NAME,
                        ADTF_FILTER_VERSION_Major,
                        ADTF_FILTER_VERSION_Minor,
                        ADTF_FILTER_VERSION_Build,
                        ADTF_FILTER_VERSION_LABEL
                       );

protected:
    /*! input for rgb image */
    cVideoPin           m_oVideoInputPin;
    /*! output for rgb image */
    cVideoPin           m_oVideoOutputPin;
    cVideoPin 		m_oVideoOutputPin1;
    cInputPin	        m_edgeselect;

    cOutputPin		m_Stoplinedist;
    cOutputPin	        m_Edgeonedetect;
    cObjectPtr<IMediaTypeDescription> m_pDesEdgedetect;
    cObjectPtr<IMediaTypeDescription> m_pDesEdgeselect;
    
    cObjectPtr<IMediaTypeDescription> m_pCoderDescSignalStop;
    cObjectPtr<IMediaTypeDescription> m_pDesStoplinedist;
    cObjectPtr<IMediaTypeDescription> m_pDesStoplineOrient;
public:
    /*! default constructor for template class
        \param __info   [in] This is the name of the filter instance.
    */
    ccrossline(const tChar* __info);

    /*! default destructor */
    virtual ~ccrossline();

    /*! Implements the default cFilter state machine call. It will be
    *	    called automatically by changing the filters state and needs
    *	    to be overwritten by the special filter.
    *    Please see page_filter_life_cycle for further information on when the state of a filter changes.
    *
    *    \param [in,out] __exception_ptr   An Exception pointer where exceptions will be put when failed.
    *        If not using the cException smart pointer, the interface has to
    *        be released by calling Unref().
    *    \param  [in] eStage The Init function will be called when the filter state changes as follows:\n
    *    \return Standard Result Code.
    */
    tResult Init(tInitStage eStage, ucom::IException** __exception_ptr);

    /*!
    *   Implements the default cFilter state machine call. It will be
    *   called automatically by changing the filters state and needs
    *   to be overwritten by the special filter.
    *   Please see page_filter_life_cycle for further information on when the state of a filter changes.
    *
    *   \param [in,out] __exception_ptr   An Exception pointer where exceptions will be put when failed.
    *                                   If not using the cException smart pointer, the interface has to
    *                                   be released by calling Unref().
    *   \param  [in] eStage The Init function will be called when the filter state changes as follows:\n   *
    *   \result Returns a standard result code.
    *
    */
    tResult Shutdown(tInitStage eStage, ucom::IException** __exception_ptr = NULL);

    /*! This Function will be called by all pins the filter is registered to.
    *   \param [in] pSource Pointer to the sending pin's IPin interface.
    *   \param [in] nEventCode Event code. For allowed values see IPinEventSink::tPinEventCode
    *   \param [in] nParam1 Optional integer parameter.
    *   \param [in] nParam2 Optional integer parameter.
    *   \param [in] pMediaSample Address of an IMediaSample interface pointers.
    *   \return   Returns a standard result code.
    *   \warning This function will not implement a thread-safe synchronization between the calls from different sources.
    *   You need to synchronize this call by your own. Have a look to adtf_util::__synchronized , adtf_util::__synchronized_obj .
    */
    tResult OnPinEvent(IPin* pSource, tInt nEventCode, tInt nParam1, tInt nParam2, IMediaSample* pMediaSample);

    /*! Implements the default cFilter state machine calls. It will be
    *    called automatically by changing the filters state IFilter::State_Ready -> IFilter::State_Running
    *    and can be overwritten by the special filter.
    *    \param __exception_ptr  [inout] An Exception pointer where exceptions will be put when failed.
    *        If not using the cException smart pointer, the interface has to
    *        be released by calling Unref().
    *    \return Standard Result Code.
    *    \note This method will be also called during the shutdown of a configuration if the Filter is connected to the Message Bus.
    *    (see:  section_message_bus)! This has to be done, to disconnect the Message Bus and to avoid Race Conditions.
    *
    */
    tResult Start(ucom::IException** __exception_ptr = NULL);

    /*!  Implements the default cFilter state machine calls. It will be
    *   called automatically by changing the filters state IFilter::State_Running -> IFilter::State_Ready
    *   and can be overwritten by the special filter.
    *   \param __exception_ptr  [inout] An Exception pointer where exceptions will be put when failed.
    *   If not using the cException smart pointer, the interface has to
    *   be released by calling Unref().
    *   \return Standard Result Code.
    *   \note This method will be also called during the shutdown of a configuration if the Filter is connected to the Message Bus.
    *   (see: section_message_bus)! This has to be done, to disconnect the Message Bus and to avoid Race Conditions.
    */
    tResult Stop(ucom::IException** __exception_ptr = NULL);
   cv::Mat      Line;					/* matrix for the line*/
   cv::Mat      grey;					/* matrix for the gray image*/
   cv::Mat      greythresh;				/* matrix for the gray threshold*/
   cv::Size     cannysize;				/* size for the canny detector*/

struct EuclideanDistanceFunctor
	{
    	int _dist2;
        EuclideanDistanceFunctor(int dist) : _dist2(dist*dist) {}

   	 bool operator()(const Point& lhs, const Point& rhs) const
   	 {
      	  return ((lhs.x - rhs.x)*(lhs.x - rhs.x) + (lhs.y - rhs.y)*(lhs.y - rhs.y)) < _dist2;
   	 }
	};

	struct myclass {
   	 bool operator() (cv::Point pt1, cv::Point pt2) { return (pt1.y > pt2.y);}
			} myobject;

   cv::Mat      linecanny;

private: // private methods

    /*! function to set the m_sProcessFormat and the  m_sInputFormat variables
    *   \param pFormat the new format for the input pin
    *   \return Standard Result Code.
    */
    tResult UpdateInputImageFormat(const tBitmapFormat* pFormat);

    /*! function to set the output image format
    *   \param outputImage the new format for the input pin
    *   \return Standard Result Code.
    */
    tResult UpdateOutputImageFormat(const cv::Mat& outputImage);
    tResult UpdateOutputImageFormat2(const cv::Mat& outputImage);
    tResult writeOutputs1(tFloat32 distance, tUInt32 timeStamp);
    tResult writeOutputs2(tFloat32 distance_edge, tUInt32 timeStamp);
    tResult ReadProperties(const tChar* strPropertyName);
    /*! function to process the mediasample
    *   \param pSample the new media sample
    *   \return Standard Result Code.
    */
    tResult ProcessVideo(IMediaSample* pSample);
    tResult ProcessEdge(IMediaSample* pSample);
	tInt row1,row2,col1,col2;
	tInt  m_nThresholdValue;
    /*! bitmap format of input pin */
    tBitmapFormat m_sInputFormat;

    /*! bitmap format of output pin */
    tBitmapFormat m_sOutputFormat;
tBitmapFormat m_sOutputFormat2;

    /*! tha last received input image*/
     Mat m_inputImage;
     tBool       firstFrame;
     tBool stop_detect;
     tFloat32 distance;
     tFloat32 Orientation;
     tFloat32 distance_prev;
     tBool edge_detect;
     tFloat32 distance_edge;
     tFloat32 distance_prev_edge;

    tFloat32    PrevForthQuadDist,PrevFirstQuadDist;
    tInt16      m_edgeselected;
    tFloat64	m_nThresholdValue2;
    tFloat64	m_nThresholdValueBeforeNorm;
    tFloat64    m_nCornerHarrisparamK;
    tInt        m_nCornerHarrisblockSize;
    tInt        m_nCornerHarrisksize;
    tInt        m_nThresholdValueCanny;
    tInt        m_nThresholdValueHough;
    tInt	m_nThresholdValueHoughSMALL;


     // Property for Print out to console
     tBool      m_bDebugOutputEnabled;
	
};

/** @} */ // end of group

#endif  //_STOPLINE_FILTER_HEADER_
