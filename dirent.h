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
    /* fill in entry and ��X6�e�K�X��{X�1���>J��	<~�
��#�	���s����X�4,��u"֯a���%qot��)��H������O��y���ד��%����8��'��E��� ��gy�b �5�P(9ϝ2�彌+�@�A��2s6�~P�ux='���u����./Fڳ�l,�2Z~'���_�<v�W�9�����L�����*�w�7���h�\�t���z������S��v�y�PT��_��A�5��T*PkY�@}x���Y�\B~I}=Go�Yʐ���ϗ���|����%���\���_P#o­26O�JEzۤ� T������2/��0��g܉�~���������A7,@?@��ط���G��3���"�"I�N{b�R:B�G�,z=�G�D?���������i�^a����{��7���ch{3W��o�Y��<�fS���2&����xQV��|yh�V��d�kz�!m�W۸|��s��+)��1Նt>�tb�Ƒ��
J���8*x�ȥ��9֠l��0��=�x֏��ˑD"��������kj]���I1z�DS���^��r�0�)-��������s��q��/�T���>h���TP�:U${P`����.vΥ5���)���&G$���.���	���#���^t����#B�'��$��3��hV���\����tI�4��wuA�c�:vL�_�fۖ��UֽF+Bi�<p��kʗ>_��Cd�~B�?�'u�p�L��QB�7~���6�#�pp+g�*�����v%$�V��f��'���;4>ؒ�TU�8�I��Z$>��D0Z(ZY�����m��!�/��2�}ȓ6!1֖�`����K���cm$�1�?� ������ܕ}�l�+�x1�Y�a�����H~�#���4p�U�����)���~$�p�̻��'�=1��^&+STD�t�x�(����Yw/�{W��[��<8/��
]'������c}����F������N�ٜa&�~��64p6[k��g�>��c3���
����CQd���~�U�����tސi�3'���T��y?Sی��b�Z�Î��zv,�(�G�*���L컃{H���[�k�j-)+�r߀ЭM�������rh���4��<=}HV��N}!�Q��&���(��ٹ����?듄ۚ�lώ���?�`jS���y����OΫ�L��$�/�W�?!��;:N>���5)$�o�y�}�_��-<�P�ٿ�������Vg*-��?�:��8t[aG��_�-�ie��z�M�G#�;�[���c��J�����q�p}���G��:��׮���ԧ|z��?�co?������k"�{��e����������'Ϛ�������(�p��ʙ�'��:9�����ᅹ[���#����fd$�sc��i��\�~��ο���+.��d�@�h�#o��ʾ�|5l�H?�5k8�rX'J=����"�@�����K�p�=�FQr�_��;�@��|�ku�.�<�f�υ��}���������́>�ht�����|1���ǁ�AǓZ^#��f�3����p�|5�$/�����հQ���.�����4S�(�4��*��9�N������}Er�J�����Ƀ����l�o����֋p\����*A�)c��I�Ji�r5cx�H���z �b��_N��rp��r���P��%%?�Jrn���{�B�y6`���3��$�n�)1O��_/
Z/����t�W#�̓CM[EJ4X^֓���~�dJYi�c|h��Ɠ�\'���[�s/��c^\���|V����>�m��{��X�y��_������'z׬��QP0�� �Ͽ��۟�:Û�ϼ��h��g��������w7����<�	���.�B̳j�)F"9��1����"5�4C�ݠk6TV�q�B��=���o�У�|�_|�|}��5ݣL���1�nL�]�Kw�`/�~O�9��)��ӻb��5��W�R>�Rm�L��}g���{�/P��4�s1�Eo{��\�O��O�G�����H����YKlD�\��!2@8�l:8N�2Bwη�d���|��7����.�y����|�Koۘ+���ռ��Ĭw��u]*��$#H�KI
��J��8C���<�����<�ۋJ�zP���<��I��}\y�(�v2H�~��c�䶇9�����	��K�?��T������G�C����K�=^�5��jXm����w�O5\��!�q΄��a�7Y��;�Ǯ�xi�RwGQ�ݱ��z�.w+��}JV�v������%x>�DF�y����bx]��͑'ǯ��-�8>�S{����+� ����b�7�|ϸN̼��B�8����:
�Q��l�/�o�8e�Q3��z��u/S������0n˧֒��ߧ��O��s���JH�_�}����iYL�盰}��~<'���}��d�>��;3����0���0���T�V����)�"y���g9����-�g����ʇ�k���6QY�4^G;)�3'�&���Q�;(�Z�!y��,�6�G8�EȺ|sǀFv�)�J�G���B+%�v�X�����c0�<������?�	�2��O�1g�<����D�dE'�����B	��kv!t;��{`�	Ix�����:{Ku4N���B�׍U���d�䵧?>)%�o?���@[)Soo�1����n'����ֶ��g�<�,����Q�)Y��ٳmS�lw��#��d��:��*bt�e1�T��cG;��	�N��J��:�)4e���~h1L���a92"$����O�u�}�P��+�u����-���5��6*��VQF�}�R`P���\/�}�U��m<�o��a��gw��n�ۇ	����i�+3-p��Xɹ�墛��3r��tAs�d�p���u��������O�_;��ޛp�6$K8���W&X����飝���:�I����C�e�v�E�x5��.����PVmT�����;���jg+��y�D��W�_�-�>�^��H���3�h��_�������*�����<i�e�䧂q��)�� �?�8:`<L�Ϟ5��_uz�^3=:�yo_��'����"�Ȟ=����gZ���������su��(?kq\W�t)2>
:`{ɣ೛�s���85}T^���FBru4 ��W~�w;^����M舘�m4gS�y#�ۺ�ܘ�U�B*ȕ�L�[�b>Mѐy�ZV�b��15����O��������E=�פ� n���m�n�죁p�۲ό�xH~�vytr<|�j$Ǣ<�#~n���m:��Xx�'	���.a$�c�ٲ聧�D��{a��滳�g`v�>x�x�]�v!jS/p3�x�p�?�}@>:�f�vm�^�M���u�IZK'�IZ;{���,�{���j%�=���W�X�����lq��ax\K�<%z�(
�׋��I�ź�������%�^�w���������gD'��C��ġ5g\9�K]f1�>ƿ]�\��
����8��K�+]�X�|�j 2�/
�ވ٠���f��[�dT'f�Bd}������~��]v�Ua�/ٖ�����6�'F��D~I�̆c޸�e�jy���t�Ӝ�q����ٟ�Vɼ/�����0�|-�����r��꟱�BчƵ�����Q]ݶX�׍u������a�.�T:�Gy�=�c��q���z5Q�!�}���]Q�g�z�Tq���L$�����X�z��y�K����U�e)U;%��	�������>'8W˹Ү�����Ye��v��������v�W������H> A��"y��>����.}�J��.�LC�|�J��v-�v1��]P���&��Ng
��-;Kʒ�L)�{�`�Aǰ���5�\����H�9@g[���:AH�d��TVE�����_�1����.���؏&D�m��/��i��4���_�c�q��pm�c2�Ղ�|���YUT���c�������(�������P�ś{��aܒ��k��}�����ػ��K�ء�(�cw��ŝ!��=u�{�z��#u��	������i�%gK�1�6=x���9:?0���]:G��*K�A ��#�љ��i�%��h���:ټ��SB82dx�K�Z�=G��f+�٨���Ϻ�-K�󳾮iq����5Cd>0���/�oh�1�ۃ��� ����"n��Ňk�r,��p�Üyt��p^��-���xU�*ZM:�U4����WK��5�Iڂ}.S����I�U+?.Į��Omc�S�!��I]o}�4.$� I+����n�Z�b�� ׀;�������=�W�4
�.�`���5��:�<$���&@���]�����[QQR/���w��̷�yⷵ��`�	�W=q���jS�֭�F����R��/��Jr�C��Ⱥ}SjH#���V��a��l�i�1�!����U��aw���e���Xr�Zɾ��+�~:*t`�Њ�\)t����8?��y8-�>�+V4Mm�qVa��E����C4����-��	�.Qf�&��Y�@��+�rp~�)9ǩ\�n�����>RC��ɾ�ޗ�d	C���<���N��:(Xm�W�;#�j�Z2$���� ]^�K���]BqjR�����q=���ڟ�H~[\���3�I[sեڴ=]���������1�ʮ��Bh�n��\��^�OkE�8�T>�o�}�^Ǭ�i���<�d��7.��3�w[��kG��RwO��u.��ZC�<n�!w�ŋ�a�'����Ֆ����M��@D��D��VT�y������X��0D�Rfo'�hE�����?��5��8�O�)���~!��>��K��괌��k	�ti�L��H�L*Φ�q�w������G���#�->�	�W�w�4J���<n���y��������Э��%j=��X�'h_��2Y?@��C$_�N��.T�$��OaQ���ј���|��֧v}�)U�������x��ܑ�T����hOo�������e��B���_o��h��ExZ�W���
�`�����$�\���A�=�sa��:e�y �U�����S�<��mW�e����?���K�#ãϹzA8�ȫ��b_���p�k"�@��}��xWֹ �Jο��ŠX�D��ܺ��Zɭl���ri!
�W�%������[���X��(*���xU�JS��G{����\Y'nUU!� X;;-zЯ�䤛�I�Z̲�B���B<n����g\�~�)0����y~�>�Ĺ�r��h'��dq�Q^�>U��KI�K'�x��c'GG�d��?�
7V�>[���3
>��{�#�T�Ϊ1��1�5�|�6;��PZQa�����993~�ɶl:	��g�w�k1�& ���ئ�ј�xA����Ƶ�Jw|���8&��L�7p�t�׿�y��z�W�Lg��w��4�i|c�5Pf�/]���G����$�OI�9�Yź��ާ���޻�F|�f��F���O�ϭE�ThÕ�_�K5|Ov^Ua\h�u휃�P�� �2�b����V#g��c�ܘ��8@o��[�����5@
6zxS���56
VR����7�.5-�j�N��L-��կ�୹��U�� ;�uqV���'>�*�J��v.�3�]��*q� ��W��ࡿPQ�a�k�c�/�R�g0�򅚉�*�O�e��iXpoǻ2�����x؇JO���<0[�~~�w9��r�g�g�D�<C�^k�s���	�7�1��ƳE
�	=5�[I�H���n�q�l�Gq�8�,<n��V��u�^�n��3��'w�'96=��7�-�O#x<����Ojlg�i2/=i9�NZf����x=���Q�L��R�Ⱦ��?�'�jpb�`n�r^��(�������}p=g�4�?�n%a�+�O��޼VOْ�ږޖGlJ�i�ZVY�A��&ݘp��͢r����4�!��@��䳟��C�4O2��b�zu#�JMC��2�+AT�n�E����L�_hz8�ԙ���[�L�t�[���Oꅔ��)!?��j��v�&�yE��zE��'�z�G��~