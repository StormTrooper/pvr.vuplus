#pragma once

#include <string>

#include "BaseEntry.h"

namespace enigma2
{
  namespace data
  {
    class EpgPartialEntry : public BaseEntry
    {
      public:
        unsigned int GetEpgUid() const { return m_epgUid; }
        void SetEpgUid(unsigned int value) { m_epgUid = value; }

        bool EntryFound() const { return m_epgUid != 0; };

      private:
        unsigned int m_epgUid;
    };
  } //namespace data
} //namespace enigma2