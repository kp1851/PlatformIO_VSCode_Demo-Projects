#include <Arduino.h>

//ATTINY13A

//#define F_CPU 1200000UL       // MCU frequency in hertz

#include <avr/io.h>
#include <avr/wdt.h>          
#include <avr/sleep.h>        
#include <avr/power.h>
#include <avr/interrupt.h>    
#include <util/delay.h>

#define led 0                 // PB0

void sleepFewSeconds() {
  wdt_reset();                // reset the watchdog

  PORTB = 0x00;               // submit the log. 0 to all ports
  DDRB = 0x00;

  ADCSRA &= ~(1 << ADEN);     // disable ADC
  // otherwise there will be excess current consumption in sleep mode

  MCUSR &= ~(1 << WDRF);
  /* Start the WDT Config change sequence. */
  WDTCR |= (1 << WDCE) | (1 << WDE);
  /* Configure the prescaler and the WDT for interrupt mode only*/

  // Uncomment the interval you need
  WDTCR = (1 << WDP0) | (1 << WDP3) | (1 << WDTIE); 			// 8sec
  //WDTCR = (1<<WDP3) | (1<<WDTIE); 							// 4sec
  //WDTCR = (1<<WDP2) | (1<<WDP1) | (1<<WDP0) | (1<<WDTIE); 	// 2sec
  //WDTCR = (1<<WDP2) | (1<<WDP1) | (1<<WDTIE); 				// 1sec
  //WDTCR = (1<<WDP2) | (1<<WDP0) | (1<<WDTIE); 				// 0.5sec

  WDTCR |= (1 << WDTIE);

  sei();      // Enable global interrupts

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
  while (1) {
    sleep_enable();   // allow sleep
    sleep_cpu();      // sleep!
    sleep_disable();
  }
}

int main( void )              // similar to void setup ()
{

  wdt_reset();                // first you need to reset the Wachdog
  // otherwise there may be a reboot
  pinMode(led, OUTPUT);

  while (1) {                 // perpetual loop, analog of void loop ()

    digitalWrite(led, HIGH);
    _delay_ms(100);            // On Time
    digitalWrite(led, LOW);
    sleepFewSeconds();        // sleep for 8 sec.
  }
}
