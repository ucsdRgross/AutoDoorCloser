int ax = 0;
int ay = 0;
int az = 0;
int motion;
const int relay = 8;
bool pull = false;
bool unwind = false;

//refresh rate to check accelerometer for motion
unsigned long before = millis();
//timer to wait before closing foor
unsigned long before2 = millis();

//keep track of how long machine spent pulling,
//and spend same amount of time unwinding
unsigned long initial = millis();
unsigned long ending = millis();

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
  unsigned long initial = millis();

  if (now - before >= 100){
    readAccelSensor();
    //attempt at zeroing out the data of noise
    ax = abs(ax) - 324;
    ay = abs(ay) - 274;
    az = abs(az) - 277;

    // Send to Serial Plotter. Notice the last print has a newline.
    motion = abs(ax) + abs(ay) + abs(az);
    Serial.println(motion);
    before = now;
  }

  if (motion > 150 and unwind == false){
    pull = true; 
    Serial.println("about to pull");
  }

  if (pull == false){
    before2 = now2;
  } 
  
  // wait 5 seconds before pulling
  if(now2 - before2 >= 5000 and unwind == false){
      motorSpinRight();
      before2 = now2;
      //begin pulling in door
      //puller will be stationary for a while,
      //so only stop after a second pause in motion has been detected
      bool moving = false;
      initial = millis();
      while (!moving or motion > 50){
        readAccelSensor();
        ax = abs(ax) - 324;
        ay = abs(ay) - 274;
        az = abs(az) - 277;
        motion = abs(ax) + abs(ay) + abs(az);
        Serial.println(motion);
        if (motion > 50){
          moving = true;
        }
      }
      ending = millis();
      pull = false;
      unwind = true;
  }

  if (unwind == true){
    motorSpinLeft();
    before2 = now2;
    //unwind spooled up string for as long as machine spent pulling
    while (now2 - before2 <= ending - initial){
      now2 = millis();
      Serial.println("unwinding");
    }
    unwind = false;
  }
  if (pull == false and unwind == false){
    motorStop();
  }
}
