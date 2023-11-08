extern int but, pot;
extern float angle, ajuste, atraso, temp, targettemp;

void serialmonitor(void *parameter);

void serialmonitor(void *parameter){
  Serial.println("Monitoramento iniciado.");
    while (1) {
    
    Serial.print("but = ");
    Serial.println(but);
    Serial.print("pot = ");
    Serial.println(pot);
    Serial.print("angle = ");
    Serial.println(angle);
    Serial.print("ajuste = ");
    Serial.println(ajuste);
    Serial.print("atraso = ");
    Serial.println(atraso);
    Serial.print("temp = ");
    Serial.println(temp);
    Serial.print("target = ");
    Serial.println(targettemp);

    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}