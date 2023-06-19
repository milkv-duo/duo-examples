#!/bin/bash

SDK_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)
echo "SDK_DIR: ${SDK_DIR}"

MILKV_DUO_SDK=${SDK_DIR}/duo-sdk
SDK_URL="https://github.com/milkv-duo/milkv-duo-buildroot-sdk/releases/download/20230616/duo-sdk.tar.gz"

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
fi

export TOOLCHAIN_PREFIX=${MILKV_DUO_SDK}/bin/riscv64-unknown-linux-musl-
export SYSROOT=${MILKV_DUO_SDK}/riscv64-buildroot-linux-musl/sysroot

export LDFLAGS="-mcpu=c906fdv -march=rv64imafdcv0p7xthead -mcmodel=medany -mabi=lp64d"
# -Os
export CFLAGS="-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64"

echo "SDK environment is ready"

