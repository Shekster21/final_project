int pinV = 9;
int pinXor = 10;
int Vpin = A4;
int Ipin = A3;
int Ppin = A5;
unsigned long half_cycle,common_time,phase_delay,disp_time=0,period;
double time_period,frequency,phase_angle,power_factor,voltage,current,kVA,kW,kWh = 0,kjoules = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pinV, INPUT);
  pinMode(pinXor, INPUT);
  period = micros();
}

void loop() {
  half_cycle = pulseIn(pinV, HIGH);
  common_time = pulseIn(pinXor,HIGH);
  time_period = 2 * half_cycle;
  frequency = 1000000 / time_period;

  phase_delay = common_time;
  phase_angle = (phase_delay/time_period)*360;

  voltage = analogRead(Vpin);
  current = analogRead(Ipin);
  kVA = analogRead(Ppin);

  if((millis() - disp_time) > 1000){
      Serial.print("Voltage: ");
      Serial.println(voltage);
      Serial.print("Current: ");
      Serial.println(current);
      Serial.print("Frequency: ");
      Serial.println(frequency);
      Serial.print("Phase Angle: ");
      Serial.println(phase_angle);
      Serial.print("kVA: ");
      Serial.println(kVA);
      disp_time = millis();
    }
  
  /*kVA = voltage * current/1000;
  kW = kVA * cos(phase_angle*3.1415/180);
  
  kjoules = kjoules+ (kW *((micros()-period)/1000000));
  period = micros();
  
  kWh = kWh + (kjoules/3600) ;
  
  
  if((millis() - disp_time) > 1000){
      Serial.print("Voltage: ");
      Serial.println(voltage);
      Serial.print("Current: ");
      Serial.println(current);
      Serial.print("Frequency: ");
      Serial.println(frequency);
      Serial.print("Phase Angle: ");
      Serial.println(phase_angle);
      Serial.print("kVA: ");
      Serial.println(kVA);
      Serial.print("kW :");
      Serial.println(kW);
      Serial.print("kWh :");
      Serial.println(kWh);
      disp_time = millis();
    }*/

  
  
}
