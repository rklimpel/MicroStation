docker build -t microstation-server:latest .
docker rm -f $(docker ps -a -q)
#docker rm $(docker stop $(docker ps -a -q --filter ancestor=microstation-server --format="{{.ID}}"))
docker run --name microstation-server -p 5000:5000 microstation-server