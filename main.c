#include "at32f421.h"                   // Device header
// ArteryTek::Device:at32f421_firmware_library:cmp
#include "at32f421_cmp.h"
//#include <C:\Users\U3B6\Documents\keil\test_proj\RTE\Device\-AT32F421K8T7\at32f421_cmp.c>



void gpio_set(gpio_type *PORT, uint32_t PIN, gpio_drive_type DRIVE, gpio_mode_type MODE, gpio_output_type OUT_TYPE, gpio_pull_type PULL ) {


    gpio_init_type pinx;

    gpio_init_type *pina = &pinx;

    pinx.gpio_drive_strength= DRIVE;
    pinx.gpio_mode =MODE;
    pinx.gpio_out_type=OUT_TYPE;
    pinx.gpio_pins = PIN;
    pinx.gpio_pull = PULL;

    gpio_init( PORT,pina);

}


void delay(unsigned long cycles)
{
    while(cycles >0)
        cycles--; // Some stupid delay, it is not in milliseconds or microseconds, but rather in some 'wasted clock cycles'
 wdt_counter_reload();


}

void ADC1_CMP_IRQHandler(void) {
    wdt_counter_reload();
    gpio_bits_set(GPIOA,GPIO_PINS_4);
 
}


void TMR6_GLOBAL_IRQHandler(void) {

     gpio_bits_set(GPIOA,GPIO_PINS_5);
        delay(1000);
        gpio_bits_reset(GPIOA,GPIO_PINS_5);
        delay(1000);
    tmr_period_value_set(TMR6,200);
    TMR6 ->ists_bit.ovfif =0;
}



void timer_init() {




    nvic_irq_enable(TMR6_GLOBAL_IRQn,35,36);

    TMR6->iden_bit.ovfien =1;

    TMR6 ->ctrl1_bit.ocmen = 0;

    TMR6 ->ctrl1_bit.ovfen = 0;

    tmr_channel_buffer_enable(TMR6,TRUE);

    tmr_base_init(TMR6,20,4000);

    tmr_counter_enable(TMR6,TRUE);



}


         cmp_init_type *cmp_def;

exint_init_type *exi_def;
int main() {
	
	    crm_periph_clock_enable(CRM_ADC1_PERIPH_CLOCK,TRUE);
    crm_periph_clock_enable(CRM_TMR6_PERIPH_CLOCK,TRUE);
	crm_periph_clock_enable(  CRM_GPIOF_PERIPH_CLOCK,TRUE);

       timer_init();

	exint_default_para_init(exi_def);
	exi_def ->line_select =EXINT_LINE_21;
	exi_def ->line_enable =1;
	exi_def ->line_mode = EXINT_LINE_INTERRUPUT;
	exint_init(exi_def);
	
	exint_event_enable(EXINT_LINE_21,TRUE);
	exint_interrupt_enable(EXINT_LINE_21,TRUE);


    wdt_register_write_enable(TRUE);

    wdt_divider_set(WDT_CLK_DIV_8);
    wdt_register_write_enable(FALSE);
//	wdt_counter_reload();
//wdt_enable();
     
    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK,TRUE);

	    gpio_set(GPIOF,
             GPIO_PINS_0,
             GPIO_DRIVE_STRENGTH_MODERATE,
             GPIO_MODE_OUTPUT,
             GPIO_OUTPUT_PUSH_PULL,
             GPIO_PULL_NONE);
	
	
    gpio_set(GPIOA,
             GPIO_PINS_3,
             GPIO_DRIVE_STRENGTH_MODERATE,
             GPIO_MODE_OUTPUT,
             GPIO_OUTPUT_PUSH_PULL,
             GPIO_PULL_NONE);

    gpio_set(GPIOA,
             GPIO_PINS_4,
             GPIO_DRIVE_STRENGTH_MODERATE,
             GPIO_MODE_OUTPUT,
             GPIO_OUTPUT_PUSH_PULL,
             GPIO_PULL_NONE);
						 
	 gpio_set(GPIOA,
             GPIO_PINS_5,
             GPIO_DRIVE_STRENGTH_MODERATE,
             GPIO_MODE_OUTPUT,
             GPIO_OUTPUT_PUSH_PULL,
             GPIO_PULL_NONE);


 //   crm_ertc_clock_select(CRM_ERTC_CLOCK_LICK);
 //   crm_ertc_clock_enable(TRUE);

   // ertc_write_protect_disable();
//   ertc_interrupt_enable(ERTC_TS_INT,TRUE);

    crm_periph_clock_enable(CRM_CMP_PERIPH_CLOCK,TRUE);
 
   
        
    nvic_irq_enable( ADC1_CMP_IRQn,0,1);
    cmp_default_para_init(cmp_def);
		CMP ->ctrlsts_bit.scalen =1;
	//cmp_def ->cmp_non_inverting = CMP_NON_INVERTING_VSSA;
 //  cmp_def -> cmp_inverting = CMP_INVERTING_PA0;
 
      
 //cmp_filter_config(10,10,TRUE);
    cmp_enable(CMP1_SELECTION,TRUE);

   /*
    gpio_bits_set(GPIOA,GPIO_PINS_4);
    delay(10000);
    gpio_bits_reset(GPIOA,GPIO_PINS_4);
    delay(10000);
    gpio_bits_set(GPIOA,GPIO_PINS_4);
    delay(10000);
    gpio_bits_reset(GPIOA,GPIO_PINS_4);
    delay(10000);
  */




    while(1) {


        gpio_bits_set(GPIOF,GPIO_PINS_0);
        delay(10000);
        gpio_bits_reset(GPIOF,GPIO_PINS_0);
        delay(10000);

		
			
	/*		    if (CMP ->ctrlsts_bit.cmpvalue){
						   gpio_bits_set(GPIOA,GPIO_PINS_4);
        delay(10000);
        gpio_bits_reset(GPIOA,GPIO_PINS_4);
        delay(10000);
						
					}
   */
     //   pwc_deep_sleep_mode_enter(PWC_DEEP_SLEEP_ENTER_WFI);



    }






}
