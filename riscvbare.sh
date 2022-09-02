#!/bin/sh

CMD=riscv64-unknown-linux-gnu-gcc

if [ -x "$(command -v "$CMD")" ]; then
    echo "$CMD is in \$PATH"
else
    echo You must source riscvtoolspath.sh to set the path prior to running this script
    exit 1 	
fi

export CC=riscv64-unknown-elf-gcc
export AR=riscv64-unknown-elf-ar
export LD=riscv64-unknown-elf-ld

CFLAGS="-DMBEDTLS_CONFIG_FILE='<mbedtls/riscv_bare.h>'"  make clean
CFLAGS="-DMBEDTLS_CONFIG_FILE='<mbedtls/riscv_bare.h>'"  make lib
#DEBUG=1
