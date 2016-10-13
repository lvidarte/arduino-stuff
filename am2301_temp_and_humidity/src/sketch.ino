/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

#define DHT11_PIN A0      // ADC0

byte read_dht11_dat()
{
 byte i = 0;
 byte result=0;
 for(i=0; i< 8; i++){
   while(!digitalRead(DHT11_PIN));  // wait for 50us
   delayMicroseconds(30);
   if(digitalRead(DHT11_PIN)) 
     result |=(1<<(7-i));
   while(digitalRead(DHT11_PIN));  // wait '1' finish
 }
 return result;
}
void setup()
{
 pinMode(DHT11_PIN,OUTPUT);
 Serial.begin(9600);
 Serial.println("Ready");
}
void loop()
{
 byte dht11_dat[5];
 byte dht11_in;
 byte i;
 float humdity,temperature;
 // start condition
 // 1. pull-down i/o pin from 18ms
 digitalWrite(DHT11_PIN,LOW);
 delay(18);
 digitalWrite(DHT11_PIN,HIGH);
 delayMicroseconds(40);
 pinMode(DHT11_PIN,INPUT);
 while(digitalRead(DHT11_PIN)){
   Serial.println("dht11 start condition 1 not met");
 }
 delayMicroseconds(80);
 while(!digitalRead(DHT11_PIN)){
   Serial.println("dht11 start condition 2 not met");
 }
 delayMicroseconds(80);
 // now ready for data reception
 for (i=0; i<5; i++)
   dht11_dat[i] = read_dht11_dat();
 pinMode(DHT11_PIN,OUTPUT);
 digitalWrite(DHT11_PIN,HIGH);
 byte dht11_check_sum = dht11_dat[0]+dht11_dat[1]+dht11_dat[2]+dht11_dat[3];
 // check check_sum
 if(dht11_dat[4]!= dht11_check_sum)
 {
   Serial.println("DHT11 checksum error");
 }
 humdity=((float)(dht11_dat[0]*256+dht11_dat[1]))/10;
 temperature=((float)(dht11_dat[2]*256+dht11_dat[3]))/10;
 Serial.print("Current humdity = ");
 Serial.print(humdity,1);
 Serial.print("%  ");
 Serial.print("temperature = ");
 Serial.print(temperature,1);
 Serial.println("C  ");
 delay(2000);
}
