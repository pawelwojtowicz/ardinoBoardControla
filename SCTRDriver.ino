#define GC_READY_IN 7
#define GC_START_OUT 8

void setUpGPIOs()
{
  //set up inputs
  pinMode(GC_READY_IN, INPUT);

  //set up outputs
  pinMode(GC_START_OUT, OUTPUT);
}

byte read_GCReady()
{
  return digitalRead(GC_READY_IN);
}

void set_GCStart( byte start)
{
  digitalWrite(GC_START_OUT,start);  
}