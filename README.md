# Octoduino

[![Join the chat at https://gitter.im/NETponents/octoduino](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/NETponents/octoduino?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![GitHub license](https://img.shields.io/github/license/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![Build Status](https://travis-ci.org/NETponents/octoduino.svg?branch=master)](https://travis-ci.org/NETponents/octoduino)
[![GitHub forks](https://img.shields.io/github/forks/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![GitHub stars](https://img.shields.io/github/stars/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![GitHub release](https://img.shields.io/github/release/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![GitHub issues](https://img.shields.io/github/issues/NETponents/octoduino.svg)](https://github.com/NETponents/octoduino)
[![Issue Stats](http://issuestats.com/github/NETponents/octoduino/badge/pr?style=flat)](http://issuestats.com/github/NETponents/octoduino)
[![Issue Stats](http://issuestats.com/github/NETponents/octoduino/badge/issue?style=flat)](http://issuestats.com/github/NETponents/octoduino)

## What is it?
Octoduino is a program for the Arduino that allows you to run script files from an SD card.

## What languages are supported?
No "real" languages are supported right now. We only support ParseBasic. It's pretty much the BIOS of Octoduino. We're hard at work adding support for new languages. Check out the issues page on GitHub if you would like to help move things along.

### Fully supported
- ParseBasic

### Partially supported

### On the drawing board
- NODE.JS
- Ruby
- Arduino (C++)

## Getting started
Want to get started using Octoduino? Here's how to get started:

### Prerequisites
- A supported MCU*
- A shield that can interface with an SD card (Octoduino is pre-configured for the official Ethernet Shield from AdaFruit)
- An SD card, at least 512 MB in size but no more than 2 GB
- A computer with the Arduino/Energia IDE installed and an SD card reader
- FTDI + USB/RS232 cable for programming

#### *A note about device selection
Any Arduino-certified device that supports shields should work. Please note that Leonardo and Yun are not supported at this time. Some "tiny" Arduinos will not work due to size constraints.

Although not officially supported or tested, any Energia-capable TI MSP430 MCU should also work assuming there is enough space for Octoduino. It may be possible to use external EEPROM depending on the capabilities of the MCU. Also be aware that Octoduino will run MUCH slower on non-ATmega MCUs.

The official size requirements:

     AVR Memory Usage
     ----------------
     Device: atmega2560
     
     Program:   14412 bytes (5.5% Full)
     (.text + .data + .bootloader)
     
     Data:       1232 bytes (15.0% Full)
     (.data + .bss + .noinit)

Here is a list of certified Arduino devices that are tested on every build in our CI environment:
- Arduino UNO V3
- Arduino Mega

### 1. Installing Octoduino
Grab a copy of our code from GitHub:

     git clone http://github.com/NETponents/octoduino.git

Then go ahead and open the sketch using your favorite Arduino IDE. Go ahead and deploy it to your Arduino. If you hit an error, reset your Arduino and make sure that no shields are attached. Also make sure that your device has enough SRAM to run Octoduino. If you are still hitting errors, file a bug on our GitHub page <http://github.com/NETponents/octoduino/issues>. Be sure to leave information about your Arduino and your IDE!

### 2. Creating the config files
Now that your Arduino is ready to go, let's get the SD card ready. Insert the card into your computer. Make sure the card is COMPLETELY empty. Then format it as 'FAT32' or 'FAT16'. We reccommend 'FAT32' as it is newer and slightly faster. Once that is complete, create a new file named 'octoduino.ini'. Open it using your favorite text editor. Copy the following code, replacing anything between {} with your own parameters (do not include the brackets). If you are unsure of what to put, see the language-specific options in the **~/Docs** folder.

     language={ your language id }
     output=true
     debug={ set to true for debug messages }
     start={ The source file to be executed }

### 5. Install the bootloader
Now you get to install the "BIOS" for Octoduino. From the files you downloaded, copy everything **inside** the **~/bootloader** directory to the root of your SD card. Although ParseBasic is a relatively simple language, we do not reccommend playing with these files as there is no error catching, which may lead to unpredictable results (ever seen an Arduino expode? Me neither...).

### 4. Uploading your code files
Now you can begin to upload your code files. For a simple NODE.JS program, your SD card would look like this:

     + root
     |-- octoduino.ini
     |-- program.js
     |-+ inc
       |-- library.js

### 5. Run your program
Make sure you have a serial console open to your Arduino. Insert the SD card an reset your Arduino. You should begin to see your program get executed. Yay! If you hit a bug that was not caused by your code, be sure to let us know by filing a bug in our issue tracker.

## Contributing
We welcome contributions of all kinds. For code contributions, this project follows the NETponents RING system (explained below). If you cannot make a code contribution, please consider making a donation through PayPal. NETponents only has one employee(an unpaid high school student), and we spend most of our time developing open source software.

#### Ring 2
If you are not in rings 1 or 0, you are in ring 2. Ring 2 is the public ring. Here's how contributtions work in Ring 2:
- To make changes, you must fork the project to your own account.
- Since we don't know you, permanant forking of this project is not allowed.
- When you open a PR, you will be given lowest priority (unless it is a bug patch).

#### Ring 1
This is a ring of trusted developers. We give them the **Collaborator** badge on the issues page, and give them some perks:
- To make changes, you still have to fork the project to your own account.
- With a project administrators permission, you may create a permanent fork of the project (as long as you adhere to the terms in LICENSE.md).
- When you open a PR, you will be given medium priority (unless it is a bug patch).
- In the issues section of the project, you will be given the **Collaborator** badge.
- You get added as a member (NOT employee) of the NETponents organization.

#### Ring 0
This ring is closed to the public. This ring contains employees of NETponents. Full admin access is given, however new progress must be done on a separate branch.

### Getting promoted
Put simply, if you show interest in the project, contribute regularly, and follow all the guidelines for contributions, you'll get promoted in no time.

### Contributing guidelines
We are very strict in terms of how everything is documented on GitHub. For full details, please view this projects *~/CONTRIBUTING.md*.
