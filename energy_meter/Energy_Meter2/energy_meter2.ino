int pinV = 10;
int pinXor = 9;
int Vpin = A0;
int Ipin = A1;
unsigned long phase_delay,disp_time=0,period;
double time_period,frequency,phase_angle,power_factor,voltage,current,kVA,kW,kWh = 0,kjoules = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pinV, INPUT);
  pinMode(pinXor, INPUT);
  period = micros();
}

void loop() {
  
  //time_period = 2 * pulseIn(pinV, HIGH);
  phase_delay = pulseIn(pinXor,HIGH);
  //frequency = 1000000 / time_period;
  
  power_factor = cos((phase_delay/20000.00)*6.283);

  voltage = analogRead(Vpin);
  current = analogRead(Ipin);
 
  kVA = voltage * current * 0.0944 /1000;
  kW = kVA * power_factor ;

  
  kjoules = kjoules+ (kW *((micros()-period)/1000000.000));
  //Serial.println(micros()-period);
  //Serial.print(".");
  period = micros();
  
  kWh = kWh + (kjoules/3600) ;
  
  
  if((millis() - disp_time) > 1000){
      Serial.print("Power factor: ");
      Serial.println(power_factor);
      Serial.print("kVA: ");
      Serial.println(kVA);
      Serial.print("kW :");
      Serial.println(kW);
      Serial.print("kWh :");
      Serial.println(kWh);
      disp_time = millis();
    }

  
  
}
