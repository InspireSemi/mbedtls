#!/bin/sh

CMD=riscv64-unknown-linux-gnu-gcc

if [ -x "$(command -v "$CMD")" ]; then
    echo "$CMD is in \$PATH"
else
    echo You must source riscvtoolspath.sh to set the path prior to running this script
    exit 1 	
fi

export CC=riscv64-unknown-linux-gnu-gcc
export AR=riscv64-unknown-linux-gnu-ar
export LD=riscv64-unknown-linux-gnu-ld
#export SHARED=1


CFLAGS="-DMBEDTLS_CONFIG_FILE='<mbedtls/riscv_linux.h>'"  make clean
CFLAGS="-DMBEDTLS_CONFIG_FILE='<mbedtls/riscv_linux.h>'"  make
