# Octoduino
## What is it?
Octoduino is a program for the Arduino that allows you to run script files from an SD card.

## What languages are supported?
None right now. We are still in the early stages of development, so we're trying to perfect the underlying framework first. Once we get that out of the way, we can get started working on individual languages.

### Fully supported

### Partially supported

### On the drawing board
- BASIC
- NODE.JS
- Ruby
- Arduino (C++)

## Getting started
Want to get started using Octoduino? Great! Here's how to get started:

### Prerequisites
- Arduino (we perform testing on an UNO V3)
- A shield that can interface with an SD card
- An SD card, at least 512 MB but 4 GB (some shields don't support larger cards)
- A computer with the Arduino IDE installed and an SD card reader
- USB type B cable (the one that came with your Arduino)

### 1. Installing Octoduino
Grab a copy of our code from GitHub:

     git clone http://github.com/NETponents/octoduino.git

Then go ahead and open the sketch using your favorite Arduino IDE. Go ahead and deploy it to your Arduino. If you hit an error, reset your Arduino and make sure that no shields are attached. If you are still hitting errors, file a bug on our GitHub page <http://github.com/NETponents/octoduino/issues>. Be sure to leave information about your Arduino and your IDE!

### 2. Creating the config files
Now that your Arduino is ready to go, let's get the SD card ready. Insert the card into your computer. Make sure the card is COMPLETELY empty. Then format it as 'FAT32'. Once that is complete, create a new file named 'octoduino.config'. Open it using your favorite text editor. Copy the following code, replacing anything between {} with your own parameters (do not include the brackets). If you are unsure of what to put, see the language-specific options in the **~/Docs** folder.

     language={ your language id }
     output=true
     debug={ set to true for debug messages }
     start={ The source file to be executed }

### 3. Uploading your code files
Now you can begin to upload your code files. For a simple NODE.JS program, your SD card would look like this:

     + root
     |-- octoduino.config
     |-- program.js
     |-+ inc
       |-- library.js

### 4. Run your program
Make sure you have a serial console open to your Arduino. Insert the SD card an reset your Arduino. You should begin to see your program get executed. Yay! If you hit a bug that was not caused by your code, be sure to let us know by filing a bug in our issue tracker.
