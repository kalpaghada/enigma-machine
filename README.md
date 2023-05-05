# enigma-machine
An enigma machine.

--------------------------------------------------------------------------------------

# A Quick Primer on How the Enigma Machine is Operated
The enigma machine takes three things as an input.
1. *Rotor configuration*
2. *Wheel configuration*
3. *Message*

## *Rotor configuration:*
There are 3 rotor slots (left, center and right) on the machine that can be filled with the 3 rotor settings the machine gives – rotors 1, 2 and 3.  
E.g. The left rotor slot can have rotor 2  
&nbsp;  &nbsp;  &nbsp;  &nbsp;The center rotor slot can have rotor 1   
&nbsp;  &nbsp;  &nbsp;  &nbsp;And the right rotor slot can have the remaining rotor, rotor 3  
&nbsp;  &nbsp;  &nbsp;  &nbsp;Hence, the *rotor configuration* here is 2 1 3.  

The left rotor slot can be filled with any of the three rotors,  
The center rotor slot can be filled with any of the remaining two rotors,  
The right rotor slot has to be filled with the last remaining rotor.  

## *Wheel configuration:*
There are 26 wheel settings for each of the rotor slots (from 1 to 26).  
The left rotor slot can have any wheel setting from 1 to 26. So can the other two.  
E.g. The left rotor wheel setting can be 5  
&nbsp;  &nbsp;  &nbsp;  &nbsp;The center rotor wheel setting can be 17  
&nbsp;  &nbsp;  &nbsp;  &nbsp;The right rotor wheel setting can be 26  

Hence, the *wheel configuration* here is 5 17 26  
Repeated numbers for the *wheel configuration* are allowed – e.g. 2 2 2, or 1 1 1, or 17 17 17.  

## *Message*
The message is a string of alphabet characters, be it small, capital, space separated or otherwise. Numbers and/or special characters are ignored.  
The message is encrypted according to the configuration settings.  
To *decrypt* an encoded message, the encoded message can be input as *message* with the same configuration settings used to *encrypt* it.  
E.g. *Rotor configuration:* 1 2 3  
&nbsp;  &nbsp;  &nbsp;  &nbsp;*Wheel configuration:* 1 1 1  
&nbsp;  &nbsp;  &nbsp;  &nbsp;*Message:* hello  
&nbsp;  &nbsp;  &nbsp;  &nbsp;Output: ILBDA  
To decrypt the message ILBDA,  
&nbsp;  &nbsp;  &nbsp;  &nbsp;*Rotor configuration:* 1 2 3  
&nbsp;  &nbsp;  &nbsp;  &nbsp;*Wheel configuration:* 1 1 1  
&nbsp;  &nbsp;  &nbsp;  &nbsp;*Message:* ILBDA  
&nbsp;  &nbsp;  &nbsp;  &nbsp;Output: HELLO  

These settings allow the machine to operate with over a hundred thousand (105,456) possible combinations to encrypt a single *message*.  

--------------------------------------------------------------------------------------

# A Quick Primer on How the Program is Operated
The program compiles without errors on the latest standard of C – C11. If compiled with C99 or any other such old standards, errors maybe thrown.  
The program is run from the command line.  
Eg: `gcc enigma.c -o enigma.exe`  
&nbsp; &nbsp; &nbsp; `.\enigma.exe`  

The program has 2 modes -
1. Normal mode
2. Command line mode

## *Normal mode*
After running enigma.exe or enigma.out, the first thing required is the *rotor configuration*.  
The three rotors – 1, 2 and 3. These can be given in any order (separated by a space each) as the input, as long as they are not repeating.  
E.g.: 1 2 3  
&nbsp;&nbsp;Or: 2 3 1  

The next thing required is the *wheel configuration*.  
Each rotor has a *wheel configuration* that goes from 1 to 26. So, for each of the rotors, a *wheel configuration* has to be given (separated by a space). These can repeat.  
E.g.: 13 26 6  
&nbsp;&nbsp;Or: 1 1 1  
&nbsp;&nbsp;Or: 25 25 1  

The last thing required is the *message*.  
This is a string that is to be decoded/encoded according to the above configuration settings, to be entered just as a normal string, with or without space. All characters OTHER than the alphabet (capital or small) are ignored.  
The configuration settings along with the message will produce an output after running through the Enigma Machine.  

## *Command line mode*
It is run through a command prompt like so – `enigma *[rotor configuration]* *[wheel configuration]* *[message]*`  

The rotor configuration is taken as three two-digit numbers. The input should be like so – `0[number]0[number]0[number]`  
E.g.: 010203 (this means the *rotor configuration* is 1, 2 3)  
&nbsp; &nbsp; &nbsp; &nbsp; 020301 (this means the *rotor configuration* is 2 3 1)  

The *wheel configuration* should be input as a two-digit number (between 1 and 26) like the *rotor configuration* - `[number][number][number]`  
E.g.: 212203 (the wheel setting is 21 22 3)  
&nbsp; &nbsp; &nbsp; &nbsp; 260107 (the wheel setting is 26 01 7)  

The *message* can be an unseparated string of characters like – `ABCDEFG`,  
Or, separated by a space in which case they should be put inside double quotes like so - `“ABCD EFG HIJ   KLM”`  
<ins>Note:</ins> If single quotes are used instead of double, it is assumed as an invalid argument and it skips the command line mode entirely. If an incorrect number of arguments are given, it does the same.  

Example: `.\enigma.exe 010203 010101 “HELLO WORLD”`  
Output: `>ILBDA AMTAZ`  

<ins>Note:</ins> If an invalid input is provided, the program specifies so and quits.
