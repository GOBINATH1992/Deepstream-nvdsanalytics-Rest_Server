/*
 * SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#include "nvds_rest_server.h"
#include "nvds_parse.h"

#define EMPTY_STRING ""


bool
nvds_rest_analytics_parse (const Json::Value & in, NvDsAnalyticsInfo * analytics_info)
{

  for (Json::ValueConstIterator it = in.begin (); it != in.end (); ++it) {

    std::string root_val = it.key ().asString ().c_str ();
    analytics_info->root_key = root_val;

    const Json::Value sub_root_val = in[root_val];      //object values of root_key

    analytics_info->stream_id = sub_root_val.get ("stream_id", 0).asUInt ();
    
    analytics_info->roi_count = sub_root_val.get ("roi_count", 0).asUInt ();
    
    analytics_info->line_count = sub_root_val.get ("line_count", 0).asUInt ();
    
    if (analytics_info->roi_count == 0 && analytics_info->line_count == 0) {
      analytics_info->analytics_log = "roi id and line id is 0";
      analytics_info->status = ANALYTICS_UPDATE_FAIL;
    }
    
    const Json::Value roi_arr = sub_root_val.get ("roi", EMPTY_STRING);
    
    const Json::Value line_arr = sub_root_val.get ("line", EMPTY_STRING);
    
    if (roi_arr == "" && line_arr == "" ) {
      analytics_info->analytics_log = "roi and  line is empty";
      analytics_info->status = ANALYTICS_UPDATE_FAIL;
    }

    for (guint i = 0; i < roi_arr.size (); i++) {
      RoiInfo roi_info;

      g_strlcpy (roi_info.pts, roi_arr[i]["pts"].asString ().c_str (),
          sizeof (roi_info.pts));
      g_strlcpy (roi_info.label, roi_arr[i]["label"].asString ().c_str (),
          sizeof (roi_info.label));
      g_strlcpy (roi_info.class_id, roi_arr[i]["class_id"].asString ().c_str (),
          sizeof (roi_info.class_id));
          
      roi_info.enable = roi_arr[i]["enable"].asBool();
      roi_info.inverse_roi = roi_arr[i]["inverse_roi"].asBool();
      
      
      roi_info.stream_id = roi_arr[i]["stream_id"].asUInt ();
      
      
      analytics_info->roi_vect.push_back (roi_info);
    }
    
    
    for (guint i = 0; i < line_arr.size (); i++) {
      LineInfo line_info;

      g_strlcpy (line_info.pts, line_arr[i]["pts"].asString ().c_str (),
          sizeof (line_info.pts));
      g_strlcpy (line_info.label, line_arr[i]["label"].asString ().c_str (),
          sizeof (line_info.label));
      g_strlcpy (line_info.class_id, line_arr[i]["class_id"].asString ().c_str (),
          sizeof (line_info.class_id));
      
      g_strlcpy (line_info.mode, line_arr[i]["mode"].asString ().c_str (),
          sizeof (line_info.mode));
          
      line_info.enable = line_arr[i]["enable"].asBool();
      line_info.extended = line_arr[i]["extended"].asBool();
      
      
      line_info.stream_id = line_arr[i]["stream_id"].asUInt ();
      
      
      analytics_info->line_vect.push_back (line_info);
    }
    
  }

  return true;
}

/*
bool
nvds_rest_analytics_parse (const Json::Value & in, NvDsAnalyticsInfo * analytics_info)
{

  for (Json::ValueConstIterator it = in.begin (); it != in.end (); ++it) {

    std::string root_val = it.key ().asString ().c_str ();
    analytics_info->root_key = root_val;

    const Json::Value sub_root_val = in[root_val];      //object values of root_key

    analytics_info->stream_id =
        sub_root_val.get ("stream_id", EMPTY_STRING).asString ().c_str ();

    if (analytics_info->analytics_flag == RESET_MODE) {
      analytics_info->reset_mode = sub_root_val.get ("reset_mode", 0).asInt ();
    }
  }

  return true;
}
*/