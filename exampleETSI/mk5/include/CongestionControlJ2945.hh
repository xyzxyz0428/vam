// -*- Mode:c++ -*-
#pragma once
//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#include "CongestionControlJ2945_defn.h"

#include <memory>
#include <mutex>
#include <string>

namespace cw
{
namespace CongestionControlJ2945
{

  class Params
  {
  public:
    Params() = delete;
    Params(const Params &) = delete;
    Params(const tCohda_App_CongestionControlJ2945 & CongestionControlJ2945);
    static std::shared_ptr<Params> Get();
    static void Flush();
    const int32_t DebugLevel;
    const bool ENABLE;

  private:
    static std::mutex Mutex;
    static std::shared_ptr<Params> LastPtr;
    static const tCohda_App_CongestionControlJ2945 *  pLastPtr;
  };
}
}
