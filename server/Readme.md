# Microstation Server

### How to run Server?

Always remember: There is a better option - running the server in docker.

start server with:
```bash
> python3 server.py
```

### How to run Server with docker?

**Installation of docker is requiered (https://docs.docker.com/install/).**


run server with docker compose:
```sh
docker-compose up -d
```

restarting running server:
```sh
docker compose restart
```

stop server with docker compose:
```sh
docker-compose down
```

run server in foreground with output:
```sh
docker-compse up
```


### How to deploy server to raspberry?

preconditions:
- Raspberry connect to Network
- SSH enabled on Raspberry

maybe you want to find raspberry in wifi network with namp (don't forget to enter the correct ip for your network):
```sh
sudo nmap -sS -p 22 192.168.178.0/24
```

now connect to pi with SSH.

check if docker is installed on pi:
```sh
docker --version
```

install docker:
```sh
curl -sSL https://get.docker.com | sh
```

clone this git repo to your pi, build docker image and run server with script:
```sh
git clone https://github.com/rklimpel/MicroStation.git
cd MicroStation/server
docker-compose up -d
```

server should be available now on pi's ip and port 5000


### Tell me more about the Microstation API!


#### upload a new temperature value:

`POST` to `<host>/api/v1.0/temperatures`

Body should look something like this:
```json
{
  "value":30.4,
  "station_id":0,
  "unit": "C",
  "sensor": "HT65XY",
  "timestamp": 6547582342
}
```
