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

#include "ModplugCodec.h"
#include "utils/URIUtils.h"
#include "filesystem/File.h"
#include "utils/log.h"
#include "utils/StringUtils.h"
#include <cstdlib>
#include <cstdio>

using namespace XFILE;

ModplugCodec::ModplugCodec()
{
  m_CodecName = "mod";
  m_module = NULL;
}

ModplugCodec::~ModplugCodec()
{
  DeInit();
}

bool ModplugCodec::Init(const std::string &strFile, unsigned int filecache)
{
  DeInit();

  if (!m_dll.Load())
    return false;

  // set correct codec name
  m_CodecName = URIUtils::GetExtension(strFile);
  StringUtils::TrimLeft(m_CodecName, ".");
  StringUtils::ToUpper(m_CodecName);

  // Read our file to memory so it can be passed to ModPlug_Load()
  CFile file;
  XFILE::auto_buffer buf;
  if (file.LoadFile(strFile, buf) <= 0)
  {
    CLog::Log(LOGERROR,"ModplugCodec: error opening file %s!",strFile.c_str());
    return false;
  }
  // Now load the module
  m_module = m_dll.ModPlug_Load(buf.get(),buf.size());
  if (!m_module)
  {
    CLog::Log(LOGERROR,"ModplugCodec: error loading module file %s!",strFile.c_str());
    return false;
  }
  m_Channels = 2;
  m_SampleRate = 44100;
  m_BitsPerSample = 16;
  m_DataFormat = AE_FMT_S16NE;
  m_TotalTime = (int64_t)(m_dll.ModPlug_GetLength(m_module));

  return true;
}

void ModplugCodec::DeInit()
{
  if (m_module)
    m_dll.ModPlug_Unload(m_module);
  m_module = NULL;
}

int64_t ModplugCodec::Seek(int64_t iSeekTime)
{
  m_dll.ModPlug_Seek(m_module, (int)iSeekTime);
  return iSeekTime;
}

int ModplugCodec::ReadPCM(BYTE *pBuffer, int size, int *actualsize)
{
  if (!m_module)
    return READ_ERROR;

  if ((*actualsize = m_dll.ModPlug_Read(m_module, pBuffer, size)) == size)
    return READ_SUCCESS;
  
  return READ_ERROR;
}

bool ModplugCodec::CanInit()
{
  return m_dll.CanLoad();
}
