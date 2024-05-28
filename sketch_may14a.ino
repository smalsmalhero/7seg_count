#include <Keypad.h>    // 引用Keypad程式庫

byte tab[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x67};
int seg7[] = {13,12,11,10,9,8,7}; // 自行定義腳位
byte com[] = {5, 4, 3, 2};        // 自行定義腳位

int Count = 0, Count_1,i;
char sw1,sw2;
int a = 1,b = 1;
long sw1t20,t5002,sw2t20;
long t5001;
String data = "";

#define KEY_ROWS 4 // 按鍵模組的列數
#define KEY_COLS 3 // 按鍵模組的行數

// 依照行、列排列的按鍵字元（二維陣列）
char keymap[KEY_ROWS][KEY_COLS] = {
  {'7', '8', '9'},
  {'4', '5', '6'},
  {'1', '2', '3'},
  {'R', '0', 'U'}
};

byte colPins[KEY_COLS] = {A0,A1,13};	   // 按鍵模組，行1~3接腳。 自行定義腳位
byte rowPins[KEY_ROWS] = {A5,A4,A3,A2}; //  按鍵模組，列1~4接腳。 自行定義腳位

// 初始化Keypad物件
// 語法：Keypad(makeKeymap(按鍵字元的二維陣列), 模組列接腳, 模組行接腳, 模組列數, 模組行數)
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, KEY_ROWS, KEY_COLS);

void setup(){
  Serial.begin(9600);
  for(i=0;i<7;i++){
    pinMode(seg7[i],OUTPUT);
  }
  for(i=0;i<4;i++){
    pinMode(com[i],OUTPUT);
  }
}
  
void loop(){
  // 透過Keypad物件的getKey()方法讀取按鍵的字元
  char key = myKeypad.getKey();

  if(a == 1 && b == 0){
    if(millis() - t5001 >= 500){
      t5001 = millis();
      Serial.println(Count);
      Count++;
      Serial.print(Count/1000);
      Serial.print(Count%1000/100);
      Serial.print(Count%100/10);
      Serial.println(Count%10);
      if (Count == 9999){
        Count = 0;
      }
    }
  }
  if(a == 1 && b == 1){
    if(millis() - t5002 >= 500){
      t5002 = millis();
      Count--;
      Serial.print(Count/1000);
      Serial.print(Count%1000/100);
      Serial.print(Count%100/10);
      Serial.println(Count%10);
      if(Count <= 0){
      	Count = 9999;
      }
    }
  }
  if(a==0){
    if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0'){
      Serial.println(data);
      Count = data.toInt();
      if (data.length() >= 4){
        data.remove(0,1);
      }
      data += key;
    }
  }
  if (key){  // 若有按鍵被按下…
    sw1 = 'R';
    sw2 = 'U';
  }
  
  if(sw1 == key){
    sw1 = 'S';
    if(sw1 == 'S'){
      if(a == 1){
        a = 0;
        data = String(Count);
      }
      else
        a = 1;
    }
  }
  if(sw2 == key){
    sw2 = 'D';
    if(sw2=='D'){
      if(b == 1){
        b = 0;
      }
      else{
        b = 1;
      }
    }
  }
  showseg(com[0], tab[Count/1000]);
  showseg(com[1], tab[Count%1000/100]);
  showseg(com[2], tab[Count%100/10]);
  showseg(com[3], tab[Count%10]);
}

void showseg(byte scan,byte data){
  digitalWrite(scan, 1);

  for(int i = 0;i < 7;i++){
    if(bitRead(data,i) == 1)
      digitalWrite(seg7[i],HIGH);
    else
      digitalWrite(seg7[i],LOW); 
  }

  for(int i = 0;i < 7;i++){
    digitalWrite(seg7[i],LOW);
  }
  delay(10);
  digitalWrite(scan, 0);
}  