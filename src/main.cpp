#include "HX711.h"
#include "WiFi.h"
#include "Api/Api.h"
#define DOUT  23
#define CLK  19
HX711 cell;
const int LOADCELL_DOUT_PIN = 26;
const int LOADCELL_SCK_PIN = 27;

const long LOADCELL_OFFSET = 50682624;
const long LOADCELL_DIVIDER = 5895655;
// TEMP ZA WIFI TESTIRANJE
Api api("192.168.1.204:3000");

 
float weight; 
float calibration_factor = 129200; 
 
void measureweight();
void setup() {
  // Set up serial monitor
  // Set up serial monitor
  // Set up serial monitor
  cell.begin(LOADCELL_DOUT_PIN,LOADCELL_SCK_PIN);
  Serial.begin(115200);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  cell.set_scale();
  cell.tare(); //Reset the scale to 0
  long zero_factor = cell.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
  api.connect();
 

}
 void loop() {
  measureweight();
}
 
void measureweight(){
  cell.set_scale(calibration_factor); //Adjust to this calibration factor
  Serial.print("Reading: ");
  weight = cell.get_units(5); 
    if(weight<0)
  {
    weight=0.00;
    }
  //Serial.print(scale.get_units(), 2);
 // Serial.print(" lbs"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print("Kilogram:");
  Serial.print( weight); 
  Serial.print(" Kg");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  api.postWeight(weight);
  Serial.println("printamo konec branja");
  // Delay before repeating measurement
  delay(100);
}