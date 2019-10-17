from flask import Flask,escape,request
app = Flask(__name__)

@app.route('/')
def hello_microstation():
    name = request.args.get("name","")
    if(name is ""):
        return "hello unkown microstation user."
    else:
        return 'hello, ' + name + '. \nwelcome at microstation server.'
    