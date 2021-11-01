/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018

// by Donald Christensen

  pins i need 
  D12 - up
  D14 - down
  D27 - left
  D26 - right
  D25 - forward
  D33 - backward
  D32 - clockwise
  D35 - counterclockwise
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#define u 12 
#define d 14 
#define l 27 
#define r 26 
#define f 25 
#define b 33 
#define w 32 
#define cc 35 
              

// Set these to your desired credentials.
const char *ssid = "debo";
const char *password = "devonbutler";

WiFiServer server(80);


void setup() {
  pinMode(u, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(l, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(w, OUTPUT);
  pinMode(cc, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<h1>Welcome to Devon's quad control page</h1><br>"); 
            client.print("<button><a href=\"/U\">up</a></button><br>");
            client.print("<button><a href=\"/D\">down</a></button><br>");
            client.print("<button><a href=\"/L\">left</a></button><br>");
            client.print("<button><a href=\"/R\">right</a></button><br>");
            client.print("<button><a href=\"/F\">forward</a></button><br>");
            client.print("<button><a href=\"/B\">backward</a></button><br>");
            client.print("<button><a href=\"/W\">clockwise</a></button><br>");
            client.print("<button><a href=\"/CC\">counterclockwise</a></button><br>");
            client.print("<button><a href=\"/S\">STOP</a></button><br>");


 
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
         if (currentLine.endsWith("GET /U")) {
          up();
        }
         if (currentLine.endsWith("GET /D")) {
          down();
        }
         if (currentLine.endsWith("GET /L")) {
         left();
        }
         if (currentLine.endsWith("GET /R")) {
         right();
        }
         if (currentLine.endsWith("GET /F")) {
          forward();
        }
         if (currentLine.endsWith("GET /B")) {
          backward();
        }
         if (currentLine.endsWith("GET /W")) {
          clockwise();
        }
         if (currentLine.endsWith("GET /CC")) {
         //counterclockwise();  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!this is wrong
          counterClock();   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! i added the correct function
        }
        if (currentLine.endsWith("GET /S")) {
         allStop();
        }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
}
}     //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!added this missing bracket
void up() {
  digitalWrite(u, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(l, LOW);
  digitalWrite(r, LOW);
  digitalWrite(f, LOW);
  digitalWrite(b, LOW);
  digitalWrite(w, LOW);
  digitalWrite(cc, LOW);
}

void down() {
  digitalWrite(u, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(l, LOW);
  digitalWrite(r, LOW);
  digitalWrite(f, LOW);
  digitalWrite(b, LOW);
  digitalWrite(w, LOW);
  digitalWrite(cc, LOW);
}

void left() {
  digitalWrite(u, LOW);
  digitalWrite(d, LOW);
  digitalWrite(l, HIGH);
  digitalWrite(r, LOW);
  digitalWrite(f, LOW);
  digitalWrite(b, LOW);
  digitalWrite(w, LOW);
  digitalWrite(cc, LOW);
}

void right() {
  digitalWrite(u, LOW);
  digitalWrite(d, LOW);
  digitalWrite(l, LOW);
  digitalWrite(r, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(b, LOW);
  digitalWrite(w, LOW);
  digitalWrite(cc, LOW);
}

void forward() {
  digitalWrite(u, LOW);
  digitalWrite(d, LOW);
  digitalWrite(l, LOW);
  digitalWrite(r, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(w, LOW);
  digitalWrite(cc, LOW);
}

void backward() {
  digitalWrite(u, LOW);
  digitalWrite(d, LOW);
  digitalWrite(l, LOW);
  digitalWrite(r, LOW);
  digitalWrite(f, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(w, LOW);
  digitalWrite(cc, LOW);
}

void clockwise() {
  digitalWrite(u, LOW);
  digitalWrite(d, LOW);
  digitalWrite(l, LOW);
  digitalWrite(r, LOW);
  digitalWrite(f, LOW);
  digitalWrite(b, LOW);
  digitalWrite(w, HIGH);
  digitalWrite(cc, LOW);
}

void counterClock() {
  digitalWrite(u, LOW);
  digitalWrite(d, LOW);
  digitalWrite(l, LOW);
  digitalWrite(r, LOW);
  digitalWrite(f, LOW);
  digitalWrite(b, LOW);
  digitalWrite(w, LOW);
  digitalWrite(cc, HIGH);
}

void allStop() {
  digitalWrite(u, LOW);
  digitalWrite(d, LOW);
  digitalWrite(l, LOW);
  digitalWrite(r, LOW);
  digitalWrite(f, LOW);
  digitalWrite(b, LOW);
  digitalWrite(w, LOW);
  digitalWrite(cc, LOW);
}
 
