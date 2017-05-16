/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved
 */

/* Define error log for daemon */

#ifndef __LOGACT_H__
#define __LOGACT_H__

extern void log_open(const char *ident, int option, int facility);
extern void log_msg(const char *fmt, ...);
extern void log_ret(const char *fmt, ...);
extern void log_quit(const char *fmt, ...) __attribute__((noreturn));
extern void log_sys(const char *fmt, ...) __attribute__((noreturn));
extern void log_exit(int error, const char *fmt, ...) __attribute__((noreturn));/* What to do */

#endif /* End of include guard: __LOGACT_H__ */
