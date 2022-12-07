#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config FPLLODIV = DIV_4         // System PLL Output Clock Divider (PLL Divide by 4)
 
// DEVCFG1
#pragma config FNOSC = FRCPLL           // Oscillator Selection Bits (Fast RC Osc with PLL)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = ON            // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
 
// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)
 
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
 
#include <xc.h>
#include "C:\Program Files\Microchip\MPLABX\v6.00\packs\Microchip\PIC32MX_DFP\1.5.259\include\proc\p32mx360f512l.h"
  
void initSPI(void);
short WriteReadSPI(unsigned short i);
void initAccel(void);
float ReadAccelX(void);
 
#define CS LATDbits.LATD1
  
 
main()
{
    TRISDbits.TRISD1 = 0;       // make CS an output
    initSPI();                  // initialize SPI module
    
}
 
 
void initSPI(void)
{
    CS = 1;              // Set chip select high (idle state is high)
     
    IEC0bits.SPI1EIE = 0;       // SPI interrupts disabled
    IEC0bits.SPI1RXIE = 0;
    IEC0bits.SPI1TXIE = 0;
     
    SPI1CONbits.ON = 0;         // Turn off SPI module
     
    SPI1BUF = 0;                // Clear the receive buffer
     
    SPI1BRG = 3;                // FSCK = 2.5MHz
     
    SPI1STATbits.SPIROV = 0;    // Clear overflow flag
     
     
    /* SPI1CON settings */
    SPI1CONbits.FRMEN = 0;      // Framed SPI support is disabled
    SPI1CONbits.SIDL = 0;       // Continue operation in IDLE mode
    SPI1CONbits.DISSDO = 0;     // SDO1 pin is controlled by the module
    SPI1CONbits.MODE16 = 1;     // 16 bit mode
    SPI1CONbits.MODE32 = 0;
    SPI1CONbits.CKP = 1;        // Idle state for clock is high, active state is low
    SPI1CONbits.CKE = 0;        // Output data changes on transition from idle to active
    SPI1CONbits.SSEN = 0;       // Not in slave mode
    SPI1CONbits.MSTEN = 1;      // Master mode
    SPI1CONbits.SMP = 1;        // Input data sampled at the end of data output time
     
    SPI1CONbits.ON = 1;         // Turn module on
}
  
short WriteReadSPI(short i)
{
    CS = 0;                         // Set the chip select low
    SPI1BUF = i;                    // Write to buffer for transmission
    while (!SPI1STATbits.SPIRBF);   // Wait for transfer to be completed
    CS = 1;                         // Set the chip select back high
    return SPI1BUF;                 // Return the received value
}
 
