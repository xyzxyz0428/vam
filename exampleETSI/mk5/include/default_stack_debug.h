#pragma once
//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
  // Cohda_PP.DebugLevel
  extern int default_stack_Cohda_PP_DebugLevel;
  // Cohda_PP.lph_pp.DebugLevel
  extern int default_stack_Cohda_PP_lph_pp_DebugLevel;
  // Cohda_PH.DebugLevel
  extern int default_stack_Cohda_PH_DebugLevel;
  // Cohda_PH.lph_api.DebugLevel
  extern int default_stack_Cohda_PH_lph_api_DebugLevel;
  // Cohda_PH.lph_circular_buffer.DebugLevel
  extern int default_stack_Cohda_PH_lph_circular_buffer_DebugLevel;
  // Cohda_PH.lph_concise_algr.DebugLevel
  extern int default_stack_Cohda_PH_lph_concise_algr_DebugLevel;
  // Cohda_PH.lph_haversine.DebugLevel
  extern int default_stack_Cohda_PH_lph_haversine_DebugLevel;
  // Cohda_PH.lph_iir.DebugLevel
  extern int default_stack_Cohda_PH_lph_iir_DebugLevel;
  // Cohda_PH.lph_kalman.DebugLevel
  extern int default_stack_Cohda_PH_lph_kalman_DebugLevel;
  // Cohda_PH.lph_leap.DebugLevel
  extern int default_stack_Cohda_PH_lph_leap_DebugLevel;
  // Cohda_PH.lph_lib.DebugLevel
  extern int default_stack_Cohda_PH_lph_lib_DebugLevel;
  // Cohda_PH.lph_ph.DebugLevel
  extern int default_stack_Cohda_PH_lph_ph_DebugLevel;
  // Cohda_PH.lph_pos.DebugLevel
  extern int default_stack_Cohda_PH_lph_pos_DebugLevel;
  // Cohda_PH.lph_pos_api.DebugLevel
  extern int default_stack_Cohda_PH_lph_pos_api_DebugLevel;
  // Cohda_PH.lph_poshandler.DebugLevel
  extern int default_stack_Cohda_PH_lph_poshandler_DebugLevel;
  // Cohda_PH.lph_tai.DebugLevel
  extern int default_stack_Cohda_PH_lph_tai_DebugLevel;
  // Cohda_PH.lph_thr.DebugLevel
  extern int default_stack_Cohda_PH_lph_thr_DebugLevel;
  // J2945CC.DebugLevel
  extern int default_stack_J2945CC_DebugLevel;
  // Cohda_VS.DebugLevel
  extern int default_stack_Cohda_VS_DebugLevel;
  // Cohda_VS.vstate_data.DebugLevel
  extern int default_stack_Cohda_VS_vstate_data_DebugLevel;
  // Cohda_VS.vstate_gen.DebugLevel
  extern int default_stack_Cohda_VS_vstate_gen_DebugLevel;
  // Cohda_VS.vstate_skel.DebugLevel
  extern int default_stack_Cohda_VS_vstate_skel_DebugLevel;
  // Cohda_VS.vstate_stub.DebugLevel
  extern int default_stack_Cohda_VS_vstate_stub_DebugLevel;
  // Cohda_VS.vstate_thr.DebugLevel
  extern int default_stack_Cohda_VS_vstate_thr_DebugLevel;
  // Cohda_TM.DebugLevel
  extern int default_stack_Cohda_TM_DebugLevel;
  // Cohda_UBX.DebugLevel
  extern int default_stack_Cohda_UBX_DebugLevel;
  // Cohda_ADR.DebugLevel
  extern int default_stack_Cohda_ADR_DebugLevel;
  // Cohda_RPS.DebugLevel
  extern int default_stack_Cohda_RPS_DebugLevel;
  // Cohda_LTE.DebugLevel
  extern int default_stack_Cohda_LTE_DebugLevel;
  // Cohda_Stack.DebugLevel
  extern int default_stack_Cohda_Stack_DebugLevel;
  // Cohda_Stack.net_its.DebugLevel
  extern int default_stack_Cohda_Stack_net_its_DebugLevel;
  // Cohda_Stack.net_its.etsi_3gpp.DebugLevel
  extern int default_stack_Cohda_Stacknet_its_etsi_3gpp_DebugLevel;
  // Cohda_Stack.net_its.etsi_btp.DebugLevel
  extern int default_stack_Cohda_Stacknet_its_etsi_btp_DebugLevel;
  // Cohda_Stack.net_its.etsi_dcc.DebugLevel
  extern int default_stack_Cohda_Stacknet_its_etsi_dcc_DebugLevel;
  // Cohda_Stack.net_its.etsi_dcc.etsi_dcc_api.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_dcc_etsi_dcc_api_DebugLevel;
  // Cohda_Stack.net_its.etsi_dcc.etsi_dcc_ctrl.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_dcc_etsi_dcc_ctrl_DebugLevel;
  // Cohda_Stack.net_its.etsi_dcc.etsi_dcc_mgmt.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_dcc_etsi_dcc_mgmt_DebugLevel;
  // Cohda_Stack.net_its.etsi_dcc.etsi_dcc_stats.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_dcc_etsi_dcc_stats_DebugLevel;
  // Cohda_Stack.net_its.etsi_g5.DebugLevel
  extern int default_stack_Cohda_Stacknet_its_etsi_g5_DebugLevel;
  // Cohda_Stack.net_its.etsi_g5.etsi_g5_ctrl.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_g5_etsi_g5_ctrl_DebugLevel;
  // Cohda_Stack.net_its.etsi_g5.etsi_g5_lib.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_g5_etsi_g5_lib_DebugLevel;
  // Cohda_Stack.net_its.etsi_g5.etsi_g5_mon.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_g5_etsi_g5_mon_DebugLevel;
  // Cohda_Stack.net_its.etsi_g5.etsi_g5_rx_replay.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_g5_etsi_g5_rx_replay_DebugLevel;
  // Cohda_Stack.net_its.etsi_g5.etsi_g5_rx.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_g5_etsi_g5_rx_DebugLevel;
  // Cohda_Stack.net_its.etsi_g5.etsi_g5_tx.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_g5_etsi_g5_tx_DebugLevel;
  // Cohda_Stack.net_its.etsi_gn.DebugLevel
  extern int default_stack_Cohda_Stacknet_its_etsi_gn_DebugLevel;
  // Cohda_Stack.net_its.etsi_gn.etsi_gn_buffer.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_gn_etsi_gn_buffer_DebugLevel;
  // Cohda_Stack.net_its.etsi_gn.etsi_gn_lib.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_gn_etsi_gn_lib_DebugLevel;
  // Cohda_Stack.net_its.etsi_gn.etsi_gn_neighbour.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_gn_etsi_gn_neighbour_DebugLevel;
  // Cohda_Stack.net_its.etsi_gn.etsi_gn_periodic.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_gn_etsi_gn_periodic_DebugLevel;
  // Cohda_Stack.net_its.etsi_gn.etsi_gn_rx.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_gn_etsi_gn_rx_DebugLevel;
  // Cohda_Stack.net_its.etsi_gn.etsi_gn_thr.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_gn_etsi_gn_thr_DebugLevel;
  // Cohda_Stack.net_its.etsi_gn.etsi_gn_tx.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_gn_etsi_gn_tx_DebugLevel;
  // Cohda_Stack.net_its.etsi_gn6.DebugLevel
  extern int default_stack_Cohda_Stacknet_its_etsi_gn6_DebugLevel;
  // Cohda_Stack.net_its.etsi_pc5.DebugLevel
  extern int default_stack_Cohda_Stacknet_its_etsi_pc5_DebugLevel;
  // Cohda_Stack.net_its.etsi_pc5.etsi_pc5_ctrl.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_pc5_etsi_pc5_ctrl_DebugLevel;
  // Cohda_Stack.net_its.etsi_pc5.etsi_pc5_tx.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_pc5_etsi_pc5_tx_DebugLevel;
  // Cohda_Stack.net_its.etsi_pc5.etsi_pc5_rx.DebugLevel
  extern int default_stack_Cohda_Stacknet_itsetsi_pc5_etsi_pc5_rx_DebugLevel;
  // Cohda_Stack.net_its.libc2xsec.DebugLevel
  extern int default_stack_Cohda_Stacknet_its_libc2xsec_DebugLevel;
  // Cohda_Stack.net_its.libc2xsec.cohda_sec.DebugLevel
  extern int default_stack_Cohda_Stacknet_itslibc2xsec_cohda_sec_DebugLevel;
  // Cohda_Stack.net_its.libc2xsec.cohda_sec_aerolink.DebugLevel
  extern int default_stack_Cohda_Stacknet_itslibc2xsec_cohda_sec_aerolink_DebugLevel;
  // Cohda_Stack.net_its.libitsnet.DebugLevel
  extern int default_stack_Cohda_Stacknet_its_libitsnet_DebugLevel;
  // Cohda_Stack.net_its.libitsnet.libitsnet_mgmt.DebugLevel
  extern int default_stack_Cohda_Stacknet_itslibitsnet_libitsnet_mgmt_DebugLevel;
  // Cohda_Stack.net_its.libitsnet.libitsnet_mgmt.log.DebugLevel
  extern int default_stack_Cohda_Stacknet_itslibitsnetlibitsnet_mgmt_log_DebugLevel;
  // Cohda_Stack.net_its.udp_btp.DebugLevel
  extern int default_stack_Cohda_Stacknet_its_udp_btp_DebugLevel;
  // Cohda_Stack.fac_its.DebugLevel
  extern int default_stack_Cohda_Stack_fac_its_DebugLevel;
  // Cohda_Stack.fac_its.etsi_uppertester.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_uppertester_DebugLevel;
  // Cohda_Stack.fac_its.etsi_uppertester.etsi_ut_btp.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_uppertester_etsi_ut_btp_DebugLevel;
  // Cohda_Stack.fac_its.etsi_uppertester.etsi_ut_cam.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_uppertester_etsi_ut_cam_DebugLevel;
  // Cohda_Stack.fac_its.etsi_uppertester.etsi_ut_denm.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_uppertester_etsi_ut_denm_DebugLevel;
  // Cohda_Stack.fac_its.etsi_uppertester.etsi_ut_gn.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_uppertester_etsi_ut_gn_DebugLevel;
  // Cohda_Stack.fac_its.etsi_uppertester.etsi_ut_gn6.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_uppertester_etsi_ut_gn6_DebugLevel;
  // Cohda_Stack.fac_its.etsi_uppertester.etsi_ut_ivi.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_uppertester_etsi_ut_ivi_DebugLevel;
  // Cohda_Stack.fac_its.etsi_uppertester.etsi_ut_msg.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_uppertester_etsi_ut_msg_DebugLevel;
  // Cohda_Stack.fac_its.etsi_uppertester.etsi_ut_spatmap.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_uppertester_etsi_ut_spatmap_DebugLevel;
  // Cohda_Stack.fac_its.etsi_uppertester.etsi_ut_srmssm.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_uppertester_etsi_ut_srmssm_DebugLevel;
  // Cohda_Stack.fac_its.etsi_uppertester.etsi_ut_udp_rx_thr.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_uppertester_etsi_ut_udp_rx_thr_DebugLevel;
  // Cohda_Stack.fac_its.etsi_util.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_util_DebugLevel;
  // Cohda_Stack.fac_its.etsi_cam.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_cam_DebugLevel;
  // Cohda_Stack.fac_its.etsi_cpm.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_cpm_DebugLevel;
  // Cohda_Stack.fac_its.etsi_denm.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_denm_DebugLevel;
  // Cohda_Stack.fac_its.etsi_evcsn.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_evcsn_DebugLevel;
  // Cohda_Stack.fac_its.etsi_imzm.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_imzm_DebugLevel;
  // Cohda_Stack.fac_its.etsi_ivi.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_ivi_DebugLevel;
  // Cohda_Stack.fac_its.etsi_map.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_map_DebugLevel;
  // Cohda_Stack.fac_its.etsi_mcdm.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_mcdm_DebugLevel;
  // Cohda_Stack.fac_its.etsi_msg.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_msg_DebugLevel;
  // Cohda_Stack.fac_its.etsi_pmm.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_pmm_DebugLevel;
  // Cohda_Stack.fac_its.etsi_rtcm.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_rtcm_DebugLevel;
  // Cohda_Stack.fac_its.etsi_sa.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_sa_DebugLevel;
  // Cohda_Stack.fac_its.etsi_spat.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_spat_DebugLevel;
  // Cohda_Stack.fac_its.etsi_srmssm.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_srmssm_DebugLevel;
  // Cohda_Stack.fac_its.etsi_toll.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_toll_DebugLevel;
  // Cohda_Stack.fac_its.etsi_trx.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_trx_DebugLevel;
  // Cohda_Stack.fac_its.etsi_trx.etsi_fac_c2c.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_trx_etsi_fac_c2c_DebugLevel;
  // Cohda_Stack.fac_its.etsi_trx.etsi_trx_action.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_trx_etsi_trx_action_DebugLevel;
  // Cohda_Stack.fac_its.etsi_trx.etsi_trx_thr.DebugLevel
  extern int default_stack_Cohda_Stackfac_itsetsi_trx_etsi_trx_thr_DebugLevel;
  // Cohda_Stack.fac_its.etsi_vam.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_etsi_vam_DebugLevel;
  // Cohda_Stack.fac_its.libitsfacilities.DebugLevel
  extern int default_stack_Cohda_Stackfac_its_libitsfacilities_DebugLevel;
  // Cohda_Stack.fac_its.libitsfacilities.libitsfac_log.DebugLevel
  extern int default_stack_Cohda_Stackfac_itslibitsfacilities_libitsfac_log_DebugLevel;
  // Cohda_Stack.fac_its.libitsfacilities.libitsfac_mgmt.DebugLevel
  extern int default_stack_Cohda_Stackfac_itslibitsfacilities_libitsfac_mgmt_DebugLevel;
  // Cohda_Stack.plat.DebugLevel
  extern int default_stack_Cohda_Stack_plat_DebugLevel;
  // Cohda_Stack.plat.persistence.DebugLevel
  extern int default_stack_Cohda_Stackplat_persistence_DebugLevel;
  // Cohda_Stack.plat.libplat.DebugLevel
  extern int default_stack_Cohda_Stackplat_libplat_DebugLevel;
  // Cohda_Stack.plat.libplat.libplat_mgmt.DebugLevel
  extern int default_stack_Cohda_Stackplatlibplat_libplat_mgmt_DebugLevel;
  // Cohda_Stack.plat.log.log.DebugLevel
  extern int default_stack_Cohda_Stackplatlog_log_DebugLevel;
  // Cohda_Stack.plat.log.log_thr.DebugLevel
  extern int default_stack_Cohda_Stackplatlog_log_thr_DebugLevel;
  // Cohda_Stack.plat.log.log_udp.DebugLevel
  extern int default_stack_Cohda_Stackplatlog_log_udp_DebugLevel;
  // Cohda_Stack.plat.log.pcap_log.DebugLevel
  extern int default_stack_Cohda_Stackplatlog_pcap_log_DebugLevel;
  // Cohda_Stack.plat.log.pcap_raw.DebugLevel
  extern int default_stack_Cohda_Stackplatlog_pcap_raw_DebugLevel;
  // Cohda_Stack.plat.log.sys_log.DebugLevel
  extern int default_stack_Cohda_Stackplatlog_sys_log_DebugLevel;
  // Cohda_Stack.plat.log.tcpdump_log.DebugLevel
  extern int default_stack_Cohda_Stackplatlog_tcpdump_log_DebugLevel;
  // Cohda_Stack.plat.plugin.DebugLevel
  extern int default_stack_Cohda_Stackplat_plugin_DebugLevel;
  // Cohda_Stack.plat.plugin.v2xlib_plugin.DebugLevel
  extern int default_stack_Cohda_Stackplatplugin_v2xlib_plugin_DebugLevel;
  // Cohda_Stack.plat.util.DebugLevel
  extern int default_stack_Cohda_Stackplat_util_DebugLevel;
  // Cohda_Stack.plat.util.Inhibit.DebugLevel
  extern int default_stack_Cohda_Stackplatutil_Inhibit_DebugLevel;
  // Cohda_Stack.plat.util.PacketBuffer.DebugLevel
  extern int default_stack_Cohda_Stackplatutil_PacketBuffer_DebugLevel;
  // Cohda_Stack.plat.util.util.DebugLevel
  extern int default_stack_Cohda_Stackplatutil_util_DebugLevel;
  // Cohda_Stack.plat.util.thread.DebugLevel
  extern int default_stack_Cohda_Stackplatutil_thread_DebugLevel;
  // Cohda_Stack.plat.util.worker.DebugLevel
  extern int default_stack_Cohda_Stackplatutil_worker_DebugLevel;
  // Cohda_Stack.interface.DebugLevel
  extern int default_stack_Cohda_Stack_interface_DebugLevel;
  // Cohda_Stack.interface.aerolink_scms.DebugLevel
  extern int default_stack_Cohda_Stackinterface_aerolink_scms_DebugLevel;
  // Cohda_Stack.fac_1609.DebugLevel
  extern int default_stack_Cohda_Stack_fac_1609_DebugLevel;
  // Cohda_Stack.fac_1609.dot2.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609_dot2_DebugLevel;
  // Cohda_Stack.fac_1609.dot2.dot2.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609dot2_dot2_DebugLevel;
  // Cohda_Stack.fac_1609.dot2.dot2_idchange.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609dot2_dot2_idchange_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609_j2735_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.J2735_BSM.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_J2735_BSM_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j2735_common.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j2735_common_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j2735_dot2.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j2735_dot2_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j2735_full_position_vector.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j2735_full_position_vector_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j2735_map.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j2735_map_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j2735_message.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j2735_message_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j2735_probe_data_management.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j2735_probe_data_management_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j2735_probe_vehicle_data.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j2735_probe_vehicle_data_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j2735_road_side_alert.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j2735_road_side_alert_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j2735_snapshot.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j2735_snapshot_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j2735_spat.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j2735_spat_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j2735_vehicle_safetyextension.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j2735_vehicle_safetyextension_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j2735_vehicle_status.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j2735_vehicle_status_DebugLevel;
  // Cohda_Stack.fac_1609.j2735.j3224_sdsm.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2735_j3224_sdsm_DebugLevel;
  // Cohda_Stack.fac_1609.j2945cc.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609_j2945cc_DebugLevel;
  // Cohda_Stack.fac_1609.j2945cc.j2945cc.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609j2945cc_j2945cc_DebugLevel;
  // Cohda_Stack.fac_1609.p1609_tx.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609_p1609_tx_DebugLevel;
  // Cohda_Stack.fac_1609.p1609_tx.p1609_fac_veh_ctrl.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609p1609_tx_p1609_fac_veh_ctrl_DebugLevel;
  // Cohda_Stack.fac_1609.p1609_tx.p1609_tx_msg.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609p1609_tx_p1609_tx_msg_DebugLevel;
  // Cohda_Stack.fac_1609.p1609_tx.p1609_tx_replay.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609p1609_tx_p1609_tx_replay_DebugLevel;
  // Cohda_Stack.fac_1609.p1609_tx.p1609_tx_thr.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609p1609_tx_p1609_tx_thr_DebugLevel;
  // Cohda_Stack.fac_1609.time.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609_time_DebugLevel;
  // Cohda_Stack.fac_1609.time.time_thr.DebugLevel
  extern int default_stack_Cohda_Stackfac_1609time_time_thr_DebugLevel;
  // Cohda_Stack.net_1609.DebugLevel
  extern int default_stack_Cohda_Stack_net_1609_DebugLevel;
  // Cohda_Stack.net_1609.dot3.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609_dot3_DebugLevel;
  // Cohda_Stack.net_1609.dot3.wsmp.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot3_wsmp_DebugLevel;
  // Cohda_Stack.net_1609.dot3.wsmp.dot3_wsmp.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot3wsmp_dot3_wsmp_DebugLevel;
  // Cohda_Stack.net_1609.dot3.wsmp.dot3_wsmp_proto.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot3wsmp_dot3_wsmp_proto_DebugLevel;
  // Cohda_Stack.net_1609.dot4.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609_dot4_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4_wmac_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_atk_ctrl.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_atk_ctrl_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_atk_rx.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_atk_rx_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_atk_tx.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_atk_tx_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_data_netdev.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_data_netdev_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_eth_ctrl.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_eth_ctrl_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_eth_rx.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_eth_rx_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_eth_tx.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_eth_tx_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_llc_ctrl.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_llc_ctrl_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_llc_rx.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_llc_rx_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_llc_tsf.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_llc_tsf_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_llc_tx.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_llc_tx_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_mgmt_netdev.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_mgmt_netdev_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_qti_ctrl.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_qti_ctrl_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_qti_rx.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_qti_rx_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_qti_tx.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_qti_tx_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_raw_netdev.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_raw_netdev_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_sync_netdev.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_sync_netdev_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_timing.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_timing_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_wmac.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_wmac_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_wmac_ctrl.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_wmac_ctrl_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_wmac_rx.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_wmac_rx_DebugLevel;
  // Cohda_Stack.net_1609.dot4.wmac.dot4_wmac_tx.DebugLevel
  extern int default_stack_Cohda_Stacknet_1609dot4wmac_dot4_wmac_tx_DebugLevel;
  // Cohda_Stack.fac_cn.DebugLevel
  extern int default_stack_Cohda_Stack_fac_cn_DebugLevel;
  // Cohda_Stack.fac_cn.libcnfac.DebugLevel
  extern int default_stack_Cohda_Stackfac_cn_libcnfac_DebugLevel;
  // Cohda_Stack.fac_cn.saec_bsm.DebugLevel
  extern int default_stack_Cohda_Stackfac_cn_saec_bsm_DebugLevel;
  // Cohda_Stack.fac_cn.saec_bsm.saec_bsm.DebugLevel
  extern int default_stack_Cohda_Stackfac_cnsaec_bsm_saec_bsm_DebugLevel;
  // Cohda_Stack.fac_cn.saec_trx.DebugLevel
  extern int default_stack_Cohda_Stackfac_cn_saec_trx_DebugLevel;
  // Cohda_Stack.fac_cn.saec_trx.saec_trx_action.DebugLevel
  extern int default_stack_Cohda_Stackfac_cnsaec_trx_saec_trx_action_DebugLevel;
  // Cohda_Stack.fac_cn.saec_trx.saec_trx_thr.DebugLevel
  extern int default_stack_Cohda_Stackfac_cnsaec_trx_saec_trx_thr_DebugLevel;
  // Cohda_Stack.fac_cn.libsaecsec.DebugLevel
  extern int default_stack_Cohda_Stackfac_cn_libsaecsec_DebugLevel;
  // Cohda_Stack.net_cn.DebugLevel
  extern int default_stack_Cohda_Stack_net_cn_DebugLevel;
  // Cohda_Stack.net_cn.libcnnet.DebugLevel
  extern int default_stack_Cohda_Stacknet_cn_libcnnet_DebugLevel;
  // Cohda_Stack.net_cn.libcnnet.libcnnet_mgmt.DebugLevel
  extern int default_stack_Cohda_Stacknet_cnlibcnnet_libcnnet_mgmt_DebugLevel;
  // Cohda_Stack.net_cn.saec_pc5.DebugLevel
  extern int default_stack_Cohda_Stacknet_cn_saec_pc5_DebugLevel;
  // Cohda_Stack.net_cn.saec_pc5.saec_pc5_qti_ctrl.DebugLevel
  extern int default_stack_Cohda_Stacknet_cnsaec_pc5_saec_pc5_qti_ctrl_DebugLevel;
  // Cohda_Stack.net_cn.saec_pc5.saec_pc5_qti_rx.DebugLevel
  extern int default_stack_Cohda_Stacknet_cnsaec_pc5_saec_pc5_qti_rx_DebugLevel;
  // Cohda_Stack.net_cn.saec_pc5.saec_pc5_qti_tx.DebugLevel
  extern int default_stack_Cohda_Stacknet_cnsaec_pc5_saec_pc5_qti_tx_DebugLevel;
  // Cohda_Stack.sensors.DebugLevel
  extern int default_stack_Cohda_Stack_sensors_DebugLevel;
  // Cohda_Stack.sensors.can_ipc.DebugLevel
  extern int default_stack_Cohda_Stacksensors_can_ipc_DebugLevel;
  // Cohda_Stack.sensors.can_ipc.can_ipc.DebugLevel
  extern int default_stack_Cohda_Stacksensorscan_ipc_can_ipc_DebugLevel;
  // Cohda_Stack.sensors.can_rx.DebugLevel
  extern int default_stack_Cohda_Stacksensors_can_rx_DebugLevel;
  // Cohda_Stack.sensors.can_rx.can_rx_thr.DebugLevel
  extern int default_stack_Cohda_Stacksensorscan_rx_can_rx_thr_DebugLevel;
  // Cohda_Stack.sensors.can_vsc3.DebugLevel
  extern int default_stack_Cohda_Stacksensors_can_vsc3_DebugLevel;
  // Cohda_Stack.sensors.can_vsc3.can_vsc3.DebugLevel
  extern int default_stack_Cohda_Stacksensorscan_vsc3_can_vsc3_DebugLevel;
  // Cohda_Stack.sensors.can_vsc3.vsc3obe.DebugLevel
  extern int default_stack_Cohda_Stacksensorscan_vsc3_vsc3obe_DebugLevel;
  // Cohda_Stack.sensors.gps_rx.DebugLevel
  extern int default_stack_Cohda_Stacksensors_gps_rx_DebugLevel;
  // Cohda_Stack.sensors.gps_rx.gps_rx_fake.DebugLevel
  extern int default_stack_Cohda_Stacksensorsgps_rx_gps_rx_fake_DebugLevel;
  // Cohda_Stack.sensors.gps_rx.gps_rx_fixed.DebugLevel
  extern int default_stack_Cohda_Stacksensorsgps_rx_gps_rx_fixed_DebugLevel;
  // Cohda_Stack.sensors.gps_rx.gps_rx_gpsd.DebugLevel
  extern int default_stack_Cohda_Stacksensorsgps_rx_gps_rx_gpsd_DebugLevel;
  // Cohda_Stack.sensors.gps_rx.gps_rx_qti.DebugLevel
  extern int default_stack_Cohda_Stacksensorsgps_rx_gps_rx_qti_DebugLevel;
  // Cohda_Stack.sensors.gps_rx.gps_rx_replay.DebugLevel
  extern int default_stack_Cohda_Stacksensorsgps_rx_gps_rx_replay_DebugLevel;
  // Cohda_Stack.sensors.gps_rx.gps_rx_thr.DebugLevel
  extern int default_stack_Cohda_Stacksensorsgps_rx_gps_rx_thr_DebugLevel;
  // Cohda_Stack.sensors.tim.DebugLevel
  extern int default_stack_Cohda_Stacksensors_tim_DebugLevel;
  // Cohda_Stack.sensors.tim.tim.DebugLevel
  extern int default_stack_Cohda_Stacksensorstim_tim_DebugLevel;
  // Cohda_Stack.sensors.tim.tim_region.DebugLevel
  extern int default_stack_Cohda_Stacksensorstim_tim_region_DebugLevel;
  // Cohda_Stack.sensors.ivi.DebugLevel
  extern int default_stack_Cohda_Stacksensors_ivi_DebugLevel;
  // Cohda_Stack.sensors.ivi.ivi.DebugLevel
  extern int default_stack_Cohda_Stacksensorsivi_ivi_DebugLevel;
  // Cohda_Stack.sensors.rsicn.DebugLevel
  extern int default_stack_Cohda_Stacksensors_rsicn_DebugLevel;
  // Cohda_Stack.sensors.rsicn.rsicn.DebugLevel
  extern int default_stack_Cohda_Stacksensorsrsicn_rsicn_DebugLevel;
  // Cohda_Stack.sensors.rsicn.rsicn_region.DebugLevel
  extern int default_stack_Cohda_Stacksensorsrsicn_rsicn_region_DebugLevel;
  // Cohda_SPATMAP.DebugLevel
  extern int default_stack_Cohda_SPATMAP_DebugLevel;
  // Cohda_SPATMAP.spat_cn_rx.DebugLevel
  extern int default_stack_Cohda_SPATMAP_spat_cn_rx_DebugLevel;
  // Cohda_SPATMAP.spat_rx.DebugLevel
  extern int default_stack_Cohda_SPATMAP_spat_rx_DebugLevel;
  // Cohda_SPATMAP.spat_utils.DebugLevel
  extern int default_stack_Cohda_SPATMAP_spat_utils_DebugLevel;
  // Cohda_TC.DebugLevel
  extern int default_stack_Cohda_TC_DebugLevel;
  // Cohda_TC.TC.DebugLevel
  extern int default_stack_Cohda_TC_TC_DebugLevel;
  // Cohda_TC.TC_Classify.DebugLevel
  extern int default_stack_Cohda_TC_TC_Classify_DebugLevel;
  // Cohda_TC.TC_ETSI.DebugLevel
  extern int default_stack_Cohda_TC_TC_ETSI_DebugLevel;
  // Cohda_TC.TC_Ext.DebugLevel
  extern int default_stack_Cohda_TC_TC_Ext_DebugLevel;
  // Cohda_TC.TC_J2735.DebugLevel
  extern int default_stack_Cohda_TC_TC_J2735_DebugLevel;
  // Cohda_TC.TC_SAEC.DebugLevel
  extern int default_stack_Cohda_TC_TC_SAEC_DebugLevel;
  // Cohda_TC.TC_J3224.DebugLevel
  extern int default_stack_Cohda_TC_TC_J3224_DebugLevel;
  // Cohda_TC.TC_Remote.DebugLevel
  extern int default_stack_Cohda_TC_TC_Remote_DebugLevel;
  // Cohda_TC.TC_Thread.DebugLevel
  extern int default_stack_Cohda_TC_TC_Thread_DebugLevel;
  // Cohda_TC.TC_Util.DebugLevel
  extern int default_stack_Cohda_TC_TC_Util_DebugLevel;
  // Cohda_LDM.DebugLevel
  extern int default_stack_Cohda_LDM_DebugLevel;
  // Cohda_LDM.ldm.DebugLevel
  extern int default_stack_Cohda_LDM_ldm_DebugLevel;
  // Cohda_LDM.ldm_online_backup.DebugLevel
  extern int default_stack_Cohda_LDM_ldm_online_backup_DebugLevel;
  // Cohda_LDM.ldm_sql.DebugLevel
  extern int default_stack_Cohda_LDM_ldm_sql_DebugLevel;
  // Cohda_LDM.ldm_thread.DebugLevel
  extern int default_stack_Cohda_LDM_ldm_thread_DebugLevel;
  // Cohda_App_UAVD.DebugLevel
  extern int default_stack_Cohda_App_UAVD_DebugLevel;
  // Cohda_App_VTRW.DebugLevel
  extern int default_stack_Cohda_App_VTRW_DebugLevel;
  // Cohda_App_VTRW.Rx.DebugLevel
  extern int default_stack_Cohda_App_VTRW_Rx_DebugLevel;
  // Cohda_App_PCW.DebugLevel
  extern int default_stack_Cohda_App_PCW_DebugLevel;
  // Cohda_App_PCW.PCW.DebugLevel
  extern int default_stack_Cohda_App_PCW_PCW_DebugLevel;
  // Cohda_App_PCW.PCW_rx.DebugLevel
  extern int default_stack_Cohda_App_PCW_PCW_rx_DebugLevel;
  // Cohda_App_MAW.DebugLevel
  extern int default_stack_Cohda_App_MAW_DebugLevel;
  // Cohda_App_MAW.MAW.DebugLevel
  extern int default_stack_Cohda_App_MAW_MAW_DebugLevel;
  // Cohda_App_MAW.MAW_rx.DebugLevel
  extern int default_stack_Cohda_App_MAW_MAW_rx_DebugLevel;
  // Cohda_TA.DebugLevel
  extern int default_stack_Cohda_TA_DebugLevel;
  // Cohda_TA.ADR.DebugLevel
  extern int default_stack_Cohda_TA_ADR_DebugLevel;
  // Cohda_TA.ADR.JSON.DebugLevel
  extern int default_stack_Cohda_TAADR_JSON_DebugLevel;
  // Cohda_TA.Map.DebugLevel
  extern int default_stack_Cohda_TA_Map_DebugLevel;
  // Cohda_TA.Replay.DebugLevel
  extern int default_stack_Cohda_TA_Replay_DebugLevel;
  // Cohda_TA.Threat.DebugLevel
  extern int default_stack_Cohda_TA_Threat_DebugLevel;
  // Cohda_TA.Utils.DebugLevel
  extern int default_stack_Cohda_TA_Utils_DebugLevel;
  // Cohda_GeoFence.DebugLevel
  extern int default_stack_Cohda_GeoFence_DebugLevel;
  // Cohda_GeoFence.main.DebugLevel
  extern int default_stack_Cohda_GeoFence_main_DebugLevel;
  // Cohda_GeoFence.read.DebugLevel
  extern int default_stack_Cohda_GeoFence_read_DebugLevel;
  // Cohda_GeoFence.ray.DebugLevel
  extern int default_stack_Cohda_GeoFence_ray_DebugLevel;

#ifdef __cplusplus
}
#endif
