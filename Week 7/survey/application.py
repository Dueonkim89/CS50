import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():
    # send appropriate message based on missing info from req header
    name = request.form.get("name")
    house = request.form.get("house")
    position = request.form.get("position")
    if not name:
        return render_template("error.html", message="You must specify your name!")
    elif not house:
        return render_template("error.html", message="You must specify your house!")
    elif not position:
        return render_template("error.html", message="You must specify your position!")
    
    # write to csv 
    file = open("survey.csv", "a")
    writer = csv.writer(file)
    writer.writerow((name, house, position))
    file.close()
    # redirect to /sheet route
    return redirect("/sheet")


@app.route("/sheet", methods=["GET"])
def get_sheet():
    # extract data from csv file and send as JSON data
    file = open("survey.csv", "r")
    reader = csv.reader(file)
    data = list(reader)
    return render_template("sheet.html", data=data)
