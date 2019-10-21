# Microstation Server

### How to run Server with docker?

**Installation of docker is requiered (https://docs.docker.com/install/).**


build docker image:
```sh
docker build -t microstation-server:latest .
```


run docker image (you may want to stop old instance before starting):
```sh
docker stop microstation-server
docker run -d -p 5000:5000 microstation-server --name microstation-server
```
