docker rm $(docker stop $(docker ps -a -q --filter ancestor=microstation-server --format="{{.ID}}"))
docker run -d --name microstation-server -p 5000:5000 microstation-server