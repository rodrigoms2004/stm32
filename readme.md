# STM32 with FreeRTOS, libopencm3 and GCC, Warren Gay

[Book Source Code](https://github.com/Apress/Beg-STM32-Devel-FreeRTOS-libopencm3-GCC)

[STM32 Nucleo](https://os.mbed.com/platforms/ST-Nucleo-L031K6/)

## Chapter 01 - Introduction
[Stewart Watkiss website](http://www.penguintutor.com/)

[FreeRTOS](https://freertos.org/)

[LibOpenCM3](https://libopencm3.org/)

## Chapter 02 - Software setup

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

### Installing st-flash

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
 serial: 2d3f0f0029135147324d4e00
openocd: "\x2d\x3f\x0f\x00\x29\x13\x51\x47\x32\x4d\x4e\x00"
  flash: 65536 (pagesize: 1024)
   sram: 20480
 chipid: 0x0410
  descr: F1 Medium-density device
```

## Chapter 3 Power Up and Blink


**Read**

Reads device's flash memory starting at address 0x8000000, and saves 0x1000 (4K) worth data to a file named saved.img

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


## Chapter 4 - GPIO

General Purpose Input/Output

### Building miniblink

Compile it

```
cd src/stm32/miniblink
make
```

Force rebuilding
```
make clobber
make
```

### Flashing miniblink

```
make flash
```

### Code

```
gpio_clear(GPIOC,GPIO13);	/* LED on */
...
gpio_set(GPIOC,GPIO13);		/* LED off */
```

In Arduino environment

```
int ledPin = 13; // LED on digital pin 13
digitalWrite(ledPin, HIGH);
...
digitalWrite(ledPin, LOW);
```

### GPIO API

Include libopencm3 headers

```
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
```

The rcc.h file is needed for definitions so as to enable the GPIO clock. The gpio.h file is necessary for the remainder:

```
void gpio_set(uint32_t gpioport, uint16_t gpios);
void gpio_clear(uint32_t gpioport, uint16_t gpios);
uint16_t gpio_get(uint32_t gpioport, uint16_t gpios);
void gpio_toggle(uint32_t gpioport, uint16_t gpios);
uint16_t gpio_port_read(uint32_t gpioport);
void gpio_port_write(uint32_t gpioport, uint16_t data);
void gpio_port_config_log(uint32_t gpioport, uint16_t gpios);
```
The gpioport argument can be one of the macros:

Port Macro|Description
----------|-----------
GPIOA|GPIO port A
GPIOB|GPIO port B
GPIOC|GPIO port C

In the libopencm3 GPIO functions, one or more GPIO bits may be st or cleared at once. Table below shoes supported macros. Note also the macro named GPIO_ALL.

Pin Macro|Definition|Description
---------|----------|-----------
GPIO0|(1 << 0)|Bit 0
GPIO1|(1 << 1)|Bit 1
GPIO2|(1 << 2)|Bit 2
GPIO3|(1 << 3)|Bit 3
GPIO4|(1 << 4)|Bit 4
GPIO5|(1 << 5)|Bit 5
GPIO0|(1 << 0)|Bit 0
GPIO7|(1 << 7)|Bit 7
GPIO8|(1 << 8)|Bit 8
GPIO9|(1 << 9)|Bit 9
GPIO10|(1 << 10)|Bit 10
GPIO11|(1 << 11)|Bit 11
GPIO12|(1 << 12)|Bit 12
GPIO13|(1 << 13)|Bit 13
GPIO14|(1 << 14)|Bit 14
GPIO15|(1 << 15)|Bit 15
GPIO_ALL|0xffff|All bits 0 through 15
