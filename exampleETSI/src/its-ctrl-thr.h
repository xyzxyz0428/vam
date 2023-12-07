/**
 * @addtogroup mod_its_ctrl ITS Control Module
 * @{
 *
 * Manages the ITS sending and receiving modules
 *
 *
 * @file
 *
 *
 */

//------------------------------------------------------------------------------
// Copyright (c) 2014 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifndef __ITS_CTRL_H_
#define __ITS_CTRL_H_

//------------------------------------------------------------------------------
// Included headers
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Macros & Constants
//------------------------------------------------------------------------------

/// Location of the ITS transmitter configuration settings
#define ITS_CONFIG_PATH_NAME  "Example.ITS.Facilities"

// DENM Configuration value names
#define ITS_CONFIG_VALUE_NAME_DENM                                 "DENM"

/// DENM event entries
#define ITS_CONFIG_VALUE_NAME_DENMEVENT1                           "EVENT1"
#define ITS_CONFIG_VALUE_NAME_DENMEVENT2                           "EVENT2"
#define ITS_CONFIG_VALUE_NAME_DENMEVENT3                           "EVENT3"
#define ITS_CONFIG_VALUE_NAME_DENMEVENT4                           "EVENT4"
// Legacy RWW equivalent event entries
#define ITS_CONFIG_VALUE_NAME_DENMRWW                              "RWW"
#define ITS_CONFIG_VALUE_NAME_DENMRWW2                             "RWW2"
#define ITS_CONFIG_VALUE_NAME_DENMRWW3                             "RWW3"
#define ITS_CONFIG_VALUE_NAME_DENMRWW4                             "RWW4"

// DENM generic options
#define ITS_CONFIG_VALUE_NAME_DENMENABLED                          "Enabled"
#define ITS_CONFIG_VALUE_NAME_DURATION                             "Duration"
#define ITS_CONFIG_VALUE_NAME_UPDATEPERIOD                         "UpdatePeriod"
#define ITS_CONFIG_VALUE_NAME_REPINTERVAL                          "RepInterval"
#define ITS_CONFIG_VALUE_NAME_RELATIVEOFFSETCUMULATIVE             "RelativeOffsetCumulative"
#define ITS_CONFIG_VALUE_NAME_EVENTOFFSETABSOLUTE                  "EventOffsetAbsolute"
#define ITS_CONFIG_VALUE_NAME_EVENTPOSSOURCE                       "EventPositionSource"
#define ITS_CONFIG_VALUE_NAME_EVENTLAT                             "EventLatitude"
#define ITS_CONFIG_VALUE_NAME_EVENTLONG                            "EventLongitude"
#define ITS_CONFIG_VALUE_NAME_EVENTALT                             "EventAltitude"
#define ITS_CONFIG_VALUE_NAME_TRAFFICCLASS                         "TrafficClass"
#define ITS_CONFIG_VALUE_NAME_LANEPOSITIONOPTION                   "LanePositionOption"
#define ITS_CONFIG_VALUE_NAME_LANEPOSITION                         "LanePosition"

/// DENM R-ITS (RSU) options
#define ITS_CONFIG_VALUE_NAME_DENMRWWTXENABLED                     "Enabled"
#define ITS_CONFIG_VALUE_NAME_DENMORIGSTATIONID                    "OriginatingStationId"
#define ITS_CONFIG_VALUE_NAME_DENMSEQNUMBER                        "SequenceNumber"
#define ITS_CONFIG_VALUE_NAME_DENMRWWINFORMATIONQUALITY            "InformationQuality"
#define ITS_CONFIG_VALUE_NAME_DENMRWWCAUSECODE                     "CauseCode"
#define ITS_CONFIG_VALUE_NAME_DENMRWWSUBCAUSECODE                  "SubCauseCode"
#define ITS_CONFIG_VALUE_NAME_DENMRWWRELEVANCETRAFFICDIRECTION     "RelevanceTrafficDirection"
#define ITS_CONFIG_VALUE_NAME_DENMRWWRELEVANCEDIST                 "RelevanceDistance"
#define ITS_CONFIG_VALUE_NAME_DENMRWWEVENTHEADINGOPTION            "EventHeadingOption"
#define ITS_CONFIG_VALUE_NAME_DENMRWWEVENTHEADING                  "EventHeading"
#define ITS_CONFIG_VALUE_NAME_DENMRWWCLOSEDLANESOPTION             "ClosedLanesOption"
#define ITS_CONFIG_VALUE_NAME_DENMRWWCLOSEDLANES                   "ClosedLanes"
#define ITS_CONFIG_VALUE_NAME_DENMRWWSPEEDLIMITOPTION              "SpeedLimitOption"
#define ITS_CONFIG_VALUE_NAME_DENMRWWSPEEDLIMIT                    "SpeedLimit"
#define ITS_CONFIG_VALUE_NAME_DENMRWWSTARTINGPOINTSPEEDLIMITOPTION "StartingPointSpeedLimitOption"
#define ITS_CONFIG_VALUE_NAME_DENMRWWSTARTINGPOINTSPEEDLIMIT       "StartingPointSpeedLimit"
#define ITS_CONFIG_VALUE_NAME_DENMRWWTRAFFICFLOWRULEOPTION         "TrafficFlowRuleOption"
#define ITS_CONFIG_VALUE_NAME_DENMRWWTRAFFICFLOWRULE               "TrafficFlowRule"
#define ITS_CONFIG_VALUE_NAME_DENMRWWOUTERHARDSHOULDERSTATUS       "OuterHardShoulderStatus"
#define ITS_CONFIG_VALUE_NAME_DENMRWWINNERHARDSHOULDERSTATUS       "InnerHardShoulderStatus"
#define ITS_CONFIG_VALUE_NAME_DENMRWWEVENTHISTORY                  "EventHistory"
#define ITS_CONFIG_VALUE_NAME_DENMRWWTRACES                        "Traces"
#define ITS_CONFIG_VALUE_NAME_DENMRWWLATITUDE                      "Latitude"
#define ITS_CONFIG_VALUE_NAME_DENMRWWLONGITUDE                     "Longitude"
#define ITS_CONFIG_VALUE_NAME_DENMRWWALTITUDE                      "Altitude"
#define ITS_CONFIG_VALUE_NAME_DENMRWWTRACEUPDATEDISTANCE           "TraceUpdateDistance"
#define ITS_CONFIG_VALUE_NAME_DENMUSEREFS                          "RefDENMs"

/// DENM V-ITS (OBU) options
#define ITS_CONFIG_VALUE_NAME_DENMEEBL                             "EEBL"
#define ITS_CONFIG_VALUE_NAME_DENMEEBLENABLED                      "Enabled"

#define ITS_CONFIG_VALUE_NAME_DENMEVW                              "EVW"
#define ITS_CONFIG_VALUE_NAME_DENMEVWENABLED                       "Enabled"
#define ITS_CONFIG_VALUE_NAME_DENMEVWAPPLINTERVAL                  "ApplInterval"

// CAM Configuration value names
#define ITS_CONFIG_VALUE_NAME_CAM             "CAM"
#define ITS_CONFIG_VALUE_NAME_CAMENABLED      "Enabled"
#define ITS_CONFIG_VALUE_NAME_CAMRSUTOLLING   "RSUTolling"
#define ITS_CONFIG_VALUE_NAME_CAMVEHTOLLING   "VehTolling"
#define ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGLATITUDE    "Latitude"
#define ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGLONGITUDE   "Longitude"
#define ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGRADIUS      "Radius"
#define ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGPROTID      "ProtID"
#define ITS_CONFIG_VALUE_NAME_CAMRSUTOLLINGTEMPORARY   "Temporary"

// SPAT Configuration value names
#define ITS_CONFIG_VALUE_NAME_SPAT                    "SPAT"
#define ITS_CONFIG_VALUE_NAME_SPATENABLED             "Enabled"
#define ITS_CONFIG_VALUE_NAME_SPATDYNAMICPHASES       "DynamicPhases"
#define ITS_CONFIG_VALUE_NAME_SPATAPPLINTERVAL        "ApplInterval"
#define ITS_CONFIG_VALUE_NAME_SPATINTERSECTIONID      "IntersectionId"
#define ITS_CONFIG_VALUE_NAME_SPATREDTIME             "RedPhasePeriod"
#define ITS_CONFIG_VALUE_NAME_SPATGREENTIME           "GreenPhasePeriod"
#define ITS_CONFIG_VALUE_NAME_SPATYELLOWTIME          "YellowPhasePeriod"
#define ITS_CONFIG_VALUE_NAME_SPATMOVEMENETS          "Movements"
#define ITS_CONFIG_VALUE_NAME_SPATSIGNALGROUP         "SignalGroup"
#define ITS_CONFIG_VALUE_NAME_SPATCURRENTSTATE        "CurrentState"
#define ITS_CONFIG_VALUE_NAME_SPATTIMETOCHANGE        "TimeToChange"
#define ITS_CONFIG_VALUE_NAME_SPATSPEEDADVICE         "SpeedAdvice"
#define ITS_CONFIG_VALUE_NAME_SPATSPEEDADVICESPEED    "Speed"
#define ITS_CONFIG_VALUE_NAME_SPATSPEEDADVICEDISTANCE "Distance"
#define ITS_CONFIG_VALUE_NAME_SPATSPEEDADVICETYPE     "Type"

// MAP Configuration value names
#define ITS_CONFIG_VALUE_NAME_MAP                "MAP"
#define ITS_CONFIG_VALUE_NAME_MAPENABLED         "Enabled"
#define ITS_CONFIG_VALUE_NAME_MAPAPPLINTERVAL    "ApplInterval"
#define ITS_CONFIG_VALUE_NAME_MAPINTERSECTIONID  "IntersectionId"
#define ITS_CONFIG_VALUE_NAME_MAPLATITUDE        "Latitude"
#define ITS_CONFIG_VALUE_NAME_MAPLONGITUDE       "Longitude"
#define ITS_CONFIG_VALUE_NAME_MAPALTITUDE        "Altitude"
#define ITS_CONFIG_VALUE_NAME_MAPLANES           "Lanes"
#define ITS_CONFIG_VALUE_NAME_MAPLANEID          "LaneId"
#define ITS_CONFIG_VALUE_NAME_MAPLANEDIRECTION   "Direction"
#define ITS_CONFIG_VALUE_NAME_MAPABSOLUTENODES   "AbsoluteNodes"
#define ITS_CONFIG_VALUE_NAME_MAPNODELAT         "Lat"
#define ITS_CONFIG_VALUE_NAME_MAPNODELON         "Lon"
#define ITS_CONFIG_VALUE_NAME_MAPNODES           "Nodes"
#define ITS_CONFIG_VALUE_NAME_MAPNODEX           "X"
#define ITS_CONFIG_VALUE_NAME_MAPNODEY           "Y"
#define ITS_CONFIG_VALUE_NAME_MAPCONNECTIONS     "Connections"
#define ITS_CONFIG_VALUE_NAME_MAPSIGNALGROUP     "SignalGroup"
#define ITS_CONFIG_VALUE_NAME_MAPCONNECTSTO      "ConnectsTo"
#define ITS_CONFIG_VALUE_NAME_MAPMANEUVER        "Maneuver"

// SA Configuration value names
#define ITS_CONFIG_VALUE_NAME_SA                 "SA"
#define ITS_CONFIG_VALUE_NAME_SAENABLED          "Enabled"
#define ITS_CONFIG_VALUE_NAME_SAPROTOCOL         "Protocol"
#define ITS_CONFIG_VALUE_NAME_SAITSAID           "ITSAID"
#define ITS_CONFIG_VALUE_NAME_SADATA             "Data"

// SRM Configuration value names
#define ITS_CONFIG_VALUE_NAME_SRM                "SRM"
#define ITS_CONFIG_VALUE_NAME_SRMENABLED         "Enabled"
#define ITS_CONFIG_VALUE_NAME_SRMAPPLINTERVAL    "ApplInterval"
#define ITS_CONFIG_VALUE_NAME_SRMINTERSECTIONID  "IntersectionId"

// SSM Configuration value names
#define ITS_CONFIG_VALUE_NAME_SSM                "SSM"
#define ITS_CONFIG_VALUE_NAME_SSMENABLED         "Enabled"
#define ITS_CONFIG_VALUE_NAME_SSMAPPLINTERVAL    "ApplInterval"
#define ITS_CONFIG_VALUE_NAME_SSMINTERSECTIONID  "IntersectionId"

// RTCM Configuration value names
#define ITS_CONFIG_VALUE_NAME_RTCM               "RTCM"
#define ITS_CONFIG_VALUE_NAME_RTCMENABLED        "Enabled"
#define ITS_CONFIG_VALUE_NAME_RTCMAPPLINTERVAL   "ApplInterval"
#define ITS_CONFIG_VALUE_NAME_RTCMDATA           "Data"

// CPM Configuration value names
#define ITS_CONFIG_VALUE_NAME_CPM                "CPM"
#define ITS_CONFIG_VALUE_NAME_CPMENABLED         "Enabled"
#define ITS_CONFIG_VALUE_NAME_CPMAPPLINTERVAL    "ApplInterval"

// VAM Configuration value names
#define ITS_CONFIG_VALUE_NAME_VAM                "VAM"
#define ITS_CONFIG_VALUE_NAME_VAMENABLED         "Enabled"
#define ITS_CONFIG_VALUE_NAME_VAMAPPLINTERVAL    "ApplInterval"

// IMZM Configuration value names
#define ITS_CONFIG_VALUE_NAME_IMZM               "IMZM"
#define ITS_CONFIG_VALUE_NAME_IMZMENABLED        "Enabled"
#define ITS_CONFIG_VALUE_NAME_IMZMAPPLINTERVAL   "ApplInterval"

// IVI Configuration value names
#define ITS_CONFIG_VALUE_NAME_IVI                "IVI"
#define ITS_CONFIG_VALUE_NAME_IVIENABLED         "Enabled"

#define ITS_CONFIG_VALUE_NAME_IVIAPPLINTERVAL    "ApplInterval"

#define ITS_CONFIG_VALUE_NAME_IVI_IVS            "IVS"
#define ITS_CONFIG_VALUE_NAME_IVI_IVS2           "IVS2"

#define ITS_CONFIG_VALUE_NAME_IVIIDNUMBER        "IviIdentificationNumber"
#define ITS_CONFIG_VALUE_NAME_IVISPRAW           "ServiceProviderRaw"
#define ITS_CONFIG_VALUE_NAME_IVISPCOUNTRYID     "ServiceProviderCountryID"
#define ITS_CONFIG_VALUE_NAME_IVISPISSUERID      "ServiceProviderIssuerId"

#define ITS_CONFIG_VALUE_NAME_IVIVALIDFROM       "ValidFrom"
#define ITS_CONFIG_VALUE_NAME_IVIVALIDTO         "ValidTo"

#define ITS_CONFIG_VALUE_NAME_REFPOSSOURCE       "RefPositionSource"
#define ITS_CONFIG_VALUE_NAME_REFPOSLATITUDE     "RefLatitude"
#define ITS_CONFIG_VALUE_NAME_REFPOSLONGITUDE    "RefLongitude"
#define ITS_CONFIG_VALUE_NAME_REFPOSALTITIUDE    "RefAltitude"
#define ITS_CONFIG_VALUE_NAME_DETECTZONEOFFSET   "DetectionZoneOffset"
#define ITS_CONFIG_VALUE_NAME_DETECTZONEABSPOS   "DetectionZoneAbsolutePos"
#define ITS_CONFIG_VALUE_NAME_RELZONEOFFSET      "RelevanceZoneOffset"
#define ITS_CONFIG_VALUE_NAME_RELZONEABSPOS      "RelevanceZoneAbsolutePos"
#define ITS_CONFIG_VALUE_NAME_GENERICZONE        "GenericZone"
#define ITS_CONFIG_VALUE_NAME_GENERICZONEID      "ZoneId"
#define ITS_CONFIG_VALUE_NAME_GENERICOFFSETS     "Offsets"
#define ITS_CONFIG_VALUE_NAME_GENERICABSOLUTES   "Absolutes"
#define ITS_CONFIG_VALUE_NAME_LATOFFSET          "Lat"
#define ITS_CONFIG_VALUE_NAME_LONGOFFSET         "Long"

#define ITS_CONFIG_VALUE_NAME_GIC                "GIC"
#define ITS_CONFIG_VALUE_NAME_GIC_MINAWARETIME   "MinimumAwarenessTime"
#define ITS_CONFIG_VALUE_NAME_GIC_IVITYPE        "IviType"
#define ITS_CONFIG_VALUE_NAME_GIC_LANES          "ApplicableLanes"
#define ITS_CONFIG_VALUE_NAME_GIC_DETZONES       "DetectionZoneIDs"
#define ITS_CONFIG_VALUE_NAME_GIC_RELZONES       "RelevanceZoneIDs"

#define ITS_CONFIG_VALUE_NAME_RCC                "RCC"
#define ITS_CONFIG_VALUE_NAME_RCC_ROADTYPE       "RoadType"
#define ITS_CONFIG_VALUE_NAME_RCC_LANECONF       "LaneConf"
#define ITS_CONFIG_VALUE_NAME_RCC_LANECONFNUM    "Number"
#define ITS_CONFIG_VALUE_NAME_RCC_LANECONFDIR    "Direction"
#define ITS_CONFIG_VALUE_NAME_RCC_RELZONES       "RelevanceZoneIDs"

#define ITS_CONFIG_VALUE_NAME_IVITYPE            "IviType"
#define ITS_CONFIG_VALUE_NAME_ITSISO14823_CHOICE "ITSISO14823_Choice"
#define ITS_CONFIG_VALUE_NAME_ITSISO14823_CODE   "ITSISO14823_Code"

#define ITS_CONFIG_VALUE_NAME_TC                  "TC"
#define ITS_CONFIG_VALUE_NAME_TC_MINAWARETIME     "MinimumAwarenessTime"
#define ITS_CONFIG_VALUE_NAME_TC_TEXT             "Text"
#define ITS_CONFIG_VALUE_NAME_TC_TEXT_ID          "LayoutComponentId"
#define ITS_CONFIG_VALUE_NAME_TC_TEXT_LANG        "LanguageBitStr"
#define ITS_CONFIG_VALUE_NAME_TC_TEXT_TEXTCONTENT "TextContent"

#define ITS_CONFIG_VALUE_NAME_ROADSIGNS          "RoadSigns"
#define ITS_CONFIG_VALUE_NAME_ROADSIGNS_CODE4    "ITSISO14823Code_4"
#define ITS_CONFIG_VALUE_NAME_ROADSIGNS_PICTO    "TrafficSignPictogram"
#define ITS_CONFIG_VALUE_NAME_ROADSIGNS_NATURE   "PictogramCategoryCodeNature"
#define ITS_CONFIG_VALUE_NAME_ROADSIGNS_SERNUM   "PictogramCategoryCodeSerialNumber"
#define ITS_CONFIG_VALUE_NAME_ROADSIGNS_SPEVAL   "AttributesSPEValue"
#define ITS_CONFIG_VALUE_NAME_ROADSIGNS_SPEUNIT  "AttributesSPEUnits"

#define ITS_CONFIG_VALUE_NAME_HGVINFO_INCLUDED   "HGVInfo"

#define ITS_CONFIG_VALUE_NAME_EXTRATEXT          "ExtraText"
#define ITS_CONFIG_VALUE_NAME_EXTRATEXT_ID       "LayoutComponentId"
#define ITS_CONFIG_VALUE_NAME_EXTRATEXT_LANG     "LanguageBitStr"
#define ITS_CONFIG_VALUE_NAME_EXTRATEXT_TEXT     "TextContent"

// Configuration value defaults for mandatory items
#define ITS_CONFIG_VALUE_DEFAULT_DURATION                 (60) // sec
#define ITS_CONFIG_VALUE_DEFAULT_ORIGSTATIONID    (0x10000000)
#define ITS_CONFIG_VALUE_DEFAULT_SEQNUMBER            (0x8001)
#define ITS_CONFIG_VALUE_DEFAULT_UPDATEPERIOD           (1000) // msec
#define ITS_CONFIG_VALUE_DEFAULT_REPINTERVAL            (1000) // mSec
#define ITS_CONFIG_VALUE_DEFAULT_EVENTOFFSETABSOLUTE       (1) // absolute
#define ITS_CONFIG_VALUE_DEFAULT_RELATIVEOFFSETCUMULATIVE  (0) // don't accumulate offsets
#define ITS_CONFIG_VALUE_DEFAULT_EVENTPOSITIONSOURCE ITS_CONFIG_VALUE_EVENTPOSITION_GPS
// event position, lat/long/alt
#define ITS_CONFIG_VALUE_DEFAULT_EVENTLAT         (-340000000)
#define ITS_CONFIG_VALUE_DEFAULT_EVENTLONG        (1380000000)
#define ITS_CONFIG_VALUE_DEFAULT_EVENTALT                  (0)
#define ITS_CONFIG_VALUE_DEFAULT_TRAFFICCLASS              (3) // DP3
#define ITS_CONFIG_VALUE_DEFAULT_RWW_CAUSECODE             (3) // roadworks
#define ITS_CONFIG_VALUE_DEFAULT_INFORMATIONQUALITY        (1) // lowest
#define ITS_CONFIG_VALUE_DEFAULT_CAUSECODE                 (ITS_CONFIG_VALUE_DEFAULT_RWW_CAUSECODE)
#define ITS_CONFIG_VALUE_DEFAULT_SUBCAUSECODE              (0)
#define ITS_CONFIG_VALUE_DEFAULT_TRAFFICDIRECTION          (-1) // Don't include
#define ITS_CONFIG_VALUE_DEFAULT_RELEVANCEDIST             (-1) // Don't include
// lane stuff
// speed limit
// traffic flow
#define ITS_CONFIG_VALUE_DEFAULT_EVENTHEADING              (0) // North
// hard shoulder
// traces
#define ITS_CONFIG_VALUE_DEFAULT_TRACEUPDATEDISTANCE_M    (-1)


#define ITS_CONFIG_VALUE_EVENTPOSITION_GPS              (0)
#define ITS_CONFIG_VALUE_EVENTPOSITION_CONFIG           (1)
#define ITS_CONFIG_VALUE_DEFAULT_TRACEUPDATEDISTANCE_M  (-1)

#define ITS_CONFIG_VALUE_DEFAULT_SPATDYNAMICPHASES    (false)
#define ITS_CONFIG_VALUE_DEFAULT_SPATAPPLINTERVAL     (100) // mSec
#define ITS_CONFIG_VALUE_DEFAULT_SPATINTERSECTIONID   (0x5566)
#define ITS_CONFIG_VALUE_DEFAULT_SPATREDTIME          (260)
#define ITS_CONFIG_VALUE_DEFAULT_SPATGREENTIME        (100)
#define ITS_CONFIG_VALUE_DEFAULT_SPATYELLOWTIME       (30)
#define ITS_CONFIG_VALUE_DEFAULT_SPATSIGNALGROUP      (0)
#define ITS_CONFIG_VALUE_DEFAULT_SPATCURRENTSTATE     (0) // Unavailble/Off
#define ITS_CONFIG_VALUE_DEFAULT_SPATTIMETOCHANGE     (36002) // Undefined

#define ITS_CONFIG_VALUE_DEFAULT_MAPAPPLINTERVAL      (1000) // mSec
#define ITS_CONFIG_VALUE_DEFAULT_MAPINTERSECTIONID    (0x5566)
#define ITS_CONFIG_VALUE_DEFAULT_MAPLATITUDE          (-340000000)
#define ITS_CONFIG_VALUE_DEFAULT_MAPLONGITUDE         (1380000000)
#define ITS_CONFIG_VALUE_DEFAULT_MAPALTITUDE          (800001)
#define ITS_CONFIG_VALUE_DEFAULT_MAPLANEID            (0)
#define ITS_CONFIG_VALUE_DEFAULT_MAPNODEX             (0) // Segment length = 0
#define ITS_CONFIG_VALUE_DEFAULT_MAPNODEY             (0) // Segment length = 0
#define ITS_CONFIG_VALUE_DEFAULT_MAPSIGNALGROUP       (0)
#define ITS_CONFIG_VALUE_DEFAULT_MAPCONNECTSTO        (0)
#define ITS_CONFIG_VALUE_DEFAULT_MAPMANEUVER          (0) // Undefined

#define ITS_CONFIG_VALUE_DEFAULT_SRMAPPLINTERVAL      (10000) // mSec
#define ITS_CONFIG_VALUE_DEFAULT_SRMINTERSECTIONID    (0x1234)

#define ITS_CONFIG_VALUE_DEFAULT_SSMAPPLINTERVAL      (10000) // mSec
#define ITS_CONFIG_VALUE_DEFAULT_SSMINTERSECTIONID    (0x1234)

#define ITS_CONFIG_VALUE_DEFAULT_IVIAPPLINTERVAL      (1000) // mSec

#define ITS_CONFIG_VALUE_DEFAULT_RTCMAPPLINTERVAL     (5000) // mSec

#define ITS_CONFIG_VALUE_DEFAULT_CPMAPPLINTERVAL      (500) // mSec

#define ITS_CONFIG_VALUE_DEFAULT_VAMAPPLINTERVAL      (500) // mSec

#define ITS_CONFIG_VALUE_DEFAULT_IMZMAPPLINTERVAL     (1000) // mSec

#define ITS_CONFIG_VALUE_DEFAULT_EVWDURATION          (3) // sec
#define ITS_CONFIG_VALUE_DEFAULT_EVWAPPLINTERVAL      (1000) // mSec

//-----------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------

typedef struct DENMReferencePoint
{
  int32_t DeltaLatitude;
  int32_t DeltaLongitude;
  int32_t DeltaAltitude;
  int8_t  InformationQuality;
} tDENMReferencePoint;

/// State IDs for ITS thread state
typedef enum ITSThreadState
{
  /// Not initialized
  ITS_THREAD_STATE_NONE = 0x00,
  /// Initializing
  ITS_THREAD_STATE_INIT = 0x01,
  /// Running
  ITS_THREAD_STATE_RUN  = 0x02,
  /// Stopping
  ITS_THREAD_STATE_STOP = 0x04,
  /// Stopped
  ITS_THREAD_STATE_END  = 0x08,
} eITSThreadState;

/// @ref ITSThreadState
typedef int tITSThreadState;

/// ITS transmitter Statistics
typedef struct ITSCtrlStats
{
  /// Transmit counters
  struct {
    uint32_t Okay;
    uint32_t Fail;
  } Tx;

  /// Receive counters
  struct {
    uint32_t Okay;
    uint32_t Fail;
  } Rx;

} tITSCtrlStats;

/// ITS transmitter parameters - Stored in Config File
typedef struct ITSCtrlParams
{
  /// ID of UDP thread
  pthread_t ThreadID;
  /// Thread state
  tITSThreadState ThreadState;
  /// Attributes used for thread
  pthread_attr_t ThreadAttr;

} tITSCtrlParams;

/// RWW DENM parameters
typedef struct ITSTxRWWParams
{
  /// Enable transmission of RWW DENMs
  bool Enabled;

  /// ITS FL DENM Duration
  uint16_t Duration;
  /// OriginatingStationId
  uint32_t OrigStationId;
  /// SequenceNumber
  uint16_t SeqNumber;
  /// Update Period of DENM
  uint16_t UpdatePeriod;
  /// Next RWW DENM
  uint64_t NextTxTimeMS;
  /// ITS FL DENM RepInterval
  uint16_t RepInterval;
  /// Absolute or Relative offset positions
  uint8_t EventOffsetAbsolute;
  /// Absolute or Relative offset positions
  uint8_t RelativeOffsetCumulative;
  /// Offsets stored are relative (same as PH points) or cumulative (legacy format used in .cfg)
  uint8_t EventPositionSource;
  /// ITS FL DENM EventLatitude
  int32_t EventLatitude;
  /// ITS FL DENM EventLongitude
  int32_t EventLongitude;
  /// ITS FL DENM EventAltitude
  int32_t EventAltitude;
  /// ITS FL DENM TrafficClass
  uint8_t TrafficClass;
  /// ITS FL DENM InformationQuality
  uint8_t InformationQuality;
  /// ITS FL DENM CauseCode
  uint8_t CauseCode;
  /// ITS FL DENM SubCauseCode
  uint8_t SubCauseCode;
  /// ITS FL DENM RelevanceTrafficDirection
  uint8_t RelevanceTrafficDirection;
  /// ITS FL DENM RelevanceDistance
  uint8_t RelevanceDistance;
  /// ITS DENM closed lanes option
  bool ClosedLanesOption;
  ///  The number of lanes in the road
  /// segment referenced by the ClosedLanes
  uint8_t NumClosedLanes;
  /// ITS DENM ClosedLanes
  int *ClosedLanes;
  /// ITS DENM speed limit option
  bool SpeedLimitOption;
  /// ITS DENM SpeedLimit
  uint8_t SpeedLimit;
  /// ITS StartingPointSpeedLimit option
  bool StartingPointSpeedLimitOption;
  /// ITS StartinPointSpeedLimit
  tDENMReferencePoint StartingPointSpeedLimit;
  /// ITS DENM TrafficRuleOption
  uint8_t TrafficFlowRuleOption;
  /// ITS DENM TrafficRule
  uint8_t TrafficFlowRule;
  /// ITS DENM LanePositionOption
  bool LanePositionOption;
  /// ITS DENM LanePosition
  int8_t LanePosition;
  /// ITS FL DENM EventHeadingOption
  uint16_t EventHeadingOption;
  /// ITS FL DENM EventHeading
  uint16_t EventHeading;
  /// ITS DENM OuterHardShoulderStatus
  uint8_t OuterHardShoulderStatus;
  /// ITS DENM InnerHardShoulderStatus
  uint8_t InnerHardShoulderStatus;
  /// The number of event points defined for this
  /// DENM message
  uint8_t NumEventPoints;
  /// ITS DENM eventHistory - made up of a set of event points
  tDENMReferencePoint *pEventPoints;
  /// The number of traces defined for this
  /// DENM message
  uint8_t NumTraces;
  /// ITS DENM Traces
  tDENMReferencePoint *pTraces;
  /// Update distance for traces for mobile RWW
  int16_t TraceUpdateDistance_m;
} tITSTxRWWParams;

/// Emergency Electronic Brake Light DENM parameters
typedef struct ITSTxEEBLParams
{
  bool Enabled;
} tITSTxEEBLParams;

/// Emergency Vehicle DENM parameters
typedef struct ITSTxEVWParams
{
  bool Enabled;
  uint16_t Duration;
  uint16_t ApplInterval;
  uint64_t NextTxTimeMS;
} tITSTxEVWParams;

typedef struct SPATSpeedAdvisory
{
  uint16_t Speed_tenthmps;
  uint16_t Distance_m;
  uint8_t  Type;
} tSPATSpeedAdvisory;


typedef struct SPATMovementParams
{
  uint8_t CurrentState;
  uint8_t SignalGroup;
  uint16_t TimeToChange;
  /// Number of SpeedAdvisories for this Movement
  uint8_t NumSpeedAdvisories;
  /// Intersection lanes config
  tSPATSpeedAdvisory *pSpeedAdvisories;
} tSPATMovementParams;

/// Spat parameters
typedef struct ITSTxSPATParams
{
  bool Enabled;
  /// When set, SPAT phases keeps changing each Tx (using phases timing below)
  bool DynamicPhases;
  /// Spat transmission interval (mSec)
  uint16_t ApplInterval;
  /// Next SPAT
  uint64_t NextTxTimeMS;
  /// RSU intersection Id
  uint32_t IntersectionId;
  /// Red state reload time period (tength of sec)
  uint16_t RedPhasePeriod;
  /// Green state reload time period (tength of sec)
  uint16_t GreenPhasePeriod;
  /// Yellow state reload time period (tength of sec)
  uint16_t YellowPhasePeriod;
  /// Number of movement states for this SPAT msg
  uint8_t NumMovements;
  /// All current movement states
  tSPATMovementParams *pMovements;
} tITSTxSPATParams;


typedef struct MAPLaneNodeParams
{
  // X,Y represent delta offset for relative positioning
  // X,Y represent Lon,Lat for absolute positioning
  int X;
  int Y;
} tMAPLaneNodeParams;

typedef struct MAPLaneConnectionParams
{
  int ConnectsTo;
  uint8_t SignalGroup;
  uint8_t Maneuver;
} tMAPLaneConnectionParams;

typedef struct MAPLaneParams
{
  int LaneId;
  int NumNodes;
  int NumConnections;
  bool egressLane;
  bool ingressLane;
  bool AbsolutePosNodes;
  tMAPLaneNodeParams *pNodes;
  tMAPLaneConnectionParams *pConnections;
} tMAPLaneParams;

/// Map parameters
typedef struct ITSTxMAPParams
{
  bool Enabled;
  /// Map transmission interval (mSec)
  uint16_t ApplInterval;
  /// Next MAP
  uint64_t NextTxTimeMS;
  /// RSU intersection Id
  uint32_t IntersectionId;
  /// RSU latitude in tenths of microdegrees
  int32_t Latitude;
  /// RSU longitude in tenths of microdegrees
  int32_t Longitude;
  /// RSU altitude in centimetres
  int32_t Altitude_cm;
  /// Number of "vehicle" lanes in this intersection
  uint8_t NumLanes;
  /// Intersection lanes config
  tMAPLaneParams *pLanes;
} tITSTxMAPParams;

/// SRM parameters
typedef struct ITSTxSRMParams
{
  bool Enabled;
  /// SRM transmission interval (mSec)
  uint16_t ApplInterval;
  /// Next SRM
  uint64_t NextTxTimeMS;
  /// RSU intersection Id
  uint32_t IntersectionId;
} tITSTxSRMParams;

/// SSM parameters
typedef struct ITSTxSSMParams
{
  bool Enabled;
  /// SSM transmission interval (mSec)
  uint16_t ApplInterval;
  /// Next SSM
  uint64_t NextTxTimeMS;
  /// RSU intersection Id
  uint32_t IntersectionId;
} tITSTxSSMParams;

/// SA parameters
typedef struct ITSTxSAParams
{
  bool Enabled;
  uint8_t Protocol;
  uint32_t ITSAID;
  uint8_t Data[256];
  uint16_t DataLen;
} tITSTxSAParams;

/// RTCM parameters
typedef struct ITSTxRTCMParams
{
  bool Enabled;
  uint16_t ApplInterval;
  uint64_t NextTxTimeMS;
  uint32_t ITRTCMID;
  uint8_t Data[256];
  uint16_t DataLen;
} tITSTxRTCMParams;

/// Cpm parameters
typedef struct ITSTxCPMParams
{
  bool Enabled;

  /// CPM transmission interval (mSec)
  uint16_t ApplInterval;
  /// Next CPM
  uint64_t NextTxTimeMS;
} tITSTxCPMParams;

/// Vam parameters
typedef struct ITSTxVAMParams
{
  bool Enabled;

  /// VAM transmission interval (mSec)
  uint16_t ApplInterval;
  /// Next VAM
  uint64_t NextTxTimeMS;
} tITSTxVAMParams;

/// IMZM parameters
typedef struct ITSTxIMZMParams
{
  bool Enabled;

  /// IMZM transmission interval (mSec)
  uint16_t ApplInterval;
  /// Next IMZM
  uint64_t NextTxTimeMS;
} tITSTxIMZMParams;

typedef struct IVIDeltaPoint
{
  int32_t DeltaLatitude;
  int32_t DeltaLongitude;
} tIVIDeltaPoint;

typedef struct IVIAbsPoint
{
  int32_t Latitude;
  int32_t Longitude;
} tIVIAbsPoint;

typedef struct IVIRoadSignsParams
{
  int ITSISO14823Code_4;
  int TrafficSignPictogram;
  int PictogramCategoryCodeNature;
  int PictogramCategoryCodeSerialNumber;
  int AttributesSPEValue;
  int AttributesSPEUnits;
} tIVIRoadSignsParams;

typedef struct IVIExtraTextParams
{
  int LayoutComponentId;
  uint8_t LanguageBitStr[2];
  char TextContent[256];
} tIVIExtraTextParams;

typedef struct IVIGICPart
{
  int MinimumAwarenessTime;
  int IviType;

  int NumDetZones;
  int DetZones[8];

  int NumRelZones;
  int RelZones[8];

  int NumApplicLanes;
  int ApplicLanes[16];

  int HGVInfo;

  int NumRoadSigns;
  tIVIRoadSignsParams RoadSigns[4];

  int NumExtraText;
  tIVIExtraTextParams ExtraText[4];

  bool useITSISO14823Code;
  unsigned int ITSISO14823Code;
} tIVIGICPart;

typedef struct IVIRCCPart
{
  int RoadType;

  int NumRelZones;
  int RelZones[8];

  int NumLaneConf;
  int LaneInfoNumbers[16];
  int LaneInfoDirs[16];
} tIVIRCCPart;

typedef struct IVITCPart
{
  int MinimumAwarenessTime;

  int NumText;
  tIVIExtraTextParams Text[4];
} tIVITCPart;

/// Ivi parameters
typedef struct ITSTxIVIParams
{
  bool Enabled;

  /// Map transmission interval (mSec)
  uint16_t ApplInterval;
  /// Next IVI
  uint64_t NextTxTimeMS;

} tITSTxIVIParams;

/// Ivi generic zone parameters
typedef struct ITSTxIVIGenericZone
{
  int32_t GenericZoneId;
  int32_t GenericSegmentCount;
  bool IsAbsolutes;
  tIVIAbsPoint GenericSegment[32];
} tITSTxIVIGenericZone;

/// IVS parameters
typedef struct ITSTxIVSParams
{
  bool Enabled;

  /// IVI ID assigned
  uint64_t IviIDAssigned;

  /// IviIdentificationNumber
  uint32_t IviIdentificationNumber;
  /// ServiceProviderCountryID
  uint32_t ServiceProviderCountryID;
  /// ServiceProviderIssuerId
  uint32_t ServiceProviderIssuerId;

  /// ValidFrom
  uint64_t ValidFromTime;
  /// ValidTo
  uint64_t ValidToTime;

  /// Real or Configured RefPosition?
  uint8_t RefPositionSource;
  /// IVI RefLatitude
  int32_t RefLatitude;
  /// IVI RefLongitude
  int32_t RefLongitude;
  /// IVI RefAltitude
  int32_t RefAltitude;

  // Dutifully read in both delta and absolute positions for
  // Detection and Relevance Zones and decide later which has priority

  /// IVI DetectionZoneOffset count
  int32_t DetectionZoneOffsetCount;
  /// IVI DetectionZoneOffset
  tIVIDeltaPoint DetectionZoneOffset[40];

  /// IVI DetectionZoneAbsPosn count
  int32_t DetectionZoneAbsPosnCount;
  /// IVI DetectionZoneAbsPosn
  tIVIAbsPoint DetectionZoneAbsPosn[8];

  /// IVI RelevanceZoneOffset count
  int32_t RelevanceZoneOffsetCount;
  /// IVI RelevanceZoneOffset
  tIVIDeltaPoint RelevanceZoneOffset[40];

  /// IVI RelevanceZoneAbsPosn count
  int32_t RelevanceZoneAbsPosnCount;
  /// IVI RelevanceZoneAbsPosn
  tIVIAbsPoint RelevanceZoneAbsPosn[8];

  /// IVI Generic Zone count
  int32_t GenericZoneCount;
  /// IVI Generic Zone
  tITSTxIVIGenericZone GenericZone[16];

  int GICPartsCount;
  tIVIGICPart GICPart[4];

  int RCCPartsCount;
  tIVIRCCPart RCCPart[4];

  int TCPartsCount;
  tIVITCPart TCPart[16];

} tITSTxIVSParams;

/// ITS thread parameters
typedef struct ITSTxParams
{
  /// ID of UDP thread
  pthread_t ThreadID;
  /// Thread state
  tITSThreadState ThreadState;
  /// Attributes used for thread
  pthread_attr_t ThreadAttr;
  /// LPH info
  void *pLPH_Handle;

  /// RWW DENM Parameters
  tITSTxRWWParams RWW;

  /// RWW2 DENM Parameters
  tITSTxRWWParams RWW2;

  /// RWW3 DENM Parameters
  tITSTxRWWParams RWW3;

  /// RWW4 DENM Parameters
  tITSTxRWWParams RWW4;

  /// EEBL DENM Parameters
  tITSTxEEBLParams EEBL;

  /// EVW DENM Parameters
  tITSTxEVWParams EVW;

  /// SPAT Parameters
  tITSTxSPATParams SPAT;

  /// MAP Parameters
  tITSTxMAPParams MAP;

  /// SRM Parameters
  tITSTxSRMParams SRM;

  /// SSM Parameters
  tITSTxSSMParams SSM;

  /// SA Parameters
  tITSTxSAParams SA;

  /// IVI Parameters
  tITSTxIVIParams IVI;

  /// IVS Parameters
  tITSTxIVSParams IVS;

  /// IVS2 Parameters
  tITSTxIVSParams IVS2;

  /// RTCM Parameters
  tITSTxRTCMParams RTCM;

  /// CPM Parameters
  tITSTxCPMParams CPM;

  /// VAM Parameters
  tITSTxVAMParams VAM;

  /// IMZM Parameters
  tITSTxIMZMParams IMZM;

  /// ITS FL CAM Enabled
  bool CAMEnabled;
  /// ITS FL CAM with RSU Tolling info
  struct ITSProtectedCommunicationZonesRSU * pRSUCont;
  /// ITS FL CAM with Veh Tolling info
  struct ITSCenDsrcTollingZone * pVehCont;

  /// ITS Reference DENMs used
  bool UseRefDENMEnabled;
} tITSTxParams;

/// ITS thread parameters
typedef struct ITSRxParams
{
  /// ID of UDP thread
  pthread_t ThreadID;
  /// Thread state
  tITSThreadState ThreadState;
  /// Attributes used for thread
  pthread_attr_t ThreadAttr;

} tITSRxParams;

/// ITS state
typedef struct ITSCtrl
{
  /// Configuration for Ctrl
  struct ITSCtrlParams Ctrl;
  /// Configuration for Tx
  struct ITSTxParams Tx;
  /// Configuration for Rx
  struct ITSRxParams Rx;
  /// Module statistics
  struct ITSCtrlStats Stats;
} tITSCtrl;

//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------

int ITSCtrl_Open (struct ITSCtrl *pITS,
                pthread_attr_t *pAttr,
                char *pConfigFileName);

void ITSCtrl_Close (struct ITSCtrl *pITS);

int ITSTx_Open (struct ITSCtrl *pITS);

void ITSTx_Close (struct ITSCtrl *pITS);

int ITSRx_Open (struct ITSCtrl *pITS);

void ITSRx_Close (struct ITSCtrl *pITS);

#endif // __ITS_CTRL_H_
/**
 * @}
 */
