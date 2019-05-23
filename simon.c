int leds[3] = {2, 3, 4}; //index 0,1,2 for red, green, blue repectively
int switches[3] = {10, 11, 12}; 

int gameMode; //gameMode 1 for play and 2 for end.

int sequence[10];
int input[5];

//returns index of button pressed or returns -1 when no switch is pressed within delay time
int waitForSwitch(int delay)
{
  int buttonPressed = -1;
  int input;
  int buttonBackUp = 0;
  
  int currentTime = millis();     // The number of ms since the program started running
  int previousTime = currentTime;   // Records the point when we start spinning the loop.
  
  //loop keeps running until delay time has passed
  while (((currentTime - previousTime) < delay) && buttonBackUp == 0)
  {
    // Read the button and record when it has been pushed down.
    for(int pin = 0; pin < 3 && buttonBackUp == 0; pin++)
    {
      if(digitalRead(switches[pin]) == HIGH)
        //I have changed the circuit given in problem statement and connected the other end of the switch to HIGH(5V)
      {
        buttonPressed = pin;
        
        // Show the LED pushed.
        digitalWrite(leds[pin], HIGH);
              
        // Taking care of debounce
        // This loop spins until the button is let up.
        while (currentTime - previousTime < delay && buttonBackUp == 0)
        {
          input = digitalRead(switches[pin]);
          if(input == LOW)
          {
            buttonBackUp = 1;
          }
          currentTime = millis();
        }
        
        // Turn the LED pushed off.
        digitalWrite(leds[pin], LOW);
        
        // See if player took more than delay time.
        if(currentTime - previousTime > delay)
        {
          buttonPressed = -1; // Delay time passed. return -1
        }
      }
    }

    currentTime = millis();
  }
  
  return buttonPressed;
}
         
void showSequence(){
  for(int i = 0; i < 5; i++){ //will show a seq of 5 leds.
    sequence[i] = random(0,3);
    digitalWrite(leds[sequence[i]], HIGH);
    delay(500);
    digitalWrite(leds[sequence[i]], LOW);
    delay(300); // to distinguish between two leds of same colour
  }
  
}
void readSequence(){
  int switchPress = -1;
  
  
  for(int i = 0; i < 5; i++){ //read 5 inputs

    input[i] = waitForSwitch(800);
    Serial.println("pressed");
    Serial.println(input[i]);
  }
  
  
  gameMode = 2;
}
int check(){
  int result = 1; //flag, if won = 1, if lose = 0.
  
  for(int i = 0; i < 5; i++){
    if(sequence[i] != input[i])
      result = 0;
  }
  
  return result;
}
         
void endGame(){
  int result = check();
  if(result == 1)
    Serial.print("You mastered the basics of Arduino.");
  else Serial.print("Try once more kid!!!");
 
  
}

void setup(){
  for(int i = 0; i < 3; i++)
    pinMode(leds[i], OUTPUT);
  
  for(int i = 0; i < 3; i++)
    pinMode(switches[i], INPUT);
  
  Serial.begin(9600);
  
  randomSeed(analogRead(7));
  
  gameMode = 1;
  
}

void loop(){
  
  if(gameMode == 1)
    showSequence();
    serial.println("Press Button");
    readSequence();
  
  if(gameMode == 2)
    endGame();
}


           
           
         
         

