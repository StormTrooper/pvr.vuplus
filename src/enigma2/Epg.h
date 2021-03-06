#pragma once
/*
 *      Copyright (C) 2005-2015 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1335, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Channels.h"
#include "ChannelGroups.h"
#include "data/EpgPartialEntry.h"
#include "data/EpgChannel.h"
#include "extract/EpgEntryExtractor.h"

#include "libXBMC_pvr.h"

#include "p8-platform/threads/threads.h"

namespace enigma2
{
  static const float LAST_SCANNED_INITIAL_EPG_SUCCESS_PERCENT = 0.99f;

  class Epg
  {
  public:
    Epg(enigma2::extract::EpgEntryExtractor &entryExtractor);
    Epg(const enigma2::Epg& epg);

    bool Initialise(enigma2::Channels &channels, enigma2::ChannelGroups &channelGroups);
    bool IsInitialEpgCompleted();
    void TriggerEpgUpdatesForChannels();
    void MarkChannelAsInitialEpgRead(const std::string &serviceReference);
    PVR_ERROR GetEPGForChannel(ADDON_HANDLE handle, const std::string &serviceReference, time_t iStart, time_t iEnd);
    std::string LoadEPGEntryShortDescription(const std::string &serviceReference, unsigned int epgUid);
    data::EpgPartialEntry LoadEPGEntryPartialDetails(const std::string &serviceReference, time_t startTime);
    data::EpgPartialEntry LoadEPGEntryPartialDetails(const std::string &serviceReference, unsigned int epgUid);

  private:
    PVR_ERROR TransferInitialEPGForChannel(ADDON_HANDLE handle, const std::shared_ptr<data::EpgChannel> &epgChannel, time_t iStart, time_t iEnd);
    std::shared_ptr<data::EpgChannel> GetEpgChannel(const std::string &serviceReference);
    bool LoadInitialEPGForGroup(const std::shared_ptr<enigma2::data::ChannelGroup> group);
    bool ChannelNeedsInitialEpg(const std::string &serviceReference);
    bool InitialEpgLoadedForChannel(const std::string &serviceReference);
    bool InitialEpgReadForChannel(const std::string &serviceReference);
    std::shared_ptr<data::EpgChannel> GetEpgChannelNeedingInitialEpg(const std::string &serviceReference);

    enigma2::extract::EpgEntryExtractor &m_entryExtractor;

    bool m_initialEpgReady = false;

    std::vector<std::shared_ptr<data::EpgChannel>> m_epgChannels;
    std::map<std::string, std::shared_ptr<data::EpgChannel>> m_epgChannelsMap;
    std::map<std::string, std::shared_ptr<data::EpgChannel>> m_readInitialEpgChannelsMap;
    std::map<std::string, std::shared_ptr<data::EpgChannel>> m_needsInitialEpgChannelsMap;
  };
} //namespace enigma2