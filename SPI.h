/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SPI.h
 * Author: emon
 *
 * Created on June 16, 2017, 5:21 AM
 */

#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif

int SPI_GetFd     (int channel) ;
int SPI_DataRW    (int channel, unsigned char *data, int len) ;
int SPI_SetupMode (int channel, int speed, int mode) ;
int SPI_Setup     (int channel, int speed) ;

#ifdef __cplusplus
}
#endif

#endif /* SPI_H */

