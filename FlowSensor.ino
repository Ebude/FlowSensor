
//------------------------------------------------------//
// Project: Refueling simulation with flow sensor
// Developped: Ebude
// Date: 24/08/2018
// -----------------------------------------------------//


//---------------Initialisation of variables------------//

int sensorPin = A0; // pin on which the pressure guage is connected to the arduino
float vol = 0; // volume in a tank after a certain time
int sensorValue = 0; // pressure value read from the pressure gauge

float P1=0; // initial pressure

// characteristics of the flow cylinder
int rho=832; // Density of diesel
const float D1=0.04; // diameter of cylinder
const float D2=0.018; //diameter of guage cylinder
const float pi= 3.14; //pi
const int time=1800; // 30mins
float d, CD, a2, a1, FR, s; // d=diameter ratio, CD= ,  a1 and a2 are areas

//------------------------------------------------------//


void setup() {
  // prepare serial communication  
  Serial.begin(9600);
  Serial.print("Choose pressure get the volume in 30minutes");
  Serial.println();
  Serial.print("NB: Pressure should be below 150");
  Serial.println();
  Serial.println();
  delay(1000);
 
   
}

void loop() {
  // read value from the pressure gauge
  sensorValue  = ((analogRead(sensorPin)*54/1023)-2)*5; //transforming bits to value
  
  // when a value more than 150 is selected signal
  if (sensorValue<0){
   Serial.print("Choose a value below 150!!!");
   Serial.println();
   Serial.println();
  }
  
  // when the right value is selected
  else{
  // print value
  Serial.print("Pressure: ");
  Serial.print(sensorValue);
  Serial.print(" N/m3");
  Serial.println();  
  
  //-------------Calculations-----------------------//
  a1=pi*D1*D1/4.0;
  a2=pi*D2*D2/4.0;
  CD=a2/a1;
  d=D2/D1;
  s=(2*(sensorValue-P1))/(rho*(1-(d*d*d*d)));
  FR=CD*a2*sqrt(s)*1000000;
  
  //-----------------------------------------------//
  
  Serial.print("Flow rate: ");
  Serial.print(FR, 2);
  Serial.print(" l/s");
  Serial.println();
  
  vol = FR*time;
  
  Serial.print("Volume: ");
  Serial.print(vol, 3);
  Serial.print(" l");
  Serial.println();
  Serial.println();
  }
  
  
                 
 delay(2000);                 
}
