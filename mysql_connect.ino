 /*
 Project: NodeMCU MYSQL Connector
 Link: 
 */
 
 #include <ESP8266WiFi.h>
 #include <WiFiClient.h>
 #include <MySQL_Connection.h>
 #include <MySQL_Cursor.h>
 
 IPAddress server_addr(172,18,0,21);   // IP of the MySQL server
 char user[] = "elbrinke";                     // MySQL user login username
 char password[] = "elbrinke";                 // MySQL user login password
 
 // WiFi card example
 char ssid[] = "Research & Development";                     // your SSID
 char pass[] = "Eddy&Gail";                     // your SSID Password
 
 // Sample query
 char INSERT_SQL[] = "INSERT INTO arduino.data (digital) VALUES ('1')";
 
 WiFiClient client;
 MySQL_Connection conn((Client *)&client);
 
 void setup() {
   Serial.begin(115200);
   
   WiFi.begin(ssid, pass);                      // initializing the WIFI library
 
   while ( WiFi.status() != WL_CONNECTED ) {    // while loop to write dots during connecting
     delay ( 500 );
     Serial.print ( "." );
   }
 
   // print out information about the WIFI connection
   Serial.println ( "" );
   Serial.print ( "Connected to " );
   Serial.println ( ssid );
   Serial.print ( "IP address: " );
   Serial.println ( WiFi.localIP() );
 
   // connecting to the MySQL server
   Serial.println("DB - Connecting...");
   while (conn.connect(server_addr, 3306, user, password) != true) {
     delay(500);
     Serial.print ( "." );
   }
 }
 
 void loop() {
   delay(2000);
 
   Serial.println("Recording data.");
 
   // Initiate the query class instance
   MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
   // Execute the query
   cur_mem->execute(INSERT_SQL);
   // Note: since there are no results, we do not need to read any data
   // Deleting the cursor also frees up memory used
   delete cur_mem;
 }