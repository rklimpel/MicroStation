# Wifi Controller Serial Commands

### General Command Scheme:

1. Command start and end with a '$' symbol
2. First string after the starting '$' symbol is the command itself
3. Arguments will be added in the following style: &ARG_NAME=argdata

Sample:
`$CONNECT&SSID=MyWlanSSID&PW=MyWiFiPassword$`

---

#### Test Request

`CMD:` TEST

`ARGs:` NAME

#### Wifi Verbindung herstellen

`CMD:` CONNECT

`ARGs:` SSID, PW
