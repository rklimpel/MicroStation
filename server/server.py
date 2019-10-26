import os
from flask import Flask,escape,request, render_template
from tinydb import TinyDB, Query

app = Flask(__name__)

lastTemperature="-1.0"

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

if __name__ == '__main__':
    app.run(debug=False, host='0.0.0.0')