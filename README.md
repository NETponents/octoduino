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
Octoduino was created to allow novice programmers to create programs for the Arduino using any language they want. It also makes use of external SWAP space, so if you decide to do something extremely complex, you aren't limited by the Arduinos small RAM space.

## Documentation
All documentation, along with a change log and known bugs list, is located in the `~/docs` directory and on the GitHub Wiki. All items on the Github wiki reflect the latest source on the master branch, not the latest release.

## What do I need?
Want to get started using Octoduino? Here's what you need to get started.
- [ ] A supported Arduino board (see documentation for full list)
- [ ] An ethernet + SD card shield (or a compatible custom circuit using breakout board)
- [ ] SD/microSD card (depends on your shield) any size up to 4 GB

Next, you'll need to grab a copy of our code from GitHub:

     git clone http://github.com/NETponents/octoduino.git
 
## How do I install it?
See our [Wiki article](https://github.com/NETponents/octoduino/wiki/Building) with the latest information.

## Do you support non-Arduino products?
Energia is a popular tool used to deploy Arduino code on a vast array of devices. Energia devices are not supported at this time. The reason being that no usable SDFAT library exists for non-Arduino devices. In addition, the Octoduino bootloader is too big to fit on any MSP430 devices, so we decided to not support any Energia devices for now, however we may look at it in the future.

## Contributing
I welcome contributions of all kinds. Octoduino is developed by an unpaid high school student and the community. If you know C++, please consider making a code contribution. Please review the guidelines in **~/CONTRIBUTING.md** before starting. Otherwise, I accept donations through Gratipay (badge is at top of README.md).
