#ifndef A_LOG_H
#define A_LOG_H

#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_ERROR 3

extern int log_level;

void a_log_debug(char *log);
void a_log_info(char *log);
void a_log_warning(char *log);
void a_log_error(char *log);

#endif  // A_LOG_H
