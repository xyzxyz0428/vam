/**
 * @addtogroup mod_raw_its ITS MSG Tx/Rx Module
 * @{
 *
 * ITS MSG sender & receiver thread
 *
 * @file
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2012 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------
#include "raw-its.h"
#include "raw-asn.h"
#include "raw-asn_def.h"

#include "ExampleETSI_debug.h"

// v2x-lib includes
#include "id-global.h"
#include "util.h"
#include "ext.h"
#include "PacketBuffer.h"
#include "etsi-msg-if.h"
#include "etsi-btp.h"
#include "etsi-g5.h"
#include "debug-levels.h"

#include "libconfig.h" // used to read configuration file

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

//UDP
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h> // for close
#define BUFLEN 512  //Max length of buffer
#define PORT1 8888   //The port on which to listen for incoming data
//LPH
#include "lph.h"
void *lphhandle;

//------------------------------------------------------------------------------
// Local Macros & Constants
//------------------------------------------------------------------------------

#define D_LEVEL ExampleETSI_ExampleETSI_Raw_DebugLevel

//------------------------------------------------------------------------------
// Local Type definitions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local (static) Function Prototypes
//------------------------------------------------------------------------------

static int RAWIts_LoadConfig (struct RAWIts *pRAW,
		char * pConfigFileName);

static void RAWIts_ThreadProc (void *pArg);

static void RAWIts_ExtCallback(tExtEventId Event,
		tExtMessage *pMsg,
		void *pPriv);

static int RAWIts_ReqSend(tETSIMSGHandleCode Handle,
		tRAWItsParams *pParams);

//static int RAW_MsgCreate(RAW_RAW **ppMsg, int Len, uint8_t *Data);
static int RAW_MsgCreate(RAW_RAW **ppMsg,const struct LPHData *pLPHData);
void die(char *s);
int udpserver ();
//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------
struct RAWexternedata pudpserver;
/// Local pointer to config
struct RAWIts *pRAWStat;

//------------------------------------------------------------------------------
// API Functions
//------------------------------------------------------------------------------


/**
 * @brief Allocate RAWIts object, Setup thread and associated data structures
 * @param pRAW pointer to RAW handle (populated by this function)
 * @param pAttr POSIX thread attributes
 * @param pConfigFileName Configuration filename
 * @return Zero for success or an negative errno
 */
int RAWIts_Open (struct RAWIts *pRAW,
		pthread_attr_t *pAttr,
		char *pConfigFileName)
{
	int Res;
	d_fnstart(D_INTERN, NULL, "(%p,%p,%s)\n",
			pRAW, pAttr, pConfigFileName);

	memset(pRAW, 0, sizeof(struct RAWIts));

	// Load config settings
	Res = RAWIts_LoadConfig(pRAW, pConfigFileName);
	if (Res != 0)
	{
		d_printf(D_INFO, NULL, "RAWIts_LoadConfig(%p,%s) != 0\n", pRAW, pConfigFileName);
		goto Error;
	}

	pRAWStat = pRAW;

	// Init state
	//add LPH handle
	lphhandle=LPH_Open();
	// Assign thread attributes from input param
	pRAW->ThreadAttr = *pAttr;

	// Create RAWIts thread
	pRAW->ThreadState |= RAWITS_THREAD_STATE_INIT;
	Res = pthread_create(&pRAW->ThreadID,
			&pRAW->ThreadAttr,
			(void *)RAWIts_ThreadProc,
			pRAW);
	if (Res != 0)
	{
		d_printf(D_INFO, NULL, "pthread_create() failed\n");
		// Thread creation error
		pRAW->ThreadState = RAWITS_THREAD_STATE_NONE;
		goto Error;
	}

	// Success!
	Res = 0;
	d_printf(D_INFO, NULL, "Successfully started raw-its\n");
	goto Success;

	Error:
	d_error(D_ERR, 0, "Error!\n");
	RAWIts_Close(pRAW);
	Success:
	d_fnend(D_INFO, NULL, "()\n");
	return Res;
}

/**
 * @brief Stop execution of RAW, free the thread and its associated resources
 * @param pRAW RAW handle
 */
void RAWIts_Close (struct RAWIts *pRAW)
{
	int Res = -ENOSYS;
	d_fnstart(D_INFO, NULL, "()\n");

	// Catch attempt to close invalid object pointer
	if (pRAW == NULL)
	{
		Res = -EINVAL;
		goto Error;
	}
	//close LPH handle
	LPH_Close(lphhandle);
	// Signal thread to terminate
	pRAW->ThreadState |= RAWITS_THREAD_STATE_STOP;
	// Wait for thread termination
	if (pRAW->ThreadState & RAWITS_THREAD_STATE_INIT)
		pthread_join(pRAW->ThreadID, NULL);

	// Success!
	Res = 0;

	Error:
	(void)Res;    // value not currently used

	d_fnend(D_INFO, NULL, "()\n");
	return;
}

/**
 * @brief Prints the statistics
 * @param pRAW RAW handle
 */
void RAWIts_PrintStats (struct RAWIts *pRAW)
{
	fprintf(stdout, "RAWIts: Rx (Okay %8u Fail %8u)\n",
			pRAW->Stats.Rx.Okay, pRAW->Stats.Rx.Fail);

}

//------------------------------------------------------------------------------
// Local Functions
//------------------------------------------------------------------------------

/**
 * @brief Load RAWITS parameters from the config file
 * @param pRAW RAW receiver handle
 * @param pConfigFileName Filename of the config file
 * @return Zero for success or a negative errno
 */
static int RAWIts_LoadConfig (struct RAWIts *pRAW,
		char *pConfigFileName)
{
	int Res = -ENOSYS;
	config_t Config; // configuration object read from config file
	config_t *pConfig;
	config_setting_t *pSetting; // setting for RAWITS in config file
	int ConfigVal = 0;
	long long ConfigVal64 = 0;

	pConfig = &Config;
	config_init(pConfig); // initialise the config object

	// Set defaults
	pRAW->Params.BTPPort = RAWITS_CONFIG_VALUE_DEFAULT_BTPPORT;
	pRAW->Params.TxInterval = RAWITS_CONFIG_VALUE_DEFAULT_TXINTERVAL;
	pRAW->Params.RxInterval = RAWITS_CONFIG_VALUE_DEFAULT_RXINTERVAL;
	pRAW->Params.DestInfo = RAWITS_CONFIG_VALUE_DEFAULT_DESTINFO;
	pRAW->Params.PktTransport = RAWITS_CONFIG_VALUE_DEFAULT_PKTTRANSPORT;
	pRAW->Params.Location = RAWITS_CONFIG_VALUE_DEFAULT_LOCATION;
	pRAW->Params.AreaLat = RAWITS_CONFIG_VALUE_DEFAULT_AREALAT;
	pRAW->Params.AreaLong = RAWITS_CONFIG_VALUE_DEFAULT_AREALONG;
	pRAW->Params.AreaDistA = RAWITS_CONFIG_VALUE_DEFAULT_AREADISTA;
	pRAW->Params.AreaDistB = RAWITS_CONFIG_VALUE_DEFAULT_AREADISTB;
	pRAW->Params.AreaAngle = RAWITS_CONFIG_VALUE_DEFAULT_AREAANGLE;
	pRAW->Params.AreaShape = RAWITS_CONFIG_VALUE_DEFAULT_AREASHAPE;
	pRAW->Params.CommProfile = RAWITS_CONFIG_VALUE_DEFAULT_COMMPROFILE;
	pRAW->Params.TrafficClass = RAWITS_CONFIG_VALUE_DEFAULT_TRAFFICCLASS;
	pRAW->Params.MaxPktLifetime = RAWITS_CONFIG_VALUE_DEFAULT_MAXPKTLIFETIME;
	pRAW->Params.SecProfile = RAWITS_CONFIG_VALUE_DEFAULT_SECPROFILE;
	pRAW->Params.DataLength = RAWITS_CONFIG_VALUE_DEFAULT_DATALENGTH;
	memcpy(pRAW->Params.Data,
			RAWITS_CONFIG_VALUE_DEFAULT_DATA,
			RAWITS_CONFIG_VALUE_DEFAULT_DATALENGTH);

	// Try to read the specified config file into the config object
	if (config_read_file(pConfig, pConfigFileName) != CONFIG_TRUE)
	{
		d_error(D_ERR, 0, "Could not open %s\n", pConfigFileName);
		// "libconfig: %s at line %d\n", config_error_text (pConfig),
		Res = -EINVAL;
		goto Error;
	}

	// Get the RAWIts Setting
	pSetting = config_lookup(pConfig, RAWITS_CONFIG_PATH_NAME);
	if (pSetting == NULL)
	{
		d_error(D_ERR, 0, "config_lookup(%s) failed\n", RAWITS_CONFIG_PATH_NAME);
		Res = -EINVAL;
		goto Error;
	}

	// config is open, now look for configuration entries

	// BTP Port
	if (config_setting_lookup_int(pSetting,
			RAWITS_CONFIG_VALUE_NAME_BTPPORT,
			&ConfigVal))
		pRAW->Params.BTPPort = (uint16_t) ConfigVal;

	// Rx thread Interval
	if (config_setting_lookup_int(pSetting,
			RAWITS_CONFIG_VALUE_NAME_RXINTERVAL,
			&ConfigVal))
		pRAW->Params.RxInterval = (uint32_t) ConfigVal;

	// TxInterval
	if (config_setting_lookup_int(pSetting,
			RAWITS_CONFIG_VALUE_NAME_TXINTERVAL,
			&ConfigVal))
		pRAW->Params.TxInterval = (uint32_t) ConfigVal;

	// Packet
	config_setting_t *pPacket;
	pPacket = config_setting_get_member(pSetting,
			RAWITS_CONFIG_VALUE_NAME_PACKET);

	if (pPacket != NULL)
	{
		// DestInfo
		if (config_setting_lookup_int(pPacket,
				RAWITS_CONFIG_VALUE_NAME_DESTINFO,
				&ConfigVal))
			pRAW->Params.DestInfo = (uint16_t) ConfigVal;

		// PktTransport
		if (config_setting_lookup_int(pPacket,
				RAWITS_CONFIG_VALUE_NAME_PKTTRANSPORT,
				&ConfigVal))
			pRAW->Params.PktTransport = (uint8_t) ConfigVal;

		// CommProfile
		if (config_setting_lookup_int(pPacket,
				RAWITS_CONFIG_VALUE_NAME_COMMPROFILE,
				&ConfigVal))
			pRAW->Params.CommProfile = (uint8_t) ConfigVal;

		// TrafficClass
		if (config_setting_lookup_int(pPacket,
				RAWITS_CONFIG_VALUE_NAME_TRAFFICCLASS,
				&ConfigVal))
			pRAW->Params.TrafficClass = (uint8_t) ConfigVal;

		// MaxPktLifetime
		if (config_setting_lookup_int(pPacket,
				RAWITS_CONFIG_VALUE_NAME_MAXPKTLIFETIME,
				&ConfigVal))
			pRAW->Params.MaxPktLifetime = ConfigVal;

		// Security Profile
		if (config_setting_lookup_int(pPacket,
				RAWITS_CONFIG_VALUE_NAME_SECPROFILE,
				&ConfigVal))
			pRAW->Params.SecProfile = (uint8_t) ConfigVal;

		// Location
		if (config_setting_lookup_int64(pPacket,
				RAWITS_CONFIG_VALUE_NAME_LOCATION,
				&ConfigVal64))
			pRAW->Params.Location = ConfigVal64;

		// Area
		if (config_setting_lookup_int(pPacket,
				RAWITS_CONFIG_VALUE_NAME_AREALAT,
				&ConfigVal))
			pRAW->Params.AreaLat = ConfigVal;
		if (config_setting_lookup_int(pPacket,
				RAWITS_CONFIG_VALUE_NAME_AREALONG,
				&ConfigVal))
			pRAW->Params.AreaLong = ConfigVal;
		if (config_setting_lookup_int(pPacket,
				RAWITS_CONFIG_VALUE_NAME_AREADISTA,
				&ConfigVal))
			pRAW->Params.AreaDistA = ConfigVal;
		if (config_setting_lookup_int(pPacket,
				RAWITS_CONFIG_VALUE_NAME_AREADISTB,
				&ConfigVal))
			pRAW->Params.AreaDistB = ConfigVal;
		if (config_setting_lookup_int(pPacket,
				RAWITS_CONFIG_VALUE_NAME_AREAANGLE,
				&ConfigVal))
			pRAW->Params.AreaAngle = ConfigVal;
		if (config_setting_lookup_int(pPacket,
				RAWITS_CONFIG_VALUE_NAME_AREASHAPE,
				&ConfigVal))
			pRAW->Params.AreaShape = ConfigVal;

		// Data
		config_setting_t *pData;
		pData = config_setting_get_member(pPacket, RAWITS_CONFIG_VALUE_NAME_DATA);
		if (pData != NULL)
		{
			int i;
			int Cnt = config_setting_length(pData);

			if (Cnt > RAWITS_DATA_BUF_SIZE)
				Cnt = RAWITS_DATA_BUF_SIZE;

			for (i = 0; i < Cnt; i++)
			{
				ConfigVal = config_setting_get_int_elem(pData, i);
				pRAW->Params.Data[i] = (uint8_t)ConfigVal;
			}
			// Data Length
			pRAW->Params.DataLength = Cnt;
		}
	}

	// Update complete - close the configuration
	config_destroy(pConfig);

	// Success!
	Res = 0;

	Error:
	return Res;
}

/**
 * @brief RAW Periodic thread processing - sends a RAW
 * @param pArg Pointer to RAWIts object passed as generic input parameter
 *
 */
static void RAWIts_ThreadProc (void *pArg)
{
	struct RAWIts *pRAW;
	struct timespec Time;
	int RAWHandle;
	int ExtHandle;

	d_printf(D_INFO, NULL, "Started thread\n");

	pRAW = (struct RAWIts *) pArg;

	// Initialise the timespec struct for the polling loop
	clock_gettime(CLOCK_MONOTONIC, &Time);

	// "Starting RAW Periodic Thread");
	pRAW->ThreadState |= RAWITS_THREAD_STATE_RUN;

	// Register the callback with the Ext Module
	ExtHandle = Ext_CallbackRegister(RAWIts_ExtCallback, pRAW);

	if (ExtHandle < 0)
	{
		d_error(D_ERR, 0, "Unable to register callback with EXT module\n");
		goto Error;
	}

	// Open BTP Port
	// No handler provided, use EXT interface to get MSG Indications
	RAWHandle = ETSIMSG_OpenInterface(pRAW->Params.BTPPort, NULL);

	if (RAWHandle < ETSIMSG_SUCCESS)
	{
		d_error(D_ERR, 0, "Unable to open BTP port %d\n", pRAW->Params.BTPPort);
		goto Error;
	}

	// Thread loop
	while ((pRAW->ThreadState & RAWITS_THREAD_STATE_STOP) == 0)
	{
		// sleeping delay
		Util_Nap(pRAW->Params.TxInterval, &Time);

		// Send something
		RAWIts_ReqSend(RAWHandle, &pRAW->Params);
	}

	// Close BTP Port
	ETSIMSG_CloseInterface(RAWHandle);

	// Deregister the Ext Callback
	Ext_CallbackDeregister(ExtHandle);

	Error:
	// exit thread
	(void) pthread_exit(NULL);

}


/**
 * @brief RAW Packet Sending
 * @param Handle Handle from ETSI MSG API
 * @param pParams Pointer to parameters of control and data
 *
 */
static int RAWIts_ReqSend(tETSIMSGHandleCode Handle,
		tRAWItsParams *pParams)
{
	int Ret = -1;
	tETSIMSGStatusCode Stat;
	RAW_RAW *pMsg = NULL;

	(void)Handle;

	// Fill BTP header
	tETSIMSGReqMgmt MSGReqHdr;

	memset(&MSGReqHdr, 0, sizeof(MSGReqHdr));

	MSGReqHdr.ID = ETSIMSG_ACTIONID(0x1234);
	MSGReqHdr.RepetitionDuration = ETSIFAC_REPETITIONDURATIONNONE;
	MSGReqHdr.RepetitionInterval = ETSIFAC_REPETITIONINTERVALNONE;

	MSGReqHdr.DestPort = pParams->BTPPort;
	MSGReqHdr.DestInfo = pParams->DestInfo;
	MSGReqHdr.BTPType = ETSIFAC_BTP_TYPE_B;

	MSGReqHdr.PktTransport = pParams->PktTransport;
	MSGReqHdr.CommProfile = pParams->CommProfile;
	MSGReqHdr.TrafficClass = pParams->TrafficClass;
	MSGReqHdr.HopLimit = ETSIFAC_GN_HOP_LIMIT_DEFAULT;
	MSGReqHdr.MaxPktLifetime = pParams->MaxPktLifetime;

	// Destination Information, possibly not needed for some PktTransport types
	// but filled anyway to show example
	// For GUC, address in 64-bit host format
	MSGReqHdr.Address.GN_ADDR_as_64 = ntohll(pParams->Location);
	// For GBC/GAC
	MSGReqHdr.Area.Latitude = pParams->AreaLat;
	MSGReqHdr.Area.Longitude = pParams->AreaLong;
	MSGReqHdr.Area.Distance_a = pParams->AreaDistA;
	MSGReqHdr.Area.Distance_b = pParams->AreaDistB;
	MSGReqHdr.Area.Angle = pParams->AreaAngle;
	MSGReqHdr.Area.Shape = pParams->AreaShape;

	// Secure or Unsecure packet
	if (pParams->SecProfile == 0)
	{
		MSGReqHdr.SecControl = ETSIFAC_GN_SEC_PROF_NONE;
	}
	else if (pParams->SecProfile == 1)
	{
		// Custom security
		MSGReqHdr.SecControl = ETSIFAC_GN_SEC_PROF_AID_SSP;

		// CAM ITS-AID
		MSGReqHdr.SecInfo.AID = 0x24;
		// Replicate CAM security SSP
		MSGReqHdr.SecInfo.SSPBitmap = true;
		MSGReqHdr.SecInfo.SSPLen = 3;
		MSGReqHdr.SecInfo.SSPBits[0] = 0x01;
		MSGReqHdr.SecInfo.SSPBits[1] = 0x00;
		MSGReqHdr.SecInfo.SSPBits[2] = 0x00;
		MSGReqHdr.SecInfo.SSPMask[0] = 0xFF;
		MSGReqHdr.SecInfo.SSPMask[1] = 0x00;
		MSGReqHdr.SecInfo.SSPMask[2] = 0x00;
	}
	else if (pParams->SecProfile == 2)
	{
		// Fixed CAM security profile
		MSGReqHdr.SecControl = ETSIFAC_GN_SEC_PROF_CAM;
	}
	else
	{
		// Fixed General security profile
		MSGReqHdr.SecControl = ETSIFAC_GN_SEC_PROF_GENERAL;
	}

	//UDP server

	int resudpserver = udpserver();
	if (resudpserver)
	{
		d_error(D_ERR, 0, "UDP server failed\n");
		printf("UDP server failed\n");
	}

	//get LPH data of ego module
	const struct LPHData * plphData = 0;
	int rc = LPH_Data(lphhandle, &plphData);
	if ((rc)      ||
			(!plphData)  ||
			(plphData->Pos.Mode < LPH_POS_FIX_MODE_2D))
	{
		d_printf(D_WARN, NULL, "No Position: %d\n", plphData->Pos.Mode);
		goto Exit;
	}

	// Create and populate the message
	//  int Res = RAW_MsgCreate(&pMsg, pParams->DataLength, pParams->Data);
	int Res = RAW_MsgCreate(&pMsg,plphData);
	if (Res)
	{
		d_error(D_ERR, 0, "RAW_MsgCreate failed\n");
		goto Exit;
	}

	// Use the XER decoder to show the message in the debug output
	uint8_t *pXerBuf;
	unsigned int XerLen;

	XerLen = asn1_xer_encode(&pXerBuf, asn1_type_RAW_RAW, pMsg);

	d_printf(D_INFO, NULL, "XER[%d]:\n%s", XerLen, pXerBuf);
	free(pXerBuf);

	// Encode (with PER)
	ASN1Error Err;
	int Len;
	uint8_t *pBuf;

	Len = asn1_uper_encode2(&pBuf, asn1_type_RAW_RAW, pMsg, &Err);

	if (Len <= 0)
	{
		d_printf(D_WARN, NULL, "PER encode failed: %d (bit %d, %s)\n", Len, Err.bit_pos, Err.msg);
		goto Exit;
	}

	// Encoding finished successfully, 'encoded' is number of bits encoded
	d_printf(D_INFO, NULL, "PER encoded %d bytes\n", Len);

	int PLen;
	for (PLen = 0; (PLen < Len) && (PLen < 80); PLen++)
	{
		fprintf(stderr, " %02x", pBuf[PLen]);
	}
	fprintf(stderr, "\n");

	// And send
	Stat = ETSIMSG_SendPacket(&MSGReqHdr, pBuf, Len);

	if (Stat == ETSIMSG_SUCCESS)
	{
		Ret = 0;
	}

	asn1_free_value(asn1_type_RAW_RAW, pMsg);
	free(pBuf);
	Exit:
	return Ret;
}


/**
 * @brief EXT Callback
 * @param Event Event type of EXT event
 * @param pMsg The EXT message structure
 * @param pPriv Private pointer provided in registration
 *
 */
static void RAWIts_ExtCallback(tExtEventId Event,
		tExtMessage *pMsg,
		void *pPriv)
{
	(void)pPriv;

	// Check Event type is a 'message type' event
	if (Event == QSMSG_EXT_RX_ITSFL_MSG)
	{
		d_printf(D_INFO, NULL, "QSMSG_EXT_RX_ITSFL_MSG\n");
		d_assert(pMsg != NULL);
		d_assert(pMsg->pPkt != NULL);

		struct RAWIts *pRAW = (struct RAWIts *) pPriv;
		tUtilPacketBuffer *pRxPkt = pMsg->pPkt;

		// DestPort from BTP descriptor
		const tETSIGeoNetDesc *pBTP = pRxPkt->Elem.pETSIGeoNetDesc;
		d_printf(D_INFO, NULL, "DestPort=%d\n", pBTP->DestPort);

		if (pBTP->DestPort == pRAW->Params.BTPPort)
		{
			// Access the payload of the PacketBuffer
			uint8_t *pPayload = pRxPkt->Elem.Payload.pData;
			uint16_t Length = pRxPkt->Elem.Payload.Len;

			// Dump the packet payload
			int PLen;
			d_printf(D_INFO, NULL, "Payload[%d]...\n", Length);
			for (PLen = 0; (PLen < Length) && (PLen < 80); PLen++)
			{
				fprintf(stderr, " %02x", pPayload[PLen]);
			}
			fprintf(stderr, "\n");

			if (pPayload && (Length > 0))
			{
				pRAWStat->Stats.Rx.Okay++;
			}

			// Decode (from PER), decoded buffer will be created
			ASN1Error Err;
			RAW_RAW *pRawRx;

			int Bytes = asn1_uper_decode((void **)&pRawRx, asn1_type_RAW_RAW, (const uint8_t *)pPayload, Length, &Err);

			if (Bytes <= 0)
			{
				d_printf(D_WARN, NULL, "PER decode failed: %d (bit %d, %s)\n", Bytes, Err.bit_pos, Err.msg);
			}
			else
			{
				// Access some parts of the structure
//				d_printf(D_INFO, NULL, "StationID=0x%04x, Seq %d\n",
//						(int)pRawRx->header.stationID,
//						(int)pRawRx->dummy.sequenceNumber);

				// Use the XER decoder to show the message in the debug output
				uint8_t *pXerBuf;
				unsigned int XerLen;

				XerLen = asn1_xer_encode(&pXerBuf, asn1_type_RAW_RAW, pRawRx);

				d_printf(D_INFO, NULL, "XER[%d]:\n%s", XerLen, pXerBuf);
				free(pXerBuf);
			}
		}

		// Access some information in the packet descriptor
		// RSSI from G5 descriptor
		tETSIG5Desc *pG5 = pRxPkt->Elem.pETSIG5Desc;
		d_printf(D_INFO, NULL, "RSSI=%d\n", pG5->Rx.RSSI);
	}
}

/**
 * @brief Creates an RAW message by populating the members of the RAW
 *        message. The message is allocated, the member field values set
 *        including copying the provided Data to the relevant field.
 *
 * @param ppMsg Pointer to RAW
 * @param Len Length of payload data
 * @param Data Pointer to payload data
 * @return     0 for success,
 *
 */
static int RAW_MsgCreate(RAW_RAW **ppMsg,const struct LPHData *pLPHData)
{
	int RetVal = -ENOSYS;

	*ppMsg = (RAW_RAW *)asn1_mallocz_value(asn1_type_RAW_RAW);

	if (!*ppMsg)
	{
		RetVal = -ENOMEM;
		goto Error;
	}

	// set the PDU header
	(*ppMsg)->header.protocolVersion = 1;
	(*ppMsg)->header.messageID = 14;
	(*ppMsg)->header.stationID = 0x6666;
	(*ppMsg)->vammsg.vam.generationDeltaTime=1/RAWITS_CONFIG_VALUE_DEFAULT_TXINTERVAL;
	(*ppMsg)->vammsg.vam.vamParameters.basicContainer.stationType=2;
	//set VAM message from pLPHData
	//dummy for use pLPHData
	printf("create msg with Latitude of mk5:%d.\n",pLPHData->Pos.Latitude);
	/// J2735's DE_Latitude.
	/// Range: -900000000..900000001 (-90..90) Units: 1/10 micro degree
	//(*ppMsg)->vammsg.vam.vamParameters.basicContainer.referencePosition.latitude= pLPHData->Pos.Latitude;
	/// J2735's DE_Longitude.
	/// Range -1799999999..1800000001 (-180..180) Units: 1/10 micro degree
	//(*ppMsg)->vammsg.vam.vamParameters.basicContainer.referencePosition.longitude= pLPHData->Pos.Longitude;
	/// J2735's DE_Elevation
	/// -4096..61439
	/// -- In units of 10 cm steps above or below the reference ellipsoid
	/// -- Providing a range of -409.5 to + 6143.9 meters
	/// -- The value -4096 shall be used when Unknown is to be sent
	//(*ppMsg)->vammsg.vam.vamParameters.basicContainer.referencePosition.altitude.altitudeValue= pLPHData->Pos.Elevation;
	/// J2735's DE_Heading
	/// Range: 0..28800 (0 to 359.9875 degrees) Units: 0.0125 degrees
	//(*ppMsg)->vammsg.vam.vamParameters.vruHighFrequencyContainer.heading.headingValue= pLPHData->Pos.Heading;
	/// J2735's DE_Speed
	/// Range: 0..8190 (0..163.8 m/s) Units: 0.02 m/s
	/// Special value 8191 indicates that speed is unavailable
	//(*ppMsg)->vammsg.vam.vamParameters.vruHighFrequencyContainer.speed.speedValue= pLPHData->Pos.Speed;
	/// Acceleration (-9.9...9.9462 m/s/s, E = N * 0.0194 - 9.9)
	//	(*ppMsg)->vammsg.vam.vamParameters.vruHighFrequencyContainer.longitudinalAcceleration.longitudinalAccelerationValue= pLPHData->Pos.Acceleration;

	//YawRateValue ::= INTEGER {straight(0), degSec-000-01ToRight(-1), degSec-000-01ToLeft(1), unavailable(32767)} (-32766..32767)
	//(*ppMsg)->vammsg.vam.vamParameters.vruHighFrequencyContainer.yawRate.yawRateValue=pudpserver.yawRateValue;
	//CurvatureValue ::= INTEGER {straight(0), unavailable(1023)} (-1023..1023)
	//(*ppMsg)->vammsg.vam.vamParameters.vruHighFrequencyContainer.curvature.curvatureValue=pudpserver.curvatureValue;
	//unavailable (0), intersectionCrossing(1), zebraCrossing(2), sidewalk (3),onVehicleRoad(4), protectedGeographicArea(5), max (255)-- values 6-254 reserved for later use
	//(*ppMsg)->vammsg.vam.vamParameters.vruHighFrequencyContainer.environment=pudpserver.vruEnvironment;
	//set VAM message from pudpserver
	(*ppMsg)->vammsg.vam.vamParameters.basicContainer.referencePosition.latitude= pudpserver.lat;
	/// J2735's DE_Longitude.
	/// Range -1799999999..1800000001 (-180..180) Units: 1/10 micro degree
	(*ppMsg)->vammsg.vam.vamParameters.basicContainer.referencePosition.longitude= pudpserver.lon;
	printf("create msg with lat of bike from backend and send out through wlanp:%f.\n",(*ppMsg)->vammsg.vam.vamParameters.basicContainer.referencePosition.latitude);
	printf("create msg with lon of bike from backend and send out through wlanp:%f.\n",(*ppMsg)->vammsg.vam.vamParameters.basicContainer.referencePosition.longitude);
	RetVal = 0;
	goto Success;

	Error:
	// free the message and the Data buffer
	if (*ppMsg)
	{
		asn1_free_value(asn1_type_RAW_RAW, (*ppMsg));
	}

	Success:
	return RetVal;
}

void die(char *s)
{
	perror(s);
	exit(1);
}
//udpserver
int udpserver ()
{   
struct sockaddr_in si_me, si_other;
char buf[BUFLEN];
double lat;
double lon;
socklen_t s,  slen = sizeof(si_other) , recv_len;
//create a UDP socket
if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1U)
{
	die("socket");
}
// zero out the structure
memset((char *) &si_me, 0, sizeof(si_me));
si_me.sin_family = AF_INET;
si_me.sin_port = htons(PORT1);
si_me.sin_addr.s_addr = htonl(INADDR_ANY);
//bind socket to port
if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
{
	die("bind");
}
//keep listening for data
//printf("Waiting for data...\n");
fflush(stdout);
//try to receive some data, this is a blocking call
if ((recv_len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, &slen)) == -1U)
{
	die("recvfrom()");
	printf ("receive error!!");
}

if (sscanf(buf, "pos: (%lf, %lf)", &lat, &lon) == 2) {
	pudpserver.lat=lat;
	pudpserver.lon=lon;
} else {
       printf("Failed to parse the coordinates.\n");
}
        
        
//pudpserver=buf[0];
//print details of the client/peer and the data received
printf("RSU Received packet from client%s:%d through udp:", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
printf("\nlat=%f, lon=%f\n",
		pudpserver.lat,
		pudpserver.lon);

//now reply the client with the same data
if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
{
	die("sendto()");
}
printf("send data back through udp \n\n");
fflush(stdout);
memset(buf,0,sizeof(buf));
close(s);
return 0;
}

// Close the doxygen group
/**
 * @}
 */
