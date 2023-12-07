// -*- Mode:c++ -*-
#pragma once
//------------------------------------------------------------------------------
// Copyright (c) 2021 Cohda Wireless Pty Ltd
//-----------------------------------------------------------------------------

#include "Sync_defn.h"

#include <memory>
#include <mutex>
#include <string>

namespace cw
{
namespace Sync
{

  class Params
  {
  public:
    Params() = delete;
    Params(const Params &) = delete;
    Params(const tCohda_App_Sync & Sync);
    static std::shared_ptr<Params> Get();
    static void Flush();
    const std::string RSyncWrapper;
    const std::string RSyncOptions;
    const std::string ServerAddress;
    const std::string UploadSrcPath;
    const std::string UploadDstPath;
    const std::string DownloadSrcPath;
    const std::string DownloadDstPath;
    const std::string ExtUpSrcPath;
    const std::string ExtUpDstPath;
    const std::string ExtWrapper;
    const std::string ExtOptions;
    const std::string ExtUsername;
    const int32_t DebugLevel;
    const uint32_t PSID;
    const int32_t Period_m;
    const bool Enable;
    const bool ExternalDevice;

  private:
    static std::mutex Mutex;
    static std::shared_ptr<Params> LastPtr;
    static const tCohda_App_Sync *  pLastPtr;
  };
}
}
