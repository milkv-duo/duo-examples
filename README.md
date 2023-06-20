
# Milk-V Duo Examples
简体中文 | [English](./README-en.md)

<br>

本工程提供了在Linux环境下使用C/C++开发应用的一些例子，可以在`Milk-V Duo`设备上运行

<br>

## 开发环境

- 使用本地的Ubuntu系统，推荐 `Ubuntu 20.04 LTS`
  <br>
  (也可以使用虚拟机中的Ubuntu系统、Windows中WSL安装的Ubuntu、基于Docker的Ubuntu系统)
- 安装编译依赖的工具:
```
sudo apt-get install wget git make
```

## 获取 Examples
```
git clone https://github.com/milkv-duo/milkv-duo-examples.git
```

## 加载编译环境

```
cd milkv-duo-examples
source envsetup.sh
```
第一次加载会自动下载所需的SDK包，大小为25M左右，下载完会自动解压到`milkv-duo-examples`下，解压后的目录名为`duo-sdk`，下次加载时检测到已存在该目录，就不会再次下载了
<br><br>
*注: 如果因为网络原因无法完成SDK包的下载，请通过其他途径获取到`duo-sdk.tar.gz`包，手动解压到`milkv-duo-examples`目录下，重新`source envsetup.sh`*

## 编译测试
以`hello-world`为例，进入该例子目录直接执行make即可
```
cd hello-world
make
```
编译成功后将生成的`helloworld`可执行程序通过网口或者RNDIS网络等方式传送到Duo设备中，比如[默认固件](https://github.com/milkv-duo/milkv-duo-buildroot-sdk/releases)支持的RNDIS方式，Duo的IP为`192.168.42.1`，用户名是`root`，密码是`milkv`
```
$ scp helloworld root@192.168.42.1:/root/
```
发送成功后，在ssh或者串口登陆的终端中运行`./helloworld`，会打印`Hello, World!`
```
[root@milkv]~# ./helloworld
Hello, World!
```
至此，我们的编译开发环境就可以正常使用了

## 如何创建自己的工程

根据需要，拷贝现有的例子，稍加修改即可。比如需要操作某个GPIO，可以参考`blink`例子，LED闪烁就是通过控制GPIO电平高低实现的，当前SDK提供的GPIO操作使用的是`WiringX`的库，已经针对Duo做了适配，平台初始化和控制GPIO的方法，可参考`blink.c`中的代码

- 新建自己的工程目录`my-project`
- 复制`blink`例子中的`blink.c`和`Makefile`文件到`my-project`目录
- 将`blink.c`重命名为自己所需名字如`gpio_test.c`
- 修改`Makefile`中的`TARGET=blink`为`TARGET=gpio_test`
- 修改`gpio_test.c`，实现自己的代码逻辑
- 执行`make`命令编译
- 将生成的`gpio_test`可执行程序发送到Duo中运行

注意:
- 新建工程目录不是必须要放到milkv-duo-examples目录下的，可以根据自己的习惯放到其他位置，执行make编译命令之前，加载过milkv-duo-examples目录下的编译环境就可以了(`source /PATH/TO/milkv-duo-examples/envsetup.sh`)
- 在加载过编译环境(`envsetup.sh`)的终端里，不要编译其他平台如ARM或X86的Makefile工程，如需编译其他平台项目，需要新开终端

<br>

# 各例子说明

## hello-world

一个简单的例子，不操作Duo外设，仅打印输出"Hello, World!"，用来验证开发环境

## blink

一个让Duo板载LED闪烁的例子，操作GPIO使用的是`wiringX`的库，`blink.c`代码中包含了`wiringX`中的平台初始化以及操作GPIO的方法

注意:
<br>
当前Duo的默认固件上电后LED会自动闪烁，这个是通过开机脚本实现的，在测试该blink例子的时候，需要将LED闪烁的脚本禁用，在Duo的终端中执行:
```
mv /mnt/system/blink.sh /mnt/system/blink.sh_backup && sync
```
也就是将LED闪烁脚本改名，重启Duo后，LED就不闪了
<br>
测试完我们C语言实现的blink程序后，如果需要恢复LED闪烁脚本，再将其名字改回来，重启即可
```
mv /mnt/system/blink.sh_backup /mnt/system/blink.sh && sync
```

<br>

# 关于 Milk-V

- [官方网站](https://milkv.io/)

<br>

# 技术论坛
- [MilkV Community](https://community.milkv.io/)


