/*
 * main.h
 *
 *  Created on: Dec 28, 2018
 *      Author: Austin
 */

#ifndef MAIN_H_
#define MAIN_H_
// Function Declarations
int ADC_INIT(void);
int ADC_MOISTURE_CTRL(void);
int ADC_TEMP_CTRL(void);
int GPIO_INIT(void);
void main(void);

// Global Declarations
enum STATE {INIT, SLEEP, POLLM, POLLT};
typedef struct {
    double temp;
    double moist;
} AVG_FINAL;

// Global Variables
#define MAXNODES 50
#define RUNNING 0
STATE CURR = INIT;
int ERR = 0;
int ADC_EN = 0;
AVG_FINAL AVG_TEMP_MOIST[MAXNODES];
#endif /* MAIN_H_ */
