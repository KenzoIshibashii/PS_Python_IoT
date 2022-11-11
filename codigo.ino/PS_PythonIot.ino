// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int vaga1 = 0;

int vaga2 = 0;

int vaga1Status = 0;

int vaga2Status = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Adafruit_LiquidCrystal lcd_1(12, 13, 3, 2, 1, 0);

void setup()
{
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  lcd_1.begin(16, 2);

  lcd_1.setCursor(0, 0);
  lcd_1.print("vagas livres");
  lcd_1.setCursor(0, 1);
  lcd_1.print("vagas ocupadas");
}

void loop()
{
  vaga1 = 0.01723 * readUltrasonicDistance(7, 6);
  if (vaga1 <= 200) {
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    vaga1Status = 0;
  } else {
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    vaga1Status = 1;
  }

  vaga2 = 0.01723 * readUltrasonicDistance(5, 4);
  if (vaga2 <= 200) {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    vaga2Status = 0;
  } else {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    vaga2Status = 1;
  }

  lcd_1.setCursor(15, 0);
  lcd_1.print((vaga1Status + vaga2Status));
  lcd_1.setCursor(15, 1);
  lcd_1.print((2 - (vaga1Status + vaga2Status)));
  delay(10); // Delay a little bit to improve simulation performance
}