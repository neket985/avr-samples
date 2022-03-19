_Noreturn void servo(void)
{
    DDRA=0xff; //PD1 output
    //500 - 2400 (180 degrees)
    int minUs = 500;
    int maxUs = 2400;
    int maxAngle = 180;
    int angleStepUs = (maxUs - minUs) / maxAngle;

    int cycleUs = 20000;
    int i = 0;
    int angle = 0;
    while (1)
    {
        ++i;

        int delayUs = 0;
        if((angle/maxAngle)%2==0){
            delayUs = (minUs + angle*angleStepUs);
        }else{
            delayUs = minUs + (maxAngle - angle)*angleStepUs;
        }
        PORTA = 0xff; //hight
        _delay_us(delayUs);
        PORTA = 0x00; //low
        _delay_us(cycleUs - delayUs);

        if(i%10==1){
            angle = (angle+1)%maxAngle;
        }
    }
}

_Noreturn void servoSimple(void)
{
    DDRA=0xff; //PD1 output
    int minUs = 500;
    int maxUs = 2400;
    int cycleUs = 20000;
    while (1)
    {

        _delay_ms(1000);
        PORTA = 0xff; //hight
        _delay_us(maxUs);
        PORTA = 0x00; //low
        _delay_us(cycleUs);

        _delay_ms(1000);
        PORTA = 0xff; //hight
        _delay_us(minUs);
        PORTA = 0x00; //low
        _delay_us(cycleUs);

    }
}