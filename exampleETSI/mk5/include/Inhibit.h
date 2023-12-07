#pragma once
/**
 * @addtogroup util_inhibit Inhibit RX and TX
 * @{
 * 
 * Inhibit RX and TX at the network layer
 *
 * @file
 *
 */

//-------------------------------------------------
// Copyright (c) 2020 Cohda Wireless Pty Ltd
//-------------------------------------------------

#ifndef __PLAT_UTIL_INHIBIT_H_
#define __PLAT_UTIL_INHIBIT_H_

//-----------------------
// Included headers
//-----------------------

#include <stdbool.h>

#ifdef __cplusplus
#include <map>
#include <string>
extern "C"
{
#endif

  //-----------------------
  // Function Prototypes
  //-----------------------

  /**
   * @brief Prototype for Network Layer helper.
   *
   * @param TxDisable true if TX is to be disabled.
   * @param RxDisable trie if RX is to be disabled.
   */
  typedef void (fPLAT_TxRxDisable)(bool TxDisable, bool RxDisable);

  /**
   * @brief Set Network Layer helper.
   *
   * @param pPLAT_TxRxDisable fPLAT_TxRxDisable
   */
  void PLAT_SetTxRxDisable(fPLAT_TxRxDisable * pPLAT_TxRxDisable);

  /**
   * @brief Inhibt RX.
   *
   * @param pWhy Reason (for logging and accounting).
   *
   * @return RX inhibit count
   */
  int PLAT_AddRxInhibit(const char * pWhy);

  /**
   * @brief Inhibit TX.
   *
   * @param pWhy pWhy Reason (for logging and accounting).
   *
   * @return TX inhibit count
   */
  int PLAT_AddTxInhibit(const char * pWhy);

  /**
   * @brief Reduce RX Inhibit.
   *
   * @note the "pWhy" reason MUST match a previous @ref PLAT_AddRxInhibit invocation.
   *
   * @param pWhy pWhy Reason (for logging and accounting).
   *
   * @return RX inhibit count
   */
  int PLAT_SubRxInhibit(const char * pWhy);

  /**
   * @brief Reduce TX Inhibit.
   *
   * @note the "pWhy" reason MUST match a previous @ref PLAT_AddTxInhibit invocation.
   *
   * @param pWhy pWhy Reason (for logging and accounting).
   *
   * @return TX inhibit count
   */
  int PLAT_SubTxInhibit(const char * pWhy);

  /**
   * @brief Return current RX inhibit level.
   *
   * @return 0 if uninhibited, else inhibit counter.
   */
  unsigned PLAT_GetRxInhibit(void);

  /**
   * @brief Return current TX inhibit level.
   *
   * @return 0 if uninhibited, else inhibit counter.
   */
  unsigned PLAT_GetTxInhibit(void);

#ifdef __cplusplus
}
/**
 * @brief Retrieve inhibit reasons
 *
 * @param RxReasons why RX is (potentially) inhibited.
 * @param TxReasons why TX is (potentially) inhibited.
 */
void PLAT_Reasons(std::map<std::string, int> & RxReasons,
                  std::map<std::string, int> & TxReasons);
#endif

#endif // __PLAT_UTIL_INHIBIT_H_

/**
 * @}
 */
