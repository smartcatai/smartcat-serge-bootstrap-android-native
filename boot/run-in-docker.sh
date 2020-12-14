#!/bin/sh
set -e

. /data/boot/bootstrap.sh

/usr/bin/dumb-init -- "$@"