
#define SAMPLES 10 
#define DACPIN 2

void setup() {
  // put your setup code here, to run once:

 // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT); 
   analogWrite(DACPIN,0);  
}

void loop() {
  // put your main code here, to run repeatedly:

   int ich; 
   int s;  
   unsigned int val;
   char str[1000] ;  
   
   if( Serial.available() > 0) {
    
   int ival = Serial.readString().toInt();
   
    analogWrite(DACPIN,ival);
    delay(20);
 
 }
   

 sprintf(str," START \n"); 
 Serial.print(str);   
           
 val = analogRead(A0);
 
 // print out the value you read:

 sprintf(str," %d \n",val);
  Serial.print(str);  
    
    
}
