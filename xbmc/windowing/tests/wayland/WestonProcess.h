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
#include "system.h"

#include <boost/noncopyable.hpp>

#ifdef UNICODE
  typedef CStdStringW        CStdString;
#else
  typedef CStdStringA        CStdString;
#endif

typedef int32_t pid_t;

namespace xbmc
{
namespace test
{
class Process :
  boost::noncopyable
{
public:

  Process(const CStdString &base,
          const CStdString &socket);
  ~Process();

  void WaitForSignal(int signal, int timeout);
  void WaitForStatus(int status, int timeout);

  void Interrupt();
  void Terminate();
  void Kill();
  
  pid_t Pid();
  
  static const int DefaultProcessWaitTimeout = 3000; // 3000ms

private:
  
  void SendSignal(int signal);
  
  void Child(const char *program,
             char * const *options);
  void ForkError();
  void Parent();
  
  pid_t m_pid;
};
}
}
