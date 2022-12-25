#include <TimedAction.h>

#define GC_READY_MASK 0x01
#define GC_START_MASK 0x01


void sendOutputState()
{
  byte outputs = 0;

  if ( HIGH == read_GCReady()  )
  {
    outputs |= GC_READY_MASK;
  }
  
  byte outputMsg[4] = { 's', ((outputs&0xF0)>>4)+'0',((outputs&0xF))+'0', '\n'};    

  Serial.write(outputMsg,4);
}

TimedAction outputReporter = TimedAction(500,sendOutputState);

void commandReceived(byte cmdByte)
{
  if ( cmdByte & GC_START_MASK )
  {
    set_GCStart(HIGH);
  }
  else
  {
    set_GCStart(LOW);    
  }  
}

void setup() {
  // put your setup code here, to run once:
  setUpGPIOs();
  setUpSerialDriver();
}

void loop() {
  // put your main code here, to run repeatedly:
  outputReporter.check();
}
