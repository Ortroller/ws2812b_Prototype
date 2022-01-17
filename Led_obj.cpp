#define PORT              PORTD   // Port
#include "Led_obj.h"
#define l_pinout 5

/*--------------------------------------------------*/
uint16_t t_f;

 
Led_obj::Led_obj(uint8_t pinout, uint16_t qleds){ // CONSTRUTOR
      l_pin = pinout;
      q_led = qleds;
      int i;
      for(i=0; i< 150; i++){//Setando todas as posições para zero
        v_led[i].r = 0;
        v_led[i].g = 0;
        v_led[i].b = 0;
                
      }
      resetLed();
}
  

  
void Led_obj::resetLed(){ // Reseta as leds
    byte i;
    byte qtd_ld = q_led;
    for(qtd_ld; qtd_ld !=0; qtd_ld--){
      for(i=0; i<24; i++){
        sendZero();
      }
    }
    delay(50);
}

// ======================================== Efeitos ===========================================================

void Led_obj::PalEffect(byte r_rate, uint8_t val_effect[], uint16_t pal_size){
    uint8_t i;
    uint8_t l_i=0; // Inicia na primeira led

    lRGB tmp;
    
    for(i = 0; i < q_led; i++){
    tmp.r = val_effect[l_i];
    tmp.g = val_effect[l_i + 1];
    tmp.b = val_effect[l_i + 2];
      
      v_led[i] = tmp;
      l_i = (l_i + 3) % pal_size;
    }
    refreshALL(q_led);
}

void Led_obj::rotate(){ // Rotacao vetorial
  uint8_t i; // 8b
  // uint8_t l_i=0;

  lRGB tmp;

  tmp = v_led[q_led-1];

  for (i = q_led -1; i > 0; i--) {
   v_led[i] = v_led[i-1];
  }

  v_led[0] = tmp;
  refreshALL(q_led);
}
  
/******************************************Atualizar cores****************************************************/
  void Led_obj::setLed(int ind, lRGB color){
    v_led[ind-1] = color;
  }
  
  void Led_obj::refreshALL(byte qtd_led){
      int i;
      for(i=0;i<qtd_led;i++){
        cRainB(v_led[i]);
      }
      delay(50);
  }

void Led_obj::doPallete(byte ind, uint8_t R, uint8_t G, uint8_t B){
  lRGB tmp;
  tmp.r = R;
  tmp.g = G;
  tmp.b = B;

  v_led[ind-1] = tmp;
}

/*================================================= RGB CONVERTER SENDER ==========================================*/

void Led_obj::cRainB(lRGB ld){ // Funcao consome 3 bytes em array para ligar uma cor

    byte mask;
    byte ii;


      //=================== G
      mask = 128;
      for(ii = 0; ii < 8; ii++){
        if((ld.g & mask) > 0){
          sendUm();
        }else{
          sendZero();
        }
      mask = (mask >> 1);
      }
      //=================== R
      mask = 128;
      
      for(ii = 0; ii < 8; ii++){
        if((ld.r & mask) > 0){
          sendUm();
        }else{
          sendZero();
        }
      mask = (mask >> 1);
      }
      //=================== B
      mask = 128;
      
      for(ii = 0; ii < 8; ii++){
        if((ld.b & mask) > 0){
          sendUm();
        }else{
          sendZero();
        }
      mask = (mask >> 1);
      }
}
//========================================= Debugger Display =====================================================================
  String Led_obj::getValue(byte ind){
    String s;
    s += "QTDleds " + (String)q_led + "Dvg " + (String) v_led[ind].g + "Dvr " + (String) v_led[ind].r + "Dvb " + (String) v_led[ind].b;
    return s;
  
  }
/*=============================================================================== ROTINA DE ENVIOS =====================================================================*/
/*=============================================================================== ROTINA DE ENVIOS =====================================================================*/
/*=============================================================================== ROTINA DE ENVIOS =====================================================================*/
/*=============================================================================== ROTINA DE ENVIOS =====================================================================*/
  void Led_obj::sendZero(){
  // Cada nop equivale 62.5ns
  noInterrupts();
  
    while((micros() - t_f) < 45L);  // wait for 50us
  asm volatile(
  
      "sbi  %0, %1\n\t"     // 2    PIN HIGH      (T =  2)
      "rjmp .+0\n\t"        // 2    nop nop       (T =  4)
      "rjmp .+0\n\t"       // 2    nop nop       (T =  6)
      "cbi   %0, %1\n\t"    // 2    PIN LOW       (T =  8)
      "rjmp .+0\n\t"        // 2    nop nop       (T = 10)
      "rjmp .+0\n\t"        // 2    nop nop       (T = 12)
      "rjmp .+0\n\t"        // 2    nop nop       (T = 14)
      "rjmp .+0\n\t"        // 2    nop nop       (T = 16)
      "rjmp .+0\n\t"        // 2    nop nop       (T = 18)
      "rjmp .+0\n\t"       // 2    nop nop       (T = 20)  0
      ::
      "I" (_SFR_IO_ADDR(PORT)), //%0
      "I" (l_pinout)            //%1
  );
  
  interrupts();
  }
  void Led_obj::sendUm(){
  // Cada nop equivale 62.5ns
  noInterrupts();
  asm volatile(
      // Instruction        Clock   Description   Phase     Bit Transmitted
      "sbi  %0, %1\n\t"  // 2      PIN HIGH       (T =  2) 
      "rjmp .+0\n\t"        // 2      nop nop         (T =  4)
      "rjmp .+0\n\t"        // 2      nop nop         (T =  6)
      "rjmp .+0\n\t"        // 2      nop nop         (T =  8)
      "rjmp .+0\n\t"        // 2      nop nop         (T = 10)
      "rjmp .+0\n\t"        // 2      nop nop         (T = 12)
      "nop\n\t"               // 1      nop                (T = 13)
      "cbi   %0, %1\n\t" // 2      PIN LOW       (T = 15)
      "rjmp .+0\n\t"        // 2      nop nop         (T = 17)
      "rjmp .+0\n\t"        // 2      nop nop         (T = 19)
      "nop\n\t"               // 1      nop                (T = 20)      1
      ::
      // Input operands
      "I" (_SFR_IO_ADDR(PORT)), //%0
      "I" (l_pinout)            //%1
    );
    interrupts();
  }
