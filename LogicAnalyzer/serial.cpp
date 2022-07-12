#include <windows.h>
#include <string>

/* Serial Port */
static HANDLE port;
static DCB    serial;

bool serialOpen(int portNumber, int baudRate)
{
   std::string portName = std::string("\\\\.\\COM") + std::to_string(portNumber);


   port = CreateFileA(portName.c_str(),
                      GENERIC_READ | GENERIC_WRITE,
                      FILE_SHARE_VALID_FLAGS,
                      NULL,
                      OPEN_EXISTING,
                      0,
                      NULL);
   if (!GetCommState(port, &serial) )
   {
      return(false);
   }
   serial.BaudRate    = baudRate;
   serial.Parity      = NO_PRIORITY;
   serial.StopBits    = ONESTOPBIT;
   serial.ByteSize    = 8;
   serial.DCBlength   = sizeof(serial);
   serial.fDtrControl = DTR_CONTROL_DISABLE;

   return(SetCommState(port, &serial) );
}
bool serialOpen(int portNumber)
{
   return(serialOpen(portNumber, CBR_9600) );
}
bool serialIsOpened(void)
{
   return(GetCommState(port, &serial) );
}
bool serialSend(unsigned char serialData)
{
   DWORD writtenBytes;


   return(WriteFile(port, &serialData, 1, &writtenBytes, NULL) );
}
bool serialSend(const void *serialData, int data_size)
{
   DWORD writtenBytes;


   return(WriteFile(port, serialData, data_size, &writtenBytes, NULL) );
}
bool serialReceive(void *serialdata, int &data_size)
{
   COMSTAT com_stat;
   DWORD   temp;


   ClearCommError(port, &temp, &com_stat);
   data_size = 0;

   return(  (com_stat.cbInQue > 0)
         && ReadFile(port, serialdata, com_stat.cbInQue, (DWORD *)&data_size, NULL) );
}
bool serialClear(void)
{
   return(PurgeComm(port, PURGE_RXCLEAR | PURGE_TXCLEAR) );
}
void serialClose(void)
{
   CloseHandle(port);
}
