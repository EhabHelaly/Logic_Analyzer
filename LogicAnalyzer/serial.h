#ifndef SERIAL_PORT_H_INC
#define SERIAL_PORT_H_INC

bool serialOpen(int portNumber, int baudRate);
bool serialOpen(int portNumber);
bool serialIsOpened(void);
bool serialSend(unsigned char serialdata);
bool serialSend(const void *serialdata, int data_size);
bool serialReceive(void *serialdata, int &data_size);
bool serialClear(void);
void serialClose(void);

#endif /* SERIAL_PORT_H_INC */
