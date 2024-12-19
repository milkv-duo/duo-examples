# Milk-V Duo Examples
English | [简体中文](./README-zh.md)

This project provides some examples of developing applications using C/C++ in a Linux environment, which can be run on the `Milk-V Duo` device.

## Build environment on Ubuntu20.04

You can also use Ubuntu installed in a virtual machine, Ubuntu installed via WSL on Windows, or Ubuntu-based systems using Docker.

- Install the tools that compile dependencies.
  ```
  sudo apt-get install wget git make
  ```
- Get example source code
  ```
  git clone https://github.com/milkv-duo/duo-examples.git
  ```

- Prepare compilation environment
  ```
  cd duo-examples
  source envsetup.sh
  ```
  The first time you source it, the required compilation toolchain will be automatically downloaded. The downloaded directory is named `host-tools`. The next time the compilation environment is loaded, the directory will be detected. If it already exists, it will not be downloaded again.

  In the source process, you need to enter the required compilation target as prompted:
  ```
  Select Product:
  1. Duo (CV1800B)
  2. Duo256M (SG2002) or DuoS (SG2000)
  ```
  If the target board is Duo, select `1`, if the target board is Duo256M or DuoS, select `2`. Since Duo256M and DuoS support both RISCV and ARM architectures, you need to continue to select as prompted:
  ```
  Select Arch:
  1. ARM64
  2. RISCV64
  Which would you like:
  ```
  If the test program needs to be run on a ARM system, select `1`, if it is an RISCV system, select `2`.

  **In the same terminal, you only need to source it once.**

- Compile testing  

  Take hello-world as an example, enter the hello-world directory and execute make:
  ```
  cd hello-world
  make
  ```
  After the compilation is successful, send the generated `helloworld` executable program to the Duo device through the network port or the USB-NCM network. For example, the USB-NCM method supported by the [default firmware](https://github.com/milkv-duo/duo-buildroot-sdk/releases), Duo’s IP is 192.168.42.1, the user name is `root`, and the password is `milkv`
  ```
  scp helloworld root@192.168.42.1:/root/
  ```
  After sending successfully, run ./helloworld in the terminal logged in via ssh or serial port, and it will print `Hello, World!`
  ```
  [root@milkv]~# ./helloworld
  Hello, World!
  ```
  **At this point, our compilation and development environment is ready for use.**

## How to create your own project

You can simply copy existing examples and make necessary modifications. For instance, if you need to manipulate a GPIO, you can refer to the `blink` example. LED blinking is achieved by controlling the GPIO's voltage level. The current SDK utilizes the WiringX library for GPIO operations, which has been adapted specifically for Duo. You can find the platform initialization and GPIO control methods in the `blink.c` code for reference.

- Create your own project directory called `my-project`.
- Copy the `blink.c` and `Makefile` files from the `blink` example to the `my-project` directory.
- Rename `blink.c` to your desired name, such as `gpio_test.c`.
- Modify the `Makefile` by changing `TARGET=blink` to `TARGET=gpio_test`.
- Modify `gpio_test.c` to implement your own code logic.
- Execute the `make` command to compile.
- Send the generated `gpio_test` executable program to Duo for execution.
  
Note:

- Creating a new project directory is not mandatory to be placed within the `duo-examples` directory. You can choose any location based on your preference. Before executing the `make` compilation command, it is sufficient to load the compilation environment from the `duo-examples` directory (source /PATH/TO/duo-examples/envsetup.sh).
- Within the terminal where the compilation environment (envsetup.sh) is loaded, avoid compiling Makefile projects for other platforms such as ARM or X86. If you need to compile projects for other platforms, open a new terminal.

# Explanation of each example

## hello-world

A simple example that doesn't interact with Duo peripherals, only prints the output "Hello, World!" to verify the development environment.

## blink

This example demonstrates how to control an LED connected to a GPIO pin. It uses the WiringX library to toggle the GPIO pin's voltage level, resulting in the LED blinking.  

The `blink.c` code includes platform initialization and GPIO manipulation methods from the WiringX library.

To test the `blink` example, which involves LED blinking, you need to disable the script responsible for the automatic LED blinking on the default firmware of Duo. In the Duo terminal, execute the following command:
```
mv /mnt/system/blink.sh /mnt/system/blink.sh_backup && sync
```
This command renames the LED blinking script. After restarting Duo, the LED will no longer blink.

Once you have finished testing the `blink` program implemented in C, if you want to restore the LED blinking script, you can rename it back using the following command and then restart Duo:
```
mv /mnt/system/blink.sh_backup /mnt/system/blink.sh && sync
```

## I2C

App|Description
---|---
[bmp280_i2c](i2c/bmp280_i2c) | By connecting the temperature and pressure sensor `BMP280` through the I2C interface, you can read the current temperature and pressure values.
[vl53l0x_i2c](i2c/vl53l0x_i2c) | Read the Time of Flight sensor `VL53L0X` module to get the measured distance.
[ssd1306_i2c](i2c/ssd1306_i2c) | Displaying strings on `SSD1306` OLED display via I2C interface.
[adxl345_i2c](i2c/adxl345_i2c) | Read the acceleration data obtained by `ADXL345` through the I2C interface, once every 1 sencond.
[lcm1602_i2c](i2c/lcm1602_i2c) | Display string on `1602 LCD` screen via I2C interface.
[lcm2004_i2c](i2c/lcm2004_i2c) | Display string on `2004 LCD` screen via I2C interface.
[tcs34725_i2c](i2c/tcs34725_i2c) | Read the `TCS34725` color sensor through the I2C interface and output the obtained data.

## SPI

App|Description
---|---
[max6675_spi](spi/max6675_spi) | Connect the K-type thermocouple measurement module `MAX6675` through the SPI interface to measure the temperature on the current sensor.
[rc522_spi](spi/rc522_spi) | Connect the `RC522` RFID reading and writing module through the SPI interface, read the card ID and type and output it to the screen.

## AnalogRead (ADC)

This example enables the CV180x 12bit resolution analog-digital converter module, called SARADC. [/adc/](/adc) has two examples to run the module, first is an [sh script](adc/adcRead.sh) and the other one is [C source file](adc/adcRead.c), which can be easy compiled with TinyCC on Duo board.

The SARADC utilization reference is the [CV180x CV181x Peripheral Drive Operation Guide](adc/PeripheralDriverOperationGuide_en.pdf).

# About Milk-V

- [Official Website](https://milkv.io/)

# FORUM

- [MilkV Community](https://community.milkv.io/)
