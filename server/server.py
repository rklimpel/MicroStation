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

@app.route('/viewdata',methods=['GET'])
def view_temperature():
    db = TinyDB('./appdata/station_0.json', indent=4)
    data = db.table('temperature').all()
    return render_template('listview.html', data=data)

# ------------------------------------------------------

@app.route('/api/v1.0/temperatures',methods=['POST'])
def post_temperature():
    print("uploading temperature...")

    print(request)

    if not request.is_json:
        return 'ERROR'

    body = request.get_json()
    print("this worked!")

    print("body:\n\n" + json.dumps(body) + "\n\n")

    value = body['value']
    unit = body['unit']
    timestamp = body['timestamp']
    station_id = body['station_id']
    sensor = body['sensor']

    if not os.path.exists('./appdata/'):
        os.makedirs('./appdata/')

    db = TinyDB('./appdata/station_'+str(station_id)+'.json', indent=4)
    table = db.table('temperature')
    table.insert({
        'timestamp': timestamp, 
        'value': value,
        'unit': unit,
        'sensor': sensor
        })

    print("Saved Temperature to database.")

    db.close()

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


