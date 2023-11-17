extern int but, pot;
extern float angle, ajuste, atraso, temp, targettemp, vm, vefc, pl, vp, pt1, pt2;

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
    Serial.print("Vef = ");
    Serial.println(vefc);
    Serial.print("Pl = ");
    Serial.println(pl);
    Serial.print("vp = ");
    Serial.println(vp);
    Serial.print("Pt1 = ");
    Serial.println(pt1);
    Serial.print("Pt2 = ");
    Serial.println(pt2);


    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}