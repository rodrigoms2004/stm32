# STM32 with FreeRTOS, libopencm3 and GCC, Warren Gay

[Book Source Code](https://github.com/Apress/Beg-STM32-Devel-FreeRTOS-libopencm3-GCC)

### Chapter 01 - Introduction
[Stewart Watkiss website](http://www.penguintutor.com/)

[FreeRTOS](https://freertos.org/)

[LibOpenCM3](https://libopencm3.org/)

### Chapter 02 - Software setup

https://developer.arm.com/

[LibOpenCM3 Repo](git://github.com/libopencm3/libopencm3.git)


[Arm’s C/C++ Compiler toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)


**Installing arm compiler**

```
tar xjf gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2
mv gcc-arm-none-eabi-9-2019-q4-major gcc-arm
sudo su
mv gcc-arm /opt


vim ~/.bashrc

vim ~/.bashrc

  # arm compiler
  export PATH=$PATH:/opt/gcc-arm/bin

source ~/.bashrc 
```

#### Installing st-flash

**Install it before libs**
```
sudo apt-get install libusb-1.0-0-dev
sudo apt-get install cmake
```

[Open source version of the STMicroelectronics Stlink Tools](https://github.com/texane/stlink)

```
cd ~
git clone https://github.com/texane/stlink.git
cd ./stlink
make
cd build/Release/
sudo make install
```

**Configure the Path**

```
vim ~/.bashrc


  # stlinl-tools
  export PATH=$PATH:$HOME/stlink/build/Release
  export LD_LIBRARY_PATH=/usr/local/lib


source ~/.bashrc 
```


**Check the st-flash version**
```
st-flash --version
v1.5.1-50-g3690de9
```

**Connect STM32 to the USB port**
```
st-info --probe
Found 1 stlink programmers
 serial: 303636434646353235313439373837383637313934343239
openocd: "\x30\x36\x36\x43\x46\x46\x35\x32\x35\x31\x34\x39\x37\x38\x37\x38\x36\x37\x31\x39\x34\x34\x32\x39"
  flash: 262144 (pagesize: 2048)
   sram: 49152
 chipid: 0x0435
  descr: L43x/L44x device
```

### Chapter 3 Power Up and Blink


**Read**

Reads device's flash memory starting at address 0x8000000, and saves 0x1000 (4K) worth datato a file named saved.img

```
st-flash read ./saved.img 0x8000000 0x1000

st-flash 1.5.1-50-g3690de9
2019-12-10T23:30:11 INFO common.c: Loading device parameters....
2019-12-10T23:30:11 INFO common.c: Device connected is: L43x/L44x device, id 0x10016435
2019-12-10T23:30:11 INFO common.c: SRAM size: 0xc000 bytes (48 KiB), Flash: 0x40000 bytes (256 KiB) in pages of 2048 bytes
```


To open de the file install [hexedit](https://linux.die.net/man/1/hexedit)
Ctrl-X: save and exit
Ctrl-C: exit without saving

```
sudo apt install hexedit
hexedit saved.img
```

**Writing at the same address**

```
st-flash write ./saved.img 0x8000000

st-flash 1.5.1-50-g3690de9
2019-12-10T23:36:25 INFO common.c: Loading device parameters....
2019-12-10T23:36:25 INFO common.c: Device connected is: L43x/L44x device, id 0x10016435
2019-12-10T23:36:25 INFO common.c: SRAM size: 0xc000 bytes (48 KiB), Flash: 0x40000 bytes (256 KiB) in pages of 2048 bytes
2019-12-10T23:36:25 INFO common.c: Attempting to write 4096 (0x1000) bytes to stm32 address: 134217728 (0x8000000)
Flash page at addr: 0x08000800 erasedEraseFlash - Page:0x1 Size:0x800 
2019-12-10T23:36:25 INFO common.c: Finished erasing 2 pages of 2048 (0x800) bytes
2019-12-10T23:36:25 INFO common.c: Starting Flash write for F2/F4/L4
2019-12-10T23:36:25 INFO flash_loader.c: Successfully loaded flash loader in sram
size: 4096
2019-12-10T23:36:26 INFO common.c: Starting verification of write complete
2019-12-10T23:36:26 INFO common.c: Flash written and verified! jolly good!
```

**Erase Flash**

```
st-flash erase
```


### Chapter 4 - GPIO

