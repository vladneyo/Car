#include "esp_camera.h"

#include "camera.h"
#include "http_server_bootstrapper.h"


// GPIO Setting
extern int gpLed = 4; // Light

Camera camera;
HttpServerBootstrapper server;

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  pinMode(gpLed, OUTPUT); // Light
  digitalWrite(gpLed, LOW);

  camera.setup();
  server.setup();
}

void loop()
{
  // put your main code here, to run repeatedly:
}
