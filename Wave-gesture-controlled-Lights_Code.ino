/*Gesture Controlled Auto ON OFF Table Lamp !!
 * Features - Table lamp ON main Light OFF
 *          - Table lamp OFF main Light ON
 * by Ashraf Minhaj. 
 * for any query ashraf_minhaj@yahoo.com
 * Tutorial on http://ashrafminhajfb.blogspot.com
 * and https://youtube.com/c/fusebatti
 */

int s = 3;        //PIR outPin on digital 3
int lamp = 11;     //lamp relay trigger pin on 11
int mlight = 12;   //main light trigger pin on 12
int buz = 19;      //connect buzzer on pin 19

void setup()       // put your setup code here, to run once:
{
 pinMode(s,INPUT);        //Setting Sensor as Input
 
 pinMode(mlight,OUTPUT);  //mainlight pin output
 pinMode(lamp,OUTPUT);    //LED pin as output'
 pinMode(buz,OUTPUT);     //buzzer output
 Serial.begin(9600);      //initialize Serial Monitor- for debugging(else not mandatory)
}

void loop() 
{

 /*the board restarts andt By default the desk light will be off
  * and the Main light will be on.
  * main light to relay1 - NC (normally connected pin)
  * lamp  to relay - NO (Normally Open pin)
  */
  digitalWrite(lamp,HIGH);    //By default lamp off,depends on relay-see Circuit Diagram
  digitalWrite(mlight,HIGH);
  delay(60000);               //1 minute delay so that the PIR gets enough hot to function
  goto off;           //going to off statement
 
ON:                  //the ON statement
{
  Serial.println("ON is running");
  
   digitalWrite(mlight,LOW);   //relay -ON/depends on NC/NO
  digitalWrite(lamp,LOW);      //relay -ON/depends on NC/NO
  
  
  if((digitalRead(s)))   //if again sensor input has been read - switch off
  {
    tone(buz,10000,100);
    delay(100);
    delay(6500);        //around 7 seconds delay before switching light
       /* PIR needs at least 5 seconds to function again*/
    goto off;
  }
  
  else           //Else just Be ON
  { 
    goto ON;
  }
}

off:              //OFF statement
{
  Serial.println("OFF is on");

  digitalWrite(mlight,HIGH);  //On rlay -OFF/depends on NC/NO
  digitalWrite(lamp,HIGH);    //on relay -off/depends on NC/NO
  
  if((digitalRead(s)))       //if again sensor input has been read - switch ON
  {
    tone(buz,10000,1000);
    delay(10);
    digitalWrite(mlight,LOW);   
  digitalWrite(lamp,LOW); 
   delay(6500);           /* PIR needs at least 5 seconds to function again*/
    goto ON;
  }
  
  else        //just be off
  { 
    goto off; 
  }
}

}

