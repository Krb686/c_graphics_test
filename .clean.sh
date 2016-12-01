#!/bin/bash

[[ -f "aclocal.m4" ]] && rm -f "aclocal.m4"
[[ -d "autom4te.cache" ]] && rm -rf "autom4te.cache"
[[ -f "config.log" ]] && rm -f "config.log"
[[ -f "config.status" ]] && rm -f "config.status"
[[ -f "configure" ]] && rm -f "configure"
[[ -h "depcomp" ]] && rm -f "depcomp"
[[ -h "install-sh" ]] && rm -f "install-sh"
[[ -f "Makefile" ]] && rm -f "Makefile"
[[ -f "Makefile.in" ]] && rm -f "Makefile.in"
[[ -h "missing" ]] && rm -f "missing"
rm -f src/*.o
rm -f src/*.in
rm -f src/Makefile
rm -rf src/.deps
rm -f src/example
