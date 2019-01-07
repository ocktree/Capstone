// Capstone Design Project
// Authors:
// Stefan Heincke
// Ockert Strydom
// Austin Tyson
// Kendal Zimmer
#include "driverlib.h"
#include "main.h"
// ========================= GPIO BLOCK =========================
void GPIO_INIT(void) {

}
// ========================= ADC BLOCK =========================
/*
 * This function initializes the ADC for operation
 */
void ADC_INIT(void) {
    ADC12_B_initParam initParam = {0};
    initParam.sampleHoldSignalSourceSelect = ADC12_B_SAMPLEHOLDSOURCE_SC;
    initParam.clockSourceSelect = ADC12_B_CLOCKSOURCE_MCLK;
    initParam.clockSourceDivider = ADC12_B_CLOCKDIVIDER_1;
    initParam.clockSourcePredivider = ADC12_B_CLOCKPREDIVIDER_1;
    initParam.internalChannelMap = ADC12_B_MAPINTCH0;

    ADC12_B_init(ADC12_B_BASE, &initParam);
}
void ADC_MOISTURE_CTRL(void) {
    if (ADC_EN==0) {
        ADC12_B_enable(ADC12_B_BASE);
        ADC_EN = 1;
    }
    ADC12_B_setupSamplingTimer(ADC12_B_BASE,ADC12_B_CYCLEHOLD_16_CYCLES,ADC12_B_CYCLEHOLD_16_CYCLES,ADC12_B_MULTIPLESAMPLESENABLE);
    ADC12_B_configureMemoryParam memParam = {0};
    memParam.memoryBufferControlIndex = ADC12_B_MEMORY_0;
    memParam.inputSourceSelect = ADC12_B_INPUT_A; //Whatever the moisture sensor's analog wiring is.
    memParam.refVoltageSourceSelect = ADC12_B_VREFPOS_AVCC_VREFNEG_VSS;
    memParam.endOfSequence = ADC12_B_NOTENDOFSEQUENCE;
    memParam.windowComparatorSelect = ADC12_B_WINDOW_COMPARATOR_DISABLE;
    memParam.differentialModeSelect = ADC12_B_DIFFERENTIAL_MODE_DISABLE;
    ADC12_B_configureMemory(ADC12_B_BASE, &memParam);
}
void ADC_TEMP_CTRL(void) {
    if (ADC_EN==0) {
        ADC12_B_enable(ADC12_B_BASE);
        ADC_EN = 1;
    }
    ADC12_B_setupSamplingTimer(ADC12_B_BASE,ADC12_B_CYCLEHOLD_16_CYCLES,ADC12_B_CYCLEHOLD_16_CYCLES,ADC12_B_MULTIPLESAMPLESENABLE);
    ADC12_B_configureMemoryParam memParam = {0};
    memParam.memoryBufferControlIndex = ADC12_B_MEMORY_0;
    memParam.inputSourceSelect = ADC12_B_INPUT_A; //Whatever the temperature sensor's analog wiring is.
    memParam.refVoltageSourceSelect = ADC12_B_VREFPOS_AVCC_VREFNEG_VSS;
    memParam.endOfSequence = ADC12_B_NOTENDOFSEQUENCE;
    memParam.windowComparatorSelect = ADC12_B_WINDOW_COMPARATOR_DISABLE;
    memParam.differentialModeSelect = ADC12_B_DIFFERENTIAL_MODE_DISABLE;
    ADC12_B_configureMemory(ADC12_B_BASE, &memParam);
}
int STATE_CHECK(void) {
    if (CURR == SLEEP) {
        ADC12_B_disable(ADC12_B_BASE);
        ADC_EN = 0;
        __bis_SR_register(LPM3_bits + GIE);
        __no_operation();
        return 1;
    } if (CURR == POLLM) {
        ADC_MOISTURE_CTRL();
        return 1;
    } if (CURR == POLLT) {
        ADC_TEMP_CTRL();
        return 1;
    } if (CURR == INIT) {
        DISPLAY();
        return 1;
    }
    return 0;
}

void main(void) {
    while(1) {
        // Sets Frequency to 1MHz low, 1MHz high
        CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_0);
        // Sets Master Clock (System and CPU clock to 1 MHz)
        CS_initClockSignal(CS_BASE,CS_MCLK,CS_DCOCLK_SELECT,CS_CLOCK_DIVIDER_1);
        // Disable Watchdog Timer while Initializing.
        WDT_A_hold(WDT_A_BASE);

        GPIO_INIT();
        ADC_INIT();
        // State Check Call/Switch
        ERR = STATE_CHECK();
        if (ERR==0) CURR = SLEEP;


    }
}

#pragma vector =
__interrupt
#pragma vector =
__interrupt
#pragma vector =
__interrupt
#pragma vector =
__interrupt
#pragma vector =
__interrupt
#pragma vector =
__interrupt
#pragma vector =
__interrupt
#pragma vector =
__interrupt
#pragma vector =
__interrupt
#pragma vector =
__interrupt
#pragma vector =
__interrupt
#pragma vector =
__interrupt
