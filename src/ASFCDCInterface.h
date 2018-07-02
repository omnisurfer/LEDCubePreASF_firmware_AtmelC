/*
 * ASFCDCInterface.h
 *
 * Created: 3/20/2016 6:11:18 PM
 *  Author: Daniel
 */ 


#ifndef ASFCDCINTERFACE_H_
#define ASFCDCINTERFACE_H_

bool callback_usb_cdc_enable(void);

void callback_usb_cdc_disable(void);

void app_usb_cdc(Byte);

void app_usb_cdc_write_char_string(char* string, int length);

#endif /* ASFCDCINTERFACE_H_ */