#ifndef BLINKING_LED_H
#define BLINKING_LED_H

extern int ledPin;
extern int ledState;
extern unsigned long previousMillis;
extern long interval;

void InitBlinkLed(int pin, bool state, unsigned long previousMillis, long blinkInterval);
void BlinkLed(void);

#endif
