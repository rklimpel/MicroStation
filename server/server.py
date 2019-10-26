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
    db.close()

    return "Data saved."

@app.route('/fuckgivemethisshit',methods=['GET'])
def get_temperature():
        return "<meta http-equiv=\"refresh\" content=\"5\">"+lastTemperature

if __name__ == '__main__':
    app.run(debug=False, host='0.0.0.0')