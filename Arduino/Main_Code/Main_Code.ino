
/*-----( Import needed libraries )-----*/
#include "IRremote.h"
#include <Servo.h>



/*-----( Declare Constants )-----*/
int receiver = 3; // pin 1 (signal pin) of IR receiver to Arduino digital pin 3




/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'
Servo linkerservo;                 // create servo object to control a servo
Servo rechterservo;                // create servo object to control a servo



/*-----( Declare Variables )-----*/



void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("Incoming IR signals:"); // Tip: to see the IR codes open the 'Serial Monitor' under 'Tools'
  irrecv.enableIRIn();                    // Start the receiver
  linkerservo.attach(9);                  // attaches the left servo on pin 9 to the servo object
  rechterservo.attach(11);                // attaches the right servo on pin 11 to the servo object
  linkerservo.writeMicroseconds(1500);    // initially, the servo must be stopped
  rechterservo.writeMicroseconds(1510);   // initially, the servo must be stopped
  pinMode(LED_BUILTIN, OUTPUT);           // attaches a LED to pin 13 (standard LED-pin)

}/*--(end setup )---*/



void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    Serial.print(" Input: ");
    Serial.println(results.value, HEX);  // Shows raw IR value
    translateIR();                       // This function will translate to IR codes and take action based on which IR code is sent
    irrecv.resume();                     // receive the next value
  }  
}/* --(end main loop )-- */



/*-----( Declare User-written Functions )-----*/
void translateIR()                       // takes action based on IR code received (Open 'Serial Monitor' under 'Tools' to see IR codes)

{

  switch(results.value)

  {

  case 0x562A:  // Main up button on remote ==> Both curtains go up
    Serial.println(" Output: Both curtains go up           "); 
    
    led_blink();   
    
    linkerservo.writeMicroseconds(1600);        // left servo rotates counterclockwise full speed 
    rechterservo.writeMicroseconds(1600);       // right servo rotates counterclockwise full speed
    delay(14000);                               // delay to wait for the servos to turn 
    rechterservo.writeMicroseconds(1510);       // right servo stops rotating
    delay(475);
    linkerservo.writeMicroseconds(1500);        // left servo stops rotating
    
    delay(1000);                     
    break;

  case 0x362A:  // Main down button on remote ==> Both curtains go down
    Serial.println(" Output: Both curtains go down            "); 
    
    led_blink();   
    
    linkerservo.writeMicroseconds(1400);        // left servo rotates clockwise half speed 
    rechterservo.writeMicroseconds(1410);       // right servo rotates clockwise half speed
    delay(12300);                               // delay to wait for the servos to turn
    linkerservo.writeMicroseconds(1500);        // left servo stops rotating
    delay(400);
    rechterservo.writeMicroseconds(1510);       // right servo stops rotating

    delay(1000);
    break;

  case 0xC2A:  // Constrast up on remote ==> Right curtain goes up
    Serial.println(" Output: Right curtain goes  up            "); 
    
    led_blink();   

    rechterservo.write(180);                  // right servo rotates counterclockwise full speed
    delay(14200);                             // delay to wait for the servos to turn 
    rechterservo.writeMicroseconds(1510);     // right servo stops rotating
    
    delay(1000);                   
    break;
    
  case 0x4C2A:  // Contrast down on remote ==> Right curtain goes down
    Serial.println(" Output: Right curtain goes  down            "); 
    
    led_blink();   
 
    rechterservo.writeMicroseconds(1450);     // right servo rotates clockwise half speed
    delay(17500);                             // delay to wait for the servos to turn 
    rechterservo.writeMicroseconds(1510);     // right servo stops rotating
    
    delay(1000);                   
    break;

  case 0x3C2A:  // Brightness up on remote ==> Left curtain goes up
    Serial.println(" Output: Left curtain goes  up            "); 
    
    led_blink();   

    linkerservo.write(180);                 // left servo rotates counterclockwise full speed 
    delay(13500);                           // delay to wait for the servos to turn
    linkerservo.writeMicroseconds(1500);    // left servo stops rotating
    
    delay(1000);                   
    break;

  case 0x7C2A:  // Brightness down on remote ==> Left curtain goes down
    Serial.println(" Output: Left curtain goes  down            "); 
    
    led_blink();   

    linkerservo.writeMicroseconds(1450);      // left servo rotates clockwise half speed 
    delay(21000);                             // delay to wait for the servos to turn
    linkerservo.writeMicroseconds(1500);      // left servo stops rotating
    
    delay(1000);                   
    break;

  case 0x542A:  // On/Off button on remote ==> Cut power to the servos

    Serial.println(" Power to the servos on/off            "); 

    led_blink(); 

    // Write the power on/off here

    delay(1000);
    break;

  default: // When any other button is pressed or an assigned button is long-pressed ==> Nothing happens
    Serial.println(" Output: You clicked on an unassigned button   ");

    delay(1000);

  }

  delay(500);


}/* --(end translate IR )-- */

void led_blink() {

    digitalWrite(LED_BUILTIN, HIGH);          // LED blinks 3 times
    delay(100);                       
    digitalWrite(LED_BUILTIN, LOW);    
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(100);                       
    digitalWrite(LED_BUILTIN, LOW);    
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(100);                       
    digitalWrite(LED_BUILTIN, LOW);
}

