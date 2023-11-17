double
  Raux = 10000.0,
  Rd0 = 10000.0,
  T_0 = 298.15,
  Vadc = 0.0,
  Rntc = 0.0,
  T_1 = 273.15,
  T_2 = 373.15,
  RT1 = 35563.0,
  RT2 = 549.4,
  beta = 0.0,
  Rinf = 0.0,
  tempK = 0.0;

extern int but, pot, res;
extern float angle, ajuste, atraso, temp, targettemp, vefc, pl;
extern double npi;
extern volatile int trigtime;
float vp, pt1, pt2;

void mode(void *parameter);
void controlarTemperatura();
void lerTemperatura();
void calcs();

void mode(void *parameter) {
  Serial.print("Modo iniciado: ");
  if (but == 1)
    Serial.println("automatico.");
  else
    Serial.println("manual.");

  beta = (log(RT1 / RT2)) / ((1 / T_1) - (1 / T_2));
  Rinf = Rd0 * exp(-beta / T_0);

  while (1) {
    calcs();
    if (but == 1) {
      lerTemperatura();
      controlarTemperatura();
    } else {
      lerTemperatura();
      angle = map(pot, 0, 100, 170, 10);
      ajuste = angle / 180;
      portENTER_CRITICAL_ISR(&mux);
      trigtime = (8333.33 * ajuste) + atraso;
      portEXIT_CRITICAL_ISR(&mux);
    }
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void controlarTemperatura() {

  if (temp < targettemp) {
    angle = angle - 1;
  } else if (temp > targettemp) {
    angle = angle + 1;
  }
  if (angle > 170.00) {
    angle = 170.00;
  }
  if (angle < 10.00) {
    angle = 10.00;
  }

  ajuste = angle / 180;
  portENTER_CRITICAL_ISR(&mux);
  trigtime = (8333.33 * ajuste) + atraso;
  portEXIT_CRITICAL_ISR(&mux);
}

void lerTemperatura() {
  float ntcRead = analogRead(ntcpin);
  Vadc = (3.3 * ntcRead) / 4096;

  Rntc = (Raux * Vadc / (3.3 - Vadc));
  tempK = (beta / log(Rntc / Rinf));
  temp = tempK - 273.15;
}

void calcs(){
  float rad = angle*(npi/180);
  vp = 220*sqrt(2);
  pt1 = (rad/(2*npi));
  pt2 = sin(2*rad)/(4*npi);

  vefc = vp*sqrt(0.5-pt1+pt2);
  pl = (pow(vefc,2))/res;
}