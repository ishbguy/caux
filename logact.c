/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved
 */

/* Implement error log for daemon */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <syslog.h>
#include "logact.h"

#define MAXLINE 4096

static void log_doit(int eflag, int error, int priority, const char *fmt,
                     va_list ap);

/*
 * Caller must define and set this: nonzero if interactive, zore if daemon.
 */
extern int log_to_stderr;

/*
 * Initialize syslog(), if running as daemon.
 */
void log_open(const char *ident, int option, int facility)
{
    if (log_to_stderr == 0)
        openlog(ident, option, facility);
}

/*
 * Nofatal error unrelated to a system call.
 * Print a message and return.
 */
void log_msg(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(0, 0, LOG_ERR, fmt, ap);
    va_end(ap);
}

/*
 * Nonfatal error related to a system call.
 * Print a message with the system's errno value and return.
 */
void log_ret(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, errno, LOG_ERR, fmt, ap);
    va_end(ap);
}

/*
 * Fatal error unreated to a system call.
 * Print a message and terminate.
 */
void log_quit(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(0, 0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

/*
 * Fatal error related to a system call.
 * Print a message and terminate.
 */
void log_sys(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, errno, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

/*
 * Fatal error related to a system call.
 * Error number passed as an explict parameter.
 * Print a message and terminate.
 */
void log_exit(int error, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, error, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

static void log_doit(int eflag, int error, int priority, const char *fmt,
                     va_list ap)
{
    char buf[MAXLINE];

    vsnprintf(buf, MAXLINE - 1, fmt, ap);
    if (eflag)
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s",
                 strerror(error));
    strcat(buf, "\n");
    if (log_to_stderr) {
        fflush(stdout);         /* in case strout is same as stderr */
        fputs(buf, stderr);
        fflush(stderr);         /* flushed all message to stderr */
    }
    else
        syslog(priority, "%s", buf);
}
