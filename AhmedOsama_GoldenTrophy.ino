//pins declaration
#define led 13

//variables declaration
String password;
unsigned long time;
unsigned long interval;

void setup()
{
  Serial.begin(9600);
  
  //taking password for the first time
  while (!Serial.available()){}
  password = Serial.readString();
  cesar(&password);
  
  //led setup
  pinMode(led, OUTPUT);
}

void loop()
{
  if(Serial.readString() == password) {
    digitalWrite(13, HIGH);
    delay(3000);
    //encoding password
    cesar(&password);
  }
  else {
    //blink for 3 seconds
    time = millis();
    interval = time + 3000;
    while (millis() < interval) {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
    }
  }
}

void cesar(String *pass) {
  //handling special cases
  for(int i = 0; i < (*pass).length(); i++) {
    if ((*pass)[i] == 'z') {
      (*pass)[i] = 'a';
    }
    else if ((*pass)[i] == 'Z') {
      (*pass)[i] = 'A';
    }
    else if ((*pass)[i] == '9') {
      (*pass)[i] = '0';
    }
    //shifting password by one
    else {
      (*pass)[i] = (char)((*pass)[i]+1);
    }
  }
}

