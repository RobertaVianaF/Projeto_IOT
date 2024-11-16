# Projeto_IOT

## Projeto de Detecção de Gases Tóxicos
Este projeto desenvolve um sistema de IoT para monitoramento de gases e condições ambientais em áreas de armazenamento. A solução utiliza a placa ESP32 para capturar dados do sensor MQ-2, capaz de detectar gases como fumaça, metano, entre outros. A comunicação é realizada via MQTT, com o uso da plataforma CallMebot, possibilitando o acionamento de alertas! 

## Código e Documentação
O código feito para este projeto estará na pasta .zip em Código Do Projeto. 

## Hardware

- **Placa ESP-32:** Placa que foi utilizada para controlar o sensor e os atuadores, além de fazer a conexão com a internet via WiFi.
- **MQ-2:** Sensor usado para detecção dos gases tóxicos.
- **Atuador Led:** Os atuadores de led possuem a função de alerta. O verde se inicia ligado, até que algum gás tóxico seja detectado, e assim acenderá o Led Vermelho para alerta.

## Protocolo de Comunicação 

O sistema desenvolvido utiliza a API **CallMeBot** para comunicação via protocolo *MQTT*. Sendo tais tópicos:

- **Inicio do sistema:** Logo que o sistema é ligado, chegará uma mensagem via WhatsApp informando o seu início.
- **Detecção:** Quando algum gás tóxico é detectado, chegará, também via WhatsApp, um alerta imediato.

  ## Protocolo MQTT e Comunicação TCP/IP

A comunicação do sistema é feita pela rede Wi-Fi (TCP/IP) e utiliza o protocolo MQTT para envio e recebimento de dados. A configuração inclui:
1. **Credenciais do Wi-Fi**: Configure seu `wifi_ssid` e `wifi_senha` para conexão com a internet.
2. **Credenciais do CallMeBot**: Configure seu `numero de telefone` e `api_key` para autenticação MQTT.

## Acesso do vídeo no Youtube
- Acesse o link para visualizar: https://youtu.be/qZK4po9SEk0


