#!/bin/bash

SDK_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
echo "SDK_DIR: ${SDK_DIR}"

MILKV_DUO_SDK=${SDK_DIR}/duo-sdk
TOOLCHAIN_DIR=${MILKV_DUO_SDK}/riscv64-linux-musl-x86_64

SDK_URL="https://github.com/milkv-duo/duo-app-sdk/releases/download/duo-app-sdk-v1.2.0/duo-sdk-v1.2.0.tar.gz"

function get_duo_sdk()
{
  pushd ${SDK_DIR}

  echo "SDK_URL: ${SDK_URL}"
  sdk_file=${SDK_URL##*/}
  echo "sdk_file: ${sdk_file}"

  wget ${SDK_URL} -O ${sdk_file}
  if [ $? -ne 0 ]; then
    echo "Failed to download ${SDK_URL} !"
    return 1
  fi

  if [ ! -f ${sdk_file} ]; then
    echo "${sdk_file} not found!"
    return 1
  fi

  echo "Extracting ${sdk_file}..."
  tar -xf ${sdk_file}
  if [ $? -ne 0 ]; then
    echo "Extract ${sdk_file} failed!"
    return 1
  fi

  [ -f ${sdk_file} ] && rm -rf ${sdk_file}

  popd
}

if [ ! -d ${MILKV_DUO_SDK} ]; then
  echo "SDK does not exist, download it now..."
  get_duo_sdk
  if [ $? -ne 0 ]; then
    echo "Get SDK failed!"
    return 1
  fi
fi

export TOOLCHAIN_PREFIX=${TOOLCHAIN_DIR}/bin/riscv64-unknown-linux-musl-
export SYSROOT=${MILKV_DUO_SDK}/rootfs

export LDFLAGS="-mcpu=c906fdv -march=rv64imafdcv0p7xthead -mcmodel=medany -mabi=lp64d"
# -Os
export CFLAGS="-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64"

echo "SDK environment is ready"

