import processing.serial.*;
Serial Arduino;
int wWidth = 900;
int wHeight = 600;
String ioval;
ArrayList wave = new ArrayList();
ArrayList waveAvg = new ArrayList();
int waveLength = 880;
int avgWin = 15;
int offset = wHeight / 2;
float multiplier = 7.5;

void setup() {
  size(wWidth,wHeight);
  // sexy black BG
  background(0);
  Arduino = new Serial(this,  Serial.list()[0], 9600);
  smooth();
  //Arduino.bufferUntil('\n');
}

float getLastAvg (ArrayList list) {
 float tot = 0.0;
 float avg = 0.0;
 int cnt = 0;
 for (int i = list.size() - 1; i >= 0 && i >= (list.size() - avgWin) -1; i--) {
   tot += (Float) list.get(i);
   cnt++;
 } 
 if (cnt > 0) avg = tot / cnt;
 return avg;
}


void draw() {
  
  while(Arduino.available() > 0) {
    ioval = Arduino.readStringUntil('\n');
    if (ioval != null && !ioval.trim().equals("")) {
      float val = Float.parseFloat(ioval.trim());
      wave.add(val);
      waveAvg.add(3 * getLastAvg (wave));
    }
  }
  // background reset on frame
  background(0);    
  if(wave.size() >= waveLength) {
    wave.remove(0); 
  }
  if (waveAvg.size() >= waveLength) {
    waveAvg.remove(0);
  }
  
  drawWave(wave, 100);
  drawWave(waveAvg, 255);
}

void drawWave (ArrayList wave, int bw) {
  float prevX = 0;
  float prevY = wHeight;
  
  // add samples to canvas
  for(int i = 0; i < wave.size(); i++)
  {
    stroke(bw);    
    if(prevX == 0 && prevY == wHeight)
    {
      prevX = i;
      prevY = wHeight - ((Float)wave.get(i));
    }
    line(prevX, prevY, i, ((float) wHeight) - ((Float)wave.get(i)));
    prevX = i;
    prevY = ((float) wHeight) - ((Float)wave.get(i)); 
  }

}
