#include <ESP8266WiFi.h> 
#include <ThingerESP8266.h>
#include <DHT.h>

// KONFIGURASI AWAL

#define USERNAME "Laden" //Username thinger.io
#define DEVICE_ID "praktikum_03" // Lihat pada setting dari device yang sudah dibuat di thinger.io
#define DEVICE_CREDENTIAL "jjh1aF-ty?J6$hQT" // Lihat pada setting dari device yang sudah dibuat di thinger.io (Generate random saja)

#define SSID "KazuyoSan" //Hotspot yang kita pakai
#define SSID_PASSWORD "akuajayangtau"

#define DHTPIN D4 //Pin data dari DHT terhubung ke pin D4 NodeMCU
#define LEDPIN D8 //Kaki anoda dari LED terhubung ke pin D8 NodeMCU
#define DHTTYPE DHT11 //Mengatur TYPE DHT (Karena ada 2 jenis [DHT11 & DHT22])

// Inisialisasi objek untuk terhubung ke Thinger.io
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

// Inisialisasi objek untuk DHT11
DHT dht(DHTPIN, DHTTYPE);

// Variabel untuk menyimpan data suhu dan kelembaban
float suhu, kelembaban;

void setup() {
    pinMode(LEDPIN, OUTPUT);
    dht.begin();
    thing.add_wifi(SSID, SSID_PASSWORD);
    // digital pin control
    thing["led"] << digitalPin(LEDPIN);
    // Setup sensor DHT11
    thing["dht11"] >> [](pson& out){
      out["kelembaban"] = kelembaban;
      out["suhu"] = suhu;
    };
}

void loop() {
    thing.handle();
    float h = dht.readHumidity(); //Membaca kelembaban
    float c = dht.readTemperature(); //Membaca suhu dalam satuan Celcius

    kelembaban = h; // Update nilai kelembaban
    suhu = c; // Update nilai suhu
}