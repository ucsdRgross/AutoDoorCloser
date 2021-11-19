int ax = 0;
int ay = 0;
int az = 0;
int motion;
const int relay = 8;

unsigned long before = millis();
unsigned long before2 = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  setupAccelSensor();
  pinMode(relay, OUTPUT);
  setupMotor();
}

void loop() {

  unsigned long now = millis();
  unsigned long now2 = millis();

  if (now - before >= 100){
    readAccelSensor();
    // Send to Serial Plotter. Notice the last print has a newline.
    ax = ax - 324;
    ay = ay - 402;
    az = az - 322;
    
    motion = abs(ax) + abs(ay) + abs(az);
    Serial.println(motion);
    before = now;
  }

  if (motion > 100){
    if(now2 - before2 >= 100){
    motorSpinLeft();
    }
  }
  else{
    motorStop();
    before2 = now2;
  }
  
}
