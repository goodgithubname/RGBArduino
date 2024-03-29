                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int button = 7;
int choice = 0;
int buttonstate = 0;

void setup() {
  // Start off with the LED off.
  setColourRgb(0,0,0);
  Serial.begin(9600);
  pinMode(button,INPUT);
}

void loop() {
  buttonstate = digitalRead(button);
  
  if (buttonstate == HIGH){
    choice++; 
  }
  switch(choice){
    case 0:
      breathing(0,255,255,10);
      break;
    case 1:
      colorcycle();
      break;
    default:
      choice = 0;
      break;
  }
  
  //colorcycle();
  //setColourRgb(0,0,0);
  //breathing(0,255,255,10);
  /*if (digitalRead(1)==HIGH){
    choice++;
    if (choice > 1){
      choice == 0;
    }
  }
  */
  Serial.print(choice);
  delay(100);
}

void colorcycle(){
  unsigned int rgbColour[3];

  // Start off with red.
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;  

  // Choose the colours to increment and decrement.
  for (int decColour = 0; decColour < 3; decColour += 1) {
    int incColour = decColour == 2 ? 0 : decColour + 1;

    // cross-fade the two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;
      
      setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
      delay(5);
      
    }
  }
}

void breathing(unsigned int red, unsigned int green, unsigned int blue, unsigned long ms){
  //shortest delay 1, longest delay 50
  int temp[3],rate[3],min = 255, i;

  temp[0]=red; temp[1]=green; temp[2]=blue;
  
  for (i =0;i<3;i++){
    if (temp[i]<=min && temp[i] != 0){
      min = temp[i];
    }
  }

  for (i = 0;i<3;i++){
    rate[i] = temp[i]/min;
  }
  
  for (i = min;i>0;i--){
    temp[0] -= rate[0];
    temp[1] -= rate[1];
    temp[2] -= rate[2];
    setColourRgb(temp[0],temp[1],temp[2]);
    delay(ms);
  }
  delay(100);
  for (i=0;i<3;i++){
    temp[i] = 0;
  }
  for (int i = 0;i < min;i++){
    temp[0] += rate[0];
    temp[1] += rate[1];
    temp[2] += rate[2];
    setColourRgb(temp[0],temp[1],temp[2]);
    delay(ms);
  }

  delay(100);
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 }
