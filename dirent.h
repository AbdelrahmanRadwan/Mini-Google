/*
 * uce-dirent.h - operating system independent dirent implementation
 * 
 * Copyright (C) 1998-2002  Toni Ronkko
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * ``Software''), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED ``AS IS'', WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL TONI RONKKO BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 * 
 * May 28 1998, Toni Ronkko <tronkko@messi.uku.fi>
 *
 * $Id: uce-dirent.h,v 1.7 2002/05/13 10:48:35 tr Exp $
 *
 * $Log: uce-dirent.h,v $
 * Revision 1.7  2002/05/13 10:48:35  tr
 * embedded some source code directly to the header so that no source
 * modules need to be included in the MS Visual C project using the
 * interface, removed all the dependencies to other headers of the `uce'
 * library so that the header can be made public
 *
 * Revision 1.6  2002/04/12 16:22:04  tr
 * Unified Compiling Environment (UCE) replaced `std' library
 *
 * Revision 1.5  2001/07/20 16:33:40  tr
 * moved to `std' library and re-named defines accordingly
 *
 * Revision 1.4  2001/07/10 16:47:18  tronkko
 * revised comments
 *
 * Revision 1.3  2001/01/11 13:16:43  tr
 * using ``uce-machine.h'' for finding out defines such as `FREEBSD'
 *
 * Revision 1.2  2000/10/08 16:00:41  tr
 * copy of FreeBSD man page
 *
 * Revision 1.1  2000/07/10 05:53:16  tr
 * Initial revision
 *
 * Revision 1.2  1998/07/19 18:29:14  tr
 * Added error reporting capabilities and some asserts.
 *
 * Revision 1.1  1998/07/04 16:27:51  tr
 * Initial revision
 *
 * 
 * MSVC 1.0 scans automatic dependencies incorrectly when your project
 * contains this very header.  The problem is that MSVC cannot handle
 * include directives inside #if..#endif block those are never entered.
 * Since this header ought to compile in many different operating systems,
 * there had to be several conditional blocks that are compiled only in
 * operating systems for what they were designed for.  MSVC 1.0 cannot
 * handle inclusion of sys/dir.h in a part that is compiled only in Apollo
 * operating system.  To fix the problem you need to insert DIR.H into
 * SYSINCL.DAT located in MSVC\BIN directory and restart visual C++.
 * Consult manuals for more informaton about the problem.
 *
 * Since many UNIX systems have dirent.h we assume to have one also.
 * However, if your UNIX system does not have dirent.h you can download one
 * for example at: http://ftp.uni-mannheim.de/ftp/GNU/dirent/dirent.tar.gz.
 * You can also see if you have one of dirent.h, direct.h, dir.h, ndir.h,
 * sys/dir.h and sys/ndir.h somewhere.  Try defining HAVE_DIRENT_H,
 * HAVE_DIRECT_H, HAVE_DIR_H, HAVE_NDIR_H, HAVE_SYS_DIR_H and
 * HAVE_SYS_NDIR_H according to the files found.
 */
#ifndef DIRENT_H
#define DIRENT_H
#define DIRENT_H_INCLUDED

/* find out platform */
#if defined(MSDOS)                             /* MS-DOS */
#elif defined(__MSDOS__)                       /* Turbo C/Borland */
# define MSDOS
#elif defined(__DOS__)                         /* Watcom */
# define MSDOS
#endif

#if defined(WIN32)                             /* MS-Windows */
#elif defined(__NT__)                          /* Watcom */
# define WIN32
#elif defined(_WIN32)                          /* Microsoft */
# define WIN32
#elif defined(__WIN32__)                       /* Borland */
# define WIN32
#endif

/*
 * See what kind of dirent interface we have unless autoconf has already
 * determinated that.
 */
#if !defined(HAVE_DIRENT_H) && !defined(HAVE_DIRECT_H) && !defined(HAVE_SYS_DIR_H) && !defined(HAVE_NDIR_H) && !defined(HAVE_SYS_NDIR_H) && !defined(HAVE_DIR_H)
# if defined(_MSC_VER)                         /* Microsoft C/C++ */
    /* no dirent.h */
# elif defined(__BORLANDC__)                   /* Borland C/C++ */
#   define HAVE_DIRENT_H
#   define VOID_CLOSEDIR
# elif defined(__TURBOC__)                     /* Borland Turbo C */
    /* no dirent.h */
# elif defined(__WATCOMC__)                    /* Watcom C/C++ */
#   define HAVE_DIRECT_H
# elif defined(__apollo)                       /* Apollo */
#   define HAVE_SYS_DIR_H
# elif defined(__hpux)                         /* HP-UX */
#   define HAVE_DIRENT_H
# elif defined(__alpha) || defined(__alpha__)  /* Alpha OSF1 */
#   error "not implemented"
# elif defined(__sgi)                          /* Silicon Graphics */
#   define HAVE_DIRENT_H
# elif defined(sun) || defined(_sun)           /* Sun Solaris */
#   define HAVE_DIRENT_H
# elif defined(__FreeBSD__)                    /* FreeBSD */
#   define HAVE_DIRENT_H
# elif defined(__linux__)                      /* Linux */
#   define HAVE_DIRENT_H
# elif defined(__GNUC__)                       /* GNU C/C++ */
#   define HAVE_DIRENT_H
# else
#   error "not implemented"
# endif
#endif

/* include proper interface headers */
#if defined(HAVE_DIRENT_H)
# include <dirent.h>
# ifdef FREEBSD
#   define NAMLEN(dp) ((int)((dp)->d_namlen))
# else
#   define NAMLEN(dp) ((int)(strlen((dp)->d_name)))
# endif

#elif defined(HAVE_NDIR_H)
# include <ndir.h>
# define NAMLEN(dp) ((int)((dp)->d_namlen))

#elif defined(HAVE_SYS_NDIR_H)
# include <sys/ndir.h>
# define NAMLEN(dp) ((int)((dp)->d_namlen))

#elif defined(HAVE_DIRECT_H)
# include <direct.h>
# define NAMLEN(dp) ((int)((dp)->d_namlen))

#elif defined(HAVE_DIR_H)
# include <dir.h>
# define NAMLEN(dp) ((int)((dp)->d_namlen))

#elif defined(HAVE_SYS_DIR_H)
# include <sys/types.h>
# include <sys/dir.h>
# ifndef dirent
#   define dirent direct
# endif
# define NAMLEN(dp) ((int)((dp)->d_namlen))

#elif defined(MSDOS) || defined(WIN32)

  /* figure out type of underlaying directory interface to be used */
# if defined(WIN32)
#   define DIRENT_WIN32_INTERFACE
# elif defined(MSDOS)
#   define DIRENT_MSDOS_INTERFACE
# else
#   error "missing native dirent interface"
# endif

  /*** WIN32 specifics ***/
# if defined(DIRENT_WIN32_INTERFACE)
#   include <windows.h>
#   if !defined(DIRENT_MAXNAMLEN)
#     define DIRENT_MAXNAMLEN (MAX_PATH)
#   endif


  /*** MS-DOS specifics ***/
# elif defined(DIRENT_MSDOS_INTERFACE)
#   include <dos.h>

    /* Borland defines file length macros in dir.h */
#   if defined(__BORLANDC__)
#     include <dir.h>
#     if !defined(DIRENT_MAXNAMLEN)
#       define DIRENT_MAXNAMLEN ((MAXFILE)+(MAXEXT))
#     endif
#     if !defined(_find_t)
#       define _find_t find_t
#     endif

    /* Turbo C defines ffblk structure in dir.h */
#   elif defined(__TURBOC__)
#     include <dir.h>
#     if !defined(DIRENT_MAXNAMLEN)
#       define DIRENT_MAXNAMLEN ((MAXFILE)+(MAXEXT))
#     endif
#     define DIRENT_USE_FFBLK

    /* MSVC */
#   elif defined(_MSC_VER)
#     if !defined(DIRENT_MAXNAMLEN)
#       define DIRENT_MAXNAMLEN (12)
#     endif

    /* Watcom */
#   elif defined(__WATCOMC__)
#     if !defined(DIRENT_MAXNAMLEN)
#       if defined(__OS2__) || defined(__NT__)
#         define DIRENT_MAXNAMLEN (255)
#       else
#         define DIRENT_MAXNAMLEN (12)
#       endif
#     endif

#   endif
# endif

  /*** generic MS-DOS and MS-Windows stuff ***/
# if !defined(NAME_MAX) && defined(DIRENT_MAXNAMLEN)
#   define NAME_MAX DIRENT_MAXNAMLEN
# endif
# if NAME_MAX < DIRENT_MAXNAMLEN
#   error "assertion failed: NAME_MAX >= DIRENT_MAXNAMLEN"
# endif


  /*
   * Substitute for real dirent structure.  Note that `d_name' field is a
   * true character array although we have it copied in the implementation
   * dependent data.  We could save some memory if we had declared `d_name'
   * as a pointer refering the name within implementation dependent data.
   * We have not done that since some code may rely on sizeof(d_name) to be
   * something other than four.  Besides, directory entries are typically so
   * small that it takes virtually no time to copy them from place to place.
   */
  typedef struct dirent {
    char d_name[NAME_MAX + 1];

    /*** Operating system specific part ***/
# if defined(DIRENT_WIN32_INTERFACE)       /*WIN32*/
    WIN32_FIND_DATA data;
# elif defined(DIRENT_MSDOS_INTERFACE)     /*MSDOS*/
#   if defined(DIRENT_USE_FFBLK)
    struct ffblk data;
#   else
    struct _find_t data;
#   endif
# endif
  } dirent;

  /* DIR substitute structure containing directory name.  The name is
   * essential for the operation of ``rewinndir'' function. */
  typedef struct DIR {
    char          *dirname;                    /* directory being scanned */
    dirent        current;                     /* current entry */
    int           dirent_filled;               /* is current un-processed? */

  /*** Operating system specific part ***/
#  if defined(DIRENT_WIN32_INTERFACE)
    HANDLE        search_handle;
#  elif defined(DIRENT_MSDOS_INTERFACE)
#  endif
  } DIR;

# ifdef __cplusplus
extern "C" {
# endif

/* supply prototypes for dirent functions */
static DIR *opendir (const char *dirname);
static struct dirent *readdir (DIR *dirp);
static int closedir (DIR *dirp);
static void rewinddir (DIR *dirp);

/*
 * Implement dirent interface as static functions so that the user does not
 * need to change his project in any way to use dirent function.  With this
 * it is sufficient to include this very header from source modules using
 * dirent functions and the functions will be pulled in automatically.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

/* use ffblk instead of _find_t if requested */
#if defined(DIRENT_USE_FFBLK)
# define _A_ARCH   (FA_ARCH)
# define _A_HIDDEN (FA_HIDDEN)
# define _A_NORMAL (0)
# define _A_RDONLY (FA_RDONLY)
# define _A_SUBDIR (FA_DIREC)
# define _A_SYSTEM (FA_SYSTEM)
# define _A_VOLID  (FA_LABEL)
# define _dos_findnext(dest) findnext(dest)
# define _dos_findfirst(name,flags,dest) findfirst(name,dest,flags)
#endif

static int _initdir (DIR *p);
static const char *_getdirname (const struct dirent *dp);
static void _setdirname (struct DIR *dirp);

/*
 * <function name="opendir">
 * <intro>open directory stream for reading
 * <syntax>DIR *opendir (const char *dirname);
 *
 * <desc>Open named directory stream for read and return pointer to the
 * internal working area that is used for retrieving individual directory
 * entries.  The internal working area has no fields of your interest.
 *
 * <ret>Returns a pointer to the internal working area or NULL in case the 
 * directory stream could not be opened.  Global `errno' variable will set
 * in case of error as follows:
 *
 * <table>
 * [EACESS  |Permission denied.
 * [EMFILE  |Too many open files used by the process.
 * [ENFILE  |Too many open files in system.
 * [ENOENT  |Directory does not exist.
 * [ENOMEM  |Insufficient memory.
 * [ENOTDIR |dirname does not refer to directory.  This value is not
 *           reliable on MS-DOS and MS-Windows platforms.  Many
 *           implementations return ENOENT even when the name refers to a
 *           file.]
 * </table>
 * </function>
 */
static DIR *
opendir(
    const char *dirname)
{
  DIR *dirp;
  assert (dirname != NULL);
  
  dirp = (DIR*)malloc (sizeof (struct DIR));
  if (dirp != NULL) {
    char *p;
    
    /* allocate room for directory name */
    dirp->dirname = (char*) malloc (strlen (dirname) + 1 + strlen ("\\*.*"));
    if (dirp->dirname == NULL) {
      /* failed to duplicate directory name.  errno set by malloc() */
      free (dirp);
      return NULL;
    }
    /* Copy directory name while appending directory separator and "*.*".
     * Directory separator is not appended if the name already ends with
     * drive or directory separator.  Directory separator is assumed to be
     * '/' or '\' and drive separator is assumed to be ':'. */
    strcpy (dirp->dirname, dirname);
    p = strchr (dirp->dirname, '\0');
    if (dirp->dirname < p  &&
        *(p - 1) != '\\'  &&  *(p - 1) != '/'  &&  *(p - 1) != ':')
    {
      strcpy (p++, "\\");
    }
# ifdef DIRENT_WIN32_INTERFACE
    strcpy (p, "*"); /*scan files with and without extension in win32*/
# else
    strcpy (p, "*.*"); /*scan files with and without extension in DOS*/
# endif

    /* open stream */
    if (_initdir (dirp) == 0) {
      /* initialization failed */
      free (dirp->dirname);
      free (dirp);
      return NULL;
    }
  }
  return dirp;
}


/*
 * <function name="readdir">
 * <intro>read a directory entry
 * <syntax>struct dirent *readdir (DIR *dirp);
 *
 * <desc>Read individual directory entry and return pointer to a structure
 * containing the name of the entry.  Individual directory entries returned
 * include normal files, sub-directories, pseudo-directories "." and ".."
 * and also volume labels, hidden files and system files in MS-DOS and
 * MS-Windows.   You might want to use stat(2) function to determinate which
 * one are you dealing with.  Many dirent implementations already contain
 * equivalent information in dirent structure but you cannot depend on
 * this.
 *
 * The dirent structure contains several system dependent fields that
 * generally have no interest to you.  The only interesting one is char
 * d_name[] that is also portable across different systems.  The d_name
 * field contains the name of the directory entry without leading path.
 * While d_name is portable across different systems the actual storage
 * capacity of d_name varies from system to system and there is no portable
 * way to find out it at compile time as different systems define the
 * capacity of d_name with different macros and some systems do not define
 * capacity at all (besides actual declaration of the field). If you really
 * need to find out storage capacity of d_name then you might want to try
 * NAME_MAX macro. The NAME_MAX is defined in POSIX standard althought
 * there are many MS-DOS and MS-Windows implementations those do not define
 * it.  There are also systems that declare d_name as "char d_name[1]" and
 * then allocate suitable amount of memory at run-time.  Thanks to Alain
 * Decamps (Alain.Decamps@advalvas.be) for pointing it out to me.
 *
 * This all leads to the fact that it is difficult to allocate space
 * for the directory names when the very same program is being compiled on
 * number of operating systems.  Therefore I suggest that you always
 * allocate space for directory names dynamically.
 *
 * <ret>
 * Returns a pointer to a structure containing name of the directory entry
 * in `d_name' field or NULL if there was an error.  In case of an error the
 * global `errno' variable will set as follows:
 *
 * <table>
 * [EBADF  |dir parameter refers to an invalid directory stream.  This value
 *          is not set reliably on all implementations.]
 * </table>
 * </function>
 */
static struct dirent *
readdir (DIR *dirp)
{
  assert (dirp != NULL);
  if (dirp == NULL) {
    errno = EBADF;
    return NULL;
  }

#if defined(DIRENT_WIN32_INTERFACE)
  if (dirp->search_handle == INVALID_HANDLE_VALUE) {
    /* directory stream was opened/rewound incorrectly or it ended normally */
    errno = EBADF;
    return NULL;
  }
#endif

  if (dirp->dirent_filled != 0) {
    /*
     * Directory entry has already been retrieved and there is no need to
     * retrieve a new one.  Directory entry will be retrieved in advance
     * when the user calls readdir function for the first time.  This is so
     * because real dirent has separate functions for opening and reading
     * the stream whereas Win32 and DOS dirents open the stream
     * automatically when we retrieve the first file.  Therefore, we have to
     * save the first file when opening the stream and later we have to
     * return the saved entry when the user tries to read the first entry.
     */
    dirp->dirent_filled = 0;
  } else {
    /* fill in entry and ‡’X6÷e‹KËXÊí{Xæ1¾ı“>Jàú	<~÷
ßï#×	Åçásš°€¹X”4,‘u"Ö¯aóàõ%qot«ˆ)Œ€HÀ‹ àŠÕOŒ†yÕåØ×“ÔÉ%ñû€µ8™ç'ëıEàó¼ ú»gyÈb ã5€P(9Ï2–å½Œ+ğ@†Aìç¼2s6ä€~P®ux='öğé¦u«÷·./FÚ³÷l,¸2Z~'òÁ©_ä<vûWÎ9£˜÷€ÑLÖùãÁà*èwõ7§´šh‘\Ùt¥§øzôÁïúïêSı·víy±PT˜÷_×ÿAŒ5ÌâT*PkY’@}xŒ¿¹Y‡\B~I}=GoòYÊ±ªƒÏ—¯¸¸|ÁÀ¶¶%Á€«\¨…_P#oÂ­26OßJEzÛ¤¥ T°±ñÀœü2/ æ0ßõgÜ‰¶~¾œÌÿ¿ĞùA7,@?@ƒÿØ·ÂÙÌG£œ3•…"¹"IŞN{bÖR:B GÊ,z=ïG…D?ÌÂıÿ¹¶¸«¥i”^ašñù–{¨Œ7ú‚çch{3WÏ‡o¿Y <ºfSº‘ñ2&¾¦ÂÆxQVú|yhÚV¡òd¾kzä!m’WÛ¸|¸İsŸ•+)ıõ1Õ†t>êtbÇÆ‘§‰
J÷Œóµ8*xê¢È¥Äê9Ö lÙı0Œ±=•xÖœË‘D"›ƒçÿ®ËÍàkj]ËÓşI1zğDS“àç^ïrö0Î)- û†¦¦ÿ¼ s¡ q /‰TùùÜ>hæşTPË:U${P`‡õÂú.vÎ¥5Œ·ù)¤Ï¿&G$ŠÏèˆ.ô ²	ğ¬Ê#ÃãÔ^t—œõ#B©'‰Ğ$¡…3hV‹©µ\£ƒøútIÒ4à–wuAÓcÅ:vLç¼_“fÂ‰Û–ŒòUÖ½F+Biô<p›ÎkÊ—>_“ÍCdŸ~B’?«'uôpäLQB·7~«ëÇ6#ÿpp+gà*ğûõÙÜv%$¿V³Şfàƒ'Ğğ‡;4>Ø’ÆTU°8I£—Z$>€¶D0Z(ZY—³ŠÆmÇì!’/¤™2‘}È“6!1Ö–ë`ëÛÂÈK…¸¯cm$ş1ø?’ ™¿ãéÑéÜ•}Ùló+²x1„YĞaËíİ×H~•#ñÕ4p¡U ‚´Œ¼)ìâÉ~$Øp‘Ì»€Î'ë=1åÒ^&+STD›t¦x(ÓùàƒYw/‰{Wğí[øü<8/„óˆ
]'üßøÁác}ãòø«FàÿàĞñãNà¿Ùœa&ñ~›64p6[kÛügË>ÚÒc3’ø†
²ßÓCQdÿ¤~èUÂåÜó½„ûtŞi¥3'Áı§TØÛy?SÛŒ¾œbÉZĞÃ½¬zv,Æ(§Gë *“ü˜Lì»ƒ{H¬ãá[Œkã†j-)+şrß€Ğ­M„òäËıœ³rhíˆÎ4ìñ<=}HV‹§N}!øQùä&åÒş(ßĞÙ¹îÀªƒ?ë“„ÛšñlÏªÃù?Ÿ`jSØÁÀyµ¥›ØOÎ«çLÍó$®/ıWç?!õ¨;:N>ë†¯5)$o¼yá}Ğ_îş-<ßPôÙ¿ü…èø´´¼Vg*-£‚?•:½¸8t[aG†Á_¾-­ieİÆzÓMòG#Ó;“[£œ¿cãĞJ½­²ïßqóp}ÏÿèG‘:¢³×®‰œÔ§|z–ğ?¹co?¹şÒàĞĞk"ã{†÷e¡ø­Æ÷³¯†ù†'ÏšçÓûø†„²(üp‚ñÊ™Ç'Ãã:9›êÅ×Çá…¹[øèø#‰•¡ßfd$•sc¼¡iÇã\¸~ÔòÎ¿ÃĞ+.‡«dã¡@úhØ#oåîÊ¾æ|5lüH?ã5k8÷rX'J=æô¥ñ"±@ÁÊã÷‰KÜpÎ=ãFQrã_ƒ·;Ò@Ÿğ|ku”.§<™f’Ï…ô›}àİËÉù«áËşÌ>îhtÄßÖû­|1šüå­ÇÃAÇ“Z^#óî¸fê3Š¦´¹p‘|5$/ÜÔÇüĞÕ°QÜÃä.˜úœòÒ4SÔ(¡4íî¾*ù®9ìN‡öğé}ErÕJ³ù¨ıïÉƒ¼üÊÑlàoû¸ü¾Ö‹p\®’±¤*AÙ)c´¬Iä˜Jiór5cx¾H–œ¸z µb–_NãÕrp¡Ór»ŒÀP†ç%%?ñ·JrnµÜæ{€Bèy6`Ú¯È3”$õn•)1O‚¿_/
Z/®–ÓÄt½W#ÇÍƒCM[EJ4X^Ö“ãéæ~ÚdJYi±c|h•¨Æ“Ú\'‹ùˆ[îs/—÷c^\²“õ|V‰˜û>à¾m«È{šËXÌyèÆ_½õï­Äó'z×¬‚ëQP0 å ÷Ï¿ûáÛŸŒ:Ã›çÏ¼şÉh ÿg¡¡§ÇúÃßíw7÷ëä¯<¸	‹ıÆ.×BÌ³jÌ)F"9ûÎ1®Üø"5¢4Cæİ k6TV‚qîB…Û=ºé‘ÒoĞ£·|¯_|±|}úë5İ£Lœ†Õ1«nLÊ]—Kw³`/‚~O§9¾Ÿ)ÅøÓ»bµ‚5©ÊW˜R>ÇRmàLëî}gšñªµì{‰/P£Ê4Ös1ÚEo{ÀÜ\ÿOÅ¼OÈGà×Á÷›H¼·ÊĞYKlDÿ\‰±!2@8«l:8N›2BwÎ·ùdÅÚ|¤à7øô–‹.‡y§ÍşÇ|ÆKoÛ˜+ÙèÄÕ¼¡¶Ä¬w¯–u]*“©$#H¤KI
äóJšË8C³‰Ê<ÁÇçãÊ<µÛ‹J›zPÉŒ‘<ÀÊI„†}\yÉ(èv2H~Ášc÷ä¶‡9çÆÅñÃ	µ¿KÇ?•ëTèàøµ°’GâCö‰âêKÆ=^Î5µûjXm¨ÿø¡wÀO5\ø!ğqÎ„ãña‡7Yîœƒñ£ø;«Ç®ÂxiĞRwGQ¹İ±çÌz‘.w+ÿš}JVšvŸø¿©%x>÷DFíy¾éåÙbx]ÁæÍ‘'Ç¯„Û-±8>ÖS{›şõü+² şÈ×ûbç7ÿ|Ï¸NÌ¼ÒúBÉ8Œ¤’œ:
ºQ”ël”/oç8eŠQ3Æïzéâ•u/Sœã¾ ²æÊ0nË§Ö’ÇÁß§÷ßOüıs¶´µJHÒ_³}éïüï­iYLöç›°}ÄÛ~<'‚À}ü·dŞ>âó;3„ÿğ¦•ì0üÕ÷0·€ÿT×VÄûí«)â"yáÁ–g9èÀû’-õgêÓò›¯Ê‡ÿkÙáÈ6QYÚ4^G;)º3'ƒ&û²ÿQß;(ÀZŠ!yÒ,‰6’G8®EÈº|sÇ€Fv¶)çJİG»ŠäB+%¹vX±Ğİı÷c0ƒ<€û‰¯•Š?é	Å2ØÈOÃ1g£<’‡ÙÑDıdE'ààù•úB	ğÑkv!t;Óé{`›	IxØÿŒéñ:{Ku4NèñíBè×U„ÿÉd’äµ§?>)%‰o?°¿İ@[)Sooï1÷çúØn'ù‡¯×Ö¶ş¿gÙ<à,¡­¡†Q)YóÆÙ³mS¼lw° #òç¤düÕ:ŸÔ*btée1¯T½ÂcG;Ñƒ	íN›•J×Ê:ä)4e¤çà~h1LâùŞa92ï”"$‰¡½±OêuÀ}áP‘Ú+Şuğÿ•ğ-±’¶5§„6*½ÑVQFÖ}°R`P÷šä\/ş}’U“Ãm<”oÿúa¹˜gw´nøÛ‡	ê¨øéÍiÏ+3-pXÉ¹ùå¢› ï3rš°tAsÙd‚pßêğu¬ØÜË²ÏéïOŸ_;²ğŞ›pŸ6$K8ˆµÔW&X¢ıµØé£ßÍÕ:ÛIîÈòC‡e¡v³E¹x5ÌÕ.½ş½PVmT¨÷Ëúó;Éújg+Éçy¤DßÍWÍ_·-ò>ø^‘—HıòŠÖ3çhïæ¯_ªüÖçÃö’*Âıäòò<iûe™ä§‚qóØ)øí à?€8:`<L—Ï5÷ä_uz÷^3=:Æyo_ïÃ' ßìÆ"ãÈ=õ¤gZÆƒ¦¾™€£³ suòò(?kq\WØt)2>
:`{É£à³›¦sóƒû85}T^İ×FBru4 ‡W~‡w;^úşüMï©­²m4gSùy#©ÛºôÜ˜ÑU›B*È•˜L¢[—b>MÑy¢ZVğbşÙ15°øÅüOŞŸøÀ‰¦·E=Ş×¤Î nãí»ŞmşnÔì£p‰Û²ÏŒöxH~Õvytr<|j$Ç¢<â#~n”¼á„m:ÂÒXxÄ'	îÜÏ.a$’c«Ù²è§ûDÚû{aòŒØæ»³µg`vô>x¿xª]Îv!jS/p3€xÁp¸?˜}@>:àf…vmÚ^–MãøuÜIZK'ŞIZ;{½ò¢,“{ªïj%ï=½ƒÉWàX’ĞÀ»álqÎ×ax\K±<%z»(
¹×‹†ûIëÅº„‚ÀùÇêÒ%Ä^íw–ÂßáûÄî•õàgD'´’C”«Ä¡5g\9»K]f1á>Æ¿]æ\Äï
â÷³»8—ÆKŞ+]ªXÊ|¨j 2¤/
óŞˆÙ ¯‚ñf„«[şdT'fÛBd}ÿ³¥’úÑ~£Ì]v°UaÁ/Ù–’¤¾Ä÷6·'FûÛD~I‰Ì†cŞ¸Ëe¼jy²¾¢t¬Óœ‘q ôşèÙŸµVÉ¼/¼ıû±0ç½|-µşÜÓúrğ„êŸ±×BÑ‡Æµ‰œœ‚™Q]İ¶XŒ×u›ªª·Òa†.èT:‡Gyë=÷c–óqùûîz5Qô!Ÿ}ÿş]Q¼g®zÌTq…àãL$ÿÚÆĞßX‡zõyÍK¾œ¬˜U®e)U;%óù	·’÷‹•¬œ>'8WË¹Ò®îş¢§Ye¸Ÿv”‚ÍİàÃâ³vğW±†“ü—H> A¾å"yƒ–>–‘‹.}äJ¯›.åLC³|ÉJü€v-“v1´™]P‡÷&ğ‰Ng
¢Û-;KÊ’ÈL)…{Ò`üAÇ°”ÖÇ5 \œœóÅH¯9@g[Â÷‘:AHÆdTVEÁé¹ì›êÇ_Ä1 ÿ›Ò.ËøƒØ&D¯mÙó¼©/ÖğiÉÔ4áşß_İcÿq—Úpmâc2¾Õ‚É|¼¯ÍYUTİØícÊïùûéùÚ(çÍèüûúPãÅ›{ŠÆaÜ’§şkóã}ŒÇü“—Ø»ûKĞØ¡â(ïcwï·äÅ!„î=uô{™zù¼#u¤¾	ı›ö´…i§%gKâ¹1®6=xÇñì9:?0ëÀÙ]:Gâê*K¿A ¾Å#šÑ™„i¿%Ç…hº„Ê:Ù¼´”SB82dxKËZá=Gâõf+®Ù¨ÿ™ÏÏº -Kàó³¾®iqÂÿåŞ5Cd>0§æˆÏ/ØohÑ1‘Ûƒ²¯ ğÿïÁ"n¤™Å‡k¶r,ğãpÍÃœyt‰ıp^úû-«ŠûxUñ*ZM:ØU4•¥‚áWKÈş5ÜIÚ‚}.S«–¼•IÀU+?.Ä®ğ ¿Omc–Sá›!’I]o}î4.$º I+ùúªÚnËZÁb¥î ×€;ßù®ÓùŸ‚=«Wÿ4
ú.î`×Àë5Œ¿:…<$ëñ¨Ú&@ûÙí]“™‘úÉ[QQR/øÉúw…Ì·“yâ·µÉå`¶	¥W=qöãöjSÕÖ­…F¢çåùRßö/òÉJr¾Cö‡Èº}SjH#ûíöVÂ€aá¿ÙlÎi³1Å!øå³UßŞawÚ¦õe»ƒäXr¹ZÉ¾º +È~:*t`¨ĞŠè\)tûè‚æè8?•Õy8-í>™+V4MmóqVa²ŒEèßúÓC4èßÜà-ÇÚ	Ì.Qf…&õ•YÎ@ø‡+Ÿrp~£)9Ç©\ƒn­’˜çÉ>RC‚É¾ÒŞ—íd	CâúŠ<¼õNŒï:(Xm¶Wˆ;#™j‹Z2$¯¹¹ú ]^öKõÀ£]BqjRù¸ÿæq=É÷ÔÚŸ‡H~[\ù›Œ3µI[sÕ¥Ú´=]ßØĞÇÔâÛöÙ1ĞÊ®¦ŠBhín¥\ÿú^¿OkE¡8ºT>éo«}ò^Ç¬ŸiĞş¶<€dĞÏ7.ÇÈ3·w[ãåkG¼ÿRwO‹«u.¢˜ZC®<n¹!wãÅ‹İaÆ'¥ï„Õ–¤«ñéM‚ÿ@DÁ½DêÄVT‘y€Éø§‰X¾½0DòRfo'‹hE¼Ÿ÷áç?ıö5ğ›ÿ8şOì)Ùèİ~!İö>ŒÃK—ïê´Œşªk	¶ti¹L‡æHL*Î¦÷q¾wö¦ô´ì°íGâè‡#ú->	èWêwş4JÖÓ<nœúÚyàôÏóä»ñÿĞ­ÿÇ%j=¯æXÀ'h_¼ş2Y?@¯³C$_ïN°ë.TÉ$¯òOaQöÊãÑ˜ÿ×ÿ|‹İÖ§v}¯)UõÿçÖÔäx˜ñÜ‘¤TµÜíÃhOoµìñÂÿƒÚe§—B¤Îæ¬_oÇÒh¿èExZWÀ’ô
Ñ`ÈÛåËş$´\øŠËA©=¥sağı:e‘y àUËîšôàSÎ<ş¤mW¬eõ›Š¢?ÄùâK×#Ã£Ï¹zA8ôÈ«êÒb_“Éúpåk"­@ê½Â}½œxWÖ¹ ÏJÎ¿ÄãÅ XèDÁ¦Üº±áZÉ­lœˆ®ri!
­W‹%‡€ÖğŒ„[ùôöX±¤(*èäÒxUèJS²œG{™òÄÆ\Y'nUU!Ö X;;-zĞ¯Ìä¤›şIŸZÌ²™B•óğB<nìêöğg\à~£)0Ã÷ùŸy~à>ÛÄ¹Ôr¿h'ùúdq½Q^á>UñKI—K'Ïxõ†c'GG‹dÀñ¯?­
7V×>[Ü“3
>‡É{ı#âTòÎª1£Ø1Â5“|¿6;ø—PZQa·Ïø…Ò993~äÉ¶l:	ºÙgŞw×k1¸& §¡åØ¦áÑ˜õxAÁ¥™³Æµ“Jw|¡²Æ8&äïLì7påtÖ×¿Şy÷ßzëWÓLgºĞwô—4ğ´§i|cÚ5Pfã˜/]Ïñ¨ÛG“õ¿$OI9ÇYÅºÁŞ§ßò÷Ş»úF|êf»ÃFÏñ¼ÿOƒÏ­EüThÃ•˜_ÃK5|Ov^Ua\h™uíœƒëPÚ÷ ª2ºbÌÏÒçV#gâçc®Ü˜¥8@o µ[–÷¨˜5@
6zxS°·‚56
VR«›ä‚7ã.5-Åj‰NĞL-ÉèÕ¯êà­¹ğüU¯Ê ;ŞuqV•ÂÚ'>Ş*ñJ©­v.ß3Ş]«§*qş ø’Wƒßà¡¿PQ¡a‡k¾cØ/ÔR•g0èºò…š‰É*•Oÿe¿ôiXpoÇ»2ïüş¿³xØ‡JOîŸ‡ûª<0[Ã~~w9ğûråƒgŸg‹Dã¶<C†^kósÿ	§7”1‰ûÆ³E
Á	=5æ[IHº¼Æn³q¾lšGqÌ8©,<n¿üV“‚uĞ^®nÂà3éÍ'wü'96=üÉ7£-ÎO#x<ğùçÀOjlgÇi2/=i9üNZfíïƒ‘x=àÑÍQÙLæó“RéÈ¾ô½?ê'ùjpbÀ`nûr^¸Ï(™³şÃÁ¾}p=gö4³?÷n%aû+ÜO˜ÏŞ¼VOÙ’ËÚ–Ş–GlJÁiÛZVYëA¯¡&İ˜p©ÕÍ¢rÂıÎÕ4´!ù„@êê„ä³Ÿ¢òC×4O2µ±bízu#í†JMCø‹2Ÿ+ATïnäE¥éúìLŞ_hz8ãÔ™¶¯Ì[ëLït®[÷ÍÁOê…”Ÿš)!?—ıj›Ívó&×yEÖÿzEÖı'§zõG£Ã~