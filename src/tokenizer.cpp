#include <Arduino.h>

String TKgetToken(String line, int tokenIndex)
{
    String resultToken = "";
    int counter = -1;
    int tcounter = -1;
    line.trim();
    int length = line.length();
    boolean isend = false;
    bool isstring = false;
    while(true)
    {
        tcounter++;
        while(true)
        {
            counter++;
            if(counter >= length - 1)
            {
                isend = true;
                break;
            }
            else if(line.charAt(counter == ';'))
            {
                isend = true;
                break;
            }
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
            else
            {
                resultToken = resultToken + line.charAt(counter);
            }
        }
        if(tcounter == tokenIndex)
        {
            return resultToken;
        }
        else if(isend == true)
        {
            resultToken = "TKERROR";
            return resultToken;
        }
        else
        {
            resultToken = "";
        }
    }
    resultToken = "TKERROR";
    return resultToken;
}
