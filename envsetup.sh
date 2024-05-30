#!/bin/bash

SDK_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
echo "SDK_DIR: ${SDK_DIR}"

MILKV_DUO_SDK=${SDK_DIR}/duo-sdk
TOOLCHAIN_DIR=${MILKV_DUO_SDK}/riscv64-linux-musl-x86_64

SDK_URL="https://github.com/milkv-duo/duo-sdk.git"

function get_duo_sdk()
{
  pushd ${SDK_DIR}

  git clone ${SDK_URL}
  if [ $? -ne 0 ]; then
    echo "Failed to download ${SDK_URL} !"
    return 1
  fi

  popd
}

if [ ! -d ${MILKV_DUO_SDK} ]; then
  echo "SDK does not exist, download it now..."
  get_duo_sdk
  if [ $? -ne 0 ]; then
    echo "Get the SDK failed!"
    return 1
  fi
else
  if [ ! -d ${MILKV_DUO_SDK}/.git ]; then
    echo "SDK is not the latest one, re-downloading ..."
    rm -rf ${MILKV_DUO_SDK}
    get_duo_sdk
    if [ $? -ne 0 ]; then
      echo "Re-downloading the SDK failed!"
      return 1
    fi
  fi
fi

export TOOLCHAIN_PREFIX=${TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-musl-
export SYSROOT=${MILKV_DUO_SDK}/rootfs
export CC=${TOOLCHAIN_PREFIX}gcc

export CFLAGS="-mcpu=c906fdv -march=rv64imafdcv0p7xthead -mcmodel=medany -mabi=lp64d"
# -Os
export LDFLAGS="-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64"

echo "SDK environment is ready"

