#include <arduinoFFT.h>

#define SAMPLE 512
#define SAMPLING_FREQUENCY 2600.0
#define inPin A0
#define MAX_HARM 25

double Real[SAMPLE],Imag[SAMPLE],harmonics[MAX_HARM];
long sampling_time = round(1000000*(1.0/SAMPLING_FREQUENCY));
double bin_value = SAMPLING_FREQUENCY/SAMPLE ;

void getSample(){
  /* Samples the input into inPin at SAMPLING_FREQUENCY*/
  unsigned long timestamp = micros();
  int samples = 0;
  while(1){
    if(samples == SAMPLE)
      break;
    else{
      if((micros() - timestamp) > sampling_time ){
      timestamp = micros();
      Real[samples] = analogRead(inPin);
      Imag[samples] = 0;
      samples++; 
      }
      }
    }
    return;
  }

float getSpectrum(){
  double freq,temp;
  for(int i = 0;i<SAMPLE;i++){//Scales the analog input values to 5 volt range.
    temp = Real[i]/1024.0;
    Real[i] = temp;
  }
  
  // The fft code goes here.
  arduinoFFT FFT = arduinoFFT();
  //FFT.DCRemoval(Real,SAMPLE);
  FFT.Windowing(Real,SAMPLE,FFT_WIN_TYP_HANN,FFT_FORWARD);
  FFT.Compute(Real,Imag,SAMPLE,FFT_FORWARD);
  FFT.ComplexToMagnitude(Real,Imag,SAMPLE);
  
  freq = FFT.MajorPeak(Real,SAMPLE,SAMPLING_FREQUENCY);
  return freq; //returns the fundamental frequency
  }

double getTHD(double freq){//takes fundamental frequency as argument and returns thd
  double squared_sum = 0,sum,mean,thd,rms;
  int order,terms; 

  for(order = 1;order<=MAX_HARM;order++){
    sum = 0;
    terms = 0;
    for(int i = 0;i<(SAMPLE/2);i++){
    if(((i*bin_value) < (order*freq+2.6)) && ((i*bin_value)>(order*freq-2.6))){//computes squared sum of harmonics
      sum += Real[i];
      terms ++;
    }
    mean = (sum/terms)*2.57/100.0;
    harmonics[order-1] = mean;  
  }
  }
  Serial.println("Fundamental : "+String(harmonics[0]));
  for(int i=1;i<MAX_HARM;i++){
    if(isnan((harmonics[i])))
      continue;
    Serial.println("Harmonic "+String(i+1)+" : "+String(harmonics[i]));
    squared_sum += pow(harmonics[i],2);
  }
  rms = sqrt(squared_sum + pow(harmonics[0],2));
  Serial.println("RMS value : "+String(rms));
  thd = sqrt(squared_sum)/(harmonics[0]) * 100; // compute thd
  return thd;
  }

void setup(){
  Serial.begin(9600);
  }

void loop(){

  double freq;
  
  getSample();
  freq = getSpectrum();
  /*if((freq>55 && freq<45))
    goto start;*/
  Serial.println("Fundamental Frequency : "+String(freq));
  Serial.println("THD : "+String(getTHD(freq)));
  Serial.println("");
  
  delay(5000);
  }
