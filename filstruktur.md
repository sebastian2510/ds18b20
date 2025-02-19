### /src
_____

#### main.cpp  
denne fil håndtere loading af div. moduler og kalde funktioner til at sende & gemme værdier.

#### APService.(h/cpp)
* .h: Indeholder funktionsforskrifter men uden funktionalitet.
* .cpp: Indeholder funktionalitet ift. at lave access point, tilslutte et wifi samt at resette indstillinger.

#### FileManager.(h/cpp)
* .h: Indeholder funktionsforskrifter men uden funktionalitet.
* .cpp: Indeholder diverse funktioner til at gemme, læse og konvertere data til/fra json/WeatherData.

#### Models/WeatherData.h
* .h: Indeholder data klassen, properties, constructors samt getters & setters.

#### SensorService.(h/cpp)
* .h: Indeholder funktionsforskrifter men uden funktionalitet.
* .cpp: Registrere temperaturmåleren og sætter den op.

#### NTPService.(h/cpp)
* .h: Indeholder funktionsforskrifter men uden funktionalitet.
* .cpp: Kalder ntp api'en for at finde ud af klokkeslæt.

#### Pages.(h/cpp)
* .h: Indeholder global/statisk variabel.
* .cpp: Sætter værdien i den globale variabel til at være en parsed html hjemmeside.

#### WebServerService.(h/cpp)
* .h: Indeholder funktionsforskrifter men uden funktionalitet.
* .cpp: Opstarter webserveren med div. endpoints til forskellige funktionaliteter og sider fra Pages, samt opstarter websocketen


#### WebSocketService.(h/cpp)
* .h: Indeholder funktionsforskrifter men uden funktionalitet.
* .cpp: Opstarter websocketen for at data kan modtages af en klient som der lytter med.