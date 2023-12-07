#pragma once

// AUTOGENERATED
// /home/duser/mk5/stack/apps/exampleETSI/src/RAW.asn1
//     to
// /home/duser/mk5/stack/apps/exampleETSI/src/raw-asn*

#ifdef __cplusplus
extern "C"
{
#endif
// with prefix 'RAW_'

// #define RAW_VruSpecificExteriorLights_??? ???
// #define RAW_ExteriorLights_??? ???
// #define RAW_ClusterProfiles_??? ???

// RAW_AccelerationConfidence_ID
#define RAW_AccelerationConfidence_ID_pointOneMeterPerSecSquared                 1
#define RAW_AccelerationConfidence_ID_outOfRange                                 101
#define RAW_AccelerationConfidence_ID_unavailable                                102

// RAW_AccelerationConfidence_Limit
#define RAW_AccelerationConfidence_Limit_Min                                     0
#define RAW_AccelerationConfidence_Limit_Max                                     102

// RAW_ActionDeltaTime_ID
#define RAW_ActionDeltaTime_ID_zero                                              0
#define RAW_ActionDeltaTime_ID_hundredMs                                         1
#define RAW_ActionDeltaTime_ID_twoHundredMs                                      2
#define RAW_ActionDeltaTime_ID_unavailable                                       127

// RAW_ActionDeltaTime_Limit
#define RAW_ActionDeltaTime_Limit_Min                                            0
#define RAW_ActionDeltaTime_Limit_Max                                            127

// RAW_AltitudeConfidence_Limit
#define RAW_AltitudeConfidence_Limit_Min                                         0
#define RAW_AltitudeConfidence_Limit_Max                                         15

// RAW_AltitudeValue_ID
#define RAW_AltitudeValue_ID_referenceEllipsoidSurface                           0
#define RAW_AltitudeValue_ID_oneCentimeter                                       1
#define RAW_AltitudeValue_ID_unavailable                                         800001

// RAW_AltitudeValue_Limit
#define RAW_AltitudeValue_Limit_Min                                              -100000
#define RAW_AltitudeValue_Limit_Max                                              800001

// RAW_ClusterBreakupReason_Limit
#define RAW_ClusterBreakupReason_Limit_Min                                       0
#define RAW_ClusterBreakupReason_Limit_Max                                       15

// RAW_ClusterCardinalitySize_ID
#define RAW_ClusterCardinalitySize_ID_unavailable                                0
#define RAW_ClusterCardinalitySize_ID_onlyLeader                                 1

// RAW_ClusterCardinalitySize_Limit
#define RAW_ClusterCardinalitySize_Limit_Min                                     0
#define RAW_ClusterCardinalitySize_Limit_Max                                     255

// RAW_ClusterId_Limit
#define RAW_ClusterId_Limit_Min                                                  0
#define RAW_ClusterId_Limit_Max                                                  255

// RAW_ClusterLeaveReason_Limit
#define RAW_ClusterLeaveReason_Limit_Min                                         0
#define RAW_ClusterLeaveReason_Limit_Max                                         15

// RAW_CurvatureCalculationMode_Limit
#define RAW_CurvatureCalculationMode_Limit_Min                                   0
#define RAW_CurvatureCalculationMode_Limit_Max                                   2

// RAW_CurvatureConfidence_Limit
#define RAW_CurvatureConfidence_Limit_Min                                        0
#define RAW_CurvatureConfidence_Limit_Max                                        7

// RAW_CurvatureValue_ID
#define RAW_CurvatureValue_ID_straight                                           0
#define RAW_CurvatureValue_ID_unavailable                                        1023

// RAW_CurvatureValue_Limit
#define RAW_CurvatureValue_Limit_Min                                             -1023
#define RAW_CurvatureValue_Limit_Max                                             1023

// RAW_DeltaAltitude_ID
#define RAW_DeltaAltitude_ID_oneCentimeterDown                                   -1
#define RAW_DeltaAltitude_ID_oneCentimeterUp                                     1
#define RAW_DeltaAltitude_ID_unavailable                                         12800

// RAW_DeltaAltitude_Limit
#define RAW_DeltaAltitude_Limit_Min                                              -12700
#define RAW_DeltaAltitude_Limit_Max                                              12800

// RAW_DeltaLatitude_ID
#define RAW_DeltaLatitude_ID_oneMicrodegreeSouth                                 -10
#define RAW_DeltaLatitude_ID_oneMicrodegreeNorth                                 10
#define RAW_DeltaLatitude_ID_unavailable                                         131072

// RAW_DeltaLatitude_Limit
#define RAW_DeltaLatitude_Limit_Min                                              -131071
#define RAW_DeltaLatitude_Limit_Max                                              131072

// RAW_DeltaLongitude_ID
#define RAW_DeltaLongitude_ID_oneMicrodegreeWest                                 -10
#define RAW_DeltaLongitude_ID_oneMicrodegreeEast                                 10
#define RAW_DeltaLongitude_ID_unavailable                                        131072

// RAW_DeltaLongitude_Limit
#define RAW_DeltaLongitude_Limit_Min                                             -131071
#define RAW_DeltaLongitude_Limit_Max                                             131072

// RAW_GenerationDeltaTime_ID
#define RAW_GenerationDeltaTime_ID_oneMilliSec                                   1

// RAW_GenerationDeltaTime_Limit
#define RAW_GenerationDeltaTime_Limit_Min                                        0
#define RAW_GenerationDeltaTime_Limit_Max                                        65535

// RAW_HeadingConfidence_ID
#define RAW_HeadingConfidence_ID_equalOrWithinZeroPointOneDegree                 1
#define RAW_HeadingConfidence_ID_equalOrWithinOneDegree                          10
#define RAW_HeadingConfidence_ID_outOfRange                                      126
#define RAW_HeadingConfidence_ID_unavailable                                     127

// RAW_HeadingConfidence_Limit
#define RAW_HeadingConfidence_Limit_Min                                          1
#define RAW_HeadingConfidence_Limit_Max                                          127

// RAW_HeadingValue_ID
#define RAW_HeadingValue_ID_wgs84North                                           0
#define RAW_HeadingValue_ID_wgs84East                                            900
#define RAW_HeadingValue_ID_wgs84South                                           1800
#define RAW_HeadingValue_ID_wgs84West                                            2700
#define RAW_HeadingValue_ID_unavailable                                          3601

// RAW_HeadingValue_Limit
#define RAW_HeadingValue_Limit_Min                                               0
#define RAW_HeadingValue_Limit_Max                                               3601

// RAW_IntersectionID_Limit
#define RAW_IntersectionID_Limit_Min                                             0
#define RAW_IntersectionID_Limit_Max                                             65535

// RAW_ItsPduHeaderMessageID_ID
#define RAW_ItsPduHeaderMessageID_ID_denm                                        1
#define RAW_ItsPduHeaderMessageID_ID_cam                                         2
#define RAW_ItsPduHeaderMessageID_ID_poi                                         3
#define RAW_ItsPduHeaderMessageID_ID_spatem                                      4
#define RAW_ItsPduHeaderMessageID_ID_mapem                                       5
#define RAW_ItsPduHeaderMessageID_ID_ivim                                        6
#define RAW_ItsPduHeaderMessageID_ID_ev_rsr                                      7
#define RAW_ItsPduHeaderMessageID_ID_tistpgtransaction                           8
#define RAW_ItsPduHeaderMessageID_ID_srem                                        9
#define RAW_ItsPduHeaderMessageID_ID_ssem                                        10
#define RAW_ItsPduHeaderMessageID_ID_evcsn                                       11
#define RAW_ItsPduHeaderMessageID_ID_saem                                        12
#define RAW_ItsPduHeaderMessageID_ID_rtcmem                                      13
#define RAW_ItsPduHeaderMessageID_ID_vam                                         14

// RAW_ItsPduHeaderMessageID_Limit
#define RAW_ItsPduHeaderMessageID_Limit_Min                                      0
#define RAW_ItsPduHeaderMessageID_Limit_Max                                      255

// RAW_ItsPduHeader_ProtocolVersion_Limit
#define RAW_ItsPduHeader_ProtocolVersion_Limit_Min                               0
#define RAW_ItsPduHeader_ProtocolVersion_Limit_Max                               255

// RAW_LaneID_Limit
#define RAW_LaneID_Limit_Min                                                     0
#define RAW_LaneID_Limit_Max                                                     255

// RAW_LanePosition_ID
#define RAW_LanePosition_ID_offTheRoad                                           -1
#define RAW_LanePosition_ID_hardShoulder                                         0
#define RAW_LanePosition_ID_outermostDrivingLane                                 1
#define RAW_LanePosition_ID_secondLaneFromOutside                                2

// RAW_LanePosition_Limit
#define RAW_LanePosition_Limit_Min                                               -1
#define RAW_LanePosition_Limit_Max                                               14

// RAW_LateralAccelerationValue_ID
#define RAW_LateralAccelerationValue_ID_pointOneMeterPerSecSquaredToRight        -1
#define RAW_LateralAccelerationValue_ID_pointOneMeterPerSecSquaredToLeft         1
#define RAW_LateralAccelerationValue_ID_unavailable                              161

// RAW_LateralAccelerationValue_Limit
#define RAW_LateralAccelerationValue_Limit_Min                                   -160
#define RAW_LateralAccelerationValue_Limit_Max                                   161

// RAW_Latitude_ID
#define RAW_Latitude_ID_oneMicrodegreeSouth                                      -10
#define RAW_Latitude_ID_oneMicrodegreeNorth                                      10
#define RAW_Latitude_ID_unavailable                                              900000001

// RAW_Latitude_Limit
#define RAW_Latitude_Limit_Min                                                   -900000000
#define RAW_Latitude_Limit_Max                                                   900000001

// RAW_Longitude_ID
#define RAW_Longitude_ID_oneMicrodegreeWest                                      -10
#define RAW_Longitude_ID_oneMicrodegreeEast                                      10
#define RAW_Longitude_ID_unavailable                                             1800000001

// RAW_Longitude_Limit
#define RAW_Longitude_Limit_Min                                                  -1800000000
#define RAW_Longitude_Limit_Max                                                  1800000001

// RAW_LongitudinalAccelerationValue_ID
#define RAW_LongitudinalAccelerationValue_ID_pointOneMeterPerSecSquaredBackward  -1
#define RAW_LongitudinalAccelerationValue_ID_pointOneMeterPerSecSquaredForward   1
#define RAW_LongitudinalAccelerationValue_ID_unavailable                         161

// RAW_LongitudinalAccelerationValue_Limit
#define RAW_LongitudinalAccelerationValue_Limit_Min                              -160
#define RAW_LongitudinalAccelerationValue_Limit_Max                              161

// RAW_OffRoadLanePosition_Limit
#define RAW_OffRoadLanePosition_Limit_Min                                        0
#define RAW_OffRoadLanePosition_Limit_Max                                        15

// RAW_Offset_B10_Limit
#define RAW_Offset_B10_Limit_Min                                                 -512
#define RAW_Offset_B10_Limit_Max                                                 511

// RAW_Offset_B11_Limit
#define RAW_Offset_B11_Limit_Min                                                 -1024
#define RAW_Offset_B11_Limit_Max                                                 1023

// RAW_Offset_B12_Limit
#define RAW_Offset_B12_Limit_Min                                                 -2048
#define RAW_Offset_B12_Limit_Max                                                 2047

// RAW_Offset_B13_Limit
#define RAW_Offset_B13_Limit_Min                                                 -4096
#define RAW_Offset_B13_Limit_Max                                                 4095

// RAW_Offset_B14_Limit
#define RAW_Offset_B14_Limit_Min                                                 -8192
#define RAW_Offset_B14_Limit_Max                                                 8191

// RAW_Offset_B16_Limit
#define RAW_Offset_B16_Limit_Min                                                 -32768
#define RAW_Offset_B16_Limit_Max                                                 32767

// RAW_PathDeltaTime_ID
#define RAW_PathDeltaTime_ID_tenMilliSecondsInPast                               1

// RAW_PathDeltaTime_Limit
#define RAW_PathDeltaTime_Limit_Min                                              1
#define RAW_PathDeltaTime_Limit_Max                                              65535

// RAW_PathHistory_SeqSize
#define RAW_PathHistory_SeqSize_Min                                              0
#define RAW_PathHistory_SeqSize_Max                                              40

// RAW_PolyPointList_SeqSize
#define RAW_PolyPointList_SeqSize_Min                                            3
#define RAW_PolyPointList_SeqSize_Max                                            16

// RAW_Radius_ID
#define RAW_Radius_ID_zeroPointOneMeter                                          1
#define RAW_Radius_ID_oneMeter                                                   10

// RAW_Radius_Limit
#define RAW_Radius_Limit_Min                                                     0
#define RAW_Radius_Limit_Max                                                     10000

// RAW_RegionId
#define RAW_RegionId_noRegion                                                    0
#define RAW_RegionId_addGrpA                                                     1
#define RAW_RegionId_addGrpB                                                     2
#define RAW_RegionId_addGrpC                                                     3

// RAW_RegionId_Limit
#define RAW_RegionId_Limit_Min                                                   0
#define RAW_RegionId_Limit_Max                                                   255

// RAW_RoadRegulatorID_Limit
#define RAW_RoadRegulatorID_Limit_Min                                            0
#define RAW_RoadRegulatorID_Limit_Max                                            65535

// RAW_SemiAxisLength_ID
#define RAW_SemiAxisLength_ID_oneCentimeter                                      1
#define RAW_SemiAxisLength_ID_outOfRange                                         4094
#define RAW_SemiAxisLength_ID_unavailable                                        4095

// RAW_SemiAxisLength_Limit
#define RAW_SemiAxisLength_Limit_Min                                             0
#define RAW_SemiAxisLength_Limit_Max                                             4095

// RAW_SemiRangeLength_ID
#define RAW_SemiRangeLength_ID_zeroPointOneMeter                                 1
#define RAW_SemiRangeLength_ID_oneMeter                                          10

// RAW_SemiRangeLength_Limit
#define RAW_SemiRangeLength_Limit_Min                                            0
#define RAW_SemiRangeLength_Limit_Max                                            10000

// RAW_SequenceOfTrajectoryInterceptionIndication_SeqSize
#define RAW_SequenceOfTrajectoryInterceptionIndication_SeqSize_Min               1
#define RAW_SequenceOfTrajectoryInterceptionIndication_SeqSize_Max               8

// RAW_SequenceOfVruSafeDistanceIndication_SeqSize
#define RAW_SequenceOfVruSafeDistanceIndication_SeqSize_Min                      1
#define RAW_SequenceOfVruSafeDistanceIndication_SeqSize_Max                      8

// RAW_SpeedConfidence_ID
#define RAW_SpeedConfidence_ID_equalOrWithinOneCentimeterPerSec                  1
#define RAW_SpeedConfidence_ID_equalOrWithinOneMeterPerSec                       100
#define RAW_SpeedConfidence_ID_outOfRange                                        126
#define RAW_SpeedConfidence_ID_unavailable                                       127

// RAW_SpeedConfidence_Limit
#define RAW_SpeedConfidence_Limit_Min                                            1
#define RAW_SpeedConfidence_Limit_Max                                            127

// RAW_SpeedValue_ID
#define RAW_SpeedValue_ID_standstill                                             0
#define RAW_SpeedValue_ID_oneCentimeterPerSec                                    1
#define RAW_SpeedValue_ID_unavailable                                            16383

// RAW_SpeedValue_Limit
#define RAW_SpeedValue_Limit_Min                                                 0
#define RAW_SpeedValue_Limit_Max                                                 16383

// RAW_StabilityLossProbability_ID
#define RAW_StabilityLossProbability_ID_zero                                     0
#define RAW_StabilityLossProbability_ID_twoPercent                               1
#define RAW_StabilityLossProbability_ID_fourPercent                              2
#define RAW_StabilityLossProbability_ID_unavailable                              63

// RAW_StabilityLossProbability_Limit
#define RAW_StabilityLossProbability_Limit_Min                                   0
#define RAW_StabilityLossProbability_Limit_Max                                   63

// RAW_StationID_Limit
#define RAW_StationID_Limit_Min                                                  0
#define RAW_StationID_Limit_Max                                                  4294967295

// RAW_StationType_ID
#define RAW_StationType_ID_unknown                                               0
#define RAW_StationType_ID_pedestrian                                            1
#define RAW_StationType_ID_cyclist                                               2
#define RAW_StationType_ID_moped                                                 3
#define RAW_StationType_ID_motorcycle                                            4
#define RAW_StationType_ID_passengerCar                                          5
#define RAW_StationType_ID_bus                                                   6
#define RAW_StationType_ID_lightTruck                                            7
#define RAW_StationType_ID_heavyTruck                                            8
#define RAW_StationType_ID_trailer                                               9
#define RAW_StationType_ID_specialVehicles                                       10
#define RAW_StationType_ID_tram                                                  11
#define RAW_StationType_ID_lightVruVehicle                                       12
#define RAW_StationType_ID_animal                                                13
#define RAW_StationType_ID_roadSideUnit                                          15

// RAW_StationType_Limit
#define RAW_StationType_Limit_Min                                                0
#define RAW_StationType_Limit_Max                                                255

// RAW_TrajectoryInterceptionConfidence_ID
#define RAW_TrajectoryInterceptionConfidence_ID_lessthan50percent                0
#define RAW_TrajectoryInterceptionConfidence_ID_between50and70Percent            1
#define RAW_TrajectoryInterceptionConfidence_ID_between70and90Percent            2
#define RAW_TrajectoryInterceptionConfidence_ID_above90Percent                   3

// RAW_TrajectoryInterceptionConfidence_Limit
#define RAW_TrajectoryInterceptionConfidence_Limit_Min                           0
#define RAW_TrajectoryInterceptionConfidence_Limit_Max                           3

// RAW_TrajectoryInterceptionProbability_ID
#define RAW_TrajectoryInterceptionProbability_ID_zero                            0
#define RAW_TrajectoryInterceptionProbability_ID_twoPercent                      1
#define RAW_TrajectoryInterceptionProbability_ID_fourPercent                     2
#define RAW_TrajectoryInterceptionProbability_ID_oneHundredPercent               50
#define RAW_TrajectoryInterceptionProbability_ID_unavailable                     63

// RAW_TrajectoryInterceptionProbability_Limit
#define RAW_TrajectoryInterceptionProbability_Limit_Min                          0
#define RAW_TrajectoryInterceptionProbability_Limit_Max                          63

// RAW_VerticalAccelerationValue_ID
#define RAW_VerticalAccelerationValue_ID_pointOneMeterPerSecSquaredDown          -1
#define RAW_VerticalAccelerationValue_ID_pointOneMeterPerSecSquaredUp            1
#define RAW_VerticalAccelerationValue_ID_unavailable                             161

// RAW_VerticalAccelerationValue_Limit
#define RAW_VerticalAccelerationValue_Limit_Min                                  -160
#define RAW_VerticalAccelerationValue_Limit_Max                                  161

// RAW_VruClusterOpTimestamp_Limit
#define RAW_VruClusterOpTimestamp_Limit_Min                                      1
#define RAW_VruClusterOpTimestamp_Limit_Max                                      255

// RAW_VruDeviceUsage_Limit
#define RAW_VruDeviceUsage_Limit_Min                                             0
#define RAW_VruDeviceUsage_Limit_Max                                             255

// RAW_VruEnvironment_Limit
#define RAW_VruEnvironment_Limit_Min                                             0
#define RAW_VruEnvironment_Limit_Max                                             255

// RAW_VruMovementControl_Limit
#define RAW_VruMovementControl_Limit_Min                                         0
#define RAW_VruMovementControl_Limit_Max                                         255

// RAW_VruProfile_Limit
#define RAW_VruProfile_Limit_Min                                                 0
#define RAW_VruProfile_Limit_Max                                                 15

// RAW_VruSizeClass_Limit
#define RAW_VruSizeClass_Limit_Min                                               0
#define RAW_VruSizeClass_Limit_Max                                               15

// RAW_VruSubProfileAnimal_Limit
#define RAW_VruSubProfileAnimal_Limit_Min                                        0
#define RAW_VruSubProfileAnimal_Limit_Max                                        15

// RAW_VruSubProfileBicyclist_Limit
#define RAW_VruSubProfileBicyclist_Limit_Min                                     0
#define RAW_VruSubProfileBicyclist_Limit_Max                                     15

// RAW_VruSubProfileMotorcyclist_Limit
#define RAW_VruSubProfileMotorcyclist_Limit_Min                                  0
#define RAW_VruSubProfileMotorcyclist_Limit_Max                                  15

// RAW_VruSubProfilePedestrian_Limit
#define RAW_VruSubProfilePedestrian_Limit_Min                                    0
#define RAW_VruSubProfilePedestrian_Limit_Max                                    15

// RAW_WGS84AngleValue_ID
#define RAW_WGS84AngleValue_ID_wgs84North                                        0
#define RAW_WGS84AngleValue_ID_wgs84East                                         900
#define RAW_WGS84AngleValue_ID_wgs84South                                        1800
#define RAW_WGS84AngleValue_ID_wgs84West                                         2700
#define RAW_WGS84AngleValue_ID_unavailable                                       3601

// RAW_WGS84AngleValue_Limit
#define RAW_WGS84AngleValue_Limit_Min                                            0
#define RAW_WGS84AngleValue_Limit_Max                                            3601

// RAW_YawRateConfidence_Limit
#define RAW_YawRateConfidence_Limit_Min                                          0
#define RAW_YawRateConfidence_Limit_Max                                          8

// RAW_YawRateValue_ID
#define RAW_YawRateValue_ID_degSec_000_01ToRight                                 -1
#define RAW_YawRateValue_ID_straight                                             0
#define RAW_YawRateValue_ID_degSec_000_01ToLeft                                  1
#define RAW_YawRateValue_ID_unavailable                                          32767

// RAW_YawRateValue_Limit
#define RAW_YawRateValue_Limit_Min                                               -32766
#define RAW_YawRateValue_Limit_Max                                               32767

#ifdef __cplusplus
}
#endif
