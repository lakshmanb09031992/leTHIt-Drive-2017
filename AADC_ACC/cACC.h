/**
Copyright (c)
Audi Autonomous Driving Cup. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3.  All advertising materials mentioning features or use of this software must display the following acknowledgement: �This product includes software developed by the Audi AG and its contributors for Audi Autonomous Driving Cup.�
4.  Neither the name of Audi nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY AUDI AG AND CONTRIBUTORS �AS IS� AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL AUDI AG OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


**********************************************************************
* $Author:: spiesra $  $Date:: 2017-05-12 09:34:53#$ $Rev:: 63109   $
**********************************************************************/
#ifndef _ACC_FILTER_H_
#define _ACC_FILTER_H_

#define OID_ADTF_ACC_FILTER "adtf.example.acc_filter"
//#include <array>

/*! @defgroup TemplateFilter
*  @{
*
*  \image html User_Template.PNG "Plugin Template Filter"
*
* This is a small template which can be used by the AADC teams for their own filter implementations.
* \b Dependencies \n
* This plugin needs the following libraries:
*
*
* <b> Filter Properties</b>
* <table>
* <tr><th>Property<th>Description<th>Default
* </table>
*
* <b> Output Pins</b>
* <table>
* <tr><th>Pin<th>Description<th>MajorType<th>SubType
* <tr><td>output_template<td>An example output pin<td>MEDIA_TYPE_TEMPLATE<td>MEDIA_TYPE_TEMPLATE
*</table>
*
* <b> Input Pins</b>
* <table>
* <tr><th>Pin<th>Description<th>MajorType<th>SubType
* <tr><td>input_template<td>An example input pin<td>MEDIA_TYPE_TEMPLATE<td>MEDIA_TYPE_TEMPLATE
* </table>
*
* <b>Plugin Details</b>
* <table>
* <tr><td>Path<td>src/aadcUser/AADC_TemplateFilter
* <tr><td>Filename<td>user_templateFilter.plb
* <tr><td>Version<td>1.0.0
* </table>
*
*
*/

//!  Template filter for AADC Teams
/*!
* This is a example filter for the AADC
*/
class cACC : public adtf::cFilter
{
    /*! set the filter ID and the version */
    ADTF_FILTER(OID_ADTF_ACC_FILTER, "ACC", adtf::OBJCAT_DataFilter);

protected:

	/* INPUT PINS */

	// Start
	cInputPin m_oStart;
	cObjectPtr<IMediaTypeDescription> m_pDescStart;

	// input speed controller
	cInputPin   m_oInputSpeedController;
	cObjectPtr<IMediaTypeDescription> m_pDescSpeed;

	// input current speed
	cInputPin   m_oInputCurrentSpeed;
	cObjectPtr<IMediaTypeDescription> m_pDescCurrentSpeed;

	// input steering
	cInputPin   m_oInputSteering;
	cObjectPtr<IMediaTypeDescription> m_pDescSteering;

	// input first heading angle
	cInputPin   m_oInputHeadingAngle;
	cObjectPtr<IMediaTypeDescription> m_pDescHeadingAngle;

	// input ultrasonic struct
	cInputPin    m_oInputUsStruct;
	cObjectPtr<IMediaTypeDescription> m_pDescriptionUsStruct;

	// Distance over all
	cInputPin m_oDistanceOverall;
	cObjectPtr<IMediaTypeDescription> m_pDescdistanceoverall;

	cCriticalSection m_critSecMinimumUsValue;

    std::vector<tBufferID> m_szIdUsStructValues;
    std::vector<tBufferID> m_szIdUsStructTss;
    tBool	 m_szIdsUsStructSet;

	 /* OUTPUT PINS */

	// output acceleration
	cOutputPin m_oOutputAcceleration;
	cObjectPtr<IMediaTypeDescription> m_pDescriptionOutputAcceleration;

	// output steering
	cOutputPin    m_oOutputSteering;
	cObjectPtr<IMediaTypeDescription> m_pDescriptionOutputSteering;

	// output turnSignalLeftEnabled
	cOutputPin m_oOutputTurnSignalLeftEnabled;
	cObjectPtr<IMediaTypeDescription> m_pDescriptionOutputTurnSignalLeftEnabled;

	// output turnSignalRightEnabled
	cOutputPin m_oOutputTurnSignalRightEnabled;
	cObjectPtr<IMediaTypeDescription> m_pDescriptionOutputTurnSignalRightEnabled;

	// output overtake
	cOutputPin m_oOutputOvertake;
	cObjectPtr<IMediaTypeDescription> m_pDescriptionOvertake;



	/* SLAM */

	/*! Input pin for the position data */
    cInputPin m_InputPostion;
	cObjectPtr<IMediaTypeDescription> m_pDescriptionPos;

	 //Position input
    tBool m_PosInputSet;
  	tFloat32 m_szF32X,m_szF32Y,m_szF32Radius,m_szF32Speed,m_szF32Heading;

	/*! Output pin for the obstacle data */
	cOutputPin m_OutputObstacle;
	cObjectPtr<IMediaTypeDescription> m_pDescriptionObstacle;

	//Obstacle Output
	tFloat32 m_obstacleF32X,m_obstacleF32Y;

	// Flag for scanning left side
	tBool m_bFlagObstacleLeft;
	// x Distance of Left Obstacle
	tFloat32 m_fStartDistLeftObstacle;
	tFloat32 m_fEndDistLeftObstacle;

	tFloat32 m_fDistYbuffer;

 

	/* DEBUG */

	tBool m_bDebugModeEnabled;

	/* MEMBER VARIABLES INPUT*/

	tBool isInitialized_;

	tBool m_bStart;
	tFloat32 m_fSpeedControllerInput;
	tFloat32 m_fCurrentSpeedInput;
	tFloat32 m_fSteeringInput;

	// distance over all
	tFloat32 m_fDistanceOverall;

	// first heading angle
	tFloat32 m_fFirstHeadingAngle;

	/*
	// storage for US values
    tFloat32 m_oUSFrontCenter;
	tFloat32 m_oUSFrontCenterLeft;
	tFloat32 m_oUSFrontCenterRight;
	tFloat32 m_oUSFrontLeft;
	tFloat32 m_oUSFrontRight;
	*/

	//std::array<tFloat32,10> m_aUSSensors;

	tFloat32 m_aUSSensors[10];

	/* MEMBER VARIABLES PROCESS*/
	tBool m_bMovedLeft;
	tBool m_bLeftLaneIsFree;
	tBool m_bRigthLaneIsFree;

	tTimeStamp stop_time;

	tBool m_bFlagTimeOvertake;
	tTimeStamp timestampOvertake;


	// time stamp
	tTimeStamp init_time;
	tUInt32 timestamp;

	/* MEMBER VARIABLES OUTPUT*/
	tFloat32 m_fSteeringOutput;
	tFloat32 m_fAccelerationOutput;
	tBool m_bTurnSignalLeftEnabled;
	tBool m_bTurnSignalRightEnabled;
	tBool m_bOvertake;

public:
    /*! default constructor for template class
           \param __info   [in] This is the name of the filter instance.
    */
    cACC(const tChar* __info);

    /*! default destructor */
    virtual ~cACC();

protected:
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
    *   \return Returns a standard result code.
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


	tResult ProcessInputUS(IMediaSample* pMediaSample);

	tResult ReadProperties(const tChar* strPropertyName);
	tResult PropertyChanged(const char* strProperty);

	tResult CalculateSpeed();

	tResult ScanningLeftLaneForObstacle();

	tResult ProcessInputPosition(IMediaSample* pMediaSampleIn, tTimeStamp tsInputTime);

	tResult computepose(tFloat32 i_distX, tFloat32 i_distY);
	
	tResult TransmitOutput();

	tResult TransmitOutputOvertake();
	
	tResult TransmitObstaclePosition(tFloat32 i_fXPos, tFloat32 i_fYPos);


	private:
		// properties
		tFloat32    m_fMaxDist, m_fMaxDistCurve, m_fSteeringToSwitchFocus;

		tFloat32 m_fStopTTC, m_fReduceSpeedTTC;
};

//*************************************************************************************************
#endif // _ACC_FILTER_H_

/*!
*@}
*/
