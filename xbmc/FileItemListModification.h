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

#include <set>

#include "IFileItemListModifier.h"

class CFileItemListModification : public IFileItemListModifier
{
public:
  ~CFileItemListModification();

  static CFileItemListModification& Get();

  virtual bool CanModify(const CFileItemList &items) const;
  virtual bool Modify(CFileItemList &items) const;

private:
  CFileItemListModification();
  CFileItemListModification(const CFileItemListModification&);
  CFileItemListModification const& operator=(CFileItemListModification const&);

  std::set<IFileItemListModifier*> m_modifiers;
};
