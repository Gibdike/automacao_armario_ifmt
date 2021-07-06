#include <common.h>
#include <FirebaseESP32.h>
#include <FirebaseFS.h>
#include <Utils.h>
#include "WiFi.h"

#define FIREBASE_HOST "https://app-armario.firebaseio.com/"
#define FIREBASE_AUTH ""

const char *ssid = "Vivabela_Router";
const char *password = "07092002";

//Define FirebaseESP32 data object
FirebaseData firebaseData;
FirebaseJson json;
int Vrdata = 0;

void setup()
{

    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);

    //Set database read timeout to 1 minute (max 15 minutes)
    Firebase.setReadTimeout(firebaseData, 1000 * 60);
    //tiny, small, medium, large and unlimited.
    //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
    Firebase.setwriteSizeLimit(firebaseData, "tiny");

    /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */

    //String path = "/data";
}
void loop()
{
    int Sdata = map(Vrdata, 0, 4095, 0, 1000);
    Serial.println(Sdata);
    delay(100);
    json.set("/users", Sdata);
    Firebase.updateNode(firebaseData, "/users", json);
}