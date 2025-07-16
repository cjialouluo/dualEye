# ESP32C3 + GC9D01 眼睛显示项目

这个项目在GC9D01驱动的0.71寸圆形TFT显示屏上显示眼睛静态图像。

## 硬件要求

- ESP32C3开发板
- GC9D01驱动的0.71寸TFT显示屏 (160x160像素)
- 连接线

## 接线说明

根据`User_Setup.h`中的配置，推荐接线如下：

| 显示屏引脚 | ESP32C3引脚 | 说明 |
|------------|-------------|------|
| VCC        | 3.3V        | 电源 |
| GND        | GND         | 地线 |
| SCL/SCLK   | GPIO 8      | SPI时钟 |
| SDA/MOSI   | GPIO 10     | SPI数据 |
| CS         | GPIO 9      | 片选 |
| DC         | GPIO 11     | 数据/命令选择 |
| RST        | GPIO 12     | 复位 (可选) |
| BL         | GPIO 13     | 背光控制 (可选) |

**注意：** 请根据你的实际硬件调整引脚定义。

## 软件安装步骤

### 1. 安装Arduino IDE和ESP32支持

1. 下载并安装Arduino IDE
2. 在Arduino IDE中添加ESP32开发板支持：
   - 文件 → 首选项 → 附加开发板管理器网址
   - 添加：`https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. 工具 → 开发板 → 开发板管理器 → 搜索"ESP32"并安装

### 2. 安装TFT_eSPI库

1. 工具 → 管理库
2. 搜索"TFT_eSPI"
3. 安装Bodmer的TFT_eSPI库

### 3. 配置TFT_eSPI库

1. 找到TFT_eSPI库的安装位置：
   - Windows: `C:\Users\[用户名]\Documents\Arduino\libraries\TFT_eSPI\`
   - macOS: `~/Documents/Arduino/libraries/TFT_eSPI/`
   - Linux: `~/Arduino/libraries/TFT_eSPI/`

2. 备份原始的`User_Setup.h`文件

3. 将项目中的`User_Setup.h`复制到TFT_eSPI库文件夹，替换原文件

### 4. 上传代码

1. 选择正确的开发板：工具 → 开发板 → ESP32 Arduino → ESP32C3 Dev Module
2. 选择正确的端口：工具 → 端口
3. 点击上传按钮

## 文件说明

- `eye_show.ino` - 主程序文件
- `defaultEye.h` - 包含眼睛图像数据的头文件 (200x200像素，RGB565格式)
- `User_Setup.h` - TFT_eSPI库配置文件
- `README.md` - 本说明文件

## 代码说明

主要功能：

1. **初始化显示屏**：设置SPI通信和显示参数
2. **加载图像数据**：从PROGMEM中读取眼睛图像数据
3. **图像裁剪显示**：将200x200的眼睛图像中心裁剪为160x160显示在屏幕上
4. **静态显示**：图像显示后保持不变

## 自定义设置

### 调整显示位置

在`displayEye()`函数中修改裁剪起始位置：

```cpp
int cropStartX = 20;  // 从原图第20列开始截取
int cropStartY = 20;  // 从原图第20行开始截取
```

### 调整屏幕方向

在`setup()`函数中修改旋转角度：

```cpp
tft.setRotation(1); // 0-3，对应0°、90°、180°、270°
```

### 修改引脚配置

如果你的接线不同，请修改`User_Setup.h`中的引脚定义。

## 故障排除

1. **显示屏无显示**：
   - 检查接线是否正确
   - 确认电源供应是否正常
   - 检查引脚配置是否匹配

2. **颜色异常**：
   - 在`User_Setup.h`中取消注释`#define TFT_INVERSION_ON`
   - 或取消注释`#define TFT_RGB_ORDER TFT_BGR`

3. **编译错误**：
   - 确认TFT_eSPI库已正确安装
   - 检查`User_Setup.h`配置是否正确

4. **上传失败**：
   - 确认ESP32C3开发板已选择正确
   - 检查USB驱动是否已安装
   - 尝试按住BOOT按钮再上传

## 扩展功能

这个基础代码可以扩展为：

- 眨眼动画
- 眼球跟踪
- 不同表情切换
- 触摸或传感器交互

## 技术参数

- 图像分辨率：200x200像素 (原始数据)
- 显示分辨率：160x160像素 (裁剪后显示)
- 颜色深度：16位 (RGB565)
- 显示屏分辨率：160x160像素
- 内存使用：约80KB (图像数据存储在PROGMEM中)

## 许可证

请根据你的需要添加适当的许可证信息。 