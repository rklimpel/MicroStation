# MicroStation

### Run Server

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

### Run Microcontroller Code

requirements:
- Visual Studio Code with installed 'platformio-ide' Extension

steps:
- open project root folder is visual studio code
- platformio should index the project so you can build and upload via statusbar icons
