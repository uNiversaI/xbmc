#pragma once

/*
 *      Copyright (C) 2005-2014 Team Kodi
 *      http://kodi.tv
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
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "GUIWindowPVRBase.h"
#include "video/VideoThumbLoader.h"
#include "video/VideoDatabase.h"

namespace PVR
{
  class CGUIWindowPVRRecordings : public CGUIWindowPVRBase
  {
  public:
    CGUIWindowPVRRecordings(bool bRadio);
    virtual ~CGUIWindowPVRRecordings(void) {};

    static std::string GetResumeString(const CFileItem& item);

    void OnWindowLoaded();
    bool OnMessage(CGUIMessage& message);
    bool OnAction(const CAction &action);
    void GetContextButtons(int itemNumber, CContextButtons &buttons);
    bool OnContextButton(int itemNumber, CONTEXT_BUTTON button);
    bool Update(const std::string &strDirectory, bool updateFilterPath = true);
    void UnregisterObservers(void);
    void ResetObservers(void);

  protected:
    std::string GetDirectoryPath(void);
    void OnPrepareFileItems(CFileItemList &items);

  private:
    bool OnContextButtonDelete(CFileItem *item, CONTEXT_BUTTON button);
    bool OnContextButtonInfo(CFileItem *item, CONTEXT_BUTTON button);
    bool OnContextButtonPlay(CFileItem *item, CONTEXT_BUTTON button);
    bool OnContextButtonRename(CFileItem *item, CONTEXT_BUTTON button);
    bool OnContextButtonMarkWatched(const CFileItemPtr &item, CONTEXT_BUTTON button);

    CVideoThumbLoader m_thumbLoader;
    CVideoDatabase m_database;
  };
}
