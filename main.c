#include <lpc21xx.h>
#include "header.h"
#include <string.h>

int i, c = 0;

int main()
{
    char a[6] = "hello";
    char b[] = "mango";
    char s[6];

    unsigned int temp, adc_val;
    unsigned int flag1 = 0, flag2 = 0, flag3 = 0;
    unsigned int auth_flag = 0;

    float vout = 0, temperature = 0;

    IODIR0 &= ~(1 << 16);
    IODIR0 &= ~(1 << 17);

    lcd_init();
    uart0_init(9600);

    lcd_cmd(0x01);
    lcd_string("ENTER PASSWORD");
    delay_ms(1000);

    while(1)
    {
        lcd_cmd(0xC0);

        for(i = 0; i < 5; i++)
        {
            temp = uart0_rx();
            uart0_tx('*');
            lcd_data('*');
            s[i] = temp;
        }

        s[5] = '\0';

        if(strcmp(a, s) == 0)
        {
            auth_flag = 1;

            lcd_cmd(0x01);
            lcd_string("PASSWORD CORRECT");
            delay_ms(1000);
            break;
        }
        else
        {
            auth_flag = 0;
            c++;

            lcd_cmd(0x01);
            lcd_string("PASSWORD WRONG");
            delay_ms(1000);

            if(c == 3)
            {
                lcd_cmd(0x01);
                lcd_string("BACKUP PASSWORD");
                delay_ms(1000);

                lcd_cmd(0xC0);

                for(i = 0; i < 5; i++)
                {
                    temp = uart0_rx();
                    uart0_tx('*');
                    lcd_data('*');
                    s[i] = temp;
                }

                s[5] = '\0';

                if(strcmp(b, s) == 0)
                {
                    lcd_cmd(0x01);
                    lcd_string("BACKUP CORRECT");
                    delay_ms(1000);

                    lcd_cmd(0x01);
                    lcd_string("ENTER NEW PASS");
                    delay_ms(1000);

                    lcd_cmd(0xC0);

                    for(i = 0; i < 5; i++)
                    {
                        temp = uart0_rx();
                        uart0_tx('*');
                        lcd_data('*');
                        a[i] = temp;
                    }

                    a[5] = '\0';

                    auth_flag = 1;

                    lcd_cmd(0x01);
                    lcd_string("PASS CHANGED");
                    delay_ms(1000);
                    break;
                }
                else
                {
                    auth_flag = 0;

                    lcd_cmd(0x01);
                    lcd_string("UNAUTHORIZED");
                    delay_ms(2000);
                    break;
                }
            }
        }
    }

    if(auth_flag == 1)
    {
        lcd_cmd(0x01);
        lcd_string("SYSTEM STARTED");
        delay_ms(1000);

        adc_init();

        while(1)
        {
            adc_val = adc_read(0);

            vout = (adc_val * 3.3) / 1023;
            temperature = vout * 100;

            uart0_tx_string("\r\nTemperature : ");
            uart0_floa(temperature);

            lcd_cmd(0x01);
            lcd_string("TEMP : ");
            lcd_floa(temperature);

            if(temperature > 35)
                flag1 = 1;
            else
                flag1 = 0;

            if((IOPIN0 >> 16) & 1)
            {
                uart0_tx_string("\r\nWORKER: YES");
                flag2 = 1;
            }
            else
            {
                uart0_tx_string("\r\nWORKER: NO");
                flag2 = 0;
            }

            if(((IOPIN0 >> 17) & 1) == 0)
            {
                uart0_tx_string("\r\nFIRE: YES");
                flag3 = 1;
            }
            else
            {
                uart0_tx_string("\r\nFIRE: NO");
                flag3 = 0;
            }

            if(flag1 || flag2 || flag3)
            {
                uart0_tx_string("\r\nNOT SAFE");
                lcd_cmd(0xC0);
                lcd_string("STATUS: NOT SAFE");
            }
            else
            {
                uart0_tx_string("\r\nSAFE");
                lcd_cmd(0xC0);
                lcd_string("STATUS: SAFE");
            }

            delay_ms(2000);
        }
    }
    else
    {
        lcd_cmd(0x01);
        lcd_string("ACCESS DENIED");
    }
}
