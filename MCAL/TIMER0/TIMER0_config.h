/*
 * TIMER0_config.h
 *
 * Created: 2/11/2024 11:10:44 AM
 *  Author: Mostafa Edrees
 */ 


#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

#define TIMER0_MODE			FAST_PWM

#define TIMER0_PRES			PRES_64

/* You should write F_SYSTEM in KHz */
#define F_SYSTEM			1000UL

#define OC0_MODE			NON_INVERTED


#endif /* TIMER0_CONFIG_H_ */