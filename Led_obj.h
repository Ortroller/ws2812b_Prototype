#include <Arduino.h>

struct RGBnode{

  uint8_t r;
  uint8_t g;
  uint8_t b;
  
};

typedef struct RGBnode lRGB;

class Led_obj{
  
  private:
    lRGB v_led[150];  // Vetor de leds, cada indice representa uma led, guarda 3 valores de 8 bits, representando a cor
    uint8_t l_pin; // nao usado
    uint16_t q_led; // Quantidade total de leds
    
  public:
    Led_obj(uint8_t value, uint16_t qleds);
    void refreshALL(byte qtd_led); // Atualiza todas as leds de acordo com seu respectivo indice do v_led
    void setLed(int ind, lRGB color); // Seta a cor no vetor de leds
    void sendZero(); // Rotina interna de envio de bits zero
    void sendUm();  //  Rotina interna de envio de bits um
    void resetLed(); // Desliga todas as leds
    void cRainB(lRGB ld); // converte os valores em sequecia de bits indicando a cor e da intensidade da led
    String getValue(byte ind); //Debug
    void doPallete(byte ind, uint8_t R, uint8_t G, uint8_t B); // seta uma led escolhida do vetor para cor desejada

    void PalEffect(byte r_rate, uint8_t val_effect[], uint16_t pal_size); // Segue uma atualizacao de cores usando uma sequencia de 3 valores

    void  rotate(); // rotacao do vetor de cores
 
    void TearDrop(byte r_rate, lRGB color); // Efeito gota ( TO DO )
};
