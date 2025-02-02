# OneShotRGB
Temporizador One Shot utilizando Pico SDK

## Funcionamento 📋
O programa utiliza a função add_alarm_in_ms(), presente no pacote Pico SDK para executar as seguintes operações (utilizando 3 leds e 3 resistores de 300 ohms ou a placa BitDogLab):

### Utilizando 3 leds e 3 resistores de 300 ohms:
- Ao clicar no pushbutton os 3 LEDS acendem e o primeiro alarme é criado para apagar o LED vermelho.
- Após o acionamento do primeiro alarme, o LED vermelho é apagado e o segundo alarme é criado para apagar o LED verde.
- Após o acionamento do segundo alarme, o LED verde é apagado e o terceiro alarme é criado para apagar o LED azul.
- Após o acionamento do terceiro alarme, o LED azul é apagado.

### Utilizando a placa BitDogLab:
- Ao clicar no Botão "A" os 3 LEDS RGB acendem e o primeiro alarme é criado para apagar o LED vermelho.
- Após o acionamento do primeiro alarme, o LED vermelho é apagado e o segundo alarme é criado para apagar o LED verde.
- Após o acionamento do segundo alarme, o LED verde é apagado e o terceiro alarme é criado para apagar o LED azul.
- Após o acionamento do terceiro alarme, o LED azul é apagado.

## Requisitos cumpridos pelo projeto
1. Quando o usuário clica no botão (pushbutton ou Botão "A" na placa BitDogLab), os três LEDs são ligados (todos em nível alto). A partir da primeira rotina de atraso, ocorre uma mudança de estado para dois LEDs ligados e, em seguida, apenas um. 
2. Os temporizadores dos alarmes estão ajustados para um atraso de 3 segundos (3.000ms), entre os estados de acionamento dos LEDs.
3. A mudança de estado dos LEDs foi implementada em 3 funções de callback do temporizador:
int64_t desliga_ledR_callback(alarm_id_t id, void *user_data);
int64_t desliga_ledG_callback(alarm_id_t id, void *user_data);
int64_t desliga_ledB_callback(alarm_id_t id, void *user_data);
4. O botão só pode alterar o estado dos LEDs quando o último LED está desligado. Deste modo, durante a execução das rotinas de temporização, o botão não pode iniciar uma nova chamada da função callback.
5. Foi feito um experimento com a placa BitDogLab com o código do exercício utilizando o LED RGB (GPIOs 11, 12 e 13) e o Botão A (GPIO 05).
6. Foi implementada a rotina em software para atenuação do efeito bouncing no botão (software debounce).