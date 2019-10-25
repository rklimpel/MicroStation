# Microstation Server

### How to run Server?

start server for local usage with:
```bash
> export FLASK_APP=server.py
> flask run
```

start server for external usage with:
```bash
> export FLASK_APP=server.py
> flask run --host=0.0.0.0
```

### How to run Server with docker?

**Installation of docker is requiered (https://docs.docker.com/install/).**


build docker image:
```sh
docker build -t microstation-server:latest .
```


run docker image with the provided shell script:
```sh
./run-server.sh
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
docker build -t microstation-server:latest .
./run-server.sh
```

server should be available now on pi's ip and port 5000
