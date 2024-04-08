/*
 * main.c
 *
 * Created: 4/7/2024 10:53:35 AM
 *  Author: adria
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t contador = 10;	// Contador de 8 bits

void initButtons(void);

int main(void){
	
	initButtons();	// Inicializar
	
    while(1)
    {
        // Mostrar el valor del contador en el puerto D
		PORTD = contador; 
    }
}

void initButtons(void){
	
	cli();
	DDRD = 0xFF; // Habilitar com salidas
	UCSR0B = 0;
	
	PORTD = 0;	// Limpiar el puerto D
	
	DDRC = 0xFF; // Habilitar puerto C como salida
	PORTC = 0;	// Limpiar el puerto C
	
	DDRB = 0xFF; // Habilitar puerto B como salida
	PORTB = 0; // Limpiar el puerto B
	
	// Configurar los pines de entrada
	DDRB &= ~(1 << PORTB0); // PB0 como entrada
	DDRC &= ~(1 << PORTC5); // PC5 como entrada
	PCICR |= (1 << PCIE0) | (1 << PCIE1);
	PCMSK0 |= (1 << PCINT0); // Habilitar las interrupciones externas para PB0
	PCMSK1 |= (1 << PCINT13); // Habilitar las interrupciones externas para PC5
	sei();
}

ISR(PCINT0_vect){
		_delay_ms(10);
	if (!(PINB & (1 << PB0))) {
	// Incrementar al presionar el botón en PB0
	if (contador < 255) {
		contador++;
		}
	else {
		contador = 255; // Asignar el valor máximo si se quiere seguir aumentando
		}
	}
}


ISR(PCINT1_vect){
		_delay_ms(10);
	if (!(PINC & (1 << PC5))) {
	// Decrementar al presionar el botón en PC5
	if (contador > 0) {
		contador--;
		}
	else {
		contador = 0; // Asignar el valor mínimos si se quiere seguir decrementando
		}
	}
}

/*
ISR(PCINT13_vect){
	
	// Incrementar al presionar el botón en PC5
	if (contador < 255) {
		contador++;
	}
	else {
		contador = 0; // Asignar el valor máximo si se quiere seguir aumentando
	}
	
}

ISR(PCINT12_vect){
	
	// Decrementar al presionar el botón en PC5
	if (contador > 0) {
		contador--;
	}
	else {
		contador = 0; // Asignar el valor mínimos si se quiere seguir decrementando
	}
	
}
*/