void setup() {
  Serial.begin(115200);
  delay(500);
}

void loop(){
  Serial.println("\n\nAre you overweight?\nEnter your height in meters");
  float h = 0;
  float w = 0;
//  float bmi = 0;
  while (Serial.available() == 0){
    delay(5);
  }
  while (Serial.available() > 0){
    String h_str = Serial.readString();
    h = h_str.toFloat();
  }
  Serial.print("Your height is ");
  Serial.print(h);
  Serial.println(" meters");
  Serial.println("Enter your weight in kg");
  while (Serial.available() == 0){
    delay(10);
  }
  while (Serial.available() > 0){
    String w_str = Serial.readString();
    w = w_str.toFloat();
  }
  Serial.print("Your weight is ");
  Serial.print(w);
  Serial.println(" kg");
  float bmi = w / (pow(h, 2));
  Serial.print("Your BMI index is ");
  Serial.println(bmi);
  Serial.print("You are ");
  if (16.000 > bmi){
    Serial.println("severely underweight");
  } 
  else if (18.400 >= bmi  && bmi >= 16.000){
    Serial.println("underweight");
  } 
  else if (24.900 >= bmi && bmi >= 18.500){
    Serial.println("normal");
  } 
  else if (29.900 >= bmi && bmi >= 25.000){
    Serial.println("overweight");
  } 
  else if (34.900 >= bmi  && bmi >= 30.000){
    Serial.println("moderately obese");
  } 
  else if (39.900 >= bmi && bmi >= 35.000){
    Serial.println("severely obese");
  } 
  else if (bmi > 40.000) {
    Serial.println("morbidily obese");
  }
  delay(2500);
}
