# Wifi Controller Serial Commands

### General Command Scheme:

1. Command start and end with a '$' symbol
2. First string after the starting '$' symbol is the command itself
3. Arguments will be added in the following style: &ARG_NAME=argdata

Sample:
`$CONNECT&SSID=MyWlanSSID&PW=MyWiFiPassword$`

---

#### Wifi Verbindung herstellen

`CMD:` CONNECT

`ARGs:` SSID, PW

#### Send GET Request

`CMD:` GET-REQUEST

`ARGs:` URL

#### Send POST Request

`CMD:` POST-REQUEST

`ARGs:` URL,BODY
