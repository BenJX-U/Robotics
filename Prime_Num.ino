void setup(){
  Serial.begin(115200);
  delay(500);
}

void loop(){
  Serial.println("\n\nEnter integer n to check the nth prime number");
  int num = 1;
  while (Serial.available() == 0){
    delay(10);
  }
  if (Serial.available() > 0){
    String n_str = Serial.readString();
    int n = n_str.toInt();
    int clone = n;
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
    Serial.print("The ");
    Serial.print(clone);
    Serial.print("th prime number is ");
    Serial.print(num);
  }
}
