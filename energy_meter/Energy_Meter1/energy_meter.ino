int pinV = 10;
int pinXor = 9;
int Vpin = A0;
int Ipin = A1;
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
  phase_delay = pulseIn(pinXor,HIGH);
  time_period = 2 * half_cycle;
  frequency = 1000000 / time_period;

  
  phase_angle = (phase_delay/time_period)*360;
  power_factor = cos(phase_angle*3.1415/180);

  voltage = (analogRead(Vpin)/1024.0*5)*164.28;
  current = (analogRead(Ipin)/1024.0*5)*24.09;
 
  kVA = voltage * current/1000;
  kW = kVA * power_factor ;

  
  kjoules = kjoules+ (kW *((micros()-period)/1000000.000));
  period = micros();
  
  kWh = kWh + (kjoules/3600) ;
  
  
  if((millis() - disp_time) > 1000){
      Serial.print("Voltage: ");
      Serial.println(voltage);
      Serial.print("Current: ");
      Serial.println(current);
      Serial.print("Frequency: ");
      Serial.println(frequency);
      Serial.print("Power factor: ");
      Serial.println(power_factor);
      Serial.print("kVA: ");
      Serial.println(kVA);
      Serial.print("kW :");
      Serial.println(kW);
      Serial.print("kjoules :");
      Serial.println(kjoules);
      Serial.print("kWh :");
      Serial.println(kWh);
      disp_time = millis();
    }

  
  
}
