extern int but, pot;
extern float angle, ajuste, atraso, temp, targettemp;

void handleMessage(AdafruitIO_Data *data);
void condad();
void ioloop(void *parameter);
void sendtemp(void *parameter);

void sendtemp(void *parameter){
  Serial.println("Envio de temperatura iniciado.");
    while (1) {
    
    tempfeed->save(temp);
    vTaskDelay(pdMS_TO_TICKS(60000));
  }
}

void ioloop(void *parameter){
  Serial.println("Monitor de controles iniciado.");
  while (1) {
    io.run();
    vTaskDelay(pdMS_TO_TICKS(500));
  }

}

void condad(){

      while (!Serial);

    Serial.print("Connecting to Adafruit IO");

    io.connect();

    butfeed->onMessage(handleMessage);
    potfeed->onMessage(handleMessage);
    targettempfeed->onMessage(handleMessage);

    while (io.status() < AIO_CONNECTED) {
      Serial.print(".");
      delay(500);
  
    }


}

void handleMessage(AdafruitIO_Data *data) {
  String feedName = data->feedName();
  String value = data->value();

  if (feedName == "dimmer") {
    int receivedPotValue = value.toInt();
    pot = receivedPotValue;
  } else if (feedName == "onoff") {
    but = value.toInt();
  } else if (feedName == "settemp") {
    targettemp = value.toFloat();
  }

  Serial.print("Received from ");
  Serial.print(feedName);
  Serial.print(": ");
  Serial.println(value);
}