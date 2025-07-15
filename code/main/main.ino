// ESP32_three_GC9101_240x240_displays
//
// microcontroller: ESP32-WROOM-32
// displays: three specimen 1.28 inch 3.3V TFT 240*240 pixels GC9A01 controller
// simultaneous independent display
//
// purpose: three independently running Muybridge horses
//
// sequential display of the sketch by directing frames to CS pins
// TFT_eSPI user setup <User_Setups/Setup46_three_GC9A01_ESP32.h> 
//
// Floris Wouterlood
// February 2, 2024   
// public domain

// center x-y-coordinates of all devices: x = 120 and y = 120

// pin layout:
// both displays     ESP32
//     GND ---------- GND
//     VCC ---------- 3.3V
//     SCL ---------- D18
//     SDA ---------- D23
//     RES ---------- D4
//     DC  ---------- D2
//     BLK ---------- 3V3 - essential
//     CS pin wired to independent pins on the ESP32 - see their #define

   #include <SPI.h>
   #include <TFT_eSPI.h> 
   #include "EYEA.h"
   // #include "EYEB.h"  // 注释掉EYEB.h，使用EYEA.h代替
   TFT_eSPI tft = TFT_eSPI();    
    
   #define device_A_CS  2              
   #define device_B_CS  6 
  //  #define device_C_CS  -1                              
   
   #define BL1 1
   #define BL2 3

// some extra colors
   #define BLACK        0x0000
   #define BLUE         0x001F
   #define RED          0xF800
   #define GREEN        0x07E0
   #define CYAN         0x07FF
   #define MAGENTA      0xF81F
   #define YELLOW       0xFFE0
   #define WHITE        0xFFFF
   #define ORANGE       0xFBE0
   #define GREY         0x84B5
   #define BORDEAUX     0xA000
   #define DINOGREEN    0x2C86
   #define WHITE        0xFFFF

   int frameTime = 70;
   int j;

extern void user_setup(void); // Functions in the user*.cpp files
extern void user_loop(void);

#define SCREEN_X_START 0
#define SCREEN_X_END   SCREEN_WIDTH   // Badly named, actually the "eye" width!
#define SCREEN_Y_START 0
#define SCREEN_Y_END   SCREEN_HEIGHT  // Actually "eye" height

// A simple state machine is used to control eye blinks/winks:
#define NOBLINK 0       // Not currently engaged in a blink
#define ENBLINK 1       // Eyelid is currently closing
#define DEBLINK 2       // Eyelid is currently opening


#define BUFFER_SIZE 1024 // 128 to 1024 seems optimum

#ifdef USE_DMA
  #define BUFFERS 2      // 2 toggle buffers with DMA
#else
  #define BUFFERS 1      // 1 buffer for no DMA
#endif

uint16_t pbuffer[BUFFERS][BUFFER_SIZE]; // Pixel rendering buffer
                 // DMA buffer selection

// This struct is populated in config.h
typedef struct {        // Struct is defined before including config.h --
  int8_t  select;       // pin numbers for each eye's screen select line
  int8_t  wink;         // and wink button (or -1 if none) specified there,
  uint8_t rotation;     // also display rotation and the x offset
  int16_t xposition;    // position of eye on the screen
} eyeInfo_t;
 #include "config.h"
typedef struct {
  uint8_t  state;       // NOBLINK/ENBLINK/DEBLINK
  uint32_t duration;    // Duration of blink state (micros)
  uint32_t startTime;   // Time (micros) of last state change
} eyeBlink;

struct {                // One-per-eye structure
  int16_t   tft_cs;     // Chip select pin for each display
  eyeBlink  blink;      // Current blink/wink state
  int16_t   xposition;  // x position of eye image
} eye[NUM_EYES];

bool     dmaBuf = 0;
uint32_t startTime; 

void Demo_1()
{
  updateEye();
}

void Demo_2()
{
// ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160,160,gImage_A1);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160,160,gImage_A1);              
   digitalWrite (device_B_CS, HIGH);
   

   delay (frameTime);


// ============================================================================

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A2);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A2);
   digitalWrite (device_B_CS, HIGH); 
  
   delay (frameTime);


// ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A3);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A3);
   digitalWrite (device_B_CS, HIGH);
   
   delay (frameTime);

// ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A4);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A4);
   digitalWrite (device_B_CS, HIGH);
   

   delay (frameTime);

// ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A5);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A5);
   digitalWrite (device_B_CS, HIGH);
   

   delay (frameTime);
   

// ============================================================================ 
// // ============================================================================ 
   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A6);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A6);
   digitalWrite (device_B_CS, HIGH);
   delay (frameTime);


// // ============================================================================ 

  digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A7);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A7);
   digitalWrite (device_B_CS, HIGH);
   
   delay (frameTime);


// // ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A8);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A8);
   digitalWrite (device_B_CS, HIGH); 
   delay (frameTime);


// // ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A9);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A9);
   digitalWrite (device_B_CS, HIGH);
   
   delay (frameTime);


// // ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A10);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A10);
   digitalWrite (device_B_CS, HIGH); 
   delay (frameTime);
// // ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A11);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A11);
   digitalWrite (device_B_CS, HIGH); 
   delay (frameTime);
// // ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A12);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A12);
   digitalWrite (device_B_CS, HIGH); 
   delay (frameTime);
// // ============================================================================ 
}
void Demo_3()
{
// ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160,160,gImage_A1);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160,160,gImage_A1);              
   digitalWrite (device_B_CS, HIGH);
   

   delay (frameTime);


// ============================================================================

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A2);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A2);
   digitalWrite (device_B_CS, HIGH); 
  
   delay (frameTime);


// ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A3);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A3);
   digitalWrite (device_B_CS, HIGH);
   
   delay (frameTime);

// ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A4);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A4);
   digitalWrite (device_B_CS, HIGH);
   

   delay (frameTime);

// ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A5);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A5);
   digitalWrite (device_B_CS, HIGH);
   

   delay (frameTime);
   

// ============================================================================ 
// // ============================================================================ 
  digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A6);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A6);
   digitalWrite (device_B_CS, HIGH);
   delay (frameTime);


// // ============================================================================ 

  digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A7);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A7);
   digitalWrite (device_B_CS, HIGH);
   
   delay (frameTime);


// // ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A8);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A8);
   digitalWrite (device_B_CS, HIGH); 
   delay (frameTime);


// // ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A9);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A9);
   digitalWrite (device_B_CS, HIGH);
   
   delay (frameTime);


// // ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A10);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A10);
   digitalWrite (device_B_CS, HIGH); 
   delay (frameTime);
// // ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A11);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A11);
   digitalWrite (device_B_CS, HIGH); 
   delay (frameTime);
// // ============================================================================ 

   digitalWrite (device_A_CS, LOW);   
   tft.pushImage (0, 0,160, 160,gImage_A12);
   digitalWrite (device_A_CS, HIGH); 
   
   digitalWrite (device_B_CS, LOW);  
   tft.pushImage (0, 0,160, 160,gImage_A12);
   digitalWrite (device_B_CS, HIGH); 
   delay (frameTime);
// // ============================================================================ 
}

void pwm_init()
{
  //设置通道号，频率为1000HZ，分辨率为8位
  ledcSetup(1,1000,8);
  ledcSetup(2,1000,8);
  //将通道产生的PWM波映射到BL引脚上
  ledcAttachPin(BL1,1);
  ledcAttachPin(BL2,2);
}

void LED_PWM(unsigned char i)
{
  ledcWrite(1,i);
  ledcWrite(2,i);
  delay(10);
}

void led_breathing()
{
  for(int i = 0;i <= 255;i++)
  {
    ledcWrite(1,i);
    ledcWrite(2,i);
    delay(10);
  }
  for(int i = 255;i >= 0;i--)
  {
    ledcWrite(1,i);
    ledcWrite(2,i);
    delay(10);
  }
}

void PWM_test()
{
  digitalWrite (device_A_CS, LOW);
  tft.fillScreen (BLUE);                                             // we need to 'init' all displays
  digitalWrite (device_A_CS, HIGH);                                                                               
  //  tft.setRotation (3);

  digitalWrite (device_B_CS, LOW); 
  tft.fillScreen (RED);
  digitalWrite (device_B_CS, HIGH);   

}

void setup() {
 
   Serial.begin (9600); 
   for (j=0; j<10; j++)
      {
       Serial.println (""); 
       delay (20);
      }
    
   pinMode (BL1,OUTPUT);
   pinMode (BL2,OUTPUT);
   pinMode (device_A_CS, OUTPUT);
   pinMode (device_B_CS, OUTPUT);

   
   digitalWrite(BL1,HIGH);
   digitalWrite(BL2,HIGH);

   digitalWrite (device_A_CS, LOW);                                             // we need to 'init' all displays
   digitalWrite (device_B_CS, LOW);                                          
  //  digitalWrite (device_C_CS, LOW);                                          
   pwm_init();
   tft.init ();   
  //  tft.setRotation (3);
   tft.fillScreen (BLACK);
  //  tft.pushImage (0, 0,160, 160, bmp1);
   tft.setTextColor (YELLOW, BLACK); 

   digitalWrite (device_A_CS, HIGH);                                          
   digitalWrite (device_B_CS, HIGH);                                          
  //  digitalWrite (device_C_CS, HIGH); 
  
  initEyes();
  if (NUM_EYES > 1) digitalWrite(eye[1].tft_cs, HIGH);

  for (uint8_t e = 0; e < NUM_EYES; e++) {
    digitalWrite(eye[e].tft_cs, LOW);
    tft.setRotation(eyeInfo[e].rotation);
    tft.fillScreen(TFT_BLACK);
    digitalWrite(eye[e].tft_cs, HIGH);
  }
  // pwm_init(); 
  LED_PWM(255);                       
}

char i=1;
void loop (){
  
  for(int a=1;a<=4;a++){
    if(a==1){
    LED_PWM(255);
    digitalWrite (device_B_CS, LOW); 
    tft.setRotation (3);
    digitalWrite (device_B_CS, HIGH);
    digitalWrite (device_A_CS, LOW);                                             // we need to 'init' 
    digitalWrite (device_B_CS, LOW);
    tft.fillScreen (BLACK);
    Demo_1();
    delay(2000);
     
    }

    else if(a==2){
      for(i=0;i<7;i++){
        Demo_2();
      }
    }

    else if(a==3){
      digitalWrite (device_B_CS, LOW); 
      tft.setRotation (0);
      digitalWrite (device_B_CS, HIGH);
      for(i=0;i<7;i++){
        Demo_3();
      }
    }
    else if(a==4)
    {
      PWM_test();
      led_breathing();
    }

  }

} 
