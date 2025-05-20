# RA-02 (SX1278) Driver for Linux

RA-01/RA-02 (SX1278) driver for Linux that uses linux spidev API.  
Provides APIs to send/receive & configure the module.  

### How to build
#### Prerequisites
 - CMake (at least 3.27)  
 - Aarch64 linux gnu toolchain (`aarch64-unknown-linux-gnu`/`aarch64-linux-gnu-gcc`)

#### Steps
 - `cmake -B cmake-build-directory -S . -G "Unix Makefiles"`  
 - `cmake --build cmake-build-directory`

### How to run
Warning: tested only on Raspberry PI, but theoretically work on any linux machine that has spidev interface.  

#### For Raspberry PI:  
| Name | Pin # | Pin name |
|:------:|:-------:|:--------:|
| MOSI | 19    |  GPIO12  |
| MISO | 21    |  GPIO13  |
| SCK  | 23    |  GPIO14  |
| NSS  | 24    |  GPIO11  |
| GND  | Any   |   GND    |
| 3.3V | 1     |   3V3    |

To send a packet run `./linux_ra02.elf /dev/spidev0.0 send 1 2 3 4 5`.  
Where `1 2 3 4 5` are individual bytes of packet payload (in decimal).   

To receive a packet run `./linux_ra02.elf /dev/spidev0.0 recv 5000`.  
Where `5000` is receiver timeout in milliseconds.   
