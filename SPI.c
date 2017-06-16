/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <asm/ioctl.h>
#include <linux/spi/spidev.h>


#include "SPI.h"

static const char       *spiDev0  = "/dev/spidev0.0" ;
static const char       *spiDev1  = "/dev/spidev0.1" ;
static const uint8_t     spiBPW   = 8 ;
static const uint16_t    spiDelay = 0 ;

static uint32_t    spiSpeeds [2] ;
static int         spiFds [2] ;


int SPI_GetFd     (int channel) {
    return spiFds [channel & 1] ;
}
int SPI_DataRW    (int channel, unsigned char *data, int len) {
 struct spi_ioc_transfer spi ;

  channel &= 1 ;

// Mentioned in spidev.h but not used in the original kernel documentation
//	test program )-:

  memset (&spi, 0, sizeof (spi)) ;

  spi.tx_buf        = (unsigned long)data ;
  spi.rx_buf        = (unsigned long)data ;
  spi.len           = len ;
  spi.delay_usecs   = spiDelay ;
  spi.speed_hz      = spiSpeeds [channel] ;
  spi.bits_per_word = spiBPW ;

  return ioctl (spiFds [channel], SPI_IOC_MESSAGE(1), &spi) ;
}
int SPI_SetupMode (int channel, int speed, int mode) {
     int fd ;

  mode    &= 3 ;	// Mode is 0, 1, 2 or 3
  channel &= 1 ;	// Channel is 0 or 1

  if ((fd = open (channel == 0 ? spiDev0 : spiDev1, O_RDWR)) < 0)
    //return wiringPiFailure (WPI_ALMOST, "Unable to open SPI device: %s\n", strerror (errno)) ;
    printf("failed\r\n");

  spiSpeeds [channel] = speed ;
  spiFds    [channel] = fd ;

// Set SPI parameters.

  if (ioctl (fd, SPI_IOC_WR_MODE, &mode)            < 0)
    //return wiringPiFailure (WPI_ALMOST, "SPI Mode Change failure: %s\n", strerror (errno)) ;
    printf("failed\r\n");
  
  if (ioctl (fd, SPI_IOC_WR_BITS_PER_WORD, &spiBPW) < 0)
    //return wiringPiFailure (WPI_ALMOST, "SPI BPW Change failure: %s\n", strerror (errno)) ;
    printf("failed\r\n");

  if (ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)   < 0)
    //return wiringPiFailure (WPI_ALMOST, "SPI Speed Change failure: %s\n", strerror (errno)) ;
    printf("failed\r\n");

  return fd ;
}
int SPI_Setup     (int channel, int speed) {
    return SPI_SetupMode (channel, speed, 0) ;
}