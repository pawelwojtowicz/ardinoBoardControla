#define SERIAL_INPUT_SIZE 100
String inputData = "";

void setUpSerialDriver()
{
  inputData.reserve(SERIAL_INPUT_SIZE);
  Serial.begin(115200);
}

void serialEvent()
{
  while ( Serial.available())
  {
    if ( inputData.length() >= SERIAL_INPUT_SIZE )
    {
      inputData = "";
    }

    char inChar = (char)Serial.read();

    if ( inChar != '\n')
    {
      inputData += inChar;
    }
    else
    {
      if ( inputData.length() == 3 && inputData[0] == 'c' )
      {
        byte commandByte =  (inputData[1] - '0')<<4  | (inputData[2] - '0') ;
        commandReceived( commandByte );
      }
      inputData = "";  
    }                      
  }
}
