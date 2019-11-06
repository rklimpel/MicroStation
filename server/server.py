import os
import json
import time
from flask import Flask,escape,request, render_template
from tinydb import TinyDB, Query

app = Flask(__name__)

@app.route('/')
@app.route('/index')
def index():
    name = request.args.get("name","")
    title = "Microstation Server"
    if(name is ""):
        name = "Unkown User"
    return render_template('index.html', title=title, name=name)
    
@app.route('/api/v1/temperature',methods=['POST'])
def log_temperature():

    if not request.is_json:
        return 'ERROR'

    body = request.get_json()
    temperatureValue = body['temperature_value']
    timestamp = body['timestamp']
    stationId = body['station_id']

    if not os.path.exists('./appdata/'):
        os.makedirs('./appdata/')

    db = TinyDB('./appdata/station_'+str(stationId)+'.json', indent=4)
    db.insert({'timestamp': timestamp, 'temperature_value': temperatureValue})
    print("Saved Temperature to database:\ntemperature_value: '" + str(temperatureValue)+"'\ntimestamp: '"+str(timestamp)+"'")

    db.close()

    return "Data saved."

@app.route('/viewdata',methods=['GET'])
def get_temperature():
    db = TinyDB('./appdata/station_0.json', indent=4)
    data = db.all()
    return render_template('listview.html', data=data)

# ------------------------------------------------------

@app.route('/api/v1.0/temperatures',methods=['POST'])
def post_temperature():
    print("uploading temperature...")
    return "OK"

@app.route('/api/v1.0/temperatures',methods=['GET'])
def get_all_temperatures():
    print("get all temperatures...")
    return "OK"

@app.route('/api/v1.0/temperatures/<int:station_id>',methods=['GET'])
def get_station_temperature(station_id):
    print("get all temperatures form server " + station_id + "...")
    return "OK"

@app.route('/api/v1.0/humidities',methods=['POST'])
def post_humidity():
    print("uploading humidty...")
    return "OK"

@app.route('/api/v1.0/humidities',methods=['GET'])
def get_all_humidities():
    print("get all temperatures...")
    return "OK"

@app.route('/api/v1.0/temperatures/<int:station_id>',methods=['GET'])
def get_station_humidity(station_id):
    print("get all temperatures form server " + station_id + "...")
    return "OK"

@app.route('/api/v1.0/stations',methods=['GET'])
def get_all_stations():
    print(("get all stations..."))
    return "OK"

@app.route('/api/v1.0/stations/register',methods=['POST'])
def register_station():
    print("register new station...")
    return "OK"

@app.route('/api/v1.0/status',methods=['GET'])
def get_status():
    print("get server status...")

    status = {
        "status": "OK",
        "timestamp": int(time.time()),
        "api_links": {
            "humidities": request.host_url + "api/v1.0/humidities",
            "temperatures": request.host_url + "api/v1.0/temperatures",
            "stations": request.host_url + "api/v1.0/stations"
        }
    }

    return json.dumps(status)

if __name__ == '__main__':
    app.run(debug=False, host='0.0.0.0')


