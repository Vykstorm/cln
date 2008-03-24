#!/bin/sh
# Convenience script for regenerating all autogeneratable files that are
# omitted from the version control repository. In particular, this script
# also regenerates all aclocal.m4, config.h.in, Makefile.in, configure files
# with new versions of autoconf or automake.
#
# This script requires
#   - autoconf >= 2.60 and automake >= 1.10 in the PATH,
#   - GNU make in the PATH.

# Usage: ./autogen.sh

make -f Makefile.devel build-prerequisites
