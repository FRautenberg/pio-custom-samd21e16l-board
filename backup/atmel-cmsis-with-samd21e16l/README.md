# atmel-cmsis-with-samd21e16l

This is just framework-atmel-cmsis with the following additions:

Download "Microchip SAMD21 Series Device Support (3.4.116)" from https://packs.download.microchip.com/ and extract it (unzip).

Have current version of `framework-cmsis-atmel` ready, e.g. from  https://dl.registry.platformio.org/download/platformio/tool/framework-cmsis-atmel/1.2.2/framework-cmsis-atmel-1.2.2.tar.gz

copy 
```
Microchip.SAMD21_DFP.3.4.116\samd21l\include\samd21e16l.h
```
into 
```
framework-cmsis-atmel\CMSIS\Device\ATMEL\samd21\include
```

Add 
```cpp
#elif defined(__SAMD21E16L__) || defined(__ATSAMD21E16L__)
  #include "samd21e16l.h"
```
to
```
framework-cmsis-atmel\CMSIS\Device\ATMEL\samd21\include\samd21.h
```
Copy 
```
Microchip.SAMD21_DFP.3.4.116\samd21l\include\pio\samd21e16l.h
```
to
```
framework-cmsis-atmel\CMSIS\Device\ATMEL\samd21\include\pio
```