#include <Arduino.h>

String TKgetToken(String line, int tokenIndex)
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
            return resultToken;
        }
        // Check if end of string
        else if(isend == true)
        {
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
    resultToken = "TKERROR";
    return resultToken;
}
