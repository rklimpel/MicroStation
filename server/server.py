from flask import Flask,escape,request, render_template

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

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')