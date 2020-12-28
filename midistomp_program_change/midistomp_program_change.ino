const int button1Pin=2;
const int button2Pin=1;
const int button3Pin=4;
const int button4Pin=3;

int button1State=LOW;
int button2State=LOW;
int button3State=LOW;
int button4State=LOW;

const int channel=1;

long lastClick=0;
const long debounceTime=50;  //50 ms

elapsedMillis button1LastClick;
elapsedMillis button2LastClick;
elapsedMillis button3LastClick;
elapsedMillis button4LastClick;

bool switchoff1=false;
bool switchoff2=false;
bool switchoff3=false;
bool switchoff4=false;

void setup() {
  Serial.begin(9600);
  Serial.println("start");

  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);

//  digitalWrite(button1Out, HIGH);
}

int page=0;
elapsedMillis lastPageReceived;
int changeTimeMs=1000;

void buttonPressed(int buttonNumber){
  if(page==0 || lastPageReceived>changeTimeMs){
    // select page
    lastPageReceived=0;
    page=buttonNumber;
    Serial.print("set page ");
    Serial.println(page);
  } else{
    // select program and send midi message
    int midiProgram=((page-1)*4) + buttonNumber;
    usbMIDI.sendProgramChange(1, midiProgram);
    page=0;
    Serial.print("send program change to program ");
    Serial.println(midiProgram);
  }
}

void loop() {

  int buttonState=digitalRead(button1Pin);
  if(buttonState!=button1State && millis()-lastClick>debounceTime){
    Serial.println(buttonState);
    button1State=buttonState;
    lastClick=millis();
    Serial.println("pressed 1");
    button1LastClick=0;
    buttonPressed(1);
    switchoff1=true;
  }

  buttonState=digitalRead(button2Pin);
 
  if(buttonState!=button2State && millis()-lastClick>debounceTime){
    button2State=buttonState;
    lastClick=millis();
    Serial.println("pressed 2");
    button2LastClick=0;
    buttonPressed(2);
    switchoff2=true;
  }

  buttonState=digitalRead(button3Pin);  
  if(buttonState!=button3State && millis()-lastClick>debounceTime){
    button3State=buttonState;
    lastClick=millis();
    Serial.println("pressed 3");
    button3LastClick=0;
    buttonPressed(3);
    switchoff3=true;
  }
  buttonState=digitalRead(button4Pin);  
  if(buttonState!=button4State && millis()-lastClick>debounceTime){
    button4State=buttonState;
    lastClick=millis();
    Serial.println("pressed 4");
    button4LastClick=0;
    buttonPressed(4);
    switchoff4=true;
  }

//  if(switchoff1 && button1LastClick>50){
//    usbMIDI.sendNoteOn(60, 0, channel);
//    switchoff1=false; 
//  }
//  if(switchoff2 && button2LastClick>50){
//    usbMIDI.sendNoteOn(61, 0, channel);
//    switchoff2=false; 
//  }
//  if(switchoff3 && button3LastClick>50){
//    usbMIDI.sendNoteOn(62, 0, channel);
//    switchoff3=false; 
//  }
//  if(switchoff4 && button4LastClick>50){
//    usbMIDI.sendNoteOn(63, 0, channel);
//    switchoff4=false; 
//  }


  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}
