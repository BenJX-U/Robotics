int n;
String n_str;
int num = 1;

void setup(){
  Serial.begin(115200);
  delay(500);
  Serial.println("\n\nEnter integer n to check the nth prime number");
}

void loop(){
  if (Serial.available() > 0){
    n_str = Serial.readString();
    n = n_str.toInt();
    while (n > 0){
      num ++;
      for (int i = 2; i <= num; i ++){
        if (num % i == 0 && i != num){
          break;
        } else if (i != num){
          continue;
        } else if (i == num){
          n --;
        }
      }
    }
    Serial.print(num);}
}
