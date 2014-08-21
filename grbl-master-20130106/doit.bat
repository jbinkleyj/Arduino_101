rem http://cubespawn.com/wiki/index.php?title=3D_Printer_module_Electronics
rem http://www.shapeoko.com/wiki/index.php/Grbl



rem C:\WinAVR-20100110\bin\avrdude.exe -C avrdude.conf -pm328p -carduino -P"/dev/com6" -D -Uflash:w:grbl.hex
rem C:\WinAVR-20100110\bin\avrdude.exe -F -v -pm328p -cstk500v1 -P\\.\COM6 -b57600 -D -Uflash:w:"C:\Users\jobin\Documents\ArduinoWorkspaces\Arduino_101\grbl-master-20130106\grbl.hex":i


rem  The folowing is from ARP Uploader:
rem -F -v -pm328p -cstk500v1 -P\\.\COM6 -b19200 -D -Uflash:w:"C:\Users\jobin\Documents\ArduinoWorkspaces\Arduino_101\grbl-master-20130106\grbl.hex":i

rem The following is the command created in the Arduino IDE:
rem C:\Software\arduino-1.0.3\hardware/tools/avr/bin/avrdude -CC:\Software\arduino-1.0.3\hardware/tools/avr/etc/avrdude.conf -v -v -v -v -patmega328p -carduino -P\\.\COM6 -b57600 -D -Uflash:w:C:\Users\jobin\AppData\Local\Temp\build190651016098762662.tmp\Nothing.cpp.hex:i 


 
C:\Software\arduino-1.0.3\hardware\tools\avr\bin\avrdude -CC:\Software\arduino-1.0.3\hardware/tools/avr/etc/avrdude.conf -v -v -v -v -patmega328p -carduino -P\\.\COM6 -b57600 -D -Uflash:w:"C:\Users\jobin\Documents\ArduinoWorkspaces\Arduino_101\grbl-master-20130106\grbl.hex":i 
 