Smart_Home_Control.ino (Starter)

    #include <Wire.h>
    #include <LiquidCrystal_I2C.h>
    #include <DHT.h>
    #include <Stepper.h>

    #define DHTPIN 4
    #define DHTTYPE DHT22

    #define RELAY_PIN 8
    #define BUTTON_PIN 7

    LiquidCrystal_I2C lcd(0x27,16,2);
    DHT dht(DHTPIN,DHTTYPE);

    const int stepsPerRevolution=2048;
    Stepper stepper(stepsPerRevolution,10,12,11,13);

    bool relayState=false;
    bool lastButton=HIGH;

    void setup(){
      pinMode(RELAY_PIN,OUTPUT);
      pinMode(BUTTON_PIN,INPUT_PULLUP);
      digitalWrite(RELAY_PIN,LOW);

      lcd.init();
      lcd.backlight();
      dht.begin();
      stepper.setSpeed(10);

      lcd.setCursor(0,0);
      lcd.print("Smart Home");
      delay(1500);
      lcd.clear();
    }

    void loop(){
      float t=dht.readTemperature();
      float h=dht.readHumidity();

      if(!isnan(t) && !isnan(h)){
        lcd.setCursor(0,0);
        lcd.print("T:");
        lcd.print(t);
        lcd.print((char)223);
        lcd.print("C ");

        lcd.setCursor(0,1);
        lcd.print("H:");
        lcd.print(h);
        lcd.print("%   ");
      }

      bool btn=digitalRead(BUTTON_PIN);
      if(lastButton==HIGH && btn==LOW){
          relayState=!relayState;
          digitalWrite(RELAY_PIN,relayState?HIGH:LOW);
          stepper.step(256);
          delay(200);
      }
      lastButton=btn;

      delay(300);
    }

