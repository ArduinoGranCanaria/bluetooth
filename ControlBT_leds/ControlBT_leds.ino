/*
  www.diymakers.es
  by A.García
  Arduino + Bluetooth
  Tutorial en: http://diymakers.es/arduino-bluetooth/
*/

#include <SoftwareSerial.h> //Librería que permite establecer comunicación serie en otros pins

//Aquí conectamos los pins RXD,TDX del módulo Bluetooth.
SoftwareSerial BT(10, 11); //10 RX, 11 TX.

int green = 4;
int yellow = 5;
int red = 6;
char cadena[255]; //Creamos un array de caracteres de 256 cposiciones
int i = 0; //Tamaño actual del array

void setup()
{
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
}

void loop()
{
  //Cuando haya datos disponibles
  if (BT.available())
  {
    char dato = BT.read(); //Guarda los datos carácter a carácter en la variable "dato"

    cadena[i++] = dato; //Vamos colocando cada carácter recibido en el array "cadena"

    //Cuando reciba una nueva línea (al pulsar enter en la app) entra en la función
    if (dato == '\n')
    {
      Serial.print(cadena); //Visualizamos el comando recibido en el Monitor Serial

      //GREEN LED
      if (strstr(cadena, "green on") != 0)
      {
        digitalWrite(green, HIGH);
      }
      if (strstr(cadena, "green off") != 0)
      {
        digitalWrite(green, LOW);
      }
      //YELLOW LED
      if (strstr(cadena, "yellow on") != 0)
      {
        digitalWrite(yellow, HIGH);
      }
      if (strstr(cadena, "yellow off") != 0)
      {
        digitalWrite(yellow, LOW);
      }
      //RED LED
      if (strstr(cadena, "red on") != 0)
      {
        digitalWrite(red, HIGH);
      }
      if (strstr(cadena, "red off") != 0)
      {
        digitalWrite(red, LOW);
      }
      //ALL ON
      if (strstr(cadena, "on all") != 0)
      {
        digitalWrite(green, HIGH);
        digitalWrite(yellow, HIGH);
        digitalWrite(red, HIGH);
      }
      //ALL OFF
      if (strstr(cadena, "off all") != 0)
      {
        digitalWrite(green, LOW);
        digitalWrite(yellow, LOW);
        digitalWrite(red, LOW);
      }

      BT.write("\r"); //Enviamos un retorno de carro de la app. La app ya crea una línea nueva
      clean(); //Ejecutamos la función clean() para limpiar el array
    }
  }
}

//Limpia el array
void clean()
{
  for (int cl = 0; cl <= i; cl++)
  {
    cadena[cl] = 0;
  }
  i = 0;
}
