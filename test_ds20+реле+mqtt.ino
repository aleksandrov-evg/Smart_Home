#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>

#define MQTT_VERSION MQTT_VERSION_3_1_1

// Wifi: SSID and password
const PROGMEM char* WIFI_SSID = "";
const PROGMEM char* WIFI_PASSWORD = "";

// MQTT: ID, server IP, port, username and password
const PROGMEM char* MQTT_CLIENT_ID = "relays";
const PROGMEM char* MQTT_SERVER_IP = "192.168.1.103";
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;
const PROGMEM char* MQTT_USER = "";
const PROGMEM char* MQTT_PASSWORD = "";


WiFiClient wifiClient;
PubSubClient client (wifiClient);


/////////////////////////// RELAY ////////////////////////////////////////////
// payloads by default (on/off)
const char* RELAY_ON = "1";
const char* RELAY_OFF = "0";

class Relay
{
  public:
    /*
       Конструктор
       @param stateTopic - топик где публикуется состояние реле. Пример "relay/1/status"
       @param commandTopic - топик запрос на который меняет статус реле
       @param pin - пин на который подключено реле
       @param isOn - статус реле false = выключено, true = включено
    */
    Relay( String stateTopic, String commandTopic, uint8_t pin ) {
      stateTopic_ = stateTopic;
      commandTopic_ = commandTopic;
      pin_ = pin;
      isOn_ = false;
    };

    /*
       Публикация состояния реле в топике
    */
    void publishState () {
      if ( isOn_ ) {
        client.publish(stateTopic_.c_str(), RELAY_ON, true);
      } else {
        client.publish(stateTopic_.c_str(), RELAY_OFF, true);
      }
    };

    /*
       Включает или выключает реле в зависимости от предыдущего состояния
    */
    void switchState() {
      if ( !isOn_ ) {
        isOn_ = true;
        digitalWrite( pin_, HIGH);
        Serial.println( String( "INFO: Turn relay on... pin: " + String ( pin_ ) ) );

      } else {
        isOn_ = false;
        digitalWrite( pin_, LOW);
        Serial.println( String( "INFO: Turn relay off... pin: " + String ( pin_ ) ) );
      }
      publishState();
    };

    /*
       Обработчик запроса
       @param p_topic - вызывающий топик
       @param payload - тело запроса
       @return - true = если запрос обработан, false = запрос не обработан
    */
    bool handle ( char* p_topic, String payload ) {
      if ( String( commandTopic_ ).equals( p_topic )) {
        // test if the payload is equal to "ON" or "OFF"
        if ( payload.equals( String( RELAY_ON ) ) ) {
          if ( !isOn_ )
            switchState();
          return true;
        } else if ( payload.equals( String( RELAY_OFF ) ) ) {
          if ( isOn_ )
            switchState();
          return true;
        }
      };
      return false;
    };

    /*
       Функция иницилизации реле.
    */
    void init() {
      pinMode(pin_, OUTPUT);
      digitalWrite( pin_, LOW);
      publishState ();
    };
  private:
    String stateTopic_,
           commandTopic_;
    uint8_t pin_;
    bool isOn_;
};
// Количесвто реле
const uint8_t countRelays = 8;
// Список реле
Relay relays [countRelays] = {
  Relay ( "relay/1/status", "relay/1/switch", 5),
  Relay ( "relay/2/status", "relay/2/switch", 4),
  Relay ( "relay/3/status", "relay/3/switch", 0),
  Relay ( "relay/4/status", "relay/4/switch", 2),
  Relay ( "relay/5/status", "relay/5/switch", 14),
  Relay ( "relay/6/status", "relay/6/switch", 12),
  Relay ( "relay/7/status", "relay/7/switch", 13),
  Relay ( "relay/8/status", "relay/8/switch", 15),
};

// function called when a MQTT message arrived
bool relaysHandle (char* p_topic, String payload) {
  // handle message topic
  for (uint8_t id = 0 ; id < countRelays; id++) {
    if ( relays[id].handle ( p_topic, payload ) )
      return true;
  }
  return false;
}

void initRelays()
{
  for (uint8_t id = 0; id < countRelays; id++)
    relays[id].init();
}

////////////////////////////////////// TEMPERATURE ///////////////////////////////////////////////

OneWire  ds(1);     // Темпер на 13пин
bool tempHandle( char* p_topic ) {
  byte addr[8];
  String topic_name = "temp/";

  ds.reset_search();
  while (true)
  {
    if ( !ds.search(addr))
      return false;
    String tmp_topic_name = topic_name;
    for (byte i = 0; i < 8; i++)
    {
      tmp_topic_name = tmp_topic_name + String (addr[i], HEX) + "_";
    }
    if ( tmp_topic_name.equals (p_topic))
    {
      topic_name = tmp_topic_name;
      break;
    }
  }



  byte type_s;
  byte data[12];
  float celsius;

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return false;
  }
  //  Serial.println();

  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:

      type_s = 1;
      break;
    case 0x28:

      type_s = 0;
      break;
    case 0x22:
      //  Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      //  Serial.println("Device is not a DS18x20 family device.");
      return false;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);

  delay(1000);

  //  delay(1000);

  ds.reset();
  ds.select(addr);
  ds.write(0xBE);

  for (byte i = 0; i < 9; i++) {
    data[i] = ds.read();
  }
  OneWire::crc8(data, 8);
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3;
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);

    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms

  }


  celsius = (float)raw / 16.0;

  Serial.println(celsius);

  char temperaturenow [15];
  dtostrf(celsius, 7, 3, temperaturenow); //// convert float to char
  client.publish(topic_name.c_str(), temperaturenow);   /// send char
  return true;
}


/////////////////////////////////////// MAIN FUNCTIONS //////////////////////////////////////////

void callback(char* p_topic, byte* p_payload, unsigned int p_length) {
  // concat the payload into a string
  String payload;
  for (uint8_t i = 0; i < p_length; i++) {
    payload.concat((char)p_payload[i]);
  }

  if (relaysHandle( p_topic, payload ))
    return;
  if (tempHandle( p_topic))
    return;
  Serial.println("Unknown topic");
  Serial.println(p_topic);
  return;
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("INFO: Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("INFO: connected");
      // Once connected, publish an announcement...

    } else {
      Serial.print("ERROR: failed, rc=");
      Serial.print(client.state());
      Serial.println("DEBUG: try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // init the serial
  Serial.begin(115200);

  // init the WiFi connection
  Serial.println();
  Serial.println();
  Serial.print("INFO: Connecting to ");
  WiFi.mode(WIFI_STA);
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("INFO: WiFi connected");
  Serial.print("INFO: IP address: ");
  Serial.println(WiFi.localIP());

  // init the MQTT connection
  client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  client.setCallback(callback);

  // init the relays
  initRelays();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
