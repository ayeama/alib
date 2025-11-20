#include <alib/log.h>
#include <stdio.h>
#include <time.h>

// TODO use macros for __FILE__ etc?
// TODO add support for ... args for formatting
// TODO add logger object? so libraries can use it, but applications configure
//      them

#define DATETIME_SIZE 26

int log_level = LOG_LEVEL_WARNING;

void _datetime(char *datetime) {
  time_t timer;
  struct tm *tm_utc;

  timer = time(NULL);
  tm_utc = gmtime(&timer);

  strftime(datetime, DATETIME_SIZE, "%Y-%m-%dT%H:%M:%S%z", tm_utc);
}

void _log(int level, char *log) {
  char *name;
  switch (level) {
    case LOG_LEVEL_DEBUG:
      name = "DEBUG";
      break;
    case LOG_LEVEL_INFO:
      name = "INFO";
      break;
    case LOG_LEVEL_WARNING:
      name = "WARNING";
      break;
    case LOG_LEVEL_ERROR:
      name = "ERROR";
      break;
    default:
      break;
  }

  char datetime[DATETIME_SIZE];
  _datetime(datetime);

  printf("%s %s: %s\n", name, datetime, log);
}

void a_log_debug(char *log) {
  if (LOG_LEVEL_DEBUG < log_level) {
    return;
  }
  _log(LOG_LEVEL_DEBUG, log);
}

void a_log_info(char *log) {
  if (LOG_LEVEL_INFO < log_level) {
    return;
  }
  _log(LOG_LEVEL_INFO, log);
}

void a_log_warning(char *log) {
  if (LOG_LEVEL_WARNING < log_level) {
    return;
  }
  _log(LOG_LEVEL_WARNING, log);
}

void a_log_error(char *log) {
  if (LOG_LEVEL_ERROR < log_level) {
    return;
  }
  _log(LOG_LEVEL_ERROR, log);
}
