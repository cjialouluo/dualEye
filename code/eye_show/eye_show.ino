#include <TFT_eSPI.h>
#include "defaultEye.h"

// 创建TFT显示对象
TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  Serial.println("Eye Display Starting...");
  
  // 初始化显示屏
  tft.init();
  tft.setRotation(0); // 设置屏幕方向，可根据需要调整(0-3)
  
  // 清屏
  tft.fillScreen(TFT_BLACK);
  
  // 显示眼睛图像
  displayEye();
  
  Serial.println("Eye displayed successfully!");
}

void loop() {
  // 静态显示，无需在loop中做任何事情
  delay(1000);
}

void displayEye() {
  // 计算居中显示的起始坐标
  // GC9D01 0.71寸是160x160像素的圆形显示屏
  int startX = (160 - SCLERA_WIDTH) / 2;   // 居中显示X坐标 (160-200)/2 = -20 (需要缩放图像)
  int startY = (160 - SCLERA_HEIGHT) / 2;  // 居中显示Y坐标 (160-200)/2 = -20
  
  // 由于图像尺寸(200x200)大于屏幕尺寸(160x160)，我们需要调整显示策略
  // 选择1: 从图像中心截取160x160区域显示
  int cropStartX = (SCLERA_WIDTH - 160) / 2;   // 从图像中心开始截取 (200-160)/2 = 20
  int cropStartY = (SCLERA_HEIGHT - 160) / 2;  // 从图像中心开始截取 (200-160)/2 = 20
  
  // 设置显示窗口 - 全屏显示
  tft.setAddrWindow(0, 0, 160, 160);
  
  // 推送截取的像素数据到显示屏
  // 需要逐行推送，因为要跳过边缘像素
  for (int y = 0; y < 160; y++) {
    for (int x = 0; x < 160; x++) {
      int sourceIndex = (cropStartY + y) * SCLERA_WIDTH + (cropStartX + x);
      uint16_t pixel = pgm_read_word(&sclera[sourceIndex]);
      tft.pushColor(pixel);
    }
  }
  
  Serial.println("Eye image displayed (cropped to fit 160x160 screen)");
}
