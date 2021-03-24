#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#include<errno.h>
#include<tar.h>
#include<grp.h>
#include<pwd.h>

struct tar_header
{ 				/* byte offset */
char name[100]; /* 0 */
char mode[8]; /* 100 */
char uid[8]; /* 108 */
char gid[8]; /* 116 */
char size[12]; /* 124 */
char mtime[12]; /* 136 */
char chksum[8]; /* 148 */
char typeflag; /* 156 */
char linkname[100]; /* 157 */
char magic[6]; /* 257 */
char version[2]; /* 263 */
char uname[32]; /* 265 */
char gname[32]; /* 297 */
char devmajor[8]; /* 329 */
char devminor[8]; /* 337 */
char prefix[155]; /* 345 */
char pad[12] /* 500 */
};
##############
# These macros can be added by including tar.h
# typing or copy and pasting them will surely result in errors
##############
#define TMAGIC "ustar" /* ustar and a nul */
#define TMAGLEN 6
#define TVERSION "00" /* 00 and no nul */
#define TVERSLEN 2
/* Values used in typeflag field. */
#define REGTYPE ’0’ /* regular file */
#define AREGTYPE ’\0’ /* regular file */
#define LNKTYPE ’1’ /* link */
#define SYMTYPE ’2’ /* reserved */
#define CHRTYPE ’3’ /* character special */
#define BLKTYPE ’4’ /* block special */
#define DIRTYPE ’5’ /* directory */
#define FIFOTYPE ’6’ /* FIFO special */
#define CONTTYPE ’7’ /* reserved */
/* Bits used in the mode field, values in octal. */
#define TSUID 04000 /* set UID on execution */
#define TSGID 02000 /* set GID on execution */
#define TSVTX 01000 /* reserved */
/* file permissions */
#define TUREAD 00400 /* read by owner */
#define TUWRITE 00200 /* write by owner */
#define TUEXEC 00100 /* execute/search by owner */
#define TGREAD 00040 /* read by group */
#define TGWRITE 00020 /* write by group */
#define TGEXEC 00010 /* execute/search by group */
#define TOREAD 00004 /* read by other */
#define TOWRITE 00002 /* write by other */
#define TOEXEC 00001 /* execute/search by other */