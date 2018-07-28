#include <SoftwareSerial.h>
SoftwareSerial fingerPrint(2, 3);

#include <Adafruit_Fingerprint.h>
uint8_t id;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerPrint);
int c1=0;
int c2=0;
int voter[5] = { 0 };
#define cand1 5
#define cand2 10
#define RedLight 6
#define GreenLight 8

void setup() {
    Serial.begin(9600);
    finger.begin(57600);
    pinMode(cand1, INPUT_PULLUP);
    pinMode(cand2, INPUT_PULLUP);  
    pinMode(RedLight, OUTPUT);
    pinMode(GreenLight, OUTPUT);
    Serial.println("Voting System");
    Serial.println("by Personal Authentication"); 
    Serial.println("Finding Module");
}

void loop() {
  if (finger.verifyPassword()){
      Serial.println("Found fingerprint sensor!");
      Serial.println("Found Module ");
      
      digitalWrite(RedLight, HIGH);

      int check = 0;
      
      for(int i=0;i<5;i++){ 
        if(check == 0){
           Serial.println("Place Finger");
           check = 1;
        }
        int result=getFingerprintIDez();
        if(result>0 && alreadyVoted(result) > 0){
            digitalWrite(RedLight, LOW);
            delay(1000);
            digitalWrite(GreenLight, HIGH);
            
            Serial.println("Allowed to vote");
            Serial.println("Place your vote now...");
            
            while(1){
              if(digitalRead(cand1) == HIGH){
                c1++;
                
                voted(result);
                check = 0;
                break;
              }else if(digitalRead(cand2) == HIGH){
                c2++;
                voted(result);
                check = 0;
                break;
              }
            }
         }else{
          i--;
         }
      }
      delay(1000);
     
  }else {
    Serial.println("Did not find fingerprint sensor :(");
    Serial.println("module not Found");
    Serial.println("Check Connections");
  }
     
 
}

void voted(int id){
  Serial.println(id);
  delay(3000);
  digitalWrite(GreenLight, LOW);
  digitalWrite(RedLight, HIGH);
  Serial.println("Thank you for your valuable vote");
  Serial.print("candidate 1: ");
  Serial.println(c1);
  Serial.print("candidate 2: ");
  Serial.println(c2);
}

int alreadyVoted(int id){
  for(int i = 0; i < 5; i++){
    if(voter[i] == id){
      Serial.println("You have already voted");
      return -1;
    }
  }

  
  for(int j = 0; j < 5; j++){
    if(voter[j] == 0){
      voter[j] = id;
      break;
    }
  }
  
  return 1;
 
}

int getFingerprintIDez()
{
  uint8_t p = finger.getImage();
  
  if (p != FINGERPRINT_OK)  
  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  
  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)
  {
   //
   Serial.println("Finger Not Found");
   //(0,1);
   Serial.println("Try Later");
   delay(2000);  
  return -1;
  }
  // found a match!
  Serial.print("Found ID #"); 
  Serial.println(finger.fingerID); 
  return finger.fingerID; 
}


