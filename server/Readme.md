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
