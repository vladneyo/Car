#include <WiFi.h>

#include "wifi-config.h"
#include "http_server_bootstrapper.h"
#include "app_httpd.h"

String WiFiAddr = "";

void HttpServerBootstrapper::setup()
{
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  WiFiAddr = WiFi.localIP().toString();
  Serial.println("' to connect");
}
