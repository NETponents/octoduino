# Octoduino

[![Join the chat at https://gitter.im/NETponents/octoduino](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/NETponents/octoduino?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![GitHub license](https://img.shields.io/github/license/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![Build Status](https://travis-ci.org/NETponents/octoduino.svg?branch=master)](https://travis-ci.org/NETponents/octoduino)
[![ParseBasic](https://github.com/NETponents/ParseBasic)](https://img.shields.io/badge/ParseBasic-v0.0.1-blue.svg)
[![GitHub forks](https://img.shields.io/github/forks/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![GitHub stars](https://img.shields.io/github/stars/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![GitHub release](https://img.shields.io/github/release/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![GitHub issues](https://img.shields.io/github/issues/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![Issue Stats](http://issuestats.com/github/NETponents/octoduino/badge/pr?style=flat)](http://issuestats.com/github/NETponents/octoduino)
[![Issue Stats](http://issuestats.com/github/NETponents/octoduino/badge/issue?style=flat)](http://issuestats.com/github/NETponents/octoduino)
[![Gratipay](https://img.shields.io/gratipay/ARMmaster17.svg)](http://gratipay.com/~ARMmaster17)

## What is it?
Octoduino was created to allow novice programmers create programs for the Arduino using any language they want. It also makes use of external SWAP space, so if you decide to do something extremely complex, you aren't limited by the Arduinos small SRAM space.

## Getting started
Want to get started using Octoduino? Here's what you need to get started.
- [ ] A supported Arduino board*
- [ ] An ethernet + SD card shield (or a compatible custom circuit)
- [ ] Computer with the Arduino IDE
- [ ] SD/microSD card (depends on your shield) any size up to 4 GB

Only the following devices are gaurenteed to work. These build targets are tested on every build. Any devices not listed below may or may not work. Use at your own risk!
- Uno
- Mega (NOT Mega ADK)
- Micro
- Yun
- Leonardo
 
Energia devices are not supported. The reason being that no usable SDFAT library exists. In addition, the Octoduino bootloader is too big to fit on any MSP430 devices, so we decided to not support any Energia devices for now, however we may look at it in the future.

The official size requirements (percentages are for the Arduino Uno):

     AVR Memory Usage

     ----------------

     Device: atmega328p

     Program:   19122 bytes (58.4% Full)

     (.text + .data + .bootloader)

     Data:       1321 bytes (64.5% Full)

     (.data + .bss + .noinit)

Next, you'll need to grab a copy of our code from GitHub:

     git clone http://github.com/NETponents/octoduino.git

Open up the **~/src** folder. Inside, you should find several code files. Go ahead and open **main.ino** using the Arduino IDE. Go ahead and compile and deploy the program to your Arduino. If you recieve a build error, be sure to report it in our issue tracker on GitHub. Make sure you include your IDE and board information! If you recieve a deploy error, make sure no shields/wires are attached and try again. If you are still hitting errors, either your device is broken or is not supported by Octoduino.

=====

Once that is done, we can install Octoduino to the SD card. Go ahead an plug it into your computer. Make sure that the card is empty. Format the card to FAT32. Now copy the folder **~/bootloader** from the Octoduino source to the SD card.

The last part is to copy over your own code files. Right now, the only language supported is ParseBasic. This is basically the "Assembly" language of Octoduino. In the future, we'll add more languages as we develop Octoduino. See the documentation on how to create your own ParseBasic file.

=====

Now you get to run your program. Insert your SD card into your shield, then attach it to your Arduino. Make sure you have a serial console open and it is set to your Arduinos COM/tty port. Apply power and you should see your program execute. If you hit a bug, be sure to file an issue on GitHub with your system details.

## Contributing
I welcome contributions of all kinds. Octoduino is developed by an unpaid high school student. If you know how to program Arduinos, please consider making a code contribution. Please review the guidelines in **~/CONTRIBUTING.md** before starting. Otherwise, I accept donations through Gratipay (badge is at top of README.md).
