import os
import json
import time
from flask import Flask,escape,request, render_template
from tinydb import TinyDB, Query
from datetime import datetime, timedelta
import pytz

app = Flask(__name__)

def add_datetime_to_data(data_list):
    data = data_list
    local_tz = pytz.timezone('Europe/Berlin')
    utc_tz = pytz.timezone('utc')
    print(local_tz)
    for d in data:
        dt = datetime.fromtimestamp(d['timestamp'])
        dt = utc_tz.localize(dt)
        dt = dt.astimezone(local_tz)
        d['time'] = dt.time()
        d['date'] = dt.date()

    data.reverse()

    return data

def normalize_data(data_list):
    pass
    

def reduce_data_to_last_hours(data,hours):
    last_hours_date_time = datetime.now() - timedelta(hours = hours)
    result = []
    for d in data:
        dt = datetime.fromtimestamp(d['timestamp'])
        if last_hours_date_time < dt:
            result.append(d)

    return result

# --------------------- Webpages ----------------------------

@app.route('/')
@app.route('/index')
def index():
    db = TinyDB('./appdata/station_0.json', indent=4)
    data = db.table('humidity').all()

    data = add_datetime_to_data(data)
    data = reduce_data_to_last_hours(data,5)
    data.reverse()
    humidity_labels = []
    humidity_values = []
    humidity_now = "0 %"
    last_updated_humidity = "?"
    for d in data:
        if d['sensor'] == 'am2302':
            humidity_labels.append(str(d['date']) + " - " + str(d['time']))
            humidity_values.append(d['value'])
            humidity_now = str(d['value']) + " %"
            last_updated_humidity = "last updated " + str(d['date']) + "  " + str(d['time'])

    humidity_legend = 'Humidity Data'

    data = db.table('temperature').all()

    data = add_datetime_to_data(data)
    data = reduce_data_to_last_hours(data,5)
    data.reverse()
    temperature_labels = []
    temperature_values = []
    temperature_now = "0 °C"
    last_updated_temperature = "?"
    for d in data:
        if d['sensor'] == 'am2302':
            temperature_labels.append(str(d['date']) + " - " + str(d['time']))
            temperature_values.append(d['value'])
            temperature_now = str(d['value']) + " °C"
            last_updated_temperature = "last updated " + str(d['date']) + "  " + str(d['time'])

    temperature_legend = 'Temperature Data'

    return render_template('index.html', 
    humidity_values=humidity_values, humidity_labels=humidity_labels, humidity_legend=humidity_legend,
    temperature_values=temperature_values,temperature_labels=temperature_labels,temperature_legend=temperature_legend,
    temperature_now=temperature_now,last_updated_temperature=last_updated_temperature,
    humidity_now=humidity_now,last_updated_humidity=last_updated_humidity)

@app.route('/rawdata/<table>/<station_id>',methods=['GET'])
def view_rawdata(station_id,table):
    db = TinyDB('./appdata/station_' + str(station_id) + '.json', indent=4)
    data = db.table(table).all()

    data = add_datetime_to_data(data)

    return render_template('listview.html', data=data)

@app.route('/charts')
def view_charts():
    db = TinyDB('./appdata/station_0.json', indent=4)
    data = db.table('humidity').all()

    humidity_labels = []
    humidity_values = []
    for d in data:
        if d['sensor'] == 'am2302':
            humidity_labels.append(d['timestamp'])
            humidity_values.append(d['value'])

    humidity_legend = 'Humidity Data'

    data = db.table('temperature').all()

    temperature_labels = []
    temperature_values = []
    for d in data:
        if d['sensor'] == 'am2302':
            temperature_labels.append(d['timestamp'])
            temperature_values.append(d['value'])

    temperature_legend = 'Temperature Data'

    return render_template('charts.html', 
    humidity_values=humidity_values, humidity_labels=humidity_labels, humidity_legend=humidity_legend,
    temperature_values=temperature_values,temperature_labels=temperature_labels,temperature_legend=temperature_legend)

# ------------------------ API -------------------------------

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

# ===== API:POST

def upload_value(request,table):
    if not request.is_json:
        print("ERROR: request body is not in json format")
        return 'ERROR'
    print("Request data: " + str(request.data))
    body = request.get_json()

    value = body['value']
    unit = body['unit']
    timestamp = body['timestamp']
    station_id = body['station_id']
    sensor = body['sensor']

    if not os.path.exists('./appdata/'):
        os.makedirs('./appdata/')

    db = TinyDB('./appdata/station_'+str(station_id)+'.json', indent=4)
    table = db.table(table)
    table.insert({
        'timestamp': timestamp, 
        'value': value,
        'unit': unit,
        'sensor': sensor
        })

    print("Saved to database.")

    db.close()

@app.route('/api/v1.0/temperatures',methods=['POST'])
def post_temperature():
    print("uploading temperature...")
    upload_value(request,"temperature")
    return "OK"

@app.route('/api/v1.0/humidities',methods=['POST'])
def post_humidity():
    print("uploading humidty...")
    upload_value(request,"humidity")
    return "OK"

# ===== API:GET

@app.route('/api/v1.0/temperatures',methods=['GET'])
def get_all_temperatures():
    print("get all temperatures...")
    return "OK"

@app.route('/api/v1.0/temperatures/<int:station_id>',methods=['GET'])
def get_station_temperature(station_id):
    print("get all temperatures form server " + station_id + "...")
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

    print(request)

    if not request.is_json:
        return 'ERROR'

    body = request.get_json()

    mac_adress = body['mac_adress']

    return "OK"

if __name__ == '__main__':
    app.run(debug=False,use_evalex=False,host='0.0.0.0')