// Francis Hartey 
// 5/10/2020
// This program is to replicate two credit led counters for an arcade machine
// do this i was using two 7-Segment LED Displays, Arduino UNO click shield
// Arduino UNO, and 4 push buttons to increment the numbers.

// used for 7-Segment LED Display setup
#define DSI 11 
#define CLK 13
#define LATCHP1 10 // for first led latch 
#define LATCHP2 9 // for second led latch 
#define PWMP2 5 // for second led PWM 
#define PWMP1 6 // for first led PWM 

// hex values to set the 7-Segment LED Display 0-9
byte DigitValues[10] = {
0x7E, // 0
0x0A, // 1
0xB6, // 2
0x9E, // 3
0xCA, // 4
0xDC, // 5
0xFC, // 6
0x0E, // 7
0xFE, // 8
0xCE  // 9
};


// setting pin numbers for push buttons
const int buttonMinusP1 = 2;  
const int buttonMinusP2 = 3; 
const int buttonPlusP1 = 1;  
const int buttonPlusP2 = 4;  

// the current reading from the input pins
int buttonMinusStateP1 = HIGH;            
int buttonMinusStateP2 = HIGH;             
int buttonPlusStateP1 = HIGH;             
int buttonPlusStateP2 = HIGH;             

// the previous reading from the input pins
int lastButtonStateMinusP1 = LOW;  
int lastButtonStateMinusP2 = LOW;   
int lastButtonPlusStateP1 = LOW;   
int lastButtonPlusStateP2 = LOW;   


unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// to keep score of how many credits are used and not used
int CreditP1 = 0; 
int CreditP2 = 0;

// use to check for delay for minus button.
//Incase user wants to taunt instead of minus off an credit
unsigned long PushTimer = 0; 

void setup() {
 Serial.begin(9600);

  pinMode(DSI,OUTPUT);
  pinMode(CLK,OUTPUT);
  pinMode(LATCHP1,OUTPUT);
  pinMode(LATCHP2,OUTPUT);
  pinMode(PWMP1,OUTPUT);
  pinMode(PWMP2,OUTPUT);
  pinMode(buttonMinusP1, INPUT);
  pinMode(buttonMinusP2, INPUT);
  pinMode(buttonPlusP1, INPUT);
  pinMode(buttonPlusP2, INPUT);

  digitalWrite(PWMP1,HIGH);
  digitalWrite(PWMP2,HIGH);

  // defualt start up, set credits to zero on launch
  UpdateCredit(LATCHP1,00);
  UpdateCredit(LATCHP2,00);
}

void loop() {

 int readingMinusP1 = digitalRead(buttonMinusP1);
 int readingMinusP2 = digitalRead(buttonMinusP2);
 int readingPlusP1 = digitalRead(buttonPlusP1);
 int readingPlusP2 = digitalRead(buttonPlusP2);

    // if push button has been hit resets the last lastDebounceTime
  if (readingPlusP2 != lastButtonPlusStateP2 || readingPlusP1 != lastButtonPlusStateP1 ||
      readingMinusP1 != lastButtonStateMinusP1 ||  readingMinusP2 != lastButtonStateMinusP2) {

          lastDebounceTime = millis();
   }

  if ((millis() - lastDebounceTime) > debounceDelay) {

   if (readingPlusP2 != buttonPlusStateP2) {
      buttonPlusStateP2 = readingPlusP2;
      ButtonPlus(buttonPlusStateP2, CreditP2);
      UpdateCredit(LATCHP2,CreditP2);
   }

   if (readingPlusP1 != buttonPlusStateP1) {
       buttonPlusStateP1 = readingPlusP1;
       ButtonPlus(buttonPlusStateP1, CreditP1);
       UpdateCredit(LATCHP1,CreditP1);
    }

    if (readingMinusP1 != buttonMinusStateP1) {
      buttonMinusStateP1 = readingMinusP1;
      ButtonMinus(buttonMinusStateP1, CreditP1, 300);
      UpdateCredit(LATCHP1,CreditP1);

    }

     if (readingMinusP2 != buttonMinusStateP2) {
      buttonMinusStateP2 = readingMinusP2;
      ButtonMinus(buttonMinusStateP2, CreditP2, 300);
      UpdateCredit(LATCHP2,CreditP2);

     }
  }

    // reset switch: to reset the credits back to zero
    if (readingMinusP1 != buttonMinusStateP1 && readingPlusP1 != buttonPlusStateP1) {
      buttonMinusStateP1 = readingMinusP1;
      buttonPlusStateP1 = readingPlusP1;
      if (buttonPlusStateP1 == HIGH && buttonMinusStateP1 == HIGH ) {
        CreditP1 = 0;
        CreditP2 = 0;
        UpdateCredit(LATCHP1,CreditP1);
        UpdateCredit(LATCHP2,CreditP2);
      }
    }
  
  lastButtonStateMinusP1 = readingMinusP1;
  lastButtonPlusStateP1 = readingPlusP1;
  lastButtonPlusStateP2 = readingPlusP2;
  lastButtonStateMinusP2 = readingMinusP2;
}


// minus a credit when user hits push button
void ButtonMinus(int buttonminus, int &credit, int DefaultSecondWait ){
 
      if (buttonminus == HIGH && millis() > PushTimer ) {
       credit = credit - 1;
        if (credit < 0){
         credit = 0;
        }
      }
      // in some aracde games the credit button is also use to do an taunt,
      // this way if an user presses the credit button real quick then 
      // the credit button will not take off a credit.
      if (buttonminus == LOW){
        // setting push timer to current time and time we want the user
        // to hold down credit button. To see if we should take away a credit
        // or leave a credit
        PushTimer =  millis() + DefaultSecondWait; 
      }
  }


// adds a credit when user hits push button
void ButtonPlus(int buttonplus, int &credit){

  if (buttonplus == HIGH) {
      credit = credit + 1;
       if (credit > 99){
           credit = 99;
        }
      }
    }

  // controls LCD value when called sets the new value to the latch
  // that was specified
void UpdateCredit(int LatchEnter, int num){
      
      digitalWrite(LatchEnter,LOW);
      int digit1 = num % 10;
      int digit2 = num / 10;
      shiftOut(DSI,CLK, MSBFIRST,DigitValues[digit1] );
      shiftOut(DSI,CLK, MSBFIRST,DigitValues[digit2] );
      digitalWrite(LatchEnter,HIGH);
    }
