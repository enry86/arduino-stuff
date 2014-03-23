// test of touch sensor

int TSDrivePin = 11;
int TSIntIndex = 0;
int TSSensePin = 2;

unsigned long TSStartTime,TSTime;
unsigned long SPStartTime;
#define SPPeriod 40 //mains interference period in milliseconds
volatile unsigned int DischargeTMinimum = 65535;
int Difference;
int calibration = 50;
int calibCount = 0;

float DischargeTAverage;
float baseValue = 0;
unsigned long Accum=0;
unsigned int Count=0;
volatile boolean reset = false;

void setup() {
  //Setup PC serial link
  Serial.begin(9600);
  
  pinMode(TSDrivePin,OUTPUT); //Configure touch sensor drive pin
  pinMode(TSSensePin,INPUT);
  pinMode(13, OUTPUT);
  
  analogWrite(TSDrivePin,10); //Set drive on 490HZ with 20% duty cycle
  attachInterrupt(TSIntIndex,touchy,CHANGE); //Configure sensor input pin as interrupt
  
  //Start sample period time
  SPStartTime = millis();
  digitalWrite(13, LOW);
}


void loop() {

  if((millis() - SPStartTime) >= SPPeriod && DischargeTMinimum != 65535) {
    noInterrupts();

    DischargeTAverage=((float) Accum) / Count;

    reset = true;
    Accum=0;
    Count=0;  
    
    float value = (float) (DischargeTAverage);
    DischargeTMinimum = 65535;
    
    SPStartTime = millis();
    if (calibCount < calibration) {
      float avgVal = value / calibration;
      baseValue += avgVal;
      calibCount++;
      if (calibCount == calibration) digitalWrite(13, HIGH);
    }
    else {
      Serial.println(value - baseValue);
    }
    interrupts();

  }
}


void touchy() {
  unsigned long intTime = micros();
  if(digitalRead(TSSensePin)) {
    TSStartTime = intTime;
    reset = false;
  }
  else if (!reset) {
    TSTime = intTime - TSStartTime;
    Accum += TSTime;
    Count++;
    
    if(TSTime < DischargeTMinimum) {
      DischargeTMinimum = TSTime;      
    }
  }
}
