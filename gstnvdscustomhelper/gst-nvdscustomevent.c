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

#include "gst-nvdscustomevent.h"

GstEvent *
gst_nvevent_new_roi_update (gchar * stream_id, guint roi_count,
    RoiDimension * roi_dim)
{
  GstStructure *str = gst_structure_new_empty ("nv-roi-update");

  gst_structure_set (str, "stream_id", G_TYPE_STRING, stream_id,
      "roi-count", G_TYPE_UINT, roi_count, NULL);

  for (int i = 0; i < (int) roi_count; i++) {
    char key[128];
    g_snprintf (key, sizeof (key), "roi_id_%d", i);
    gst_structure_set (str, key, G_TYPE_STRING, (char *) roi_dim[i].roi_id,
        NULL);
    g_snprintf (key, sizeof (key), "left_%d", i);
    gst_structure_set (str, key, G_TYPE_UINT, roi_dim[i].left, NULL);
    g_snprintf (key, sizeof (key), "top_%d", i);
    gst_structure_set (str, key, G_TYPE_UINT, roi_dim[i].top, NULL);
    g_snprintf (key, sizeof (key), "width_%d", i);
    gst_structure_set (str, key, G_TYPE_UINT, roi_dim[i].width, NULL);
    g_snprintf (key, sizeof (key), "height_%d", i);
    gst_structure_set (str, key, G_TYPE_UINT, roi_dim[i].height, NULL);
  }

  return gst_event_new_custom ((GstEventType) GST_NVEVENT_ROI_UPDATE, str);
}

GstEvent *
gst_nvevent_infer_interval_update (gchar * stream_id, guint interval)
{
  GstStructure *str = gst_structure_new_empty ("nv-infer-interval-update");

  gst_structure_set (str, "stream_id", G_TYPE_STRING, stream_id,
      "interval", G_TYPE_UINT, interval, NULL);

  return gst_event_new_custom ((GstEventType) GST_NVEVENT_INFER_INTERVAL_UPDATE,
      str);
}


void
gst_nvevent_parse_roi_update (GstEvent * event, gchar ** stream_id,
    guint * roi_count, RoiDimension ** roi_dim)
{
  if ((GstEventType) GST_NVEVENT_ROI_UPDATE == GST_EVENT_TYPE (event)) {

    const GstStructure *str = gst_event_get_structure (event);

    gst_structure_get (str, "stream_id", G_TYPE_STRING, stream_id,
        "roi-count", G_TYPE_UINT, roi_count, NULL);

    *roi_dim = (RoiDimension *) g_malloc (sizeof (RoiDimension) * (*roi_count));

    for (int i = 0; i < (int) *roi_count; i++) {

      char key[128];
      gchar *roi_id;
      g_snprintf (key, sizeof (key), "roi_id_%d", i);
      gst_structure_get (str, key, G_TYPE_STRING, &(roi_id), NULL);
      g_strlcpy (((*roi_dim)[i].roi_id), roi_id,
          sizeof (((*roi_dim)[i].roi_id)));
      g_free (roi_id);
      g_snprintf (key, sizeof (key), "left_%d", i);
      gst_structure_get (str, key, G_TYPE_UINT, &((*roi_dim)[i].left), NULL);
      g_snprintf (key, sizeof (key), "top_%d", i);
      gst_structure_get (str, key, G_TYPE_UINT, &((*roi_dim)[i].top), NULL);
      g_snprintf (key, sizeof (key), "width_%d", i);
      gst_structure_get (str, key, G_TYPE_UINT, &((*roi_dim)[i].width), NULL);
      g_snprintf (key, sizeof (key), "height_%d", i);
      gst_structure_get (str, key, G_TYPE_UINT, &((*roi_dim)[i].height), NULL);

    }
  }
}

void
gst_nvevent_parse_infer_interval_update (GstEvent * event, gchar ** stream_id,
    guint * interval)
{
  if ((GstEventType) GST_NVEVENT_INFER_INTERVAL_UPDATE ==
      GST_EVENT_TYPE (event)) {

    const GstStructure *str = gst_event_get_structure (event);

    gst_structure_get (str, "stream_id", G_TYPE_STRING, stream_id,
        "interval", G_TYPE_UINT, interval, NULL);
  }
}

GstEvent *
gst_nvevent_osd_process_mode_update (gchar * stream_id, guint process_mode)
{
  GstStructure *str = gst_structure_new_empty ("nv-osd-process-mode-update");

  gst_structure_set (str, "stream_id", G_TYPE_STRING, stream_id,
      "process_mode", G_TYPE_UINT, process_mode, NULL);

  return gst_event_new_custom ((GstEventType)
      GST_NVEVENT_OSD_PROCESS_MODE_UPDATE, str);
}

void
gst_nvevent_parse_osd_process_mode_update (GstEvent * event, gchar ** stream_id,
    guint * process_mode)
{
  if ((GstEventType) GST_NVEVENT_OSD_PROCESS_MODE_UPDATE ==
      GST_EVENT_TYPE (event)) {

    const GstStructure *str = gst_event_get_structure (event);

    gst_structure_get (str, "stream_id", G_TYPE_STRING, stream_id,
        "process_mode", G_TYPE_UINT, process_mode, NULL);
  }
}


GstEvent *gst_nvevent_analytics_update (gchar * stream_id, guint roi_count, guint line_count, RoiInfo * roi_info, LineInfo * line_info)
{
  GstStructure *str = gst_structure_new_empty ("nv-analytics-update");

  gst_structure_set (str, "stream_id", G_TYPE_STRING, stream_id,
      "roi_count", G_TYPE_UINT, roi_count,  "line_count", G_TYPE_UINT, line_count,  NULL);

  for (int i = 0; i < (int) roi_count; i++) {
    char key[128];
    
    
    g_snprintf (key, sizeof (key), "roi_pts_%d", i);
    gst_structure_set (str, key, G_TYPE_STRING, (char *) roi_info[i].pts, NULL);
    
    g_snprintf (key, sizeof (key), "roi_label_%d", i);
    gst_structure_set (str, key, G_TYPE_STRING, (char *) roi_info[i].label, NULL);
    
    g_snprintf (key, sizeof (key), "roi_class_id_%d", i);
    gst_structure_set (str, key, G_TYPE_STRING, (char *) roi_info[i].class_id, NULL);
        
    g_snprintf (key, sizeof (key), "roi_stream_id_%d", i);
    gst_structure_set (str, key, G_TYPE_UINT, roi_info[i].stream_id, NULL);
    
    g_snprintf (key, sizeof (key), "roi_enable_%d", i);
    gst_structure_set (str, key, G_TYPE_BOOLEAN, roi_info[i].enable, NULL);
    
    g_snprintf (key, sizeof (key), "roi_inverse_roi_%d", i);
    gst_structure_set (str, key, G_TYPE_BOOLEAN, roi_info[i].inverse_roi, NULL);
    
  }
   
  for (int i = 0; i < (int) line_count; i++) {
    char key[128];
    
    
    g_snprintf (key, sizeof (key), "line_pts_%d", i);
    gst_structure_set (str, key, G_TYPE_STRING, (char *) line_info[i].pts, NULL);
    
    g_snprintf (key, sizeof (key), "line_label_%d", i);
    gst_structure_set (str, key, G_TYPE_STRING, (char *) line_info[i].label, NULL);
    
    g_snprintf (key, sizeof (key), "line_class_id_%d", i);
    gst_structure_set (str, key, G_TYPE_STRING, (char *) line_info[i].class_id, NULL);
    
    g_snprintf (key, sizeof (key), "line_mode_%d", i);
    gst_structure_set (str, key, G_TYPE_STRING, (char *) line_info[i].mode, NULL);
        
    g_snprintf (key, sizeof (key), "line_stream_id_%d", i);
    gst_structure_set (str, key, G_TYPE_UINT, line_info[i].stream_id, NULL);
    
    g_snprintf (key, sizeof (key), "line_enable_%d", i);
    gst_structure_set (str, key, G_TYPE_BOOLEAN, line_info[i].enable, NULL);
    
    g_snprintf (key, sizeof (key), "line_extended_%d", i);
    gst_structure_set (str, key, G_TYPE_BOOLEAN, line_info[i].extended, NULL);
    
    
    
  }
  
   
  return gst_event_new_custom ((GstEventType) GST_NVEVENT_ANALYTICS_UPDATE, str);
}



void gst_nvevent_parse_analytics_update (GstEvent * event, gchar ** stream_id,
      guint * roi_count, guint * line_count, RoiInfo ** roi_info, LineInfo ** line_info)
{
  if ((GstEventType) GST_NVEVENT_ANALYTICS_UPDATE == GST_EVENT_TYPE (event)) {

    const GstStructure *str = gst_event_get_structure (event);

    gst_structure_get (str, "stream_id", G_TYPE_STRING, stream_id,
        "roi_count", G_TYPE_UINT, roi_count, "line_count", G_TYPE_UINT, line_count,  NULL);

    *roi_info = (RoiInfo *) g_malloc (sizeof (RoiInfo) * (*roi_count));

    for (int i = 0; i < (int) *roi_count; i++) {

      char key[128];
      gchar *roi_pts;
      g_snprintf (key, sizeof (key), "roi_pts_%d", i);
      gst_structure_get (str, key, G_TYPE_STRING, &(roi_pts), NULL);
      g_strlcpy (((*roi_info)[i].pts), roi_pts,
          sizeof (((*roi_info)[i].pts)));
      g_free (roi_pts);
      
      gchar *roi_label;
      g_snprintf (key, sizeof (key), "roi_label_%d", i);
      gst_structure_get (str, key, G_TYPE_STRING, &(roi_label), NULL);
      g_strlcpy (((*roi_info)[i].label), roi_label,
          sizeof (((*roi_info)[i].label)));
      g_free (roi_label);
      
      gchar *roi_class_id;
      g_snprintf (key, sizeof (key), "roi_class_id_%d", i);
      gst_structure_get (str, key, G_TYPE_STRING, &(roi_class_id), NULL);
      g_strlcpy (((*roi_info)[i].class_id), roi_class_id,
          sizeof (((*roi_info)[i].class_id)));
      g_free (roi_class_id);
      
      g_snprintf (key, sizeof (key), "roi_stream_id_%d", i);
      gst_structure_get (str, key, G_TYPE_UINT, &((*roi_info)[i].stream_id), NULL);
      
      g_snprintf (key, sizeof (key), "roi_enable_%d", i);
      gst_structure_get (str, key, G_TYPE_BOOLEAN, &((*roi_info)[i].enable), NULL);
      
      g_snprintf (key, sizeof (key), "roi_inverse_roi_%d", i);
      gst_structure_get (str, key, G_TYPE_BOOLEAN, &((*roi_info)[i].inverse_roi), NULL);

    }
    
    *line_info = (LineInfo *) g_malloc (sizeof (LineInfo) * (*line_count));

    for (int i = 0; i < (int) *line_count; i++) {

      char key[128];
      gchar *line_pts;
      g_snprintf (key, sizeof (key), "line_pts_%d", i);
      gst_structure_get (str, key, G_TYPE_STRING, &(line_pts), NULL);
      g_strlcpy (((*line_info)[i].pts), line_pts,
          sizeof (((*line_info)[i].pts)));
      g_free (line_pts);
      
      gchar *line_label;
      g_snprintf (key, sizeof (key), "line_label_%d", i);
      gst_structure_get (str, key, G_TYPE_STRING, &(line_label), NULL);
      g_strlcpy (((*line_info)[i].label), line_label,
          sizeof (((*line_info)[i].label)));
      g_free (line_label);
      
      gchar *line_class_id;
      g_snprintf (key, sizeof (key), "line_class_id_%d", i);
      gst_structure_get (str, key, G_TYPE_STRING, &(line_class_id), NULL);
      g_strlcpy (((*line_info)[i].class_id), line_class_id,
          sizeof (((*line_info)[i].class_id)));
      g_free (line_class_id);
      
      g_snprintf (key, sizeof (key), "line_stream_id_%d", i);
      gst_structure_get (str, key, G_TYPE_UINT, &((*line_info)[i].stream_id), NULL);
      
      g_snprintf (key, sizeof (key), "line_enable_%d", i);
      gst_structure_get (str, key, G_TYPE_BOOLEAN, &((*line_info)[i].enable), NULL);
      
      g_snprintf (key, sizeof (key), "line_extended_%d", i);
      gst_structure_get (str, key, G_TYPE_BOOLEAN, &((*line_info)[i].extended), NULL);
      
      gchar *line_mode;
      g_snprintf (key, sizeof (key), "line_mode_%d", i);
      gst_structure_get (str, key, G_TYPE_STRING, &(line_mode), NULL);
      g_strlcpy (((*line_info)[i].mode), line_mode,
          sizeof (((*line_info)[i].mode)));
      g_free (line_mode);
      
      
      

    }
    
    
  }
}



/*
GstEvent *
gst_nvevent_analytics_reset_mode_update (gchar * stream_id, guint reset_mode)
{
  GstStructure *str = gst_structure_new_empty ("nv-analytics-reset-mode-update");

  gst_structure_set (str, "stream_id", G_TYPE_STRING, stream_id,
      "reset_mode", G_TYPE_UINT, reset_mode, NULL);

  return gst_event_new_custom ((GstEventType)
      GST_NVEVENT_ANALYTICS_RESET_MODE_UPDATE, str);
}

void
gst_nvevent_parse_analytics_reset_mode_update (GstEvent * event, gchar ** stream_id,
    guint * reset_mode)
{
  if ((GstEventType) GST_NVEVENT_ANALYTICS_RESET_MODE_UPDATE ==
      GST_EVENT_TYPE (event)) {

    const GstStructure *str = gst_event_get_structure (event);

    gst_structure_get (str, "stream_id", G_TYPE_STRING, stream_id,
        "reset_mode", G_TYPE_UINT, reset_mode, NULL);
  }
}
*/