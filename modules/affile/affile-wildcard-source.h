#pragma once

#include "syslog-ng.h"
#include "driver.h"
#include "logreader.h"
#include "affile-source.h"
#include "filemonitor/filemonitor.h"

typedef struct _AFFileWildCardSourceDriver
{
  LogSrcDriver super;
  gchar *base_dir;
  gchar *file_pattern;
  guint32 max_files;
  LogReaderOptions reader_options;
  FileMonitorOptions monitor_options;
  FileMonitor *monitor;
} AFFileWildCardSourceDriver;

LogDriver *affile_wildcard_sd_new(GlobalConfig *cfg);
void affile_wildcard_sd_set_base_dir(LogDriver *s, gchar *base_dir);
void affile_wildcard_sd_set_file_pattern(LogDriver *s, gchar *file_pattern);
void affile_wildcard_sd_set_max_files(LogDriver *s, guint32 max_files);
void affile_wildcard_sd_set_recursive(LogDriver *s, gboolean recursive);
void affile_wildcard_sd_set_follow_freq(LogDriver *s, guint32 follow_freq);
