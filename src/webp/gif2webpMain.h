// Copyright 2012 Google Inc. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license
// that can be found in the COPYING file in the root of the source
// tree. An additional intellectual property rights grant can be found
// in the file PATENTS. All contributing project authors may
// be found in the AUTHORS file in the root of the source tree.
// -----------------------------------------------------------------------------
//
//  simple tool to convert animated GIFs to WebP
//
// Authors: Skal (pascal.massimino@gmail.com)
//          Urvang (urvang@google.com)

#ifndef GIF_2_WEBP_MAIN_H_
#define GIF_2_WEBP_MAIN_H_

#include "webp/mux.h"

int convert (int argc, const char *argv[], char* data, int length, WebPData* outputData);

#endif
