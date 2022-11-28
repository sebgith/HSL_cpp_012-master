
#include <IotWebConf.h>
#include <IotWebConfUsing.h> // This loads aliases for easier class names.

// -- Initial name of the Thing. Used e.g. as SSID of the own Access Point.
const char thingName[] = "iottest123"; // muss mindestens 8 zeichen lang sein

// -- Initial password to connect to the Thing, when it creates an own Access Point.
const char wifiInitialApPassword[] = "iottest123456";

#define STRING_LEN 128
#define NUMBER_LEN 32

// -- Configuration specific key. The value should be modified if config structure was changed.
#define CONFIG_VERSION "23"

// -- When CONFIG_PIN is pulled to ground on startup, the Thing will use the initial
//      password to buld an AP. (E.g. in case of lost password)
int D2 = 25;
#define CONFIG_PIN D2

// -- Status indicator pin.
//      First it will light up (kept LOW), on Wifi connection it will blink,
//      when connected to the Wifi it will turn off (kept HIGH).
int LED_BUILTIN = 02;
#define STATUS_PIN LED_BUILTIN

// -- Method declarations.
void handleRoot();
void UpdateVariableswithUserInput();
// -- Callback methods.
void configSaved();
bool formValidator(iotwebconf::WebRequestWrapper* webRequestWrapper);

DNSServer dnsServer;
WebServer server(80);

// anlegen der im Eprom zu speichernden Werte, sind Chars mit der Länge NUMBER_LEN. U
// Umwandlung von Chars in float oder int mit atof()oder atoi()
/* Um neue Werte zum WebInterace hinzuzugügen muss folgendes gemacht werden
1. Variable anlegen als char z.B. mit Index Value
2. Objekt mit IotWebConfNumberParameter anlegen unter angabe eines Objektnamens
3. in SetupWebinterfac den Wert der gewünschten gruppe hinzufügen.
4. AdcArrayUpdateWithInputValue() variablen ergänzen*/

/* Aus beispielcode, beim bereinigen kann das gelöscht werden.
char stringParamValue[STRING_LEN];
char intParamValue[NUMBER_LEN];
char floatParamValue[NUMBER_LEN];
char checkboxParamValue[STRING_LEN];
char chooserParamValue[STRING_LEN];
static char chooserValues[][STRING_LEN] = { "red", "blue", "darkYellow" };
static char chooserNames[][STRING_LEN] = { "Red", "Blue", "Dark yellow" };
*/
//ADC0
char physicalMinAdc0Value[NUMBER_LEN]; // bekanntmachen des wertes als variable
char physicalMaxAdc0Value[NUMBER_LEN];
char minCurrentAdc0Value[NUMBER_LEN];
char maxCurrentAdc0Value[NUMBER_LEN];
char resistorAdc0Value[NUMBER_LEN];
//ADC1
char physicalMinAdc1Value[NUMBER_LEN]; // bekanntmachen des wertes als variable
char physicalMaxAdc1Value[NUMBER_LEN];
char minCurrentAdc1Value[NUMBER_LEN];
char maxCurrentAdc1Value[NUMBER_LEN];
char resistorAdc1Value[NUMBER_LEN];
//ADC2
char physicalMinAdc2Value[NUMBER_LEN]; // bekanntmachen des wertes als variable
char physicalMaxAdc2Value[NUMBER_LEN];
char minCurrentAdc2Value[NUMBER_LEN];
char maxCurrentAdc2Value[NUMBER_LEN];
char resistorAdc2Value[NUMBER_LEN];
//ADC3
char physicalMinAdc3Value[NUMBER_LEN]; // bekanntmachen des wertes als variable
char physicalMaxAdc3Value[NUMBER_LEN];
char minCurrentAdc3Value[NUMBER_LEN];
char maxCurrentAdc3Value[NUMBER_LEN];
char resistorAdc3Value[NUMBER_LEN];
//MQTT
char mqttServerCharValue[STRING_LEN];
char mqttTokenCharValue[STRING_LEN];
char mqttpublishIntervallCharValue[NUMBER_LEN];

//char stringParamValue[STRING_LEN];

IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword, CONFIG_VERSION);
// -- You can also use namespace formats e.g.: iotwebconf::TextParameter

// MQTT
IotWebConfParameterGroup groupMqqt = IotWebConfParameterGroup("MQTT", "");
IotWebConfTextParameter mqttServerName = IotWebConfTextParameter("Server Adresse MQTT", "Server Adresse MQTT", mqttServerCharValue, STRING_LEN);
IotWebConfTextParameter mqttToken = IotWebConfTextParameter("Token MQTT Client", "Token MQTT Client", mqttTokenCharValue, STRING_LEN);
IotWebConfNumberParameter mqttpublishIntervall = IotWebConfNumberParameter("Thingsboard Publish Intervall in ms", "hingsboard Publish Intervall in ms", mqttpublishIntervallCharValue, NUMBER_LEN, "20", "0..60000", "min='0' max='60000' step='1'");

//ADC Gruppen
IotWebConfParameterGroup groupadc0 = IotWebConfParameterGroup("Parametrierung Eingang 0", "Parametrierung 4-20mA Analogeingang 0");
IotWebConfParameterGroup groupadc1 = IotWebConfParameterGroup("Parametrierung Eingang 1", "Parametrierung 4-20mA Analogeingang 1");
IotWebConfParameterGroup groupadc2 = IotWebConfParameterGroup("Parametrierung Eingang 2", "Parametrierung 4-20mA Analogeingang 2");
IotWebConfParameterGroup groupadc3 = IotWebConfParameterGroup("Parametrierung Eingang 3", "Parametrierung 4-20mA Analogeingang 3");

//adc0
IotWebConfNumberParameter physicalMinAdc0 = IotWebConfNumberParameter("physical MinAdc0", "physicalMinAdc0", physicalMinAdc0Value, NUMBER_LEN, "20", "-500..500", "min='-500' max='500' step='1'");
IotWebConfNumberParameter physicalMaxAdc0 = IotWebConfNumberParameter("physicalMaxAdc0", "physicalMaxAdc0", physicalMaxAdc0Value, NUMBER_LEN,  "20", "-500..500", "min='-500' max='500' step='1'");
IotWebConfNumberParameter minCurrentAdc0 = IotWebConfNumberParameter("minCurrentAdc0", "minCurrentAdc0", minCurrentAdc0Value, NUMBER_LEN, "20", "0..20", "min='0' max='20' step='1'");
IotWebConfNumberParameter maxCurrentAdc0 = IotWebConfNumberParameter("maxCurrentAdc0", "maxCurrentAdc0", maxCurrentAdc0Value, NUMBER_LEN, "20", "0..20", "min='0' max='20' step='1'");
IotWebConfNumberParameter resistorAdc0 = IotWebConfNumberParameter("resistorAdc0", "resistorAdc0", resistorAdc0Value, NUMBER_LEN, "20", "0..250", "min='0' max='250' step='1'");
//adc1
IotWebConfNumberParameter physicalMinAdc1 = IotWebConfNumberParameter("physical MinAdc1", "physicalMinAdc1", physicalMinAdc1Value, NUMBER_LEN, "20", "-500..500", "min='-500' max='500' step='1'");
IotWebConfNumberParameter physicalMaxAdc1 = IotWebConfNumberParameter("physicalMaxAdc1", "physicalMaxAdc1", physicalMaxAdc1Value, NUMBER_LEN,  "20", "-500..500", "min='-500' max='500' step='1'");
IotWebConfNumberParameter minCurrentAdc1 = IotWebConfNumberParameter("minCurrentAdc1", "minCurrentAdc1", minCurrentAdc1Value, NUMBER_LEN, "20", "0..20", "min='0' max='20' step='1'");
IotWebConfNumberParameter maxCurrentAdc1 = IotWebConfNumberParameter("maxCurrentAdc1", "maxCurrentAdc", maxCurrentAdc1Value, NUMBER_LEN, "20", "0..20", "min='0' max='20' step='1'");
IotWebConfNumberParameter resistorAdc1 = IotWebConfNumberParameter("resistorAdc1", "resistorAdc1", resistorAdc1Value, NUMBER_LEN, "20", "0..250", "min='0' max='250' step='1'");
//adc2
IotWebConfNumberParameter physicalMinAdc2 = IotWebConfNumberParameter("physical MinAdc2", "physicalMinAdc2", physicalMinAdc2Value, NUMBER_LEN, "20", "-500..500", "min='-500' max='500' step='1'");
IotWebConfNumberParameter physicalMaxAdc2 = IotWebConfNumberParameter("physicalMaxAdc2", "physicalMaxAdc2", physicalMaxAdc2Value, NUMBER_LEN,  "20", "-500..500", "min='-500' max='500' step='1'");
IotWebConfNumberParameter minCurrentAdc2 = IotWebConfNumberParameter("minCurrentAdc2", "minCurrentAdc2", minCurrentAdc2Value, NUMBER_LEN, "20", "0..20", "min='0' max='20' step='1'");
IotWebConfNumberParameter maxCurrentAdc2 = IotWebConfNumberParameter("maxCurrentAdc2", "maxCurrentAdc2", maxCurrentAdc2Value, NUMBER_LEN, "20", "0..20", "min='0' max='20' step='1'");
IotWebConfNumberParameter resistorAdc2 = IotWebConfNumberParameter("resistorAdc2", "resistorAdc2", resistorAdc2Value, NUMBER_LEN, "20", "0..250", "min='0' max='250' step='1'");
//adc3
IotWebConfNumberParameter physicalMinAdc3 = IotWebConfNumberParameter("physical MinAdc3", "physicalMinAdc3", physicalMinAdc3Value, NUMBER_LEN, "20", "-500..500", "min='-500' max='500' step='1'");
IotWebConfNumberParameter physicalMaxAdc3 = IotWebConfNumberParameter("physicalMaxAdc3", "physicalMaxAdc3", physicalMaxAdc3Value, NUMBER_LEN,  "20", "-500..500", "min='-500' max='500' step='1'");
IotWebConfNumberParameter minCurrentAdc3 = IotWebConfNumberParameter("minCurrentAdc3", "minCurrentAdc3", minCurrentAdc3Value, NUMBER_LEN, "20", "0..20", "min='0' max='20' step='1'");
IotWebConfNumberParameter maxCurrentAdc3 = IotWebConfNumberParameter("maxCurrentAdc3", "maxCurrentAdc3", maxCurrentAdc3Value, NUMBER_LEN, "20", "0..20", "min='0' max='20' step='1'");
IotWebConfNumberParameter resistorAdc3 = IotWebConfNumberParameter("resistorAdc3", "resistorAdc3", resistorAdc3Value, NUMBER_LEN, "20", "0..250", "min='0' max='250' step='1'");

void setupWebInterface()  // Funktion muss einmal im setup aufgerufen werden
{
  //Serial.begin(115200); 
  Serial.println();
  Serial.println("Starting up...");

  groupMqqt.addItem(&mqttServerName); //TO DO
  groupMqqt.addItem(&mqttToken);
  groupMqqt.addItem(&mqttpublishIntervall);

  groupadc0.addItem(&physicalMinAdc0);
  groupadc0.addItem(&physicalMaxAdc0);
  groupadc0.addItem(&minCurrentAdc0);
  groupadc0.addItem(&maxCurrentAdc0);
  groupadc0.addItem(&resistorAdc0);

  groupadc1.addItem(&physicalMinAdc1);
  groupadc1.addItem(&physicalMaxAdc1);
  groupadc1.addItem(&minCurrentAdc1);
  groupadc1.addItem(&maxCurrentAdc1);
  groupadc1.addItem(&resistorAdc1);

  groupadc2.addItem(&physicalMinAdc2);
  groupadc2.addItem(&physicalMaxAdc2);
  groupadc2.addItem(&minCurrentAdc2);
  groupadc2.addItem(&maxCurrentAdc2);
  groupadc2.addItem(&resistorAdc2);

  groupadc3.addItem(&physicalMinAdc3);
  groupadc3.addItem(&physicalMaxAdc3);
  groupadc3.addItem(&minCurrentAdc3);
  groupadc3.addItem(&maxCurrentAdc3);
  groupadc3.addItem(&resistorAdc3);

  iotWebConf.setStatusPin(STATUS_PIN);
  iotWebConf.setConfigPin(CONFIG_PIN);
  iotWebConf.addParameterGroup(&groupMqqt); // Gruppen hinzufügen zum UI
  iotWebConf.addParameterGroup(&groupadc0);
  iotWebConf.addParameterGroup(&groupadc1);
  iotWebConf.addParameterGroup(&groupadc2);
  iotWebConf.addParameterGroup(&groupadc3);

  iotWebConf.setConfigSavedCallback(&configSaved);
  iotWebConf.setFormValidator(&formValidator);
  iotWebConf.getApTimeoutParameter()->visible = true;

  // -- Initializing the configuration.
  iotWebConf.init();

  // -- Set up required URL handlers on the web server.
  server.on("/", handleRoot);
  server.on("/config", []{ iotWebConf.handleConfig(); });
  server.onNotFound([](){ iotWebConf.handleNotFound(); });
  Serial.println("Ready.");
}

 void UpdateVariableswithUserInput()
 {



physicalMinAdc_0 = atoi(physicalMinAdc0Value);  // unterer physikalischer Messwert
physicalMaxAdc_0 = atoi(physicalMaxAdc0Value); // oberer physikalischer Messwert
minCurrentAdc_0 = atoi(minCurrentAdc0Value);   // unterer Strommesswert [mA]
maxCurrentAdc_0 = atoi(maxCurrentAdc0Value);  // oberer Strommesswert [mA]
resistorAdc_0 = atoi(resistorAdc0Value);  // Widerstandswert in Ohm

Serial.println(physicalMinAdc_0);
Serial.print(physicalMaxAdc_0);

physicalMinAdc_1 = atoi(physicalMinAdc1Value);  // unterer physikalischer Messwert
physicalMaxAdc_1 = atoi(physicalMaxAdc1Value); // oberer physikalischer Messwert
minCurrentAdc_1 = atoi(minCurrentAdc1Value);   // unterer Strommesswert [mA]
maxCurrentAdc_1 = atoi(maxCurrentAdc1Value);  // oberer Strommesswert [mA]
resistorAdc_1 = atoi(resistorAdc1Value);  // Widerstandswert in Ohm

physicalMinAdc_2 = atoi(physicalMinAdc2Value);  // unterer physikalischer Messwert
physicalMaxAdc_2 = atoi(physicalMaxAdc2Value); // oberer physikalischer Messwert
minCurrentAdc_2 = atoi(minCurrentAdc2Value);   // unterer Strommesswert [mA]
maxCurrentAdc_2 = atoi(maxCurrentAdc2Value);  // oberer Strommesswert [mA]
resistorAdc_2 = atoi(resistorAdc2Value);  // Widerstandswert in Ohm

physicalMinAdc_3 = atoi(physicalMinAdc3Value);  // unterer physikalischer Messwert
physicalMaxAdc_3 = atoi(physicalMaxAdc3Value); // oberer physikalischer Messwert
minCurrentAdc_3 = atoi(minCurrentAdc3Value);   // unterer Strommesswert [mA]
maxCurrentAdc_3 = atoi(maxCurrentAdc3Value);  // oberer Strommesswert [mA]
resistorAdc_3 = atoi(resistorAdc3Value);  // Widerstandswert in Ohm

}


 

/**
 * Handle web requests to "/" path.
 */
void handleRoot()
{
  // -- Let IotWebConf test and handle captive portal requests.
  if (iotWebConf.handleCaptivePortal())
  {
    // -- Captive portal request were already served.
    return;
  }
  
  String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s += "<title>IotWebConf 03 Custom Parameters</title></head><body>Hello world!";
  s += "<ul>";
  s += "<li>String param value: ";
  s += "<li>Int param value: ";
  s += "<li>Float param value: ";
  s += "<li>CheckBox selected: ";
  s += "<li>Option selected: ";
  s += "</ul>";
  s += "Go to <a href='config'>configure page</a> to change values.";
  s += "</body></html>\n";
  

  server.send(200, "text/html", s);
}

void configSaved()
{
  Serial.println("Configuration was updated.");
  UpdateVariableswithUserInput();
}

bool formValidator(iotwebconf::WebRequestWrapper* webRequestWrapper)
{
  Serial.println("Validating form.");
  bool valid = true;

/*
  int l = webRequestWrapper->arg(stringParam.getId()).length();
  if (l < 3)
  {
    stringParam.errorMessage = "Please provide at least 3 characters for this test!";
    valid = false;
  }
*/
  return valid;
}


