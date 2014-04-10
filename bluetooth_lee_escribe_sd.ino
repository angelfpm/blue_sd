/*
  SD card read
 
 This example shows how to read and write data to and from an SD card file 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 **hc-06 al rx tx pines 0 y 1
lee el contenido de TEST.TXT y lo pasa por bluetooth
al pulsar la L   

*/
#include <SD.h>
File myFile;

void setup()
{
  //Pin donde conectamos el led para ver el correcto funcionamiento del modulo
   pinMode(13,OUTPUT);
   // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.print("Initializing SD card...");
   pinMode(10, OUTPUT);   
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;  }
  Serial.println("initialization done.");  

  myFile = SD.open("test.txt", FILE_WRITE); 
 
   
}
  
void loop()
{
   //Mientras el puerto serie del modulo bluetooth esta disponible
   while (Serial.available())
   {
      //Guardamos en la variable dato el valor leido por el modulo bluetooth
       char dato= Serial.read();
       //Comprobamos el dato
       switch(dato)
       {
         //Si recibimos una 'w' encendemos el led 13 y enviamos para mostrar
         //en Blueterm Led encendido
         case 'w':
         {
           char texto=Serial.read();
           
           digitalWrite(13,HIGH);
           Serial.println("Led encendido");
           if (myFile) {
           Serial.print("Writing to test.txt...");
           myFile.println(texto);
	   // close the file:
           myFile.close();
           Serial.println("done.");
           } else {
           // if the file didn't open, print an error:
           Serial.println("error opening test.txt");
           }
           
           
           
           break;
           
         }
         //Si recibimos una 'e' apagamos el led 13 y enviamos para mostrar
         //en Blueterm Led apagado
         case 'e':
         {
           digitalWrite(13,LOW);
           Serial.println("Led apagado");
           break;
         }
         //Si recibimos una 'r' tiene que leer el ficher de la SD
        
         case 'r':
         {
           //luz intermitente
           digitalWrite(13,HIGH);
           delay(200);
           digitalWrite(13,LOW);
           delay(200);
           digitalWrite(13,HIGH);
           delay(100);
           digitalWrite(13,LOW);
           delay(100);

           
  // re-open the file for reading:
  Serial.println("ahora abrimos el fichero");
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
    	Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
  	// if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  //fin de abrir fichero
           
           
           break;//cerramos la lectura
         }
       }       
   }
}
