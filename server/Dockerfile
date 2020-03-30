FROM ubuntu:16.04

RUN apt-get update -y
RUN apt-get install -y python3-pip
RUN apt-get install -y python3
RUN apt-get install -y libpython2.7-stdlib
RUN pip3 install --upgrade pip

RUN pip3 install flask
RUN pip3 install flask-bootstrap4
RUN pip3 install tinydb
RUN pip3 install pytz
#RUN pip3 install json

WORKDIR /server

COPY . /server

ENTRYPOINT [ "python3" ]

CMD [ "server.py" ]