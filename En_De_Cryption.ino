int unsigned intro = 0;
int unsigned cond;
int unsigned shift;
char unsigned mess;
int unsigned pos = 0;
char out[254];


void cryption(int shift, int mess, int cond)
{
  if (mess == 32)
  {
    out[pos] = ' ';
  }
  else
  {
    int act;
    if (shift > 26)
    {
      act = shift % 26;
    }
    else
    {
      act = shift;
    }
    if (cond == 1)
    {
      if (mess >= 97 && mess <= 122 && mess + act > 122)
      {
        act = 96 + (mess + act - 122);
      }
      else if (mess >= 65 && mess <= 90 && mess + act > 90)
      {
        act = 64 + (mess + act - 90);
      }
      else
      {
        act = mess + act;
      }
    }
    else if (cond == 2)
    {
      if (mess >= 97 && mess <= 122 && mess - act < 97)
      {
        act = 123 - (shift - (mess - 97));
      }
      else if (mess >= 65 && mess <= 90 && mess - act < 65)
      {
        act = 91 - (shift - (mess - 65));
      }
      else
      {
        act = mess - act;
      }
    }
    Serial.println(act);
    out[pos] = char(act);
  }
  pos ++;
}


void reset()
{
  intro = 0;
  cond = 0;
  shift = 0;
  mess = 0;
  pos = 0;
  memset(out, 0, 75);
}


void setup()
{
  Serial.begin(115200);
}


void loop()
{
  if (intro == 0)
  {
    Serial.println("\nEnter 1 for encryption, 2 for decryption");
  }
  else if (intro == 1)
  {
    Serial.println("Enter shift");
  }
  else if (intro == 2)
  {
    Serial.println("Enter message");
  }
  while (Serial.available() == 0)
  {
    delay(10);
  }
  while (Serial.available() > 0)
  {
    if (intro == 0)
    {
      String str_cond = Serial.readString();
      cond = str_cond.toInt();
      Serial.println("Encyrption mode");
    }
    else if (intro == 1)
    {
      String str_shift = Serial.readString();
      shift = str_shift.toInt();
      Serial.print("The shift is ");
      Serial.println(shift);
    }
    else if (intro == 2)
    {
      while (Serial.available() > 0)
      {
        mess = Serial.read();
        Serial.print(char(mess));
        cryption(shift, mess, cond);
      }
    }
  }
  if (intro == 2)
  {
    Serial.println(out);
    reset();
  }
  else
  {
    intro ++;
  }
}
