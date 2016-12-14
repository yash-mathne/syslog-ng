#include "driver.h"
#include "affile-wildcard-source.h"

static gboolean
_init(LogPipe *s)
{
  AFFileWildCardSourceDriver *self = (AFFileWildCardSourceDriver *)s;
  self->monitor = file_monitor_create_instance(&self->monitor_options);
  return TRUE;
}

static gboolean
_deinit(LogPipe *s)
{
  return TRUE;
}

static void
_queue(LogPipe *s, LogMessage *msg, const LogPathOptions *path_options, gpointer user_data)
{
}

static void
_free(LogPipe *s)
{
  AFFileWildCardSourceDriver *self = (AFFileWildCardSourceDriver *)s;
  g_free(self->base_dir);
  g_free(self->file_pattern);
}

void
affile_wildcard_sd_set_base_dir(LogDriver *s, gchar *base_dir)
{
  AFFileWildCardSourceDriver *self = (AFFileWildCardSourceDriver *)s;
  if (self->base_dir)
    g_free(self->base_dir);
  self->base_dir = g_strdup(base_dir);
}

void
affile_wildcard_sd_set_file_pattern(LogDriver *s, gchar *file_pattern)
{
  AFFileWildCardSourceDriver *self = (AFFileWildCardSourceDriver *)s;
  if (self->file_pattern)
    g_free(self->file_pattern);
  self->file_pattern = g_strdup(file_pattern);
}

void
affile_wildcard_sd_set_max_files(LogDriver *s, guint32 max_files)
{
  AFFileWildCardSourceDriver *self = (AFFileWildCardSourceDriver *)s;
  self->max_files = max_files;
}

void
affile_wildcard_sd_set_recursive(LogDriver *s, gboolean recursive)
{
  AFFileWildCardSourceDriver *self = (AFFileWildCardSourceDriver *)s;
  self->monitor_options.recursion = recursive;
}


void
affile_wildcard_sd_set_follow_freq(LogDriver *s, guint32 follow_freq)
{
  AFFileWildCardSourceDriver *self = (AFFileWildCardSourceDriver *)s;
  self->monitor_options.poll_freq = follow_freq;
}

LogDriver *
affile_wildcard_sd_new(GlobalConfig *cfg)
{
  AFFileWildCardSourceDriver *self = g_new0(AFFileWildCardSourceDriver, 1);
  log_src_driver_init_instance(&self->super, cfg);
  
  self->super.super.super.init = _init;
  self->super.super.super.queue = _queue;
  self->super.super.super.deinit = _deinit;
  self->super.super.super.free_fn = _free;

  log_reader_options_defaults(&self->reader_options);
  self->reader_options.parse_options.flags |= LP_LOCAL;

  return &self->super.super;
}
