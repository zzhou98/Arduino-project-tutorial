void loop()  {
  sd_file = SD.open("data.txt", FILE_WRITE);    // Reopen the file in write mode
  if (sd_file)  {          // If the file opened successfully, call senddata function
    senddata();
  }
  else  {                 // if the file didn't open, print an error:
    Serial.println("error opening file");
  }
  delay(1000);            // Delay for a second before next iteration
}

void senddata()  {
  // Loop to collect data every 2 seconds for a minute
  for(long seconds = 00; seconds < 60; seconds=seconds+2)  {
    float temp = dht.readTemperature(); //Reading the temperature as Celsius and storing in temp
    float hum = dht.readHumidity();     //Reading the humidity and storing in hum
    float fah = dht.readTemperature(true); // Read temperature in Fahrenheit and store in fah
    float heat_index = dht.computeHeatIndex(fah, hum);

    sd_file.print(hours);               // Write data to the SD file sd_file.print(hours);
    sd_file.print(":");
    sd_file.print(minutes);
    sd_file.print(":");
    sd_file.print(seconds);
    sd_file.print(",  ");
    sd_file.print(hum);
    sd_file.print(",    ");
    sd_file.print(temp);
    sd_file.print(",      ");
    sd_file.print(fah);
    sd_file.print(",      ");
    sd_file.println(heat_index);

    Serial.print(hours);               // Also print the same data to the serial monitor
    Serial.print(":");
    Serial.print(minutes);
    Serial.print(":");
    Serial.print(seconds);
    Serial.print(",  ");
    Serial.print(hum);
    Serial.print(",    ");
    Serial.print(temp);
    Serial.print(",       ");
    Serial.print(fah);
    Serial.print(",      ");
    Serial.println(heat_index);

    if(seconds>=58)  {                 // Update the minute every 60 seconds
      minutes= minutes + 1;
    }

    if (minutes>59)  {                 // Reset minutes and increment hours after 59 minutes
      hours = hours + 1;
      minutes = 0;
    }

    sd_file.flush(); //saving the file

    delay(2000);
  }
  sd_file.close();   //closing the file
}
