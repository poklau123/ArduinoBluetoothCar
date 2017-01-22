#define RIGHT_FORWARD 4
#define RIGHT_BACK 7
#define LEFT_FORWARD 2
#define LEFT_BACK 3

#define RIGHT_SPEED 5
#define LEFT_SPEED 6

int speeds = 0;
char pre_target = 'P';
char target = 'P';
String command = "";

void setup(){
    Serial.begin(9600);
    pinMode(RIGHT_FORWARD,OUTPUT);
    pinMode(RIGHT_BACK,OUTPUT);
    pinMode(LEFT_FORWARD,OUTPUT);
    pinMode(LEFT_BACK,OUTPUT);
    
    pinMode(RIGHT_SPEED,OUTPUT);
    pinMode(LEFT_SPEED,OUTPUT);
    speeds = 200;
}

void go_ahead(){
    digitalWrite(RIGHT_FORWARD,HIGH);
    digitalWrite(RIGHT_BACK,LOW);
    digitalWrite(LEFT_FORWARD,HIGH);
    digitalWrite(LEFT_BACK,LOW);
}

void go_back(){
    digitalWrite(RIGHT_FORWARD,LOW);
    digitalWrite(RIGHT_BACK,HIGH);
    digitalWrite(LEFT_FORWARD,LOW);
    digitalWrite(LEFT_BACK,HIGH);
}

void go_left(){
    digitalWrite(RIGHT_FORWARD,HIGH);
    digitalWrite(RIGHT_BACK,LOW);
    digitalWrite(LEFT_FORWARD,LOW);
    digitalWrite(LEFT_BACK,HIGH);
}

void go_right(){
    digitalWrite(RIGHT_FORWARD,LOW);
    digitalWrite(RIGHT_BACK,HIGH);
    digitalWrite(LEFT_FORWARD,HIGH);
    digitalWrite(LEFT_BACK,LOW);
}

void pause(){
    digitalWrite(RIGHT_FORWARD,LOW);
    digitalWrite(RIGHT_BACK,LOW);
    digitalWrite(LEFT_FORWARD,LOW);
    digitalWrite(LEFT_BACK,LOW);
}

//获取窗口输入信息，区分字符串和数值命令
void getMessage(){
  while(Serial.available()){
    command += char(Serial.read());
    delay(2);
  }
  if(command.length() > 0){
    String tmp = command;
    command = "";
    if(tmp.toInt() == 0){     //如果是0则为方向指令
      target = tmp[0];
      if(target == 'W' || target == 'S' || target == 'P'){
        pre_target = target;
      }
    }else{                    //否则为速度指令
      int temp_speed = tmp.toInt();
      if(temp_speed >= 0 && temp_speed < 256){
        speeds = temp_speed;
      }
    }
    //Serial.println(String("")+"NOW:"+target+" SPEED:"+speeds);
  }
}

void loop(){
    getMessage();
    switch(target){
      case 'W':go_ahead();break;
      case 'S':go_back();break;
      case 'A':go_left();break;
      case 'D':go_right();break;
      case 'P':pause();break;
      case 'B': 
        switch(pre_target){
          case 'W':go_ahead();break;
          case 'S':go_back();break;
          default: pause();
        }break;
    }
    analogWrite(RIGHT_SPEED,speeds);
    analogWrite(LEFT_SPEED,speeds);
    
}
