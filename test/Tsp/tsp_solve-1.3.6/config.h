/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from conf.in by autoheader.  */
/* config.h
 *
 * orig ceh 5-1-94
 */
#ifndef _CONFIG_H
#define _CONFIG_H

/* Define as the return type of signal handlers (int or void).  */
#define RETSIGTYPE void

/* Define if your processor stores words with the most significant
   byte first (like Motorola and SPARC, unlike Intel and VAX).  */
/* #undef WORDS_BIGENDIAN */

/* #undef HAS_AINT */
#define HAS_CLOCK 1
#define HAS_CLOCK_DECL 1
#define HAS_CLOSE_DECL 1
#define HAS_FTIME 1
#define HAS_FTIME_DECL 1
#define HAS_GETHOSTNAME_DECL 1
#define HAS_LRAND48_DECL 1
#define HAS_NFSLOCK 1
#define MAX_RAND 0xffffffff
#define HAS_RAND_DECL 1
#define HAS_RAND48 1
#define HAS_SIGNAL 1
#define HAS_SLEEP_DECL 1
#define HAS_SPRINTF_DECL 1
#define HAS_SRAND_DECL 1
#define HAS_SRAND48_DECL 1
#define HAS_UNLINK_DECL 1
#define HAS_TIME_DECL 1
#define REMOTE_COMMAND_SHELL "/usr/bin/rsh"

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the socket library (-lsocket).  */
/* #undef HAVE_LIBSOCKET */
#endif
