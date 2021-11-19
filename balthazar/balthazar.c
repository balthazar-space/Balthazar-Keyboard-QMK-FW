#include "balthazar.h"

/**
void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    
    //setPinInputHigh(E6);

    matrix_init_user();
}
**/

/**
void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    // set the whole port F as input pulled high
    //DDRF &= ~(1<<2); 
    //PORTF \|= (1<<2)

    // enable Port F for input with pull ups activated
    //DDRF = 0x00;
    //PORTF = 0xff;

    //noInterrupts();
    // to set JTD -> disabling JTAG which may affect P:F4,F5,F7 - run this twice within 4 cycles
    MCUCR |= (1<<JTD);
    MCUCR |= (1<<JTD);
    //interrupts();

    // By default, the JTAG debugging interface is disabled as soon as the keyboard starts up. 
    // defined in tmk_core/common/keyboard.c as function disable_jtag
    // To use PORTF disable JTAG with writing JTD bit twice within four cycles.
    //#if  (defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__) || defined(__AVR_ATmega32U4__))
    //    MCUCR |= _BV(JTD);
    //    MCUCR |= _BV(JTD);
    //#endif
    
    // disable adc	
    ADCSRA = 0;

    // The ATMega32u4 has an option to divide its clock speed, to conserve power. Like in the case of JTAG, this can be set or unset in fuses. 
    // Thankfully, like in the JTAG case, we can disable this at run-time too, with the following magic words:
    //CLKPR = (1 << CLKPCE);
    //CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);

    matrix_init_user();
}
**/

