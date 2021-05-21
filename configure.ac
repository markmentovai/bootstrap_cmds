AC_INIT([bootstrap_cmds], [121.100.1])
AC_CONFIG_AUX_DIR([autotools])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC()
AC_PROG_LEX([noyywrap])
AC_PROG_YACC()
AC_CONFIG_FILES([
  Makefile
  migcom.tproj/Makefile
])

AC_CANONICAL_HOST()
case "${host}" in
  *-apple-darwin*)
    COMPAT_CPPFLAGS=
    ;;
  *)
    COMPAT_CPPFLAGS='-I$(top_srcdir)/compat/non_apple'
    ;;
esac
AC_SUBST([COMPAT_CPPFLAGS])

AC_OUTPUT()
