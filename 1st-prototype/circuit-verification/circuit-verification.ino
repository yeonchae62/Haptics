#define intDown 19
#define intUp 21
#define modeUp 23
#define modeDown 22



#define pulseLen 80

int currentMode = 1;
int currentInt = 0;

void shortPulse(int pin) {
  digitalWrite(pin, 1);
  delay(pulseLen);
  digitalWrite(pin, 0);
  delay(pulseLen);
}

void setMode(int hmode) {
  if (currentMode < hmode) {
    while (currentMode < hmode) {
      shortPulse(modeUp);
      currentMode++;
    }
  } else if (currentMode > hmode) {
    while (currentMode > hmode) {
      shortPulse(modeDown);
      currentMode--;
    }
  }
  delay(pulseLen);
}

void setInt(int intensity) {
  if (currentInt < intensity) {
    while (currentInt < intensity) {
      shortPulse(intUp);
      currentInt++;
    }
  } else if (currentInt > intensity) {
    while (currentInt > intensity) {
      shortPulse(intDown);
      currentInt--;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(modeUp, OUTPUT);
  pinMode(modeDown, OUTPUT);
  pinMode(intUp, OUTPUT);
  pinMode(intDown, OUTPUT);

  digitalWrite(modeUp, 0);
  digitalWrite(modeDown, 0);
  digitalWrite(intUp, 0);
  digitalWrite(intDown, 0);

  Serial.begin(115200);
  Serial.setTimeout(500);
}

void loop() {
  if(Serial.available()>0)
  {
    String buff = Serial.readString();

    int a = buff.indexOf(',');
    String m = buff.substring(0,a);
    String intensity = buff.substring(a+1);

    Serial.println(m);
    Serial.println(intensity);

    setMode(m.toInt());
    setInt(intensity.toInt());
  }
}

