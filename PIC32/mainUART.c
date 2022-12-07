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
#include "C:\Program Files\Microchip\MPLABX\v6.00\packs\Microchip\PIC32MX_DFP\1.5.259\include\proc\p32mx470f512h.h"
  
 
void initUART(void);
void SendChar(char c);
void SendString(char *string);
char ReadChar(void);
void ReadString(char *string, int length);
 
void main()
{
    initUART();
    PORTDbits.RD14 = 0;                 // Set RTS and CTS pins to 0
    PORTDbits.RD15 = 0;
    char string[90];
    while(1)
    {
        ReadString(string,90);          // Read in a string
        SendString(string);             // Echo that string
    }
}
  
 
void initUART(void)
{
    U1MODEbits.BRGH = 0;                // Baud Rate = 9600
    U1BRG = 129;
     
    U1MODEbits.SIDL = 0;                // Continue operation in SLEEP mode
     
    U1MODEbits.IREN = 0;                // IrDA is disabled
     
    U1MODEbits.RTSMD = 0;               // U1RTS pin is in Flow Control mode
     
    U1MODEbits.UEN = 0b00;              // U1TX, U1RX are enabled
     
    U1MODEbits.WAKE = 1;                // Wake-up enabled
     
    U1MODEbits.LPBACK = 0;              // Loopback mode is disabled
     
    U1MODEbits.RXINV = 0;               // U1RX IDLE state is '1'
     
    U1MODEbits.PDSEL = 0b00;            // 8-bit data, no parity
     
    U1MODEbits.STSEL = 0;               // 1 stop bit
     
    U1STAbits.UTXINV = 0;               // U1TX IDLE state is '1'
     
    U1MODEbits.ON = 1;                  // UART1 is enabled
     
    U1STAbits.URXEN = 1;                // UART1 receiver is enabled
     
    U1STAbits.UTXEN = 1;                // UART1 transmitter is enabled
}
  
 
void SendChar(char c)
{
    U1STAbits.UTXEN = 1;                // Make sure transmitter is enabled
    // while(CTS)                       // Optional CTS use
    while(U1STAbits.UTXBF);             // Wait while buffer is full
    U1TXREG = c;                        // Transmit character
}
  
 
void SendString(char *string)
{
     
   int i = 0;
     
    U1STAbits.UTXEN = 1;                // Make sure transmitter is enabled
     
    while(*string)
    {
        while(U1STAbits.UTXBF);         // Wait while buffer is full
        U1TXREG = *string;              // Transmit one character
        string++;                       // Go to next character in string
    }
}
  
 
char ReadChar(void)
{
    //PORTDbits.RD15 = 0;                // Optional RTS use
    while(!U1STAbits.URXDA);             // Wait for information to be received
    //PORTDbits.RD15 = 1;
    return U1RXREG;                      // Return received character
}
  
 
void ReadString(char *string, int length)
{  
    int count = length;
     
    do
    {
        *string = ReadChar();               // Read in character
        //SendChar(*string);                  // Echo character
         
        if(*string == 0x7F && count>length) // Backspace conditional
        {
            length++;
            string--;
            continue;
        }
         
        if(*string == '\r')                 // End reading if enter is pressed
            break;
         
        string++;
        length--;
         
    }while(length>1);
     
    *string = '\0';                         // Add null terminator
}
