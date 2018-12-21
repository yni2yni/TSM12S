// ADS Touch Sensor Test Example Program (IC P/N:TSM12S, 24QFN)
// Code: 
// Date: 2018.12.19  Ver.: 0.0.1
// H/W Target: ARDUINO UNO R3, S/W: Arduino IDE  1.8.8
// Author: Park, Byoungbae (yni2yni@hanmail.net)
// Note: More information? Please ,send to e-mail.
// Uno R3, A4:SDA, A5: SCL, RESET: D7, Leonardo 2:SDA,3:SCL

#include <Wire.h>

#define LF        0x0A //New Line
#define CR        0x0D //Carriage  return
#define SP        0x20 //Space

#define Sensitivity1  0x02 //ch2,ch1
#define Sensitivity2  0x03 //ch4,ch3
#define Sensitivity3  0x04 //ch6,ch5
#define Sensitivity4  0x05 //ch8,ch7
#define Sensitivity5  0x22 //ch10,ch9
#define Sensitivity6  0x23 //ch12,ch11
#define CTRL1     0x08  
#define CTRL2     0x09
#define Ref_rst1		0x0A
#define Ref_rst2		0x0B
#define Ch_Hold1      	0x0C //Touch Key Channel Enable = 0x00
#define Ch_Hold2      	0x0D //Touch Key Channel Enable = 0x00
#define Cal_Hold1     	0x0E //Calibration Enable = 0x00
#define Cal_Hold2     	0x0F //Calibration Enable = 0x00

#define OUTPUT_REG1   0x10 //cs1~cs4 output
#define OUTPUT_REG2   0x12 //cs5~cs8 output
#define OUTPUT_REG3   0x13 //cs9~cs12 output
#define Lock_mask	  0x3B //Lock Mask
#define Force_en	  0x41 //Lock Mask

// =============== TSM12S I2C Chip ID ================================================
#define TSM12S_SLAVE_GND  0x68 //7bit address: 8bit address 0xD0<<1 //Chip_ID Pin = GND
#define TSM12S_SLAVE_VDD  0x78 //7bit address: 8bit address 0xF0<<1 //Chip_ID Pin = VDD

void  Init_TSM12S(void); //Initialize TSM12S (24QFN)

#define RESET_PIN 7 //Reset pin

void setup(){
	
  delay(1); // wait for 1[msec]	
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output (Spped)
  // put your setup code here, to run once:
 
  pinMode(RESET_PIN, OUTPUT);
  //SDA, SCL = Hi-z

  // IC H/W reset signal control ,Active  High Reset
  digitalWrite(RESET_PIN, LOW); // Reset pin = low
  digitalWrite(RESET_PIN, HIGH); // Reset pin = High
  delay(2); //Min: wait for 2[msec]
  digitalWrite(RESET_PIN, LOW); // Reset pin = low
  delay(100); //wait for 100[msec]
  Init_TSM12S(); //Initialize TSM12S
  
}
void loop() {

  byte read_data[3];
  delay(5);
  
  Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
  Wire.write(byte(OUTPUT_REG1)); // sends register address
  Wire.endTransmission(); // stop transmitting
  Wire.requestFrom(TSM12S_SLAVE_GND,1); // read OUTPUT1, 1Byte Read
  read_data[0]=Wire.read();		//OUTPUT1 Data
  
  Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
  Wire.write(byte(OUTPUT_REG2)); // sends register address
  Wire.endTransmission(); // stop transmitting
  Wire.requestFrom(TSM12S_SLAVE_GND,1); // read OUTPUT2, 1Byte Read
  read_data[1]=Wire.read();		//OUTPUT2 Data
  
  Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
  Wire.write(byte(OUTPUT_REG3)); // sends register address
  Wire.endTransmission(); // stop transmitting
  Wire.requestFrom(TSM12S_SLAVE_GND,1); // read OUTPUT3, 1Byte Read
  read_data[2]=Wire.read();		//OUTPUT3 Data
  
  Serial.write(10); 
  Serial.print("--------Touch Sensor Output Data  ------ > ");  // Test Code
  delay(10);
     
  Serial.print(read_data[0],HEX); 
  Serial.write(SP); 
  Serial.print(read_data[1],HEX); 
  Serial.write(SP); 
  Serial.print(read_data[2],HEX);
  Serial.write(LF);   
  Serial.write(CR);

   delay(40);   
}

void  Init_TSM12S(void)
{
   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(CTRL2)); // sends register address
   Wire.write(byte(0x0F)); // sends register data
   Wire.endTransmission(); // stop transmitting

   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(Sensitivity1)); // sends register address
   Wire.write(byte(0xBB)); // sends register data
   Wire.endTransmission(); // stop transmitting
   
   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(Sensitivity2)); // sends register address
   Wire.write(byte(0xBB)); // sends register data
   Wire.endTransmission(); // stop transmitting
  
   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(Sensitivity3)); // sends register address
   Wire.write(byte(0xBB)); // sends register data
   Wire.endTransmission(); // stop transmitting

   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(Sensitivity4)); // sends register address
   Wire.write(byte(0xBB)); // sends register data
   Wire.endTransmission(); // stop transmitting
   
   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(Sensitivity5)); // sends register address
   Wire.write(byte(0xBB)); // sends register data
   Wire.endTransmission(); // stop transmitting   
  
   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(Sensitivity6)); // sends register address
   Wire.write(byte(0xBB)); // sends register data
   Wire.endTransmission(); // stop transmitting   
     
   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(CTRL1)); // sends register address
   Wire.write(byte(0x22)); // sends register data
   Wire.endTransmission(); // stop transmitting   
    
   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(Ref_rst1)); // sends register address
   Wire.write(byte(0xF0)); // sends register data
   Wire.endTransmission(); // stop transmitting
   
   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(Ref_rst2)); // sends register address
   Wire.write(byte(0x00)); // sends register data
   Wire.endTransmission(); // stop transmitting
  
   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(Ch_Hold1)); // sends register address
   Wire.write(byte(0xF0)); // sends register data
   Wire.endTransmission(); // stop transmitting

   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(Ch_Hold2)); // sends register address
   Wire.write(byte(0x00)); // sends register data
   Wire.endTransmission(); // stop transmitting
   
   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(Cal_Hold1)); // sends register address
   Wire.write(byte(0x00)); // sends register data
   Wire.endTransmission(); // stop transmitting   
   
   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(Cal_Hold2)); // sends register address
   Wire.write(byte(0x00)); // sends register data
   Wire.endTransmission(); // stop transmitting   

   Wire.beginTransmission(TSM12S_SLAVE_GND); // sned ic slave address
   Wire.write(byte(CTRL2)); // sends register address
   Wire.write(byte(0x07)); // sends register data 
   //sleep mode enable, S/W Reset Clear, Impedance High, Multi Output
   Wire.endTransmission(); // stop transmitting   
  
   }
// End
