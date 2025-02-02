#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define GPIO_LED_R      13
#define GPIO_LED_G      11
#define GPIO_LED_Y      12
#define INTERVALO_CICLO 3000

/*
 * Cria variáveis globais
 * static: variável permanece na memória durante toda a execução do programa 
 * volatile: a variável pode ser alterada por eventos externos
 */ 
static volatile uint contador = 1; // Contador que controla o LED que deve ser ligado a cada ciclo de 3s

// Cabeçalho função de callback que será chamada pelo temporizador
bool repeating_timer_callback(struct repeating_timer *t);

// Função para acender o LED por um tempo específico
void controlaLed(uint gpio, bool operacao) {
    gpio_put(gpio, operacao);       // Liga o LED indicado no parâmetro gpio
}

// Inicializa LEDs 
void init_leds() {
    gpio_init(GPIO_LED_R);
    gpio_set_dir(GPIO_LED_R, GPIO_OUT);

    gpio_init(GPIO_LED_G);
    gpio_set_dir(GPIO_LED_G, GPIO_OUT);

    gpio_init(GPIO_LED_Y);
    gpio_set_dir(GPIO_LED_Y, GPIO_OUT);
}

// Função de callback que será chamada pelo temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    /* Apaga ou acente os LEDs de acordo com o valor da variável contador
     * contador = 1; acente o LED vermelho
     * contador = 2; acente o LED amarelo
     * contador = 1; acente o LED verde
    */ 
    controlaLed(GPIO_LED_R, contador == 1);
    controlaLed(GPIO_LED_Y, contador == 2);
    controlaLed(GPIO_LED_G, contador == 3);

    // Verifica o valor da variável contador para controlar o seu valor que deve variar entre 1 e 3
    if (contador == 3) {
        contador = 1;
    }
    else { 
        contador++;
    }
    
    // Retorna o valor verdadeiro para manter o temporizador funcionando
    return true;
}

// Função principal
int main() {
    stdio_init_all();              // Inicializa as interface de comunicação
    init_leds();                   // Inicializa os LEDs

    // Declaração da estrutura de temporização de repetição
    struct repeating_timer timer;

    // Configuração do temporizador para chamar a função de callback a cada 3s
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Laço infinito 
    while (1) {
        // Contando minutos... fazendo algo aleatório enquanto o temporizador funciona
        int min = 0;
        printf("Contando minutos... \n");
        while (true) {
            for(int cont=1; cont <= 60; cont++) {
                printf("%d minutos e %d segundos\n", min, cont);
                sleep_ms(1000);
            }
            min++;
        }
    }
}
