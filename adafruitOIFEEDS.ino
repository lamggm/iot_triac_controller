#include "config.h"
#include <math.h>

#define inPin 22
#define outPin 23
#define ntcpin 33

int but = 1;
int pot = 0;
float temp = 0.0;
float targettemp = 33.0;

float atraso = 400;
float angle = 90.0;
float ajuste = 0.0;
volatile int trigtime = 0;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

extern void mode(void *parameter);
extern void controlarTemperatura();
extern void lerTemperatura();

extern void handleMessage(AdafruitIO_Data *data);
extern void condad();
extern void ioloop(void *parameter);
extern void sendtemp(void *parameter);

extern void serialmonitor(void *parameter);

void IntzeroCrossing();

TaskHandle_t Mode;
TaskHandle_t IOloop;
TaskHandle_t sendTemp;
TaskHandle_t serialMonitor;

AdafruitIO_Feed *butfeed = io.feed("onoff");
AdafruitIO_Feed *potfeed = io.feed("dimmer");
AdafruitIO_Feed *tempfeed = io.feed("temperature");
AdafruitIO_Feed *targettempfeed = io.feed("settemp");


void setup() {

  pinMode(ntcpin, INPUT);
  pinMode(inPin, INPUT_PULLUP);
  pinMode(outPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(inPin), IntzeroCrossing, FALLING);

  Serial.begin(115200);

  condad();

  xTaskCreatePinnedToCore(mode, "Mode", 10000, NULL, 2, &Mode, 0);
  delay(500);
  xTaskCreatePinnedToCore(ioloop, "IOloop", 10000, NULL, 3, &IOloop, 0);
  delay(500);
  xTaskCreatePinnedToCore(sendtemp, "sendTemp", 10000, NULL, 1, &sendTemp, 0);
  delay(500);
  xTaskCreatePinnedToCore(serialmonitor, "serialMonitor", 10000, NULL, 1, &serialMonitor, 0);
  delay(500);
}

void loop() {}

void IRAM_ATTR IntzeroCrossing() {
  portENTER_CRITICAL_ISR(&mux);
  delayMicroseconds(trigtime);
  digitalWrite(outPin, HIGH);
  delayMicroseconds(50);
  digitalWrite(outPin, LOW);
  portEXIT_CRITICAL_ISR(&mux);
}
