/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

#include <Arduino.h>
#include <SD.h>
#include <SPI.h> // Required for PlatformIO
#include "output.h"
#include "tokenizer.h"
#include "swap.h"

    /**
     * Parses a given PB line and returns the token found at the given token index.
     */
    String Tokenizer::TKgetToken(String line, int tokenIndex)
    {
        // Create buffer for output
        String resultToken = "";
        // Initialize index counters
        int counter = -1;
        int tcounter = -1;
        // Trim whitespace on input
        line.trim();
        // Set maximums
        int length = line.length();
        // State variables
        boolean isend = false;
        bool isstring = false;
        // Token loop
        while(true)
        {
            tcounter++;
            // Char loop
            while(true)
            {
                counter++;
                // Check char pointer against maximum
                if(counter >= length - 1)
                {
                    isend = true;
                    break;
                }
                // Check for instruction terminator
                else if(line.charAt(counter == ';'))
                {
                    isend = true;
                    break;
                }
                // Check for start or end of string literal
                else if(line.charAt(counter == '"'))
                {
                    if(isstring)
                    {
                        isstring = false;
                    }
                    else
                    {
                        isstring = true;
                    }
                }
                // Check for token separator
                else if(line.charAt(counter) == ' ')
                {
                    if(isstring)
                    {
                        // Do nothing because we are inside a string
                    }
                    else
                    {
                        break;
                    }
                }
                // No special instructions, record char at pointer
                else
                {
                    resultToken = resultToken + line.charAt(counter);
                }
            }
            // Check current token against desired token index
            if(tcounter == tokenIndex)
            {
                // Check to see if it is a var reference
                if(resultToken.startsWith("*"))
                {
                    resultToken.replace("*","");
                    resultToken = Swap::read(resultToken);
                }
                return resultToken;
            }
            // Check if end of string
            else if(isend == true)
            {
                Output::write("Error in tokenizer: unknown token");
                resultToken = "TKERROR";
                return resultToken;
            }
            // Clear token buffer and restart loop on next token
            else
            {
                resultToken = "";
            }
        }
        // Token index not found, send error
        Output::write("Error in tokenizer: argument index not found");
        resultToken = "TKERROR";
        return resultToken;
    }
