#pragma once
//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#include "Upgrade_defn.h"

namespace cw
{
namespace Upgrade
{
  class Conf
  {
  public:
    Conf()
      {
        pConf = Upgrade_Get();
      };
    virtual ~Conf()
      {
        Upgrade_Release(&pConf);
      };
    bool CheckCRC(uint64_t CRC = Upgrade_CRC)
      {
        return Upgrade_CheckCRC(CRC);
      };
    void Update(void)
      {
        Upgrade_Release(&pConf);
        pConf = Upgrade_Get();
      };
    operator const tCohda_App_Upgrade & () const
      {
        return *pConf;
      };
  private:
    const tCohda_App_Upgrade *pConf;
  };
}
}
