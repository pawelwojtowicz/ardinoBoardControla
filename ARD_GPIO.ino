#include <TimedAction.h>

#define GC_READY_MASK 0x01
#define GC_START_MASK 0x01

byte commandByte = 0;

void sendOutputState()
{
  byte inputStateMask = 0;

  if ( HIGH == read_GCReady()  )
  {
    inputStateMask |= GC_READY_MASK;
  }
  
  byte outputMsg[6] = { 's', ((commandByte&0xF0)>>4)+'0',((commandByte&0xF))+'0' ,((inputStateMask&0xF0)>>4)+'0',((inputStateMask&0xF))+'0', '\n'};    

  Serial.write(outputMsg,6);
}

TimedAction outputReporter = TimedAction(500,sendOutputState);

void commandReceived(byte cmdByte)
{
  commandByte = cmdByte;

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
