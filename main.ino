int in1=12;
int in2=11;
int in3=10;
int in4=9;
#define PIN_PWML 2
#define PIN_PWMR 3



void _mRun(int pin1,int pin2)//电机右转
{
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,LOW);
}
void _mBack(int pin1,int pin2)//回退
{
  digitalWrite(pin1,LOW);
  digitalWrite(pin2,HIGH);
}
void _mStop(int pin1,int pin2)//紧急制动
{
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,HIGH);
}
 
void setup()
{
   pinMode(PIN_PWML,OUTPUT);//左右调速
   pinMode(PIN_PWMR,OUTPUT);
 
 Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  //电机保持不动。
  digitalWrite(in1,HIGH);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,HIGH);
}

void loop()
{

  
  getstr=Serial.read();
  delayMicroseconds(50);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(50 );
  digitalWrite(TrigPin, LOW);
  
  cm = pulseIn(EchoPin, HIGH) / 58.0; //将回波时间换算成cm 
  cm = (int(cm * 100.0)) / 100.0; //保留两位小数 
  
  if (i==5)
  {//连接测5次，计算平均值，如果小于15厘米则紧急停车
    i=0;
    cmeve=cmsum/5;
    cmsum=0;
    
    if (cmeve<15 and cmeve>0) 
    {
      Serial.println(cmeve);
      _mStop(in1,in2);
      _mStop(in3,in4);
    } 
  }
  else 
       {
    i=i+1;
    cmsum=cmsum+cm;
       }                                     //超声波

 
if(MODE==1)
{  
    analogWrite(PIN_PWML,60);//左右调速
    analogWrite(PIN_PWMR,65);

         if(rec=='b')
  {
    Serial.println("go back!");
    _mStop(in1,in2);
    _mStop(in3,in4);    
    _mRun(in1,in2);
    _mRun(in3,in4);
  }
  else if(rec=='f'){
    Serial.println("go forward!");
    _mStop(in1,in2);
    _mStop(in3,in4); 
    
    _mBack(in1,in2);
    _mBack(in3,in4);
  }
  else if(rec=='r')
     {
    Serial.println("go right!");//右转
    _mStop(in1,in2);
    _mStop(in3,in4); 
    
    _mRun(in1,in2);
    _mBack(in3,in4);

    delay(600);
    _mStop(in3,in4);
    _mStop(in1,in2);
     }
  else if(rec=='l')
  {
    Serial.println("go left!");//左转
    _mStop(in2,in1);
    _mStop(in4,in3); 
    
    _mRun(in3,in4);
    _mBack(in1,in2);
    
    delay(600);
    _mStop(in3,in4);
    _mStop(in1,in2);
  }
  else if(rec=='s')
  {
    Serial.println("Stop!");
    _mStop(in3,in4);
    _mStop(in1,in2);   
  }
 

    
//模式一

}//loop




 

