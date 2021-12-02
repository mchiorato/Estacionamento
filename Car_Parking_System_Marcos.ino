

#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Change the HEX address
#include <Servo.h>

Servo myservo1;

const int trigPin = 9;    //pinos sensor ultrasom
const int echoPin = 10;   //pinos sensor ultrasom
long duration;            //varivel calculo sensor ultrasom
int distance;             //variavel distancia

bool estIR1; bool estIR2; //variaveis

int IR1 = 8;             //pin ir sensor
int IR2 = 7;             //pin ir sensor

int Vagas = 9;           //Entre com numero total de estacionamentos

int flag1 = 0;
int flag2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.begin(16, 2);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  myservo1.attach(6);
  myservo1.write(100);

  lcd.setCursor (0, 0);
  lcd.print("     Projeto    ");
  lcd.setCursor (0, 1);
  lcd.print(" INTEGRADO 2021 ");
  delay (8000);
  lcd.clear();
}

void loop() {

  Serial.print("Flag1    "); Serial.print(flag1);
  Serial.print(" | Flag2   "); Serial.print(flag2);
  Serial.print(" | Vagas   "); Serial.print(Vagas);
  Serial.print(" | IR1     "); Serial.print(IR1);
  Serial.print(" | IR2     "); Serial.print(IR2);
  Serial.print(" | estIR1  "); Serial.print(estIR1);
  Serial.print(" | estIR2  "); Serial.print(estIR2);
  Serial.print(" | Distancia  "); Serial.println(distance);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  estIR1 = digitalRead(IR1);
  estIR2 = digitalRead(IR2);

  if (distance < 5 && flag1 == 0) {
    if (Vagas > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo1.write(0);
        Vagas = Vagas - 1;
      }
    } else {
      lcd.setCursor (0, 0);
      lcd.print("    DESCULPE    ");
      lcd.setCursor (0, 1);
      lcd.print("     LOTADO!    ");
      delay (3000);
      lcd.clear();
    }
  }

  if (digitalRead (IR2) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo1.write(0);
      Vagas = Vagas + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay (1000);
    myservo1.write(100);
    flag1 = 0, flag2 = 0;
  }

  lcd.setCursor (0, 0);
  lcd.print("    Vagas    ");
  lcd.setCursor (0, 1);
  lcd.print("Disponiveis: ");
  lcd.print(Vagas);
}
