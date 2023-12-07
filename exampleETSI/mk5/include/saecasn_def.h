#pragma once

// AUTOGENERATED
// /opt/jenkins/workspace/Release_MK5_SDK/MK5/software/build/mk5-bin/stack/src/fac-cn/asn/SAEC.asn1
//     to
// /opt/jenkins/workspace/Release_MK5_SDK/MK5/software/build/mk5-bin/stack/src/fac-cn/asn/gen/saecasn*

#ifdef __cplusplus
extern "C"
{
#endif
// with prefix 'SAEC'


// SAECAcceleration_Limit
#define SAECAcceleration_Limit_Min                                          -2000
#define SAECAcceleration_Limit_Max                                          2001

// SAECAllowedManeuvers
#define SAECAllowedManeuvers_maneuverStraightAllowed                        0
#define SAECAllowedManeuvers_maneuverLeftAllowed                            1
#define SAECAllowedManeuvers_maneuverRightAllowed                           2
#define SAECAllowedManeuvers_maneuverUTurnAllowed                           3
#define SAECAllowedManeuvers_maneuverLeftTurnOnRedAllowed                   4
#define SAECAllowedManeuvers_maneuverRightTurnOnRedAllowed                  5
#define SAECAllowedManeuvers_maneuverLaneChangeAllowed                      6
#define SAECAllowedManeuvers_maneuverNoStoppingAllowed                      7
#define SAECAllowedManeuvers_yieldAllwaysRequired                           8
#define SAECAllowedManeuvers_goWithHalt                                     9
#define SAECAllowedManeuvers_caution                                        10
#define SAECAllowedManeuvers_reserved1                                      11
#define SAECAllowedManeuvers_NumBits                                        12

// SAECAntiLockBrakeStatus_Limit
#define SAECAntiLockBrakeStatus_Limit_Min                                   0
#define SAECAntiLockBrakeStatus_Limit_Max                                   3

// SAECAuxiliaryBrakeStatus_Limit
#define SAECAuxiliaryBrakeStatus_Limit_Min                                  0
#define SAECAuxiliaryBrakeStatus_Limit_Max                                  3

// SAECBasicVehicleClass
#define SAECBasicVehicleClass_unknownVehicleClass                           0
#define SAECBasicVehicleClass_specialVehicleClass                           1
#define SAECBasicVehicleClass_passenger_Vehicle_TypeUnknown                 10
#define SAECBasicVehicleClass_passenger_Vehicle_TypeOther                   11
#define SAECBasicVehicleClass_lightTruck_Vehicle_TypeUnknown                20
#define SAECBasicVehicleClass_lightTruck_Vehicle_TypeOther                  21
#define SAECBasicVehicleClass_truck_Vehicle_TypeUnknown                     25
#define SAECBasicVehicleClass_truck_Vehicle_TypeOther                       26
#define SAECBasicVehicleClass_truck_axleCnt2                                27
#define SAECBasicVehicleClass_truck_axleCnt3                                28
#define SAECBasicVehicleClass_truck_axleCnt4                                29
#define SAECBasicVehicleClass_truck_axleCnt4Trailer                         30
#define SAECBasicVehicleClass_truck_axleCnt5Trailer                         31
#define SAECBasicVehicleClass_truck_axleCnt6Trailer                         32
#define SAECBasicVehicleClass_truck_axleCnt5MultiTrailer                    33
#define SAECBasicVehicleClass_truck_axleCnt6MultiTrailer                    34
#define SAECBasicVehicleClass_truck_axleCnt7MultiTrailer                    35
#define SAECBasicVehicleClass_motorcycle_TypeUnknown                        40
#define SAECBasicVehicleClass_motorcycle_TypeOther                          41
#define SAECBasicVehicleClass_motorcycle_Cruiser_Standard                   42
#define SAECBasicVehicleClass_motorcycle_SportUnclad                        43
#define SAECBasicVehicleClass_motorcycle_SportTouring                       44
#define SAECBasicVehicleClass_motorcycle_SuperSport                         45
#define SAECBasicVehicleClass_motorcycle_Touring                            46
#define SAECBasicVehicleClass_motorcycle_Trike                              47
#define SAECBasicVehicleClass_motorcycle_wPassengers                        48
#define SAECBasicVehicleClass_transit_TypeUnknown                           50
#define SAECBasicVehicleClass_transit_TypeOther                             51
#define SAECBasicVehicleClass_transit_BRT                                   52
#define SAECBasicVehicleClass_transit_ExpressBus                            53
#define SAECBasicVehicleClass_transit_LocalBus                              54
#define SAECBasicVehicleClass_transit_SchoolBus                             55
#define SAECBasicVehicleClass_transit_FixedGuideway                         56
#define SAECBasicVehicleClass_transit_Paratransit                           57
#define SAECBasicVehicleClass_transit_Paratransit_Ambulance                 58
#define SAECBasicVehicleClass_emergency_TypeUnknown                         60
#define SAECBasicVehicleClass_emergency_TypeOther                           61
#define SAECBasicVehicleClass_emergency_Fire_Light_Vehicle                  62
#define SAECBasicVehicleClass_emergency_Fire_Heavy_Vehicle                  63
#define SAECBasicVehicleClass_emergency_Fire_Paramedic_Vehicle              64
#define SAECBasicVehicleClass_emergency_Fire_Ambulance_Vehicle              65
#define SAECBasicVehicleClass_emergency_Police_Light_Vehicle                66
#define SAECBasicVehicleClass_emergency_Police_Heavy_Vehicle                67
#define SAECBasicVehicleClass_emergency_Other_Responder                     68
#define SAECBasicVehicleClass_emergency_Other_Ambulance                     69
#define SAECBasicVehicleClass_otherTraveler_TypeUnknown                     80
#define SAECBasicVehicleClass_otherTraveler_TypeOther                       81
#define SAECBasicVehicleClass_otherTraveler_Pedestrian                      82
#define SAECBasicVehicleClass_otherTraveler_Visually_Disabled               83
#define SAECBasicVehicleClass_otherTraveler_Physically_Disabled             84
#define SAECBasicVehicleClass_otherTraveler_Bicycle                         85
#define SAECBasicVehicleClass_otherTraveler_Vulnerable_Roadworker           86
#define SAECBasicVehicleClass_infrastructure_TypeUnknown                    90
#define SAECBasicVehicleClass_infrastructure_Fixed                          91
#define SAECBasicVehicleClass_infrastructure_Movable                        92
#define SAECBasicVehicleClass_equipped_CargoTrailer                         93

// SAECBasicVehicleClass_Limit
#define SAECBasicVehicleClass_Limit_Min                                     0
#define SAECBasicVehicleClass_Limit_Max                                     255

// SAECBrakeAppliedStatus
#define SAECBrakeAppliedStatus_unavailable                                  0
#define SAECBrakeAppliedStatus_leftFront                                    1
#define SAECBrakeAppliedStatus_leftRear                                     2
#define SAECBrakeAppliedStatus_rightFront                                   3
#define SAECBrakeAppliedStatus_rightRear                                    4
#define SAECBrakeAppliedStatus_NumBits                                      5

// SAECBrakeBoostApplied_Limit
#define SAECBrakeBoostApplied_Limit_Min                                     0
#define SAECBrakeBoostApplied_Limit_Max                                     2

// SAECBrakePedalStatus_Limit
#define SAECBrakePedalStatus_Limit_Min                                      0
#define SAECBrakePedalStatus_Limit_Max                                      2

// SAECCoarseHeading_Limit
#define SAECCoarseHeading_Limit_Min                                         0
#define SAECCoarseHeading_Limit_Max                                         240

// SAECConfidence_Limit
#define SAECConfidence_Limit_Min                                            0
#define SAECConfidence_Limit_Max                                            200

// SAECConnectsToList_SeqSize
#define SAECConnectsToList_SeqSize_Min                                      1
#define SAECConnectsToList_SeqSize_Max                                      8

// SAECDDay_Limit
#define SAECDDay_Limit_Min                                                  0
#define SAECDDay_Limit_Max                                                  31

// SAECDHour_Limit
#define SAECDHour_Limit_Min                                                 0
#define SAECDHour_Limit_Max                                                 31

// SAECDMinute_Limit
#define SAECDMinute_Limit_Min                                               0
#define SAECDMinute_Limit_Max                                               60

// SAECDMonth_Limit
#define SAECDMonth_Limit_Min                                                0
#define SAECDMonth_Limit_Max                                                12

// SAECDSecond_Limit
#define SAECDSecond_Limit_Min                                               0
#define SAECDSecond_Limit_Max                                               65535

// SAECDTimeOffset_Limit
#define SAECDTimeOffset_Limit_Min                                           -840
#define SAECDTimeOffset_Limit_Max                                           840

// SAECDYear_Limit
#define SAECDYear_Limit_Min                                                 0
#define SAECDYear_Limit_Max                                                 4095

// SAECDescriptiveName
#define SAECDescriptiveName_NumOctets                                       63

// SAECElevationConfidence_Limit
#define SAECElevationConfidence_Limit_Min                                   0
#define SAECElevationConfidence_Limit_Max                                   15

// SAECElevation_Limit
#define SAECElevation_Limit_Min                                             -4096
#define SAECElevation_Limit_Max                                             61439

// SAECEventSource_Limit
#define SAECEventSource_Limit_Min                                           0
#define SAECEventSource_Limit_Max                                           5

// SAECEventType_Limit
#define SAECEventType_Limit_Min                                             0
#define SAECEventType_Limit_Max                                             65535

// SAECExteriorLights
#define SAECExteriorLights_lowBeamHeadlightsOn                              0
#define SAECExteriorLights_highBeamHeadlightsOn                             1
#define SAECExteriorLights_leftTurnSignalOn                                 2
#define SAECExteriorLights_rightTurnSignalOn                                3
#define SAECExteriorLights_hazardSignalOn                                   4
#define SAECExteriorLights_automaticLightControlOn                          5
#define SAECExteriorLights_daytimeRunningLightsOn                           6
#define SAECExteriorLights_fogLightOn                                       7
#define SAECExteriorLights_parkingLightsOn                                  8
#define SAECExteriorLights_NumBits                                          9

// SAECFuelType
#define SAECFuelType_unknownFuel                                            0
#define SAECFuelType_gasoline                                               1
#define SAECFuelType_ethanol                                                2
#define SAECFuelType_diesel                                                 3
#define SAECFuelType_electric                                               4
#define SAECFuelType_hybrid                                                 5
#define SAECFuelType_hydrogen                                               6
#define SAECFuelType_natGasLiquid                                           7
#define SAECFuelType_natGasComp                                             8
#define SAECFuelType_propane                                                9

// SAECFuelType_Limit
#define SAECFuelType_Limit_Min                                              0
#define SAECFuelType_Limit_Max                                              15

// SAECGNSSstatus
#define SAECGNSSstatus_unavailable                                          0
#define SAECGNSSstatus_isHealthy                                            1
#define SAECGNSSstatus_isMonitored                                          2
#define SAECGNSSstatus_baseStationType                                      3
#define SAECGNSSstatus_aPDOPofUnder5                                        4
#define SAECGNSSstatus_inViewOfUnder5                                       5
#define SAECGNSSstatus_localCorrectionsPresent                              6
#define SAECGNSSstatus_networkCorrectionsPresent                            7
#define SAECGNSSstatus_NumBits                                              8

// SAECHeadingConfidence_Limit
#define SAECHeadingConfidence_Limit_Min                                     0
#define SAECHeadingConfidence_Limit_Max                                     7

// SAECHeading_Limit
#define SAECHeading_Limit_Min                                               0
#define SAECHeading_Limit_Max                                               28800

// SAECIntersectionStateList_SeqSize
#define SAECIntersectionStateList_SeqSize_Min                               1
#define SAECIntersectionStateList_SeqSize_Max                               32

// SAECIntersectionStatusObject
#define SAECIntersectionStatusObject_manualControlIsEnabled                 0
#define SAECIntersectionStatusObject_stopTimeIsActivated                    1
#define SAECIntersectionStatusObject_failureFlash                           2
#define SAECIntersectionStatusObject_preemptIsActive                        3
#define SAECIntersectionStatusObject_signalPriorityIsActive                 4
#define SAECIntersectionStatusObject_fixedTimeOperation                     5
#define SAECIntersectionStatusObject_trafficDependentOperation              6
#define SAECIntersectionStatusObject_standbyOperation                       7
#define SAECIntersectionStatusObject_failureMode                            8
#define SAECIntersectionStatusObject_off                                    9
#define SAECIntersectionStatusObject_recentMAPmessageUpdate                 10
#define SAECIntersectionStatusObject_recentChangeInMAPassignedLanesIDsUsed  11
#define SAECIntersectionStatusObject_noValidMAPisAvailableAtThisTime        12
#define SAECIntersectionStatusObject_noValidSPATisAvailableAtThisTime       13
#define SAECIntersectionStatusObject_NumBits                                16

// SAECLaneAttributes_Barrier
#define SAECLaneAttributes_Barrier_median_RevocableLane                     0
#define SAECLaneAttributes_Barrier_median                                   1
#define SAECLaneAttributes_Barrier_whiteLineHashing                         2
#define SAECLaneAttributes_Barrier_stripedLines                             3
#define SAECLaneAttributes_Barrier_doubleStripedLines                       4
#define SAECLaneAttributes_Barrier_trafficCones                             5
#define SAECLaneAttributes_Barrier_constructionBarrier                      6
#define SAECLaneAttributes_Barrier_trafficChannels                          7
#define SAECLaneAttributes_Barrier_lowCurbs                                 8
#define SAECLaneAttributes_Barrier_highCurbs                                9
#define SAECLaneAttributes_Barrier_NumBits                                  16

// SAECLaneAttributes_Bike
#define SAECLaneAttributes_Bike_bikeRevocableLane                           0
#define SAECLaneAttributes_Bike_pedestrianUseAllowed                        1
#define SAECLaneAttributes_Bike_isBikeFlyOverLane                           2
#define SAECLaneAttributes_Bike_fixedCycleTime                              3
#define SAECLaneAttributes_Bike_biDirectionalCycleTimes                     4
#define SAECLaneAttributes_Bike_isolatedByBarrier                           5
#define SAECLaneAttributes_Bike_unsignalizedSegmentsPresent                 6
#define SAECLaneAttributes_Bike_NumBits                                     16

// SAECLaneAttributes_Crosswalk
#define SAECLaneAttributes_Crosswalk_crosswalkRevocableLane                 0
#define SAECLaneAttributes_Crosswalk_bicyleUseAllowed                       1
#define SAECLaneAttributes_Crosswalk_isXwalkFlyOverLane                     2
#define SAECLaneAttributes_Crosswalk_fixedCycleTime                         3
#define SAECLaneAttributes_Crosswalk_biDirectionalCycleTimes                4
#define SAECLaneAttributes_Crosswalk_hasPushToWalkButton                    5
#define SAECLaneAttributes_Crosswalk_audioSupport                           6
#define SAECLaneAttributes_Crosswalk_rfSignalRequestPresent                 7
#define SAECLaneAttributes_Crosswalk_unsignalizedSegmentsPresent            8
#define SAECLaneAttributes_Crosswalk_NumBits                                16

// SAECLaneAttributes_Parking
#define SAECLaneAttributes_Parking_parkingRevocableLane                     0
#define SAECLaneAttributes_Parking_parallelParkingInUse                     1
#define SAECLaneAttributes_Parking_headInParkingInUse                       2
#define SAECLaneAttributes_Parking_doNotParkZone                            3
#define SAECLaneAttributes_Parking_parkingForBusUse                         4
#define SAECLaneAttributes_Parking_parkingForTaxiUse                        5
#define SAECLaneAttributes_Parking_noPublicParkingUse                       6
#define SAECLaneAttributes_Parking_NumBits                                  16

// SAECLaneAttributes_Sidewalk
#define SAECLaneAttributes_Sidewalk_sidewalk_RevocableLane                  0
#define SAECLaneAttributes_Sidewalk_bicyleUseAllowed                        1
#define SAECLaneAttributes_Sidewalk_isSidewalkFlyOverLane                   2
#define SAECLaneAttributes_Sidewalk_walkBikes                               3
#define SAECLaneAttributes_Sidewalk_NumBits                                 16

// SAECLaneAttributes_Striping
#define SAECLaneAttributes_Striping_stripeToConnectingLanesRevocableLane    0
#define SAECLaneAttributes_Striping_stripeDrawOnLeft                        1
#define SAECLaneAttributes_Striping_stripeDrawOnRight                       2
#define SAECLaneAttributes_Striping_stripeToConnectingLanesLeft             3
#define SAECLaneAttributes_Striping_stripeToConnectingLanesRight            4
#define SAECLaneAttributes_Striping_stripeToConnectingLanesAhead            5
#define SAECLaneAttributes_Striping_NumBits                                 16

// SAECLaneAttributes_TrackedVehicle
#define SAECLaneAttributes_TrackedVehicle_spec_RevocableLane                0
#define SAECLaneAttributes_TrackedVehicle_spec_commuterRailRoadTrack        1
#define SAECLaneAttributes_TrackedVehicle_spec_lightRailRoadTrack           2
#define SAECLaneAttributes_TrackedVehicle_spec_heavyRailRoadTrack           3
#define SAECLaneAttributes_TrackedVehicle_spec_otherRailType                4
#define SAECLaneAttributes_TrackedVehicle_NumBits                           16

// SAECLaneAttributes_Vehicle
#define SAECLaneAttributes_Vehicle_isVehicleRevocableLane                   0
#define SAECLaneAttributes_Vehicle_isVehicleFlyOverLane                     1
#define SAECLaneAttributes_Vehicle_hovLaneUseOnly                           2
#define SAECLaneAttributes_Vehicle_restrictedToBusUse                       3
#define SAECLaneAttributes_Vehicle_restrictedToTaxiUse                      4
#define SAECLaneAttributes_Vehicle_restrictedFromPublicUse                  5
#define SAECLaneAttributes_Vehicle_hasIRbeaconCoverage                      6
#define SAECLaneAttributes_Vehicle_permissionOnRequest                      7
#define SAECLaneAttributes_Vehicle_NumBits                                  8

// SAECLaneID_Limit
#define SAECLaneID_Limit_Min                                                0
#define SAECLaneID_Limit_Max                                                255

// SAECLaneList_SeqSize
#define SAECLaneList_SeqSize_Min                                            1
#define SAECLaneList_SeqSize_Max                                            32

// SAECLaneSharing
#define SAECLaneSharing_overlappingLaneDescriptionProvided                  0
#define SAECLaneSharing_multipleLanesTreatedAsOneLane                       1
#define SAECLaneSharing_otherNonMotorizedTrafficTypes                       2
#define SAECLaneSharing_individualMotorizedVehicleTraffic                   3
#define SAECLaneSharing_busVehicleTraffic                                   4
#define SAECLaneSharing_taxiVehicleTraffic                                  5
#define SAECLaneSharing_pedestriansTraffic                                  6
#define SAECLaneSharing_cyclistVehicleTraffic                               7
#define SAECLaneSharing_trackedVehicleTraffic                               8
#define SAECLaneSharing_pedestrianTraffic                                   9
#define SAECLaneSharing_NumBits                                             10

// SAECLaneWidth_Limit
#define SAECLaneWidth_Limit_Min                                             0
#define SAECLaneWidth_Limit_Max                                             32767

// SAECLatitude_Limit
#define SAECLatitude_Limit_Min                                              -900000000
#define SAECLatitude_Limit_Max                                              900000001

// SAECLightState_Limit
#define SAECLightState_Limit_Min                                            0
#define SAECLightState_Limit_Max                                            8

// SAECLightbarInUse_Limit
#define SAECLightbarInUse_Limit_Min                                         0
#define SAECLightbarInUse_Limit_Max                                         7

// SAECLinkList_SeqSize
#define SAECLinkList_SeqSize_Min                                            1
#define SAECLinkList_SeqSize_Max                                            32

// SAECLongitude_Limit
#define SAECLongitude_Limit_Min                                             -1799999999
#define SAECLongitude_Limit_Max                                             1800000001

// SAECMinuteOfTheYear_Limit
#define SAECMinuteOfTheYear_Limit_Min                                       0
#define SAECMinuteOfTheYear_Limit_Max                                       527040

// SAECMovementList_SeqSize
#define SAECMovementList_SeqSize_Min                                        1
#define SAECMovementList_SeqSize_Max                                        32

// SAECMsgCount_Limit
#define SAECMsgCount_Limit_Min                                              0
#define SAECMsgCount_Limit_Max                                              127

// SAECNodeID_Limit
#define SAECNodeID_Limit_Min                                                0
#define SAECNodeID_Limit_Max                                                65535

// SAECNodeList_SeqSize
#define SAECNodeList_SeqSize_Min                                            1
#define SAECNodeList_SeqSize_Max                                            32

// SAECOffsetLL_B12_Limit
#define SAECOffsetLL_B12_Limit_Min                                          -2048
#define SAECOffsetLL_B12_Limit_Max                                          2047

// SAECOffsetLL_B14_Limit
#define SAECOffsetLL_B14_Limit_Min                                          -8192
#define SAECOffsetLL_B14_Limit_Max                                          8191

// SAECOffsetLL_B16_Limit
#define SAECOffsetLL_B16_Limit_Min                                          -32768
#define SAECOffsetLL_B16_Limit_Max                                          32767

// SAECOffsetLL_B18_Limit
#define SAECOffsetLL_B18_Limit_Min                                          -131072
#define SAECOffsetLL_B18_Limit_Max                                          131071

// SAECOffsetLL_B22_Limit
#define SAECOffsetLL_B22_Limit_Min                                          -2097152
#define SAECOffsetLL_B22_Limit_Max                                          2097151

// SAECOffsetLL_B24_Limit
#define SAECOffsetLL_B24_Limit_Min                                          -8388608
#define SAECOffsetLL_B24_Limit_Max                                          8388607

// SAECParticipantData_PtcId_Limit
#define SAECParticipantData_PtcId_Limit_Min                                 0
#define SAECParticipantData_PtcId_Limit_Max                                 65535

// SAECParticipantList_SeqSize
#define SAECParticipantList_SeqSize_Min                                     1
#define SAECParticipantList_SeqSize_Max                                     16

// SAECParticipantType_Limit
#define SAECParticipantType_Limit_Min                                       0
#define SAECParticipantType_Limit_Max                                       4

// SAECPathHistoryPointList_SeqSize
#define SAECPathHistoryPointList_SeqSize_Min                                1
#define SAECPathHistoryPointList_SeqSize_Max                                23

// SAECPathPointList_SeqSize
#define SAECPathPointList_SeqSize_Min                                       2
#define SAECPathPointList_SeqSize_Max                                       32

// SAECPhaseID_Limit
#define SAECPhaseID_Limit_Min                                               0
#define SAECPhaseID_Limit_Max                                               255

// SAECPhaseList_SeqSize
#define SAECPhaseList_SeqSize_Min                                           1
#define SAECPhaseList_SeqSize_Max                                           16

// SAECPhaseStateList_SeqSize
#define SAECPhaseStateList_SeqSize_Min                                      1
#define SAECPhaseStateList_SeqSize_Max                                      16

// SAECPointList_SeqSize
#define SAECPointList_SeqSize_Min                                           2
#define SAECPointList_SeqSize_Max                                           31

// SAECPositionConfidence_Limit
#define SAECPositionConfidence_Limit_Min                                    0
#define SAECPositionConfidence_Limit_Max                                    15

// SAECRSIPriority
#define SAECRSIPriority_NumOctets                                           1

// SAECRTEData_RteId_Limit
#define SAECRTEData_RteId_Limit_Min                                         0
#define SAECRTEData_RteId_Limit_Max                                         255

// SAECRTEList_SeqSize
#define SAECRTEList_SeqSize_Min                                             1
#define SAECRTEList_SeqSize_Max                                             8

// SAECRTSData_RtsId_Limit
#define SAECRTSData_RtsId_Limit_Min                                         0
#define SAECRTSData_RtsId_Limit_Max                                         255

// SAECRTSList_SeqSize
#define SAECRTSList_SeqSize_Min                                             1
#define SAECRTSList_SeqSize_Max                                             16

// SAECRadiusOfCurvature_Limit
#define SAECRadiusOfCurvature_Limit_Min                                     -32767
#define SAECRadiusOfCurvature_Limit_Max                                     32767

// SAECRadius_Limit
#define SAECRadius_Limit_Min                                                0
#define SAECRadius_Limit_Max                                                65535

// SAECReferenceLanes
#define SAECReferenceLanes_reserved                                         0
#define SAECReferenceLanes_lane1                                            1
#define SAECReferenceLanes_lane2                                            2
#define SAECReferenceLanes_lane3                                            3
#define SAECReferenceLanes_lane4                                            4
#define SAECReferenceLanes_lane5                                            5
#define SAECReferenceLanes_lane6                                            6
#define SAECReferenceLanes_lane7                                            7
#define SAECReferenceLanes_lane8                                            8
#define SAECReferenceLanes_lane9                                            9
#define SAECReferenceLanes_lane10                                           10
#define SAECReferenceLanes_lane11                                           11
#define SAECReferenceLanes_lane12                                           12
#define SAECReferenceLanes_lane13                                           13
#define SAECReferenceLanes_lane14                                           14
#define SAECReferenceLanes_lane15                                           15
#define SAECReferenceLanes_NumBits                                          16

// SAECReferenceLinkList_SeqSize
#define SAECReferenceLinkList_SeqSize_Min                                   1
#define SAECReferenceLinkList_SeqSize_Max                                   16

// SAECReferencePathList_SeqSize
#define SAECReferencePathList_SeqSize_Min                                   1
#define SAECReferencePathList_SeqSize_Max                                   8

// SAECResponseType_Limit
#define SAECResponseType_Limit_Min                                          0
#define SAECResponseType_Limit_Max                                          6

// SAECRoadRegulatorID_Limit
#define SAECRoadRegulatorID_Limit_Min                                       0
#define SAECRoadRegulatorID_Limit_Max                                       65535

// SAECSemiMajorAxisAccuracy_Limit
#define SAECSemiMajorAxisAccuracy_Limit_Min                                 0
#define SAECSemiMajorAxisAccuracy_Limit_Max                                 255

// SAECSemiMajorAxisOrientation_Limit
#define SAECSemiMajorAxisOrientation_Limit_Min                              0
#define SAECSemiMajorAxisOrientation_Limit_Max                              65535

// SAECSemiMinorAxisAccuracy_Limit
#define SAECSemiMinorAxisAccuracy_Limit_Min                                 0
#define SAECSemiMinorAxisAccuracy_Limit_Max                                 255

// SAECSignType_Limit
#define SAECSignType_Limit_Min                                              0
#define SAECSignType_Limit_Max                                              65535

// SAECSirenInUse_Limit
#define SAECSirenInUse_Limit_Min                                            0
#define SAECSirenInUse_Limit_Max                                            3

// SAECSourceType_Limit
#define SAECSourceType_Limit_Min                                            0
#define SAECSourceType_Limit_Max                                            7

// SAECSpeedConfidence_Limit
#define SAECSpeedConfidence_Limit_Min                                       0
#define SAECSpeedConfidence_Limit_Max                                       7

// SAECSpeedLimitList_SeqSize
#define SAECSpeedLimitList_SeqSize_Min                                      1
#define SAECSpeedLimitList_SeqSize_Max                                      9

// SAECSpeed_Limit
#define SAECSpeed_Limit_Min                                                 0
#define SAECSpeed_Limit_Max                                                 8191

// SAECStabilityControlStatus_Limit
#define SAECStabilityControlStatus_Limit_Min                                0
#define SAECStabilityControlStatus_Limit_Max                                3

// SAECSteeringWheelAngleConfidence_Limit
#define SAECSteeringWheelAngleConfidence_Limit_Min                          0
#define SAECSteeringWheelAngleConfidence_Limit_Max                          3

// SAECSteeringWheelAngle_Limit
#define SAECSteeringWheelAngle_Limit_Min                                    -126
#define SAECSteeringWheelAngle_Limit_Max                                    127

// SAECTimeConfidence_Limit
#define SAECTimeConfidence_Limit_Min                                        0
#define SAECTimeConfidence_Limit_Max                                        39

// SAECTimeMark_Limit
#define SAECTimeMark_Limit_Min                                              0
#define SAECTimeMark_Limit_Max                                              36001

// SAECTimeOffset_Limit
#define SAECTimeOffset_Limit_Min                                            1
#define SAECTimeOffset_Limit_Max                                            65535

// SAECTractionControlStatus_Limit
#define SAECTractionControlStatus_Limit_Min                                 0
#define SAECTractionControlStatus_Limit_Max                                 3

// SAECTransmissionState_Limit
#define SAECTransmissionState_Limit_Min                                     0
#define SAECTransmissionState_Limit_Max                                     7

// SAECVehicleEventFlags
#define SAECVehicleEventFlags_eventHazardLights                             0
#define SAECVehicleEventFlags_eventStopLineViolation                        1
#define SAECVehicleEventFlags_eventABSactivated                             2
#define SAECVehicleEventFlags_eventTractionControlLoss                      3
#define SAECVehicleEventFlags_eventStabilityControlactivated                4
#define SAECVehicleEventFlags_eventHazardousMaterials                       5
#define SAECVehicleEventFlags_eventReserved1                                6
#define SAECVehicleEventFlags_eventHardBraking                              7
#define SAECVehicleEventFlags_eventLightsChanged                            8
#define SAECVehicleEventFlags_eventWipersChanged                            9
#define SAECVehicleEventFlags_eventFlatTire                                 10
#define SAECVehicleEventFlags_eventDisabledVehicle                          11
#define SAECVehicleEventFlags_eventAirBagDeployment                         12
#define SAECVehicleEventFlags_NumBits                                       13

// SAECVehicleHeight_Limit
#define SAECVehicleHeight_Limit_Min                                         0
#define SAECVehicleHeight_Limit_Max                                         127

// SAECVehicleLength_Limit
#define SAECVehicleLength_Limit_Min                                         0
#define SAECVehicleLength_Limit_Max                                         4095

// SAECVehicleWidth_Limit
#define SAECVehicleWidth_Limit_Min                                          0
#define SAECVehicleWidth_Limit_Max                                          1023

// SAECVertOffset_B07_Limit
#define SAECVertOffset_B07_Limit_Min                                        -64
#define SAECVertOffset_B07_Limit_Max                                        63

// SAECVertOffset_B08_Limit
#define SAECVertOffset_B08_Limit_Min                                        -128
#define SAECVertOffset_B08_Limit_Max                                        127

// SAECVertOffset_B09_Limit
#define SAECVertOffset_B09_Limit_Min                                        -256
#define SAECVertOffset_B09_Limit_Max                                        255

// SAECVertOffset_B10_Limit
#define SAECVertOffset_B10_Limit_Min                                        -512
#define SAECVertOffset_B10_Limit_Max                                        511

// SAECVertOffset_B11_Limit
#define SAECVertOffset_B11_Limit_Min                                        -1024
#define SAECVertOffset_B11_Limit_Max                                        1023

// SAECVertOffset_B12_Limit
#define SAECVertOffset_B12_Limit_Min                                        -2048
#define SAECVertOffset_B12_Limit_Max                                        2047

// SAECVerticalAcceleration_Limit
#define SAECVerticalAcceleration_Limit_Min                                  -127
#define SAECVerticalAcceleration_Limit_Max                                  127

// SAECYawRate_Limit
#define SAECYawRate_Limit_Min                                               -32767
#define SAECYawRate_Limit_Max                                               32767

#ifdef __cplusplus
}
#endif
