# Wifi Controller Serial Commands

### General Command Scheme:

1. Command start and end with a '$' symbol
2. First string after the starting '$' symbol is the command itself
3. Arguments will be added in the following style: &ARG_NAME=argdata

---

#### Wifi Verbindung herstellen

`CMD:` CONNECT

`ARGs:` SSID, PW

Sample:
`$CONNECT&SSID=MyWlanSSID&PW=MyWiFiPassword$`

#### Send GET Request

`CMD:` GET-REQUEST

`ARGs:` URL

Sample:
`$HTTP-GET&SURL=http://localhost:5000/?name=Heino$`

#### Send POST Request

`CMD:` POST-REQUEST

`ARGs:` URL, BODY


Sample:
`$HTTP-POST&SURL=http://localhost:5000/someMorePath&BODY=requestBodyStuff$`
