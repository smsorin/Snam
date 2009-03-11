AC_PREREQ(2.61)
AC_INIT([snam], [0.1], [smsorin@gmail.com])
AC_CONFIG_SRCDIR([node.cc])
AM_INIT_AUTOMAKE

AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_RANLIB

AC_CHECK_LIB([GL], [glVertex3f])
AC_CHECK_LIB([GLU], [gluPerspective])
AC_CHECK_LIB([glut], [glutInit])

AC_CHECK_HEADERS([sys/time.h GL/gl.h GL/glu.h GL/glut.h])
AC_HEADER_STDC
AC_CHECK_FUNCS([sqrt gettimeofday tan])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
