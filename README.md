# arcade-led-credit-counter-simulator
This program is to replicate two credit led counters for an arcade machine. The point of this project is that if you have or are making a arcade machine you can use the Arduino hardware to add in credit buttons.To do this i was using two 7-Segment LED Displays, Arduino UNO click shield, Arduino UNO, and 4 push buttons to increment the numbers.
 

 
# How it works
pin 7  the Arduino increments first credit button by one

pin 4 increments the second credit led by one

pin 2 minuses the first credit led by one

pin 3 minues the second credit led by one

if pin 7 and pin 2 are pushed at the same time resets both led credits to zero

Pin 2 and pin 3 also currently use potentiometer for a micro second delay. This is incase if a user wants to use the credit button as a taunt. Some old arcade games did this. This way if the user hits the minus credit button under say 3 micro seonds it will not take off a credit. However if the user holds the credit button down for over 3 micro seconds they will lose a credit.

A0 pin is for the potentiometer to change through micro seconds. Depending on how high or low it is set to. When the user holds down on the minus credit button, it will take how many micro seconds that are currently set to minus off a credit. 

# model numbers for parts used

2 x	7-Segment LED Display mikroBUS Module, 2 Digits (7seg click) | Model Number: MIKROE-1201 

1 x	2x mikroBUS Interface for Arduino (Arduino UNO click shield) | Model Number: MIKROE-1581 

1 X Arduino Uno

1 X potentiometer

For the four push buttons i just wired them to PCB board with four 10k resitors. While also using the 5volt and ground on the arudino to power them and using the pins 1, 2, 3, and 4 for the buttons.
