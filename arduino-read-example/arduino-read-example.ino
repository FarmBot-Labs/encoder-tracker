#include <SPI.h>

#define NSS_PIN 22 
#define READ_ENA_PIN 49
#define NULL 0

static const int spi_encoder_offset = 4;
enum SpiEncoders
{
  _X1 = 0b0001,
  _X2 = 0b0010,
  _Y  = 0b0100,
  _Z  = 0b1000,
};

void setup()
{
  pinMode(READ_ENA_PIN, INPUT_PULLUP);
  pinMode(NSS_PIN, OUTPUT);
  digitalWrite(NSS_PIN, HIGH);

  Serial.begin(9600);
  
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.begin();
  //SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
  
  ResetEncoder(_X1);
  ResetEncoder(_X2);
  ResetEncoder(_Y);
  ResetEncoder(_Z);
}

void loop()
{
  const int readPeriodMs = 200;
  
  long X1EncoderData = ReadEncoder(_X1);
  long X2EncoderData = ReadEncoder(_X2);
  long YEncoderData = ReadEncoder(_Y);
  long ZEncoderData = ReadEncoder(_Z);
  Serial.print("EncoderData");
  Serial.print(" X1: ");
  Serial.print(X1EncoderData);
  Serial.print(" X2: ");
  Serial.print(X2EncoderData);
  Serial.print(" Y: ");
  Serial.print(YEncoderData);
  Serial.print(" Z: ");
  Serial.println(ZEncoderData);
  
  delay(readPeriodMs);
}


void ResetEncoder(SpiEncoders encoders)
{
  const byte reset_cmd = 0x00;
  
  digitalWrite(NSS_PIN,LOW);
  SPI.transfer(reset_cmd | (encoders << spi_encoder_offset) );
  digitalWrite(NSS_PIN,HIGH);
}

long ReadEncoder(SpiEncoders encoder)
{
  const byte read_cmd  = 0x0F;
  int readSize = 4;
  long encoderVal = 0;
  
  digitalWrite(NSS_PIN,LOW);
  SPI.transfer(read_cmd | (encoder << spi_encoder_offset) );
  delayMicroseconds(10);

  for (int i = 0; i < readSize; ++i)
  {
    encoderVal <<= 8;
    encoderVal |= SPI.transfer(0x01);
  }
  
  digitalWrite(NSS_PIN,HIGH);
  return encoderVal;
}

