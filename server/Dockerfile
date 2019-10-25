FROM ubuntu:16.04

RUN apt-get update -y
RUN apt-get install -y python3-pip
RUN apt-get install -y python3

RUN pip3 install flask
RUN pip3 install tinydb

WORKDIR /server

COPY . /server

ENTRYPOINT [ "python3" ]

CMD [ "server.py" ]