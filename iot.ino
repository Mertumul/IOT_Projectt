#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const char *WIFI_SSID = "";
const char *WIFI_PASSWORD = "";
const char *URL = "";
const char *URL2 = "";

WiFiClient client;
HTTPClient httpClient;

void wifi_Setup() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("Connected");
}

void send_telegram_message() {
    httpClient.begin(client, URL);
    httpClient.GET();
    String content = httpClient.getString();
    httpClient.end();

    Serial.println(content);
}

void get_weather_info() {
    httpClient.begin(client, URL2);
    httpClient.GET();
    String content = httpClient.getString();
    httpClient.end();
    printWeatherInfo(content);
    Serial.println(content);
}

void printWeatherInfo(String text) {
    lcd.clear(); // Clear the LCD screen

    if (text.length() <= 16) {
        // If the text is 16 characters or less, print it on the first line
        lcd.setCursor(0, 0);
        lcd.print(text);
    } else {
        // If the text is longer than 16 characters, split it between two lines
        lcd.setCursor(0, 0);
        lcd.print(text.substring(0, 16)); // Print the first 16 characters on the first line
        lcd.setCursor(0, 1);
        lcd.print(text.substring(16));    // Print the remaining characters on the second line
    }

    delay(5000); // Display the text for 10 seconds (adjust as needed)
    lcd.clear();  // Clear the LCD screen again
}


void setup() {
    Serial.begin(9600);
    wifi_Setup();
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);  // D2 pinini giriş olarak ayarla
    pinMode(LED_BUILTIN, OUTPUT);

    //Set the lcd display settings
    lcd.begin(16,2);
    lcd.init();
    lcd.backlight();
}

void loop() {
    static bool button1Pressed = false;
    static bool button2Pressed = false;
    byte val1 = digitalRead(D5);
    byte val2 = digitalRead(D6);

    if (val1 == HIGH && !button1Pressed) {
        // Düğme 1 basıldı ve daha önce basılmadı
        digitalWrite(LED_BUILTIN, LOW);
        send_telegram_message();
        button1Pressed = true;
    } else if (val1 == LOW) {
        // Düğme 1 bırakıldı
        digitalWrite(LED_BUILTIN, HIGH);
        button1Pressed = false;
    }

    if (val2 == HIGH && !button2Pressed) {
        // Düğme 2 basıldı ve daha önce basılmadı
        get_weather_info();
        button2Pressed = true;
    } else if (val2 == LOW) {
        // Düğme 2 bırakıldı
        button2Pressed = false;
    }

    delay(100);  // Gürültüyü önlemek için kısa bir gecikme
}
