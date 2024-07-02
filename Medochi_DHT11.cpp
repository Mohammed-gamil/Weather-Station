#include "Medochi_DHT11.h"

DHT11::DHT11(int pin) : _pin(pin)
{
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, HIGH);
}

int DHT11::readRawData(byte data[5])
{
	delay(500);
	startSignal();
	unsigned long timeout_start = millis();

	while (digitalRead(_pin) == HIGH)
	{
		if (millis() - timeout_start > 1000)
		{
			return 2;
		}
	}
	delayMicroseconds(80);
	if (digitalRead(_pin) == HIGH)
	{
		delayMicroseconds(80);
		for (int i = 0; i < 5; i++)
		{
			data[i] = readByte();
		}
	}
	else
	{
		delay(15);
	}
	if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))
	{
		return 0;
	}
	else
	{
	}
}
byte DHT11::readByte()
{
	
	byte value = 0;
	for (int i = 0; i < 8; i++)
	{
		while (digitalRead(_pin) == LOW);
		delayMicroseconds(30);
		if (digitalRead(_pin) == HIGH)
		{
			value |= (1 << (7 - i));
		}
		while (digitalRead(_pin) == HIGH);
	}
	return value;
}

void DHT11::startSignal()
{
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	delay(18);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(40);
	pinMode(_pin, INPUT);
}

float DHT11::readTemperature()
{
	byte data[5];
	int error = readRawData(data);
	if (error == 0)
	{
		return data[2];
	}
	else if (error == 1)
	{
	}
	else if (error == 2)
	{
	}
}
int DHT11::readHumidity()
{
	byte data[5];
	int error = readRawData(data);
	if (error == 0)
	{
		return data[0];
	}
}
