#include "stdafx.h"

const LPCWSTR  SENSOR_DEVICE_NAME     = L"ACC1:";
const LPWSTR  SENSOR_SERVICE_PREFIX   = L"SSS";
const LPWSTR  SENSOR_SERVICE_DLL      = L"SmiSensorServer_2.dll";
const DWORD    SENSOR_CONTROL_CODE    = 0x80122EF0;
const short    SENSOR_READINGS_OFFSET = 2048;

struct SamsungGSensorData
{
  short TiltX;
  short TiltY;
  short TiltZ;

  SamsungGSensorData()
  {
    TiltX = 0;
    TiltY = 0;
    TiltZ = 0;
  }
};

struct HTCGSensorData
{
	short TiltX;
	short TiltY;
	short TiltZ;
	short Unknown1;
	int   AngleY;  
	int   AngleX;
	int   Unknown2;
  
  HTCGSensorData()
  {
    TiltX    = 0;
    TiltY    = 0;
    TiltZ    = 0;
    Unknown1 = 0;
    AngleY   = 0;
    AngleX   = 0;
    Unknown2 = 0;
  }
};

BOOL HDeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer,
	DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize,
	LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);

HANDLE HRegisterService(LPCWSTR lpszType, DWORD dwIndex, LPCWSTR lpszLib,
  DWORD dwInfo);