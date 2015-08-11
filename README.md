# Octoduino

[![Join the chat at https://gitter.im/NETponents/octoduino](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/NETponents/octoduino?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![GitHub license](https://img.shields.io/github/license/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![Build Status](https://travis-ci.org/NETponents/octoduino.svg?branch=master)](https://travis-ci.org/NETponents/octoduino)
[![ParseBasic](https://img.shields.io/badge/ParseBasic-v0.1.1-blue.svg)](https://github.com/NETponents/ParseBasic)
[![GitHub forks](https://img.shields.io/github/forks/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![GitHub stars](https://img.shields.io/github/stars/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![GitHub release](https://img.shields.io/github/release/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![Github Releases](https://img.shields.io/github/downloads/NETponents/octoduino/latest/total.svg)](https://github.com/NETponents/octoduino/releases)
[![GitHub issues](https://img.shields.io/github/issues/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![Issue Stats](http://issuestats.com/github/NETponents/octoduino/badge/pr?style=flat)](http://issuestats.com/github/NETponents/octoduino)
[![Issue Stats](http://issuestats.com/github/NETponents/octoduino/badge/issue?style=flat)](http://issuestats.com/github/NETponents/octoduino)
[![Gratipay](https://img.shields.io/gratipay/ARMmaster17.svg)](http://gratipay.com/~ARMmaster17)

## What is it?
Octoduino was created to allow novice programmers create programs for the Arduino using any language they want. It also makes use of external SWAP space, so if you decide to do something extremely complex, you aren't limited by the Arduinos small RAM space.

## Documentation
All documentation, along with a change log and known bugs list, is located in the `~/docs` directory and on the GitHub Wiki. All items on the Github wiki reflect the latest source on the master branch, not the latest release.

## What do I need?
Want to get started using Octoduino? Here's what you need to get started.
- [ ] A supported Arduino board (see documentation for full list)
- [ ] An ethernet + SD card shield (or a compatible custom circuit using breakout board)
- [ ] SD/microSD card (depends on your shield) any size up to 4 GB

Next, you'll need to grab a copy of our code from GitHub:

     git clone http://github.com/NETponents/octoduino.git
 
## Building

***As of version 0.1.4, the Arduino IDE cannot be used to build Octoduino***. Instead, we have provided multiple build options.

### All platforms
You will need to download [PlatformIO](http://github.com/platformio/platformio) for your platform. If you don't already have it, you will need Python to install PlatformIO.

### Windows
Make sure that both PlatformIO and Python are in your system %PATH%. We have included a Visual Studio project file. Simply open the file and build the project.

### Mac OS X + Linux
You will need to deploy manually using PlatformIO. Navigate to the Octoduino download directory and run `platformio run --target upload --environment %BOARD% --BUILD_FLAGS="-DBUILDPIPE_BNUM='local'"` replacing **%BOARD%** with the type of Arduino you are deploying to.

If you need help, see the documentation or talk to us on our Gitter channel.

## Setting up

Follow these instructions once you flash over the Octoduino bootloader in the step above.

Now take your SD/microSD card and format it to FAT32. Then copy everything ***IN*** the *~/boot* folder to the card. Now you may add your own code files in the root of the SD card (see the documentation on how to name your files). Due to a limitation of the SDFAT library, your file names must conform to the 8.3 standard. This means that the name of the file may only be 8 characters long, and the extension may only be 3 characters long.

Lastly, create a file at the root of the card called *lang.oct* and inside of it, put `pb`. This tells Octoduino to use the ParseBasic interpreter (the only one available right now).

Now you get to run your program. Insert your SD card into your shield, then attach it to your Arduino. Make sure you have a serial console open and it is set to your Arduinos COM/tty port. Apply power and you should see your program execute. If you hit a bug, be sure to file an issue on GitHub with your system details.

## Do you support non-Arduino products?
Energia is a popular tool used to deploy Arduino code on a vast array of devices. Energia devices are not supported at this time. The reason being that no usable SDFAT library exists for non-Arduino devices. In addition, the Octoduino bootloader is too big to fit on any MSP430 devices, so we decided to not support any Energia devices for now, however we may look at it in the future.

## Contributing
I welcome contributions of all kinds. Octoduino is developed by an unpaid high school student and the community. If you know C++, please consider making a code contribution. Please review the guidelines in **~/CONTRIBUTING.md** before starting. Otherwise, I accept donations through Gratipay (badge is at top of README.md).
