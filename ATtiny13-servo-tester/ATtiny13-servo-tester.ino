#define servopin 1 //servo attached to pin 1
#define potipin A2 //potentiometer attached to pin A2
int value = 0;

volatile unsigned long us_startTime = 0;



void setup(){
  pinMode(servopin, OUTPUT);  // set servo as output pin
  pinMode(potipin, INPUT);  //set poti as input pin
}

void loop (){
  value = analogRead(potipin);   
     
  if(value < 5) value = 5;   //ignore lowest values
  if(value > 1018) value = 1018;   //ignore highest values
  value = map(value, 5, 1018, 0, 180);    //convert analog reading to angle
  servoPulse(servopin, value);
}



void servoPulse(byte servo, byte servoangle){
  int pulsewidth = map(servoangle, 0, 180, 500, 2500);  //convert from angle to pulse width, 0-180° to 500-2500µs
  
  digitalWrite(servo, HIGH);
  delay_micros(pulsewidth);
  digitalWrite(servo, LOW);
  
  delay_micros(19980-pulsewidth);                   // total period of 20ms
}

void delay_micros(unsigned long us_delay_time){
  us_startTime = micros();
  while((micros() - us_startTime) < us_delay_time);   //do nothing until delay_time has passed
}
