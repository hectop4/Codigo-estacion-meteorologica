#include <Wire.h>               //Comunicacion I2C
#include <LiquidCrystal_I2C.h>  //Comunicacion Pantalla I2C

//Librerias Presion/Temperatura(Inicio)
#include <Adafruit_BMP085.h>          //Sensor de temperatura y presion
#define seaLevelPressure_hPa 1013.25  //Presion al nivel del mar
//Libreria Presion/Temperatura(Fin)
float t;
//Dht11 Temperatura 2(Inicio)
#include <dht.h>
#define DHT11_PIN 13
dht DHT;
int menu;
//Dht11 Temperatura 2(fin)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Pantalla LCD
float temp;
float Celcius;


Adafruit_BMP085 bmp;

//Variables Direccion del viento (Inicio)

int direc = 5;
int direc1 = 6;
int direc2 = 7;
int direc3 = 8;
int direc4 = 9;
int direc5 = 10;
int direc6 = 11;
String direccion;
//Variables Direccion del viento (Fin)

//VARIABLES ANEMOMETRO(INICIO)
int contador = 0;
unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 1L * 1000L;
float veltan;
//VARIABLES ANEMOMETRO(FIN)

//Variables pluviometro
int contador1 = 0;
unsigned long lastConnectionTime1 = 0;
const unsigned long postingInterval1 = 1L * 1000L;
void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(direc, INPUT);
  pinMode(direc1, INPUT);
  pinMode(direc2, INPUT);
  pinMode(direc3, INPUT);  //Direccion del viento
  pinMode(direc4, INPUT);
  pinMode(direc5, INPUT);
  pinMode(direc6, INPUT);
  pinMode(2, INPUT_PULLUP);  //Anemometro
  pinMode(3, INPUT_PULLUP);  //Pluviometro
  Serial.begin(9600);
  attachInterrupt(0, Zero_Cross, FALLING);


  attachInterrupt(1, Zero_Cross1, FALLING);
  //Inicializador Presino/Temperatura (Inicion)
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");  //Verificacion BMP085
    while (1) {}
  }
  //Inicializador presion(Fin)
}

void loop() {
  temp = (bmp.readTemperature() + Celcius) / 2;

  //CODIGO ANEMOMETRO(INICIO)
  if (millis() - lastConnectionTime > postingInterval) {


    lastConnectionTime = millis();
    Serial.print("Velocidad: ");
    veltan = (2 * 3.141592) * (contador / 2) * (0.104);
    lcd.setCursor(0, 0);
lcd.print("Velocidad viento:         ");
lcd.setCursor(0, 1);
lcd.print("                               ");
lcd.setCursor(0, 1);
lcd.print((veltan/16));
lcd.setCursor(5, 1);
lcd.print("m/s");
delay(3000);


    contador = 0;
  }
  

  //Codigo pluviometro(Inicio)
  if (millis() - lastConnectionTime1 > postingInterval1) {

    Serial.print("Pluviometro: ");
    Serial.print("=");
    Serial.print(contador1 / 2);
    Serial.print(" ");
    Serial.println("Hz");
    lastConnectionTime1 = millis();

    contador1 = 0;
  }
  //Codigo pluviometro(Inicio)


  //Codigo temperatura 1(Inicio)
  int Value = analogRead(A0);
  float Voltaje = (Value * 5) / 1023.0;
  Celcius = Voltaje * 100;
  // Serial.print(Celcius);
  // Serial.println(" C");


  //Codigo temperatura 1(Fin)

  //Codigo Presion/Temperatura(Inicio)
  // Serial.println(bmp.readTemperature());  //Imprimir en pantalla valores de Bmp
  // Serial.println(bmp.readPressure());     //Imprimir en pantalla valores de Bmp
  //Codigo Presion/Temperatura(Fin)

  //Codigo Direccion del viento (Inicio)
  int lec2 = digitalRead(direc1);
  int lec1 = digitalRead(direc);
  int lec3 = digitalRead(direc2);
  int lec4 = digitalRead(direc3);
  int lec5 = digitalRead(direc4);
  int lec6 = digitalRead(direc5);
  int lec7 = digitalRead(direc6);
  int lec8 = digitalRead(A2);

  if (lec7 == 1) {
    direccion = "Norte";
    Serial.println(direccion);
  } else if (lec2 == 1) {
    direccion = "Noroeste";
    Serial.println(direccion);
  } else if (lec3 == 1) {
    direccion = "Oeste";
    Serial.println(direccion);
  } else if (lec8 == 1) {
    direccion = "Suroeste";
    Serial.println(direccion);
  } else if (lec5 == 1) {
    direccion = "Sur";
    Serial.println(direccion);
  } else if (lec6 == 1) {
    direccion = "Sureste";
    Serial.println(direccion);
  } else {
    direccion = "Este";
    Serial.println(direccion);
  }
  //Codigo Direccion del viento(Fin)
  //Codigo Radiacion Solar (Inicio);
  int panel = analogRead(A1);
  float Radiacion = ((panel * 10) / 1023.0)*10;

  // Serial.print(Radiacion);
  // Serial.println(" IRUV");

  //Codigo Radiacion Solar(Fin)

  //Codigo temperatura 2 (INicio)
  // Serial.println(DHT.temperature);
  // delay(1000);
  //Codigo temperatura 2 (Fin)


  //Promedio Temperatura
  temp=(bmp.readTemperature()+Celcius)/2;

  

lcd.setCursor(0, 0);
lcd.print("Velocidad viento:         ");
lcd.setCursor(0, 1);
lcd.print("                               ");
lcd.setCursor(0, 1);
lcd.print(veltan/10);
lcd.setCursor(5, 1);
lcd.print("m/s");
delay(3000);




lcd.setCursor(0, 0);
lcd.print("Temperatura:          ");
lcd.setCursor(0, 1);
lcd.print("                               ");
lcd.setCursor(0, 1);
lcd.print(temp);
lcd.setCursor(5, 1);
lcd.print("C");
delay(3000);

lcd.setCursor(0, 0);
lcd.print("Pluviometro:              ");
lcd.setCursor(0, 1);
lcd.print("                               ");
lcd.setCursor(0, 1);
lcd.print(contador1 );
lcd.setCursor(5, 1);
lcd.print("mm De agua");
delay(3000);
lcd.setCursor(0, 0);
lcd.print("Direccion viento:       ");
lcd.setCursor(0, 1);
lcd.print("                               ");
lcd.setCursor(0, 1);
lcd.print(direccion);
delay(3000);
lcd.setCursor(0, 0);
lcd.print("Presion:         ");
lcd.setCursor(0, 1);
lcd.print("                               ");
lcd.setCursor(0, 1);
lcd.print(bmp.readPressure());
lcd.setCursor(8, 1);
lcd.print("bares");
delay(3000);
lcd.setCursor(0, 0);
lcd.print("Humedad:         ");
lcd.setCursor(0, 1);
lcd.print("                               ");
lcd.setCursor(0, 1);
lcd.print(DHT.humidity);
delay(3000);
lcd.setCursor(0, 0);
lcd.print("Luminosidad:         ");
lcd.setCursor(0, 1);
lcd.print("                               ");
lcd.setCursor(0, 1);
lcd.print(Radiacion);
lcd.setCursor(8, 1);
lcd.print("  %");
delay(3000);



}


void Zero_Cross()  // FUnción que se activa cada vez que se detecta un cero en el pin 2
{
  contador++;
}
void Zero_Cross1()  // FUnción que se activa cada vez que se detecta un cero en el pin 2
{
  contador1++;
}



