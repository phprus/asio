AC_INIT(asio, [1.24.0])
AC_CONFIG_SRCDIR(include/asio.hpp)
AM_MAINTAINER_MODE
AM_INIT_AUTOMAKE([tar-ustar])

AC_CANONICAL_HOST
AM_PROG_CC_C_O
AC_PROG_CXX
AC_LANG(C++)
AC_PROG_RANLIB
PKG_INSTALLDIR

AC_DEFINE(_REENTRANT, [1], [Define this])

AC_ARG_WITH(boost,
  AC_HELP_STRING([--with-boost=DIR],[location of boost distribution]),
[
  if test "${withval}" = no; then
    STANDALONE="yes"
  else
    if test "${withval}" != system; then
      CPPFLAGS="$CPPFLAGS -I${withval}"
      LIBS="$LIBS -L${withval}/stage/lib"
    fi
  fi
],
[
  STANDALONE="yes"
])

AC_ARG_ENABLE(separate-compilation,
[  --enable-separate-compilation  separate compilation of asio source],
[
  SEPARATE_COMPILATION=yes
])

if test "$STANDALONE" != yes; then
  AC_CHECK_HEADER([boost/noncopyable.hpp],,
  [
    echo "Can't find boost headers. Please check the location of the boost"
    echo "distribution and rerun configure using the --with-boost=DIR option."
    echo "Alternatively, run with --without-boost to enable standalone build."
    exit 1
  ],[])
fi

AC_ARG_WITH(openssl,
  AC_HELP_STRING([--with-openssl=DIR],[location of openssl]),
[
  CPPFLAGS="$CPPFLAGS -I${withval}/include"
  LIBS="$LIBS -L${withval}/lib"
],[])

AC_CHECK_HEADER([openssl/ssl.h],,
[
  OPENSSL_FOUND=no
],[])

if test x$OPENSSL_FOUND != xno; then
  LIBS="$LIBS -lssl -lcrypto"
fi

AM_CONDITIONAL(HAVE_OPENSSL,test x$OPENSSL_FOUND != xno)

WINDOWS=no
case $host in
  *-*-linux*)
    CXXFLAGS="$CXXFLAGS -pthread"
    LDFLAGS="$LDFLAGS -pthread"
    LIBS="$LIBS -lrt"
    ;;
  *-*-solaris*)
    if test "$GXX" = yes; then
      CXXFLAGS="$CXXFLAGS -D_PTHREADS"
    else
      # We'll assume Sun's CC.
      CXXFLAGS="$CXXFLAGS -mt"
    fi
    LIBS="$LIBS -lsocket -lnsl -lpthread"
    ;;
  *-*-mingw32*)
    CXXFLAGS="$CXXFLAGS -mthreads"
    LDFLAGS="$LDFLAGS -mthreads"
    LIBS="$LIBS -lws2_32 -lmswsock"
    WINDOWS=yes
    ;;
  *-*-mingw64*)
    CXXFLAGS="$CXXFLAGS -mthreads"
    LDFLAGS="$LDFLAGS -mthreads"
    LIBS="$LIBS -lws2_32 -lmswsock"
    WINDOWS=yes
    ;;
  *-pc-cygwin*)
    CXXFLAGS="$CXXFLAGS -D__USE_W32_SOCKETS -D_WIN32_WINNT=0x0601"
    LIBS="$LIBS -lws2_32 -lmswsock"
    WINDOWS=yes
    ;;
  *-apple-darwin*)
    CXXFLAGS="$CXXFLAGS"
    LDFLAGS="$LDFLAGS"
    ;;
  *-*-freebsd*)
    CXXFLAGS="$CXXFLAGS -pthread"
    LDFLAGS="$LDFLAGS -pthread"
    ;;
  *-*-netbsd*)
    CXXFLAGS="$CXXFLAGS -pthread"
    LDFLAGS="$LDFLAGS -pthread"
    ;;
  *-*-haiku*)
    CXXFLAGS="$CXXFLAGS -lnetwork"
    LDFLAGS="$LDFLAGS -lnetwork"

esac

if test "$GXX" = yes; then
  CXXFLAGS="$CXXFLAGS -ftemplate-depth-256"
fi

if test "$SEPARATE_COMPILATION" = yes; then
  CPPFLAGS="$CPPFLAGS -DASIO_SEPARATE_COMPILATION"
fi

AC_MSG_CHECKING([whether C++17 is enabled])
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM(
    [[#if __cplusplus < 201703L]]
    [[#error C++17 not available]]
    [[#endif]])],
  [AC_MSG_RESULT([yes])
    HAVE_CXX17=yes;],
  [AC_MSG_RESULT([no])
    HAVE_CXX17=no;])

AC_MSG_CHECKING([whether C++20 is enabled])
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM(
    [[#if __cplusplus < 202002L]]
    [[#error C++20 not available]]
    [[#endif]])],
  [AC_MSG_RESULT([yes])
    HAVE_CXX20=yes;],
  [AC_MSG_RESULT([no])
    HAVE_CXX20=no;])

AC_MSG_CHECKING([whether coroutines are enabled])
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM(
    [[#if defined(__clang__)]]
    [[# if (__cplusplus >= 201703) && (__cpp_coroutines >= 201703)]]
    [[#  if __has_include(<experimental/coroutine>)]]
    [[#   define ASIO_HAS_CO_AWAIT 1]]
    [[#  endif]]
    [[# endif]]
    [[#elif defined(__GNUC__)]]
    [[# if (__cplusplus >= 201709) && (__cpp_impl_coroutine >= 201902)]]
    [[#  if __has_include(<coroutine>)]]
    [[#   define ASIO_HAS_CO_AWAIT 1]]
    [[#  endif]]
    [[# endif]]
    [[#endif]]
    [[#ifndef ASIO_HAS_CO_AWAIT]]
    [[# error coroutines not available]]
    [[#endif]])],
  [AC_MSG_RESULT([yes])
    HAVE_COROUTINES=yes;],
  [AC_MSG_RESULT([no])
    HAVE_COROUTINES=no;])

if test "$GXX" = yes; then
  if test "$STANDALONE" = yes; then
    if test "$HAVE_CXX17" = no; then
      HAVE_CXX17=yes
      CPPFLAGS="-std=c++17 $CPPFLAGS"
    fi
  fi
fi

AM_CONDITIONAL(STANDALONE,test x$STANDALONE = xyes)

AM_CONDITIONAL(SEPARATE_COMPILATION,test x$SEPARATE_COMPILATION = xyes)

AM_CONDITIONAL(WINDOWS_TARGET,test x$WINDOWS != xno)

AM_CONDITIONAL(HAVE_CXX20,test x$HAVE_CXX20 = xyes)

AM_CONDITIONAL(HAVE_COROUTINES,test x$HAVE_COROUTINES = xyes)

AC_CONFIG_FILES([asio.pc])

AC_OUTPUT([
  Makefile
  include/Makefile
  src/Makefile
  src/tests/Makefile
  src/tests/properties/Makefile
  src/examples/cpp11/Makefile
  src/examples/cpp14/Makefile
  src/examples/cpp17/Makefile
  src/examples/cpp20/Makefile])
