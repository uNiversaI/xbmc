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

#include "cores/AudioEngine/Utils/AEChannelInfo.h"
#include "cores/AudioEngine/Utils/AEAudioFormat.h"
#include "cores/AudioEngine/Engines/ActiveAE/ActiveAEBuffer.h"
#include "cores/AudioEngine/Interfaces/AE.h"

extern "C" {
#include "libavutil/avutil.h"
#include "libswresample/swresample.h"
}

namespace ActiveAE
{

class CActiveAEResample
{
public:
  CActiveAEResample();
  virtual ~CActiveAEResample();
  bool Init(uint64_t dst_chan_layout, int dst_channels, int dst_rate, AVSampleFormat dst_fmt, int dst_bits, int dst_dither, uint64_t src_chan_layout, int src_channels, int src_rate, AVSampleFormat src_fmt, int src_bits, int src_dither, bool upmix, bool normalize, CAEChannelInfo *remapLayout, AEQuality quality);
  int Resample(uint8_t **dst_buffer, int dst_samples, uint8_t **src_buffer, int src_samples, double ratio);
  int64_t GetDelay(int64_t base);
  int GetBufferedSamples();
  int CalcDstSampleCount(int src_samples, int dst_rate, int src_rate);
  int GetSrcBufferSize(int samples);
  int GetDstBufferSize(int samples);
  static uint64_t GetAVChannelLayout(CAEChannelInfo &info);
//  static CAEChannelInfo GetAEChannelLayout(uint64_t layout);
  static AVSampleFormat GetAVSampleFormat(AEDataFormat format);
  static uint64_t GetAVChannel(enum AEChannel aechannel);
  int GetAVChannelIndex(enum AEChannel aechannel, uint64_t layout);

protected:
  bool m_loaded;
  uint64_t m_src_chan_layout, m_dst_chan_layout;
  int m_src_rate, m_dst_rate;
  int m_src_channels, m_dst_channels;
  AVSampleFormat m_src_fmt, m_dst_fmt;
  int m_src_bits, m_dst_bits;
  int m_src_dither_bits, m_dst_dither_bits;
  SwrContext *m_pContext;
  double m_rematrix[AE_CH_MAX][AE_CH_MAX];
};

}
