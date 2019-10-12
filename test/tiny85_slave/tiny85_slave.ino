/*
 *  Code for the ATTiny85 gamepad terminal 
 *  by Enrique Ruiz-Velasco 2019
 * 
 */

// Include the library for I2C
#include <TinyWireS.h>

/*
 * SETUP:
 * ATtiny Pin 0 = SDA
 * ATtiny Pin 1 = GREEN
 * ATtiny Pin 2 = SCK
 * ATtiny Pin 3 = RED                              
 * ATtiny Pin 4 = YELLOW
 * ATtiny Pin 5 = BLUE
*/                     


#define SLAVE_ADDR 0x8

// LEDs
const int LED_GREEN  = 0x1;
const int LED_RED    = 0x3;
const int LED_YELLOW = 0x4;

bool led_needs_update = false;

const byte reg_size = 3; // 3 LEDs
volatile uint16_t i2c_regs[reg_size];
char i2c_data; // holds the received data;
char i2c_string[4]; // string for data
char i2c_older[4];
int reg_idx = 0; 
int i = 0;

void setup() {

  // Join I2C bus as slave with address 8
  TinyWireS.begin(SLAVE_ADDR);
    
  // Setup LED pins as outputs and turn LED off
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);

  // flash green when starting to indicate we're alive
  for (i=0; i < 10; i++) {
    digitalWrite(LED_GREEN, HIGH); 
    delay(500);
    digitalWrite(LED_GREEN, LOW); 
    delay(500);
  }

}

void loop() {

  // wait for data to be available
  i = 0;
  while (TinyWireS.available() > 0) {
    i2c_data = TinyWireS.read();
    i2c_string[i] = i2c_data;
    i++;
  }

  if (i2c_string[0])
    digitalWrite(LED_GREEN, HIGH);  
  
  if (i2c_string[1])
    digitalWrite(LED_RED, HIGH); 
  
  if (i2c_string[2]) 
    digitalWrite(LED_YELLOW, HIGH); 

  delay(1000);

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);

  memset(i2c_string,0,4);

}
