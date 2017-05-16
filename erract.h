/*
 * Copyright (c) 2017 Herbert Shen <ishbguy@hotmail.com>
 *               All Rights Reserved
 */

/* Declare error's reaction function */

extern void err_msg(const char *fmt, ...);
extern void err_ret(const char *fmt, ...);
extern void err_cont(int error, const char *fmt, ...);
extern void err_quit(const char *fmt, ...) __attribute__ ((noreturn));
extern void err_exit(int error, const char *fmt, ...) __attribute__ ((noreturn));
extern void err_sys(const char *fmt, ...) __attribute__ ((noreturn));
extern void err_dump(const char *fmt, ...) __attribute__ ((noreturn));
