/*----------------------------------------------------------
    MH-Z19 CO2 sensor  SAMPLE
  ----------------------------------------------------------*/
#include "TRIGGER_WIFI.h"               /*Includes ESP8266WiFi.h and WiFiClientSecure.h*/
#include "TRIGGER_GOOGLESHEETS.h"       /*Library file for Google Sheets, has to be used after Wi-Fi Client Secure declaration, here everything is in Trigger_WIFI.h, so using it after Trigger_WIFI.h*/
#include "MHZ19.h"


const int s1 = 05; // SWITH 1 2FANS
const int s2 = 04; // SWITH 2 2FANS
const int s3 = D0; // SWITH 3 2FANS00
const int s0 = 00; // SWITH 0 2FANSD0





const int rx_pin = 13; //Serial rx pin no
const int tx_pin = 15; //Serial tx pin no
const int threshold1 = 450;
const int threshold2 = 900;
const int threshold3 = 1500;
const int threshold4 = 3000;


/**********Google Sheets Definations***********/
char column_name_in_sheets[ ][20] = {"Co2_level"};          
String Sheets_GAS_ID = "AKfycbwLAr6ufztOrVqh1N1eg0CyohRs5AlT4Ym0jtOBloeOQKHz5A9VD4UoGb1WXdsDXfUW";                                         /* AKfycbxaZI5uyH-Sbw2sBrRr5PAaIrFOW1_EEaewqkbw-GWdXF0hqCw4p_0eQbDGfKijGk84

( AKfycbzXRzgxscNcOXL3BLLtks--GtuaQGSJHKwim2TBkLMq0D-tT-FhUKV7v3YulGX9tCE ) This is the Sheets GAS ID, you need to look for your sheets id*/
int No_of_Parameters = 1;
MHZ19 *mhz19_uart = new MHZ19(rx_pin, tx_pin);


/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup()
{
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW );
  digitalWrite(s2, LOW );
  digitalWrite(s3, LOW );


  WIFI_Connect("hp_lindani", "lindan1t1");                                                    /*Provide you Wi-Fi SSID and password to connect to Wi-Fi*/
  Google_Sheets_Init(column_name_in_sheets, Sheets_GAS_ID, No_of_Parameters );
  Serial.begin(115200);
  mhz19_uart->begin(rx_pin, tx_pin);
  mhz19_uart->setAutoCalibration(false);
  delay(300);
  //Serial.print("MH-Z19 now warming up...  status:");
 // Serial.println(mhz19_uart->getStatus());
  delay(100);
}


void loopx () {
  digitalWrite(s0, HIGH);
  delay (5000);
  digitalWrite(s1, HIGH);
  delay (5000);
  digitalWrite(s2, HIGH);
  delay (5000);
  digitalWrite(s3, HIGH);
  delay (5000);


}
/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
      digitalWrite(s0, LOW);
  delay (5000);
  digitalWrite(s1, LOW);
  delay (5000);
  digitalWrite(s2, LOW);
  delay (5000);
  digitalWrite(s3, LOW);
  delay (5000);

    digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  ----------------------------------------------------------*/
void loop()
{


  float a = 1, b = 0 ,c=0;
  float fanNumber =0;

  measurement_t m = mhz19_uart->getMeasurement();
 

  Serial.print("co2: ");
  if (m.co2_ppm > threshold1) {
    digitalWrite(s0, HIGH);
    fanNumber =fanNumber+2 ;
    
    if (m.co2_ppm > threshold2) {
      digitalWrite(s1, HIGH);
      fanNumber =fanNumber+2 ;
      if (m.co2_ppm > threshold3) {
        digitalWrite(s2, HIGH);
        fanNumber =fanNumber+2 ;
        if (m.co2_ppm > threshold4) {
          digitalWrite(s3, HIGH);
          //fanNumber =fanNumber+2 ;
        } else {
          digitalWrite(s3, LOW);
         // fanNumber =fanNumber-2 ;
        }
      } else {
        digitalWrite(s2, LOW);
         //fanNumber =fanNumber-2 ;
      }
    } else {
      digitalWrite(s1, LOW);
      // fanNumber =fanNumber-2 ;
    }

  } else  {
    digitalWrite(s0, LOW);
     //fanNumber =fanNumber-2 ;



  } //else if (m.co2_ppm > threshold2) {
  //digitalWrite(s1, HIGH);
  // } else if (m.co2_ppm <= threshold2) {
  // digitalWrite(s1, LOW);
  // }
  b=fanNumber;
  a = m.co2_ppm;
  Serial.println(a);
  Serial.println(b);
  Data_to_Sheets(No_of_Parameters,a );
  delay(10000);


}





