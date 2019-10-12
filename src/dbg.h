/**
 * \file dbg.h
 * \brief Define dbg helpers
 * \author Cedlemo
 * \version 0.1
 * \date 18 mai 2013
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifndef DBG_H
#define DBG_H

#define clean_errno() (errno == 0 ? "None" : strerror(errno))
#define SENTINEL(M, ...) printf("[SENTINEL] (%s:%s:%d: errno: %s) " M "\n",__FILE__, __FUNCTION__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define LOG_ERR(M, ...) fprintf(stderr,  "[ERROR] (%s:%s:%d: errno: %s) " M "\n", __FILE__, __FUNCTION__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define LOG_WARN(M, ...) fprintf(stderr, "[WARN]  (%s:%s:%d: errno: %s) " M "\n", __FILE__, __FUNCTION__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define LOG_INFO(M, ...) fprintf(stderr, "[INFO]  (%s:%s:%d) " M "\n", __FILE__,__FUNCTION__ , __LINE__, ##__VA_ARGS__)
/*#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }*/
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; }
/*#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }*/
#define check_mem(A) check((A), "Out of memory.")
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }
#endif

