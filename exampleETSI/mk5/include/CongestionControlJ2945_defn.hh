#pragma once
//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#include "CongestionControlJ2945_defn.h"

namespace cw
{
namespace CongestionControlJ2945
{
  class Conf
  {
  public:
    Conf()
      {
        pConf = CongestionControlJ2945_Get();
      };
    virtual ~Conf()
      {
        CongestionControlJ2945_Release(&pConf);
      };
    bool CheckCRC(uint64_t CRC = CongestionControlJ2945_CRC)
      {
        return CongestionControlJ2945_CheckCRC(CRC);
      };
    void Update(void)
      {
        CongestionControlJ2945_Release(&pConf);
        pConf = CongestionControlJ2945_Get();
      };
    operator const tCohda_App_CongestionControlJ2945 & () const
      {
        return *pConf;
      };
  private:
    const tCohda_App_CongestionControlJ2945 *pConf;
  };
}
}
