from flask import Flask,escape,request
app = Flask(__name__)

lastTemperature="Rudolf"

@app.route('/')
def hello_microstation():
    name = request.args.get("name","")
    if(name is ""):
        return "hello unkown microstation user."
    else:
        return 'hello, ' + name + '. \nwelcome at microstation server.'
    
@app.route('/api/temperature',methods=['POST','GET'])
def log_temperature():
    value = request.args.get("value","")
    if(value is ""):
        return "ERROR"
    else:
        global lastTemperature
        lastTemperature = value
        return lastTemperature

@app.route('/fuckgivemethisshit',methods=['GET'])
def get_temperature():
        return "<meta http-equiv=\"refresh\" content=\"5\">"+lastTemperature
