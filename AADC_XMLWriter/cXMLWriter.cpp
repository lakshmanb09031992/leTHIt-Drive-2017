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
* $Author:: spiesra $  $Date:: 2017-05-22 15:15:31#$ $Rev:: 63721   $
**********************************************************************/
#include "stdafx.h"
#include "cXMLWriter.h"

#define TOLERANCE_X		"cXMLWriter::tolerance_x"
#define TOLERANCE_Y		"cXMLWriter::tolerance_y"

// define the ADTF property names to avoid errors
ADTF_FILTER_PLUGIN(ADTF_FILTER_DESC,
                   OID_ADTF_FILTER_DEF,
                   cXMLWriter)



cXMLWriter::cXMLWriter(const tChar* __info) : cFilter(__info)
{
	SetPropertyFloat(TOLERANCE_X,2);
    SetPropertyBool(TOLERANCE_X NSSUBPROP_ISCHANGEABLE,tTrue);
    SetPropertyStr(TOLERANCE_X NSSUBPROP_DESCRIPTION, "position tolerance in X to identify a traffic sign");
	
	SetPropertyFloat(TOLERANCE_Y,2);
    SetPropertyBool(TOLERANCE_Y NSSUBPROP_ISCHANGEABLE,tTrue);
    SetPropertyStr(TOLERANCE_Y NSSUBPROP_DESCRIPTION, "position tolerance in Y to identify a traffic sign");
}

cXMLWriter::~cXMLWriter()
{
}

tResult cXMLWriter::Start(__exception)
{

    return cFilter::Start(__exception_ptr);
}

tResult cXMLWriter::Stop(__exception)
{
    return cFilter::Stop(__exception_ptr);
}
tResult cXMLWriter::Init(tInitStage eStage, __exception)
{
    RETURN_IF_FAILED(cFilter::Init(eStage, __exception_ptr));

    if (eStage == StageFirst)
    {
		RETURN_IF_FAILED(CreateInputPins(__exception_ptr));
  
		m_TrafficSignInputSet=tFalse;
		m_ParkingInputSet=tFalse;
		m_ObstacleInputSet=tFalse;

    }
    else if (eStage == StageNormal)
    {
    }

    else if (eStage == StageGraphReady)
    {
/*
		QDomDocument docDocument("DomDocument");

		ReadXML(docDocument);

		QDomElement docElem = docDocument.documentElement();

		DomDeleteElement(docDocument, 11, 19);

		// add a new element to DOM
		QString str = "roadSign";
		DomAddElement(docDocument, docElem, str, 27, 10.0, 19.0, 1.0, 91);

		DomAddElement(docDocument, docElem, str, 28, 11.0, 19.0, 1.0, 91);

		DomAddElement(docDocument, docElem, str, 27, 12.0, 19.0, 1.0, 91);



		// write QDomDocument to XML
		WriteToXML(docDocument);

		// DOM

		QDomDocument docDocument("DomDocument");

		ReadXML(docDocument);


		// print out the element names of all elements that are direct children
		// of the outermost element.
		QDomElement docElem = docDocument.documentElement();

		QDomNode n = docElem.firstChild();
		while(!n.isNull()) {
			QDomElement e = n.toElement(); // try to convert the node to an element.


			// read ID of the traffic sign
			QString ID = e.attribute("id");
			std::string id =ID.toStdString();
			cString cid (id.c_str());

			// read y position of traffic sign
			QString Y = e.attribute("y");
			std::string y =Y.toStdString();
			cString cy (y.c_str());

			if(!e.isNull()) {
				//LOG_INFO(cid);
				//LOG_INFO(cy);
				//LOG_INFO(cString::Format("%s", id));
				//LOG_INFO(cString::Format("%s %s", qPrintable(docElem.tagName()), qPrintable(e.tagName())));
			}
			n = n.nextSibling();
		}

		// add a new element to DOM
		QString str = "roadSign";
		DomAddElement(docDocument, docElem, str, 27, 10.0, 19.0, 1.0, 91);

		//delete an element of DOM
		//DomDeleteElement(docDocument, 2, 20.0, 200.0, 1.0, 90);

		// check and change roadsign
		CheckIfTrafficSignExistInXML(docDocument, docElem, 1, 20.5, 200.5, 2.0, 45);



		// write QDomDocument to XML
		WriteToXML(docDocument);
*/

    }

    RETURN_NOERROR;
}


tResult cXMLWriter::CreateInputPins(__exception)
{
  //get the description manager for this filter
  cObjectPtr<IMediaDescriptionManager> pDescManager;
  RETURN_IF_FAILED(_runtime->GetObject(OID_ADTF_MEDIA_DESCRIPTION_MANAGER,IID_ADTF_MEDIA_DESCRIPTION_MANAGER,(tVoid**)&pDescManager,__exception_ptr));

  tChar const * strDescTrafficSign = pDescManager->GetMediaDescription("tTrafficSign");
  RETURN_IF_POINTER_NULL(strDescTrafficSign);
  cObjectPtr<IMediaType> pTypeTrafficSign = new cMediaType(0, 0, 0, "tTrafficSign", strDescTrafficSign, IMediaDescription::MDF_DDL_DEFAULT_VERSION);
  RETURN_IF_FAILED(pTypeTrafficSign->GetInterface(IID_ADTF_MEDIA_TYPE_DESCRIPTION, (tVoid**)&m_pDescTrafficSign));
  RETURN_IF_FAILED(m_InputTrafficSign.Create("TrafficSign", pTypeTrafficSign, static_cast<IPinEventSink*> (this)));
  RETURN_IF_FAILED(RegisterPin(&m_InputTrafficSign));

  tChar const * strDescObstacle = pDescManager->GetMediaDescription("tObstacle");
  RETURN_IF_POINTER_NULL(strDescObstacle);
  cObjectPtr<IMediaType> pTypeObstacle = new cMediaType(0, 0, 0, "tObstacle", strDescObstacle, IMediaDescription::MDF_DDL_DEFAULT_VERSION);
  RETURN_IF_FAILED(pTypeObstacle->GetInterface(IID_ADTF_MEDIA_TYPE_DESCRIPTION, (tVoid**)&m_pDescObstacle));
  RETURN_IF_FAILED(m_InputObstacle.Create("Obstacle", pTypeObstacle, static_cast<IPinEventSink*> (this)));
  RETURN_IF_FAILED(RegisterPin(&m_InputObstacle));

  tChar const * strDescParkingSpace = pDescManager->GetMediaDescription("tParkingSpace");
  RETURN_IF_POINTER_NULL(strDescParkingSpace);
  cObjectPtr<IMediaType> pTypeParkingSpace = new cMediaType(0, 0, 0, "tParkingSpace", strDescParkingSpace, IMediaDescription::MDF_DDL_DEFAULT_VERSION);
  RETURN_IF_FAILED(pTypeParkingSpace->GetInterface(IID_ADTF_MEDIA_TYPE_DESCRIPTION, (tVoid**)&m_pDescParkingSpace));
  RETURN_IF_FAILED(m_InputParkingSpace.Create("ParkingSpace", pTypeParkingSpace, static_cast<IPinEventSink*> (this)));
  RETURN_IF_FAILED(RegisterPin(&m_InputParkingSpace));

  RETURN_NOERROR;
}


tResult cXMLWriter::Shutdown(tInitStage eStage, ucom::IException** __exception_ptr)
{
    if (eStage == StageGraphReady)
    {
    }

    return cFilter::Shutdown(eStage, __exception_ptr);
}

tResult cXMLWriter::PropertyChanged(const char* strProperty)
{
	ReadProperties(strProperty);
	RETURN_NOERROR;
}
		
tResult cXMLWriter::ReadProperties(const tChar* strPropertyName)
{
	if (NULL == strPropertyName || cString::IsEqual(strPropertyName, TOLERANCE_X))
	{
		propToleranceX = static_cast<tFloat32> (GetPropertyFloat(TOLERANCE_X));
	}
	if (NULL == strPropertyName || cString::IsEqual(strPropertyName, TOLERANCE_Y))
	{
		propToleranceY = static_cast<tFloat32> (GetPropertyFloat(TOLERANCE_Y));
	}
	RETURN_NOERROR;
}

tResult cXMLWriter::OnPinEvent(IPin* pSource, tInt nEventCode, tInt nParam1, tInt nParam2, IMediaSample* pMediaSample)
{
		RETURN_IF_POINTER_NULL(pMediaSample);
		RETURN_IF_POINTER_NULL(pSource);
		if (nEventCode == IPinEventSink::PE_MediaSampleReceived)
		{
		// something was received
		if (pSource == &m_InputTrafficSign)
		{
		  tTimeStamp tsInputTime;
		  tsInputTime = pMediaSample->GetTime();
		  //Process Sample
		  RETURN_IF_FAILED(ProcessInputTrafficSign(pMediaSample, tsInputTime));
		}
		else if (pSource == &m_InputParkingSpace)
		{
		  tTimeStamp tsInputTime;
		  tsInputTime = pMediaSample->GetTime();
		  //Process Sample
		  RETURN_IF_FAILED(ProcessInputParkingSpace(pMediaSample, tsInputTime));
		}
		else if (pSource == &m_InputObstacle)
		{
		  tTimeStamp tsInputTime;
		  tsInputTime = pMediaSample->GetTime();
		  //Process Sample
		  RETURN_IF_FAILED(ProcessInputObstacle(pMediaSample, tsInputTime));
		}

    }
    RETURN_NOERROR;
}


tResult cXMLWriter::ProcessInputTrafficSign(IMediaSample* pMediaSample, tTimeStamp tsInputTime)
{
	cObjectPtr<IMediaCoder> pCoderInput;
	RETURN_IF_FAILED(m_pDescTrafficSign->Lock(pMediaSample, &pCoderInput));
	pCoderInput->Get("i16Identifier", (tVoid*)&m_tsI16id);
	pCoderInput->Get("f32x", (tVoid*)&m_tsF32X);
	pCoderInput->Get("f32y", (tVoid*)&m_tsF32Y);
	pCoderInput->Get("f32angle", (tVoid*)&m_tsF32Angle);
	m_pDescTrafficSign->Unlock(pCoderInput);
	
	// call DOM functions
	QDomDocument docDocument("DomDocument");
	ReadXML(docDocument);
	
	// if ID is -1, the traffic sign has to be deleted
	if(m_tsI16id==-1)
	{
		DomDeleteElement(docDocument, m_tsF32X, m_tsF32Y);
		
	}
	// else we have to check if the traffic sign is new or has replaced an other traffic sign
	else
	{
		QDomElement docElem = docDocument.documentElement();
		QString str = "roadSign";
		// check and change roadsign
		CheckIfTrafficSignExistInXML(docDocument, docElem, m_tsI16id, m_tsF32X, m_tsF32Y, 1.0, m_tsF32Angle);
	}

	// write QDomDocument to XML
	WriteToXML(docDocument);
		

  RETURN_NOERROR;
}

tResult cXMLWriter::ProcessInputParkingSpace(IMediaSample* pMediaSample, tTimeStamp tsInputTime)
{
	cObjectPtr<IMediaCoder> pCoderInput;
	RETURN_IF_FAILED(m_pDescParkingSpace->Lock(pMediaSample, &pCoderInput));
	pCoderInput->Get("i16Identifier", (tVoid*)&m_parkingI16Id);
	pCoderInput->Get("f32x", (tVoid*)&m_parkingF32X);
	pCoderInput->Get("f32y", (tVoid*)&m_parkingF32Y);
	pCoderInput->Get("ui16Status", (tVoid*)&m_parkingUI16Status);
	m_pDescParkingSpace->Unlock(pCoderInput);
  //emit SendParkingData(static_cast<int>(i16Id),static_cast<float>(f32x), static_cast<float>(f32y),static_cast<int>(ui16Status));
  RETURN_NOERROR;
}

tResult cXMLWriter::ProcessInputObstacle(IMediaSample* pMediaSample, tTimeStamp tsInputTime)
{
	cObjectPtr<IMediaCoder> pCoderInput;
	RETURN_IF_FAILED(m_pDescObstacle->Lock(pMediaSample, &pCoderInput));
	pCoderInput->Get("f32x", (tVoid*)&m_obstacleF32X);
	pCoderInput->Get("f32y", (tVoid*)&m_obstacleF32Y);
	m_pDescObstacle->Unlock(pCoderInput);
  //emit SendObstacleData(static_cast<float>(f32x), static_cast<float>(f32y) );
  RETURN_NOERROR;
}


tResult cXMLWriter::CheckIfTrafficSignExistInXML(QDomDocument &io_domDoc, QDomElement &io_domRootElement, tInt16 i_iID, tFloat32 i_fX, tFloat32 i_fY, tFloat32 i_fRadius, tFloat32 i_fDirection)
{
	QString qstrRoadSign = "roadSign";
	QDomElement domEleConfig = io_domDoc.documentElement();
	QDomNode domNodCounter = domEleConfig.firstChildElement(qstrRoadSign);

	tBool deletFlag=tFalse;
	QDomNode domBuffer;

	while(!domNodCounter.isNull()) {
		QDomElement domEleCounter = domNodCounter.toElement();

		// check if the position is almost the same
		//tInt16 ID = domEleCounter.attribute("id").toInt();
		tFloat32 X = domEleCounter.attribute("x").toFloat();
		tFloat32 Y = domEleCounter.attribute("y").toFloat();

		//LOG_INFO(cString::Format("X %f i_fX %f  Y %f i_fY %f", X , i_fX ,  Y , i_fY));

		// traffic sign in a nearby area of an existing traffic sign
		if( ( (X>=i_fX-propToleranceX) && (X<=i_fX+propToleranceX) )  && ( (Y>=i_fY-propToleranceY) && (Y<=i_fY+propToleranceY) ) )
		{
			// element have to be deleted
			deletFlag=tTrue;
			domBuffer = domNodCounter;
			//LOG_INFO(cString::Format("Position is equal"));
		}
		else{
			// element has not to be deleted
			deletFlag=tFalse;
		}
		// go to next element
		domNodCounter = domNodCounter.nextSiblingElement(qstrRoadSign);

		// if the delet flag has been set, delete this element
		if(deletFlag)
		{
			domEleConfig.removeChild(domBuffer);
		}			
	}

	// add new traffic sign
	DomAddElement(io_domDoc, io_domRootElement, qstrRoadSign, i_iID, i_fX, i_fY, i_fRadius, i_fDirection);
	

	RETURN_NOERROR;
}

// add a new element to the DOM
tResult cXMLWriter::DomAddElement(QDomDocument &io_domDoc, QDomElement &io_domRootElement, QString i_qstrString, tInt16 i_iID, tFloat32 i_fX, tFloat32 i_fY, tFloat32 i_fRadius, tFloat32 i_fDirection)
{
	// create a new traffic sign
	QDomElement elem = io_domDoc.createElement(i_qstrString);
	elem.setAttribute("id", i_iID);
	elem.setAttribute("x", i_fX);
	elem.setAttribute("y", i_fY);
	elem.setAttribute("radius", i_fRadius);
	elem.setAttribute("direction", i_fDirection);
	io_domRootElement.appendChild(elem);
	RETURN_NOERROR;
}

// delete element of DOM if all attributes are same
tResult cXMLWriter::DomDeleteElement(QDomDocument &io_domDoc, tFloat32 i_fX, tFloat32 i_fY)
{

	QDomElement domEleConfig = io_domDoc.documentElement();
	QDomNode domNodCounter = domEleConfig.firstChild();

	tBool deletFlag=tFalse;
	QDomNode domBuffer;

	while(!domNodCounter.isNull()) {
		QDomElement domEleCounter = domNodCounter.toElement();

		// check if the ID is the same
		//tInt16 ID = domEleCounter.attribute("id").toInt();
		tFloat32 X = domEleCounter.attribute("x").toFloat();
		tFloat32 Y = domEleCounter.attribute("y").toFloat();

		if( (X==i_fX) && (Y==i_fY) )
		{
			// element have to be deleted
			deletFlag=tTrue;
			domBuffer = domNodCounter;
			
		}
		else{
			// element has not to be deleted
			deletFlag=tFalse;
		}
		// go to next element
		domNodCounter = domNodCounter.nextSibling();

		// if the delet flag has been set, delete this element
		if(deletFlag)
		{
			domEleConfig.removeChild(domBuffer);
		}			
	}
	

	RETURN_NOERROR;
}

tResult cXMLWriter::ReadXML(QDomDocument &o_docDocument)
{

	QFile file("/home/aadc/ADTF/configuration_files/roadSigns_test.xml");
	if (!file.open(QIODevice::ReadWrite))
		RETURN_NOERROR;
	if (!o_docDocument.setContent(&file)) {
		file.close();
		RETURN_NOERROR;
	}
	file.close();
	RETURN_NOERROR;
}

tResult cXMLWriter::WriteToXML(QDomDocument &i_docDocument)
{
	// write QDomDocument to XML

	QFile outFile( "/home/aadc/ADTF/configuration_files/roadSigns_test.xml" );
	if( !outFile.open( QIODevice::WriteOnly | QIODevice::Text ) )
	{
		LOG_ERROR(cString::Format("Failed to open file for writing."));
		RETURN_NOERROR;
	}

	QTextStream stream( &outFile );
	stream << i_docDocument.toString();

	outFile.close();
	RETURN_NOERROR;
}
