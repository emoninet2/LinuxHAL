/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GPIO.h
 * Author: emon
 *
 * Created on June 16, 2017, 5:42 AM
 */

#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

void GPIO_export (int pin);
void GPIO_unexport (int pin);
void GPIO_direction(int pin, int dir);
void GPIO_write(int pin, int val);
int GPIO_read(int pin);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H */

