// -*- Mode:c++ -*-
#pragma once
//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#include "Upgrade_defn.h"

#include <memory>
#include <mutex>
#include <string>

namespace cw
{
namespace Upgrade
{

  class Params
  {
  public:
    Params() = delete;
    Params(const Params &) = delete;
    Params(const tCohda_App_Upgrade & Upgrade);
    static std::shared_ptr<Params> Get();
    static void Flush();
    const std::string ServerList;
    const std::string Username;
    const std::string Password;
    const std::string SourceListFile;
    const std::string Packages;
    const std::string Pattern;
    const int32_t DebugLevel;
    const bool ENABLE;
    const bool ACTIVE;
    const bool PingRequired;

  private:
    static std::mutex Mutex;
    static std::shared_ptr<Params> LastPtr;
    static const tCohda_App_Upgrade *  pLastPtr;
  };
}
}
