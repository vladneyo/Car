#pragma once

#include "esp_camera.h"

#define CAMERA_MODEL_AI_THINKER

#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27

#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

#define FRAME_SIZE FRAMESIZE_CIF
// FRAMESIZE_96X96,          // 96x96
// FRAMESIZE_QQVGA,          // 160x120
// FRAMESIZE_QCIF,           // 176x144
// FRAMESIZE_HQVGA,          // 240x176
// FRAMESIZE_240X240,        // 240x240
// FRAMESIZE_QVGA,           // 320x240
// FRAMESIZE_CIF,            // 400x296
// FRAMESIZE_HVGA,           // 480x320
// FRAMESIZE_VGA,            // 640x480
// FRAMESIZE_SVGA,           // 800x600
// FRAMESIZE_XGA,            // 1024x768
// FRAMESIZE_HD;             // 1280x720
// FRAMESIZE_SXGA,           // 1280x1024
// FRAMESIZE_UXGA,           // 1600x1200

struct Camera
{
  void setup();
};