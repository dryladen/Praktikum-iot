
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define BLYNK_AUTH_TOKEN "Cek Device Info yang sudah dibuat"
#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SSID";  // type your wifi name
char pass[] = "PASSWORD";  // type your wifi password

#define LEDPIN D8 //Kaki anoda dari LED terhubung ke pin D8 NodeMCU
#define DHTPIN D4 //Pin data dari DHT terhubung ke pin D4 NodeMCU
#define DHTTYPE DHT11 //Mengatur TYPE DHT (Karena ada 2 jenis [DHT11 & DHT22])

BlynkTimer timer;

DHT dht(DHTPIN, DHTTYPE);

// Untuk kontroling LED
BLYNK_WRITE(V2) { // V2 adalah pin LED yang sudah kita atur pada Blynk
  digitalWrite(LEDPIN, param.asInt()); // Mengubah nilai LED dari Blynk
}

void setup(){
  Serial.begin(115200);
  // Mengatur pin LED
  pinMode(LEDPIN, OUTPUT);
  // Setup Blynk
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  // Setup Sensor DHT 11
  dht.begin();
  // Fungsi mengirim data setiap 2,5 detik
  timer.setInterval(2500L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}

void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Mengecek kondisi apakah DHT bisa dibaca atau tidak
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Mengatur nilai suhu ke pin V0(Suhu) yang sudah diatur pada Blynk
  Blynk.virtualWrite(V0, t);
  // Mengatur nilai kelembaban ke pin V1(Kelembaban) yang sudah diatur pada Blynk
  Blynk.virtualWrite(V1, h);
  
  // Menampilkan ke serial monitor
  Serial.print("Suhu : ");
  Serial.print(t);
  Serial.print("|| Kelembapan : ");
  Serial.println(h);
  // Event log
  if(t > 30){
    Blynk.logEvent("notifikasi","Suhu diatas 30 Derajat celcius");
  }
}