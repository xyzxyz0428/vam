#pragma once
//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#include "Sync_defn.h"

namespace cw
{
namespace Sync
{
  class Conf
  {
  public:
    Conf()
      {
        pConf = Sync_Get();
      };
    virtual ~Conf()
      {
        Sync_Release(&pConf);
      };
    bool CheckCRC(uint64_t CRC = Sync_CRC)
      {
        return Sync_CheckCRC(CRC);
      };
    void Update(void)
      {
        Sync_Release(&pConf);
        pConf = Sync_Get();
      };
    operator const tCohda_App_Sync & () const
      {
        return *pConf;
      };
  private:
    const tCohda_App_Sync *pConf;
  };
}
}
