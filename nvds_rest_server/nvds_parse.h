/*
 * SPDX-FileCopyrightText: Copyright (c) 2022-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef _NVDS_PARSE_H_
#define _NVDS_PARSE_H_

#include <json/json.h>

bool nvds_rest_roi_parse (const Json::Value & in, NvDsRoiInfo * roi_info);
bool nvds_rest_dec_parse (const Json::Value & in, NvDsDecInfo * dec_info);
bool nvds_rest_enc_parse (const Json::Value & in, NvDsEncInfo * enc_info);
bool nvds_rest_conv_parse (const Json::Value & in, NvDsConvInfo * conv_info);
bool nvds_rest_mux_parse (const Json::Value & in, NvDsMuxInfo * mux_info);
bool nvds_rest_inferserver_parse (const Json::Value & in,
    NvDsInferServerInfo * inferserver_info);
bool nvds_rest_stream_parse (const Json::Value & in,
    NvDsStreamInfo * stream_info);
bool nvds_rest_infer_parse (const Json::Value & in, NvDsInferInfo * infer_info);
bool nvds_rest_osd_parse (const Json::Value & in, NvDsOsdInfo * osd_info);
bool nvds_rest_analytics_parse (const Json::Value & in, NvDsAnalyticsInfo * analytics_info);
bool nvds_rest_app_instance_parse (const Json::Value & in,
    NvDsAppInstanceInfo * appinstance_info);

#endif
