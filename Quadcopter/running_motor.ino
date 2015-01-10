int arming_time;
int pin;
int pulse;

void spinInc(int st, int en)
{
  for (pulse = st; pulse <= en; pulse +=1)
  {
    Serial.println(pulse);
    digitalWrite(pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(pin, LOW);
    delay(20);
  }
} 
void spin(int st, int pin)
{
  Serial.println(st);
  digitalWrite(pin, HIGH);
  delayMicroseconds(st);
  digitalWrite(pin, LOW);
  delay(20);
}


void setup()
{
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
  for (arming_time = 0; arming_time < 200; arming_time += 1)
  {
    digitalWrite(pin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(pin, LOW);
    delay(20);
  }
}

void loop()
{
  Serial.println("Entered Loop");
  //spinInc(1200, 1700);
  spin(1400, 9);
  spin(1400, 10);
  Serial.println("Reset Loop");
}
/*  
  for (pulse = 1400; pulse >= 1150; pulse -=1)
  {
    digitalWrite(pin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(pin, LOW);
    delay(20-(pulse/1000));
  }
*/
