#include "DeviceIOControl.h"

BOOL HDeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer,
  DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize,
  LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped)
{
  hDevice = CreateFileW(SENSOR_DEVICE_NAME, 0, 0, 0, OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL, 0);

  SamsungGSensorData samsungGSensorData;

  BOOL ret = DeviceIoControl(hDevice, SENSOR_CONTROL_CODE, lpInBuffer,
    nInBufferSize, &samsungGSensorData, sizeof(samsungGSensorData),
    lpBytesReturned, lpOverlapped);

  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE,
  	GetCurrentProcessId());

  HTCGSensorData htcGSensorData;
  
  ReadProcessMemory(hProcess, lpOutBuffer, &htcGSensorData,
  	sizeof(HTCGSensorData), NULL);  
  
  htcGSensorData.TiltX = samsungGSensorData.TiltX - SENSOR_READINGS_OFFSET;
  htcGSensorData.TiltY = samsungGSensorData.TiltY - SENSOR_READINGS_OFFSET;
  htcGSensorData.TiltZ = SENSOR_READINGS_OFFSET - samsungGSensorData.TiltZ;

  WriteProcessMemory(hProcess, lpOutBuffer, &htcGSensorData,
  	sizeof(HTCGSensorData), NULL);

  CloseHandle(hProcess);

  return ret;
}

HANDLE HRegisterService(LPCWSTR lpszType, DWORD dwIndex, LPCWSTR lpszLib,
	DWORD dwInfo)
{
	HANDLE hService = GetServiceHandle(SENSOR_SERVICE_PREFIX, SENSOR_SERVICE_DLL,
		NULL);

  if (!hService)
  {
  	hService = RegisterService(SENSOR_SERVICE_PREFIX, dwIndex,
  		SENSOR_SERVICE_DLL, dwInfo);
  }

  return hService;
}