#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define GPIO_LED_R      13
#define GPIO_LED_G      11
#define GPIO_LED_B      12
#define GPIO_BOTAO_A    5
#define INTERVALO_CICLO 3000

/*
 * Cria variáveis globais
*/ 
static volatile uint32_t last_time = 0; // Armazena o tempo do último evento (em microssegundos)
static absolute_time_t tempoDesligarLeds; // Variável para armazenar o tempo em que os LEDs devem ser desligados
static  bool apagouTodos = true; // Variável que controla se todos os LEDs foram apagados

// Cabeçalhos funções de callback que serão chamadas pelos alarmes
int64_t desliga_ledR_callback(alarm_id_t id, void *user_data);
int64_t desliga_ledG_callback(alarm_id_t id, void *user_data);
int64_t desliga_ledB_callback(alarm_id_t id, void *user_data);

// Função para acender o LED por um tempo específico
void controlaLed(uint gpio, bool operacao) {
    gpio_put(gpio, operacao); // Liga/Desliga o LED indicado no parâmetro gpio
}

// Inicializa LEDs 
void init_leds() {
    gpio_init(GPIO_LED_R);
    gpio_set_dir(GPIO_LED_R, GPIO_OUT);

    gpio_init(GPIO_LED_G);
    gpio_set_dir(GPIO_LED_G, GPIO_OUT);

    gpio_init(GPIO_LED_B);
    gpio_set_dir(GPIO_LED_B, GPIO_OUT);
}

// Inicializa botão
void init_button() {
    gpio_init(GPIO_BOTAO_A);
    gpio_set_dir(GPIO_BOTAO_A, GPIO_IN);
    gpio_pull_up(GPIO_BOTAO_A);
}

// Função de callback que será chamada pelo alarme - LED B
int64_t desliga_ledB_callback(alarm_id_t id, void *user_data) {
    controlaLed(GPIO_LED_B, 0);
    apagouTodos = true;
    return 0;
}

// Função de callback que será chamada pelo alarme - LED G
int64_t desliga_ledG_callback(alarm_id_t id, void *user_data) {
    controlaLed(GPIO_LED_G, 0);
    // Declaração da estrutura do alarme que chama o callback com temporização de 3s
    add_alarm_in_ms(INTERVALO_CICLO, desliga_ledB_callback, NULL, false);
    return 0;
}

// Função de callback que será chamada pelo alarme - LED R
int64_t desliga_ledR_callback(alarm_id_t id, void *user_data) {
    controlaLed(GPIO_LED_R, 0);
    // Declaração da estrutura do alarme que chama o callback com temporização de 3s
    add_alarm_in_ms(INTERVALO_CICLO, desliga_ledG_callback, NULL, false);
    return 0;
}

// Função principal
int main() {
    stdio_init_all();    // Inicializa as interface de comunicação
    init_leds();         // Inicializa os LEDs
    init_button();       // Inicializa botão

    
    // Laço infinito 
    while (1) {
        // Obtém o tempo atual em microssegundos
        uint32_t current_time = to_us_since_boot(get_absolute_time());

        // Verifica se passou tempo suficiente desde o último evento (50 ms de debouncing)
        if (current_time - last_time > 50000) {
            last_time = current_time; // Atualiza o tempo do último evento
            // Verifica se o botão "A" foi acionado e se todos os LEDs já estão apagados
            if (gpio_get(GPIO_BOTAO_A) == 0 && apagouTodos) {
                apagouTodos = false;
                // Acente todos os LEDs
                controlaLed(GPIO_LED_R, 1);
                controlaLed(GPIO_LED_B, 1);
                controlaLed(GPIO_LED_G, 1);

                // Declaração da estrutura do alarme que chama o callback com temporização de 3s
                add_alarm_in_ms(INTERVALO_CICLO, desliga_ledR_callback, NULL, false);
            }
        }
    }
}
