// arraay de leds para el arbol
int leds[3] = {0, 1, 2};

// star led
int starLed = 3;

// led states and stuff
int ledState = LOW;
int brightness;

// button stuff
int buttonPin = 4;
int btnVal = 0;
int buttonState;           // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin
long lastDebounceTime = 0; // the last time the output pin was toggled
long debounceDelay = 50;   // the debounce time; increase if the output flickers

// time stuff for led blinking
unsigned long previousMillis = 0;
unsigned long blinkInterval = 750;

int periode = 2000;

void setup()
{
  // setupeo los 3 arrays de leds de los arboles
  for (int i = 0; i < sizeof(leds); i++)
  {
    pinMode(leds[i], OUTPUT);
  }
  // btn y starLed
  pinMode(starLed, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop()
{
  // starLed always on
  digitalWrite(3, HIGH);

  // leo
  //readBtn();
  readBtn2();
  if (btnVal > 3) {
    btnVal = 0;
  }
  
  switch (btnVal)
  {
  case 0:
    allblink();
    break;
  case 1:
    chaos();
    break;
  case 2:
    fade();
    break;
  case 3:
    allOn();
    break;
  }
}

void allblink()
{
  
  blinkInterval = 750;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > blinkInterval)
  {
    previousMillis = currentMillis;
    ledState = !ledState;
    for (int i = 0; i <= sizeof(leds); i++)
    {
      digitalWrite(i, ledState);
    }
  }
}

void chaos()
{
  blinkInterval = 250;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > blinkInterval)
  {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(leds[random(4) - 1], !ledState);
    digitalWrite(leds[random(4)], ledState);
    digitalWrite(leds[random(4) + 1], !ledState);
  }
}

void fade()
{
  blinkInterval = 30;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > blinkInterval)
  {
    previousMillis = currentMillis;
    brightness = 128 + 127 * cos(2 * PI / periode * currentMillis);
    for (int i = 0; i < 3; i++)
    {
      analogWrite(i, brightness);
    }
  }
  
}

void allOn()
{
  // for (int i = 0; i <= sizeof(leds); i++)
  // {
  //   digitalWrite(i, HIGH);
  // }
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
}

void readBtn()
{
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // if the button state has changed:
    if (reading != buttonState)
    {
      buttonState = reading;

      if (buttonState == LOW)
      {
        btnVal++;
      }
    }
  }

  // save the reading
  lastButtonState = reading;
}

void readBtn2() {
  static unsigned long cooldownUntil = 0;
  static char button = 0;
  
  unsigned long now = millis();
  
  if (now < cooldownUntil) 
    return;
  
  
  char prevButton = button;
  button = digitalRead(buttonPin);
  
  if (button == prevButton) 
    return;
  
  cooldownUntil = now + debounceDelay;
  
  if (button == LOW) // released
    return;
  
  btnVal++;
  btnVal %= 4; // 0 1 2 3 
  
  //show new btnVal 
  //digitalWrite(3, 0);
  //digitalWrite(0, btnVal & 1);
  //digitalWrite(1, (btnVal>> 1) & 1);
  //digitalWrite(2, 0);
  //delay(1000);
  //digitalWrite(3, 1);
  
  
}
