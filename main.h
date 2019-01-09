/*
 * main.h
 *
 *  Created on: Dec 28, 2018
 *      Author: Austin
 */

#ifndef MAIN_H_
#define MAIN_H_

// Includes
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// Function Declarations
void ADC_INIT(void);
void ADC_MOISTURE_CTRL(void);
void ADC_TEMP_CTRL(void);
void GPIO_INIT(void);
void main(void);

// Global Declarations
typedef enum {INIT, SLEEP, POLLM, POLLT} state;
typedef struct {
    double temp;
    double moist;
} AVG_FINAL;

// Global Variables
#define MAXNODES 50
#define RUNNING 0
state STATE = INIT;
AVG_FINAL AVG_TEMP_MOIST[MAXNODES];
#endif /* MAIN_H_ */
