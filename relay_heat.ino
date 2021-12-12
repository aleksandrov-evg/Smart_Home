
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_VERSION MQTT_VERSION_3_1_1

// Wifi: SSID and password
const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";

// MQTT: ID, server IP, port, username and password
const PROGMEM char* MQTT_CLIENT_ID = "relays";
const PROGMEM char* MQTT_SERVER_IP = "192.168.1.103";
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;
const PROGMEM char* MQTT_USER = "";
const PROGMEM char* MQTT_PASSWORD = "";

// MQTT: topics
const char* MQTT_relay_state_TOPIC1 = "relay/1/status";
const char* MQTT_LIGHT_COMMAND_TOPIC1 = "relay/1/switch";

const char* MQTT_relay_state_TOPIC2 = "relay/2/status";
const char* MQTT_LIGHT_COMMAND_TOPIC2 = "relay/2/switch";

const char* MQTT_relay_state_TOPIC3 = "relay/3/status";
const char* MQTT_LIGHT_COMMAND_TOPIC3 = "relay/3/switch";

const char* MQTT_relay_state_TOPIC4 = "relay/4/status";
const char* MQTT_LIGHT_COMMAND_TOPIC4 = "relay/4/switch";

const char* MQTT_relay_state_TOPIC5 = "relay/5/status";
const char* MQTT_LIGHT_COMMAND_TOPIC5 = "relay/5/switch";

const char* MQTT_relay_state_TOPIC6 = "relay/6/status";
const char* MQTT_LIGHT_COMMAND_TOPIC6 = "relay/6/switch";

const char* MQTT_relay_state_TOPIC7 = "relay/7/status";
const char* MQTT_LIGHT_COMMAND_TOPIC7 = "relay/7/switch";

const char* MQTT_relay_state_TOPIC8 = "relay/8/status";
const char* MQTT_LIGHT_COMMAND_TOPIC8 = "relay/8/switch";


// payloads by default (on/off)
const char* RELAY_ON = "1";
const char* RELAY_OFF = "0";

// Определение пинов
const PROGMEM uint8_t RELAY_PIN1 = 4; //d1
const PROGMEM uint8_t RELAY_PIN2 = 5; //d2
const PROGMEM uint8_t RELAY_PIN3 = 0; //d3
const PROGMEM uint8_t RELAY_PIN4 = 2; //d4
const PROGMEM uint8_t RELAY_PIN5 = 15; //d5
const PROGMEM uint8_t RELAY_PIN6 = 14; //d6
const PROGMEM uint8_t RELAY_PIN7 = 12; //d7
const PROGMEM uint8_t RELAY_PIN8 = 13; //d8


boolean m_relay_state1 = false; // реле выключено по дефолту
boolean m_relay_state2 = false; // реле выключено по дефолту
boolean m_relay_state3 = false; // реле выключено по дефолту
boolean m_relay_state4 = false; // реле выключено по дефолту
boolean m_relay_state5 = false; // реле выключено по дефолту
boolean m_relay_state6 = false; // реле выключено по дефолту
boolean m_relay_state7 = false; // реле выключено по дефолту
boolean m_relay_state8 = false; // реле выключено по дефолту


WiFiClient wifiClient;
PubSubClient client(wifiClient);

// function called to publish the state of the relay (on/off)
void publishRelayState1() {
  if (m_relay_state1) {
    client.publish(MQTT_relay_state_TOPIC1, RELAY_ON, true);
  } else {
    client.publish(MQTT_relay_state_TOPIC1, RELAY_OFF, true);
  }
}

void publishRelayState2() {
  if (m_relay_state2) {
    client.publish(MQTT_relay_state_TOPIC2, RELAY_ON, true);
  } else {
    client.publish(MQTT_relay_state_TOPIC2, RELAY_OFF, true);
  }
}

void publishRelayState3() {
  if (m_relay_state3) {
    client.publish(MQTT_relay_state_TOPIC3, RELAY_ON, true);
  } else {
    client.publish(MQTT_relay_state_TOPIC3, RELAY_OFF, true);
  }
}

void publishRelayState4() {
  if (m_relay_state4) {
    client.publish(MQTT_relay_state_TOPIC4, RELAY_ON, true);
  } else {
    client.publish(MQTT_relay_state_TOPIC4, RELAY_OFF, true);
  }
}

void publishRelayState5() {
  if (m_relay_state5) {
    client.publish(MQTT_relay_state_TOPIC5, RELAY_ON, true);
  } else {
    client.publish(MQTT_relay_state_TOPIC5, RELAY_OFF, true);
  }
}

void publishRelayState6() {
  if (m_relay_state6) {
    client.publish(MQTT_relay_state_TOPIC6, RELAY_ON, true);
  } else {
    client.publish(MQTT_relay_state_TOPIC6, RELAY_OFF, true);
  }
}

void publishRelayState7() {
  if (m_relay_state7) {
    client.publish(MQTT_relay_state_TOPIC7, RELAY_ON, true);
  } else {
    client.publish(MQTT_relay_state_TOPIC7, RELAY_OFF, true);
  }
}void publishRelayState8() {
  if (m_relay_state8) {
    client.publish(MQTT_relay_state_TOPIC8, RELAY_ON, true);
  } else {
    client.publish(MQTT_relay_state_TOPIC8, RELAY_OFF, true);
  }
}
// function called to turn on/off the light
void setRelayState1() {
  if (m_relay_state1) {
    digitalWrite(RELAY_PIN1, HIGH);
    Serial.println("INFO: Turn relay_1 on...");
  } else {
    digitalWrite(RELAY_PIN1, LOW);
    Serial.println("INFO: Turn relay_1 off...");
  }
}
void setRelayState2() {
  if (m_relay_state2) {
    digitalWrite(RELAY_PIN2, HIGH);
    Serial.println("INFO: Turn relay_2 on...");
  } else {
    digitalWrite(RELAY_PIN2, LOW);
    Serial.println("INFO: Turn relay_2 off...");
  }
}
void setRelayState3() {
  if (m_relay_state3) {
    digitalWrite(RELAY_PIN3, HIGH);
    Serial.println("INFO: Turn relay_3 on...");
  } else {
    digitalWrite(RELAY_PIN3, LOW);
    Serial.println("INFO: Turn relay_3 off...");
  }
}
void setRelayState4() {
  if (m_relay_state4) {
    digitalWrite(RELAY_PIN4, HIGH);
    Serial.println("INFO: Turn relay_4 on...");
  } else {
    digitalWrite(RELAY_PIN4, LOW);
    Serial.println("INFO: Turn relay_4 off...");
  }
}
void setRelayState5() {
  if (m_relay_state5) {
    digitalWrite(RELAY_PIN5, HIGH);
    Serial.println("INFO: Turn relay_5 on...");
  } else {
    digitalWrite(RELAY_PIN5, LOW);
    Serial.println("INFO: Turn relay_5 off...");
  }
}
void setRelayState6() {
  if (m_relay_state6) {
    digitalWrite(RELAY_PIN6, HIGH);
    Serial.println("INFO: Turn relay_6 on...");
  } else {
    digitalWrite(RELAY_PIN6, LOW);
    Serial.println("INFO: Turn relay_6 off...");
  }
}
void setRelayState7() {
  if (m_relay_state7) {
    digitalWrite(RELAY_PIN7, HIGH);
    Serial.println("INFO: Turn relay_7 on...");
  } else {
    digitalWrite(RELAY_PIN7, LOW);
    Serial.println("INFO: Turn relay_7 off...");
  }
}
void setRelayState8() {
  if (m_relay_state8) {
    digitalWrite(RELAY_PIN8, HIGH);
    Serial.println("INFO: Turn relay_8 on...");
  } else {
    digitalWrite(RELAY_PIN8, LOW);
    Serial.println("INFO: Turn relay_8 off...");
  }
}
// function called when a MQTT message arrived
void callback(char* p_topic, byte* p_payload, unsigned int p_length) {
  // concat the payload into a string
  String payload;
  for (uint8_t i = 0; i < p_length; i++) {
    payload.concat((char)p_payload[i]);
  }

  // handle message topic
  if (String(MQTT_LIGHT_COMMAND_TOPIC1).equals(p_topic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(RELAY_ON))) {
      if (m_relay_state1 != true) {
        m_relay_state1 = true;
        setRelayState1();
        publishRelayState1();
      }
    } else if (payload.equals(String(RELAY_OFF))) {
      if (m_relay_state1 != false) {
        m_relay_state1 = false;
        setRelayState1();
        publishRelayState1();
      }
    }
  }


  // handle message topic
  if (String(MQTT_LIGHT_COMMAND_TOPIC2).equals(p_topic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(RELAY_ON))) {
      if (m_relay_state2 != true) {
        m_relay_state2 = true;
        setRelayState2();
        publishRelayState2();
      }
    } else if (payload.equals(String(RELAY_OFF))) {
      if (m_relay_state2 != false) {
        m_relay_state2 = false;
        setRelayState2();
        publishRelayState2();
      }
    }
  }

  // handle message topic
  if (String(MQTT_LIGHT_COMMAND_TOPIC3).equals(p_topic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(RELAY_ON))) {
      if (m_relay_state3 != true) {
        m_relay_state3 = true;
        setRelayState3();
        publishRelayState3();
      }
    } else if (payload.equals(String(RELAY_OFF))) {
      if (m_relay_state3 != false) {
        m_relay_state3 = false;
        setRelayState3();
        publishRelayState3();
      }
    }
  }

  // handle message topic
  if (String(MQTT_LIGHT_COMMAND_TOPIC4).equals(p_topic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(RELAY_ON))) {
      if (m_relay_state4 != true) {
        m_relay_state4 = true;
        setRelayState4();
        publishRelayState4();
      }
    } else if (payload.equals(String(RELAY_OFF))) {
      if (m_relay_state4 != false) {
        m_relay_state4 = false;
        setRelayState4();
        publishRelayState4();
      }
    }
  }


  // handle message topic
  if (String(MQTT_LIGHT_COMMAND_TOPIC5).equals(p_topic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(RELAY_ON))) {
      if (m_relay_state5 != true) {
        m_relay_state5 = true;
        setRelayState5();
        publishRelayState5();
      }
    } else if (payload.equals(String(RELAY_OFF))) {
      if (m_relay_state5 != false) {
        m_relay_state5 = false;
        setRelayState5();
        publishRelayState5();
      }
    }
  }


  // handle message topic
  if (String(MQTT_LIGHT_COMMAND_TOPIC6).equals(p_topic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(RELAY_ON))) {
      if (m_relay_state6 != true) {
        m_relay_state6 = true;
        setRelayState6();
        publishRelayState6();
      }
    } else if (payload.equals(String(RELAY_OFF))) {
      if (m_relay_state6 != false) {
        m_relay_state6 = false;
        setRelayState6();
        publishRelayState6();
      }
    }
  }


  // handle message topic
  if (String(MQTT_LIGHT_COMMAND_TOPIC7).equals(p_topic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(RELAY_ON))) {
      if (m_relay_state7 != true) {
        m_relay_state7 = true;
        setRelayState7();
        publishRelayState7();
      }
    } else if (payload.equals(String(RELAY_OFF))) {
      if (m_relay_state7 != false) {
        m_relay_state7 = false;
        setRelayState7();
        publishRelayState7();
      }
    }
  }


  // handle message topic
  if (String(MQTT_LIGHT_COMMAND_TOPIC8).equals(p_topic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(RELAY_ON))) {
      if (m_relay_state8 != true) {
        m_relay_state8 = true;
        setRelayState8();
        publishRelayState8();
      }
    } else if (payload.equals(String(RELAY_OFF))) {
      if (m_relay_state8 != false) {
        m_relay_state8 = false;
        setRelayState8();
        publishRelayState8();
      }
    }
  }
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("INFO: Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("INFO: connected");
      // Once connected, publish an announcement...
      publishRelayState1();
      publishRelayState2();
      publishRelayState3();
      publishRelayState4();
      publishRelayState5();
      publishRelayState6();
      publishRelayState7();
      publishRelayState8();

      // ... and resubscribe
      client.subscribe(MQTT_LIGHT_COMMAND_TOPIC1);
      client.subscribe(MQTT_LIGHT_COMMAND_TOPIC2);
      client.subscribe(MQTT_LIGHT_COMMAND_TOPIC3);
      client.subscribe(MQTT_LIGHT_COMMAND_TOPIC4);
      client.subscribe(MQTT_LIGHT_COMMAND_TOPIC5);
      client.subscribe(MQTT_LIGHT_COMMAND_TOPIC6);
      client.subscribe(MQTT_LIGHT_COMMAND_TOPIC7);
      client.subscribe(MQTT_LIGHT_COMMAND_TOPIC8);
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

  // init the led
  pinMode(RELAY_PIN1, OUTPUT);
  setRelayState1();
  pinMode(RELAY_PIN2, OUTPUT);
  setRelayState2();
  pinMode(RELAY_PIN3, OUTPUT);
  setRelayState3();
  pinMode(RELAY_PIN4, OUTPUT);
  setRelayState4();
  pinMode(RELAY_PIN5, OUTPUT);
  setRelayState5();
  pinMode(RELAY_PIN6, OUTPUT);
  setRelayState6();
  pinMode(RELAY_PIN7, OUTPUT);
  setRelayState7();
  pinMode(RELAY_PIN8, OUTPUT);
  setRelayState8();

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
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
