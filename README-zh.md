
# Milk-V Duo Examples
[English](./README.md) | 简体中文

本工程提供了在 Linux 环境下使用 C/C++ 开发应用的一些例子，可以在 `Milk-V Duo 系列` 设备上运行。

## 开发环境

- 使用本地的 Ubuntu 系统，推荐 `Ubuntu 22.04 LTS`
  <br>
  (也可以使用虚拟机中的 Ubuntu 系统、Windows 中 WSL 安装的 Ubuntu、基于 Docker 的 Ubuntu 系统)

- 安装编译依赖的工具:
  ```
  sudo apt-get install wget git make
  ```

- 获取 Examples
  ```
  git clone https://github.com/milkv-duo/duo-examples.git
  ```

- 加载编译环境
  ```
  cd duo-examples
  source envsetup.sh
  ```
  第一次加载会自动下载所需的编译工具链，下载后的目录名为`host-tools`，下次再加载编译环境时，会检测该目录，如果已存在则不会再次下载。

  加载编译环境时需要按提示输入所需编译目标：
  ```
  Select Product:
  1. Duo (CV1800B)
  2. Duo256M (SG2002) or DuoS (SG2000)
  ```
  如果目标板是 Duo 则选择 `1`，如果目标板是 Duo256M 或者 DuoS 则选择 `2`。由于 Duo256M 和 DuoS 支持 RISCV 和 ARM 两种架构，还需要按提示继续选择：
  ```
  Select Arch:
  1. ARM64
  2. RISCV64
  Which would you like:
  ```
  如果测试程序需要在 ARM 系统中运行，选择 `1`，如果是 RISCV 系统则选择 `2`。

  **同一个终端中，只需要加载一次编译环境即可。**

- 编译测试

  以`hello-world`为例，进入该例子目录直接执行 make 即可：
  ```
  cd hello-world
  make
  ```
  编译成功后将生成的 `helloworld` 可执行程序通过网口或者 USB-NCM 网络等方式传送到 Duo 设备中，比如[默认固件](https://github.com/milkv-duo/duo-buildroot-sdk/releases)支持的 USB-NCM 方式，Duo 的 IP 为`192.168.42.1`，用户名是`root`，密码是`milkv`。
  ```
  $ scp helloworld root@192.168.42.1:/root/
  ```
  发送成功后，在 ssh 或者串口登陆的终端中运行`./helloworld`，会打印`Hello, World!`
  ```
  [root@milkv]~# ./helloworld
  Hello, World!
  ```
  **至此，我们的编译开发环境就可以正常使用了**

## 如何创建自己的工程

根据需要，拷贝现有的例子，稍加修改即可。比如需要操作某个 GPIO，可以参考`blink`例子，LED 闪烁就是通过控制 GPIO 电平高低实现的，当前 SDK 提供的 GPIO 操作使用的是`WiringX`的库，已经针对 Duo 做了适配，平台初始化和控制 GPIO 的方法，可参考`blink.c`中的代码。

- 新建自己的工程目录`my-project`
- 复制`blink`例子中的`blink.c`和`Makefile`文件到`my-project`目录
- 将`blink.c`重命名为自己所需名字如`gpio_test.c`
- 修改`Makefile`中的`TARGET=blink`为`TARGET=gpio_test`
- 修改`gpio_test.c`，实现自己的代码逻辑
- 执行`make`命令编译
- 将生成的`gpio_test`可执行程序发送到 Duo 中运行

注意:
- 新建工程目录不是必须要放到 duo-examples 目录下的，可以根据自己的习惯放到其他位置，执行 make 编译命令之前，加载过 duo-examples 目录下的编译环境就可以了(`source /PATH/TO/duo-examples/envsetup.sh`)
- 在加载过编译环境(`envsetup.sh`)的终端里，不要编译其他平台如 ARM 或 X86 的 Makefile 工程，如需编译其他平台项目，需要新开终端。

# 各例子说明

## hello-world

一个简单的例子，不操作 Duo 外设，仅打印输出 "Hello, World!"，用来验证开发环境。

## blink

一个让 Duo 板载 LED 闪烁的例子，操作 GPIO 使用的是`wiringX`的库，`blink.c`代码中包含了`wiringX`中的平台初始化以及操作 GPIO 的方法。

注意:
<br>
当前 Duo 的默认固件上电后 LED 会自动闪烁，这个是通过开机脚本实现的，在测试该 blink 例子的时候，需要将 LED 闪烁的脚本禁用，在 Duo 的终端中执行:
```
mv /mnt/system/blink.sh /mnt/system/blink.sh_backup && sync
```
也就是将 LED 闪烁脚本改名，重启 Duo 后，LED 就不闪了。
<br>
测试完我们C语言实现的 blink 程序后，如果需要恢复 LED 闪烁脚本，再将其名字改回来，重启即可：
```
mv /mnt/system/blink.sh_backup /mnt/system/blink.sh && sync
```

## I2C

App|Description
---|---
[bmp280_i2c](i2c/bmp280_i2c) | 通过 I2 C接口连接温度气压传感器 `BMP280`，读取当前温度和气压值
[vl53l0x_i2c](i2c/vl53l0x_i2c) | 通过 I2C 接口使用 TOF 测距传感器 `VL53L0X` 模块，读取测量到的距离
[ssd1306_i2c](i2c/ssd1306_i2c) | 通过 I2C 接口在 `SSD1306 OLED` 显示屏上显示字符串
[adxl345_i2c](i2c/adxl345_i2c) | 通过 I2C 接口读取 `ADXL345` 获得的加速度数据，每1s读取一次
[lcm1602_i2c](i2c/lcm1602_i2c) | 通过 I2C 接口在 `1602 LCD` 屏幕上显示字符串
[lcm2004_i2c](i2c/lcm2004_i2c) | 通过 I2C 接口在 `2004 LCD` 屏幕上显示字符串
[tcs34725_i2c](i2c/tcs34725_i2c) | 通过 I2C 接口读取 `TCS34725` 颜色传感器，并将获得的数据输出

## SPI

App|Description
---|---
[max6675_spi](spi/max6675_spi) | 通过 SPI 接口连接K型热电偶测量模块 `MAX6675`，测量当前传感器上的温度
[rc522_spi](spi/rc522_spi) | 通过 SPI 接口连接 `RC522 RFID` 读写模块，读取卡片ID和类型并输出到屏幕

## AnalogRead (ADC)

此示例启用 CV180x 12 位分辨率模数转换器模块，称为 SARADC。 [/adc/](/adc) 有两种示例， [sh script](adc/adcRead.sh) 和 [C source file](adc/adcRead.c)，它们可以非常容易的在 Duo 上使用 TinyCC 编译。

关于 SARADC 的使用可以参考 [CV180x CV181x Peripheral Drive Operation Guide](adc/PeripheralDriverOperationGuide_en.pdf)。

# 关于 Milk-V

- [官方网站](https://milkv.io/)

# 技术论坛

- [MilkV Community](https://community.milkv.io/)
