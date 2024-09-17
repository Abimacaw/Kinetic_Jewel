#include <BLEDevice.h>
#include <BLEUtils.h> 
#include <BLEServer.h>
#define in1  2// D0 arch        
#define in2  3//D1 arch
#define in3  6//D4 lotus
#define in4  7//D5lotus
#define in5  8//D8temp
#define in6  9//D9temp
#define in7  10//D10 led 
#define vib  20//D7vibration motor
const int frequency = 500;
const int resolution = 8;
const int channel1 = 0;
const int channel2 = 1, ch3 = 2, ch4 = 3, ch5 = 4, ch6 = 5;
const int dutycycleT = 100, dutycycleA = 100, dutycycleL = 255;
const int dutycycle = 0;  
int i;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "2e83cb78-c55e-4172-a529-e9597e98aa53"
#define CHARACTERISTIC_UUID "f101a3de-99aa-4375-bc5d-8e58679e267c"
BLEServer* pServer;
BLECharacteristic* pCharacteristic;
BLEAdvertising* pAdvertising;

bool isConnected = false;

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {

      std::string value = pCharacteristic->getValue();
      Serial.begin(115200);

      if (value.length() > 0) {
        Serial.println("***");
        Serial.print("New value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("***");
      }

      if(value == "T")//54 arch
      {
        Serial.println("Arch up");
        ledcWrite(channel1,dutycycleA);
        digitalWrite(in2, LOW );
        delay(6000);
        ledcWrite(channel1,dutycycle);
        digitalWrite(in2, LOW);       
      }

      if(value == "B")//42 arch
      { 
        Serial.println("Arch down");
        digitalWrite(in1, LOW);
        ledcWrite(channel2,dutycycleA);
        Serial.print("ON");
        delay(6000);
        digitalWrite(in1, LOW);
        ledcWrite(channel2,dutycycle);
       }

       if(value == "O")// lotus 4f /////:)
      { 
       
        Serial.println("Lotus Open");
        digitalWrite(in4, LOW);
        ledcWrite(ch3,dutycycleL);
        digitalWrite(in7,HIGH);
        Serial.print("ON");
        delay(5000);
        digitalWrite(in4, LOW);
        ledcWrite(ch3,dutycycle);
       }

       if(value == "C")// Lotus 43
      {         
        Serial.println("Lotus close");
        digitalWrite(in3, LOW);
        digitalWrite(in7,LOW);
        ledcWrite(ch4,dutycycleL);
        Serial.print("ON");
        delay(5000);
        digitalWrite(in3, LOW);
        ledcWrite(ch4,dutycycle);
       }

       if(value == "U")//temple 55///:)
      {        
        Serial.println("Temple up");
        digitalWrite(in6, LOW);
        ledcWrite(ch5,dutycycleT);
        Serial.print("ON");
        delay(10000);
        digitalWrite(in6, LOW);
        ledcWrite(ch5,dutycycle);
       }

       if(value == "D")// temple 44
      { 
        Serial.println("Temple down"); 
        digitalWrite(in5, LOW);
        ledcWrite(ch6,dutycycleT);
        Serial.print("ON");
        delay(10000);
        digitalWrite(in5, LOW);
        ledcWrite(ch6,dutycycle);
       }

       if(value == "F")// Stop 46        1
      { 
        Serial.println("Stop");
        ledcWrite(channel1,dutycycle);
        ledcWrite(channel2,dutycycle);
        ledcWrite(ch3,dutycycle);
        ledcWrite(ch4,dutycycle);
        ledcWrite(ch5,dutycycle);
        ledcWrite(ch6,dutycycle);
       }

       if(value == "A")//
      {
        Serial.println("Arch stop");
        ledcWrite(channel1,dutycycle);
        ledcWrite(channel2,dutycycle);  
      }
      if(value == "L")//
      {         
        Serial.println("Lotus Stop");
        ledcWrite(ch3,dutycycle);
        ledcWrite(ch4,dutycycle);
       }
       if(value == "S")// temple 44///:)                     1
      { 
        Serial.println("Temple stop");
        ledcWrite(ch5,dutycycle);
        ledcWrite(ch6,dutycycle);
       }
       if(value == "G")
       {
        Serial.println("Sequential");
        ledcWrite(ch3,dutycycleL);  
        digitalWrite(in4,LOW);
        digitalWrite(in7,HIGH);

        delay(6000);
        ledcWrite(ch3,dutycycle);
        digitalWrite(in4,LOW);
        ledcWrite(ch5,dutycycleT);
        digitalWrite(in6,LOW);
        ledcWrite(channel1,dutycycleA);
        digitalWrite(in2,LOW);
        delay(7000);
        ledcWrite(channel1,dutycycle);
        digitalWrite(in2,LOW);
        ledcWrite(ch5,dutycycle);
        digitalWrite(in6,LOW);
      }
      if(value=="F")
      {
        Serial.println("Reverse");
        Serial.println("temple down, arch up");
        digitalWrite(in5, LOW);
        ledcWrite(ch6,dutycycleT);
        digitalWrite(in2, LOW);
        ledcWrite(channel1,dutycycleA);
        delay(7000);
        ledcWrite(ch6,dutycycle);
        digitalWrite(in5, LOW);
        ledcWrite(channel1,dutycycle);
        digitalWrite(in2, LOW);
        Serial.println("Lotus close");
        digitalWrite(in3, LOW);
        ledcWrite(ch4,dutycycleL);
        //Serial.print("ON");
        delay(6000);
        digitalWrite(in7,LOW);
        digitalWrite(in3, LOW);
        ledcWrite(ch4,dutycycle);
      }
    }
  };
void startAdvertising() {
  pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void setup() {
  Serial.begin(115200);
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);


  ledcSetup(channel1,frequency,resolution);
  ledcSetup(channel2,frequency,resolution);
  ledcSetup(ch3,frequency,resolution);
  ledcSetup(ch4,frequency,resolution);
  ledcSetup(ch5,frequency,resolution);
  ledcSetup(ch6,frequency,resolution);
  ledcAttachPin(in1,channel1);
  ledcAttachPin(in2,channel2);
  ledcAttachPin(in3,ch3);
  ledcAttachPin(in4,ch4);
  ledcAttachPin(in5,ch5);
  ledcAttachPin(in6,ch6);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);

  BLEDevice::init("MyESP32");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new BLEServerCallbacks());

  BLEService* pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
  );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Hello World");
  pService->start();

  // Initialize advertising
  pAdvertising = pServer->getAdvertising();
  pAdvertising->setScanResponse(false);
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();
}


void loop() {
  if (!isConnected && pServer->getConnectedCount() > 0) {
    isConnected = true;   
    Serial.println("Connected");
  }
  
  if (isConnected && pServer->getConnectedCount() == 0) {
    isConnected = false;
    Serial.println("Disconnected");
    startAdvertising();
  }
  delay(2000);
}  