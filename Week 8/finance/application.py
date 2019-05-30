import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # if no symbol
        if not symbol:
            return apology("Please provide a symbol!")

        # get price of the stock.
        price = lookup(symbol)
        if not price:
            return apology("Invalid symbol!")

        # not a positive integer
        if int(shares) < 0:
            return apology("Value must be greater than or equal to 1!")

        # get userId from cookie session
        userId = session["user_id"]

        # get current cash balance of user
        currentCash = db.execute("SELECT cash FROM users WHERE id = :id", id=userId)[0]["cash"]

        # if not enough cash to purchase stocks
        if currentCash < int(shares) * price['price']:
            # return render_template("buy.html", number=shares, symbol=symbol)
            return apology("Not enough funds!")

        # update cash balance of user
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", id=userId, cash=currentCash - (int(shares) * price['price']))

        # get datetime
        dt = '{0:%m-%d-%Y %I:%M:%S %p}'.format(datetime.datetime.now())

        # update database of user tx
        db.execute("INSERT INTO history (id, stock, shares, price, datetime, symbol) VALUES (:id, :stock, :shares, :price, :datetime, :symbol)",
            id=userId, stock=price['name'], shares=int(shares), price=price['price'], datetime=dt, symbol=price['symbol'])

        # redirect to home page
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""
    return jsonify("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # get symbol from input
        symbol = request.form.get("symbol")

        # if no symbol
        if not symbol:
            return apology("Please provide a symbol!")

        # get quote of the stock.
        quote = lookup(symbol)
        if not quote:
            return apology("Invalid symbol!")

        # use helper function to format value in USD
        price = usd(quote["price"])

        return render_template("quote.html", quote=quote, price=price)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # get username
        name = request.form.get("username")

        # check if name field is empty
        if not name:
            return apology("Must provide a username!")

        # see if username is taken
        rows = db.execute("SELECT * FROM users WHERE username = :name", name=name)
        if len(rows) != 0:
            return apology("That username is already taken!")

        # get passwords
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # check passwords
        if not name or not confirmation:
            return apology("Must provide a password!")

        if password != confirmation:
            return apology("Passwords do not match!")

        # hash the password
        hash = generate_password_hash(password)

        # insert new user into database
        db.execute("INSERT INTO users (username, hash) VALUES (:name, :hash)", name=name, hash=hash)

        # find user inside the database
        userInfo = db.execute("SELECT * FROM users WHERE username = :name", name=name)

        # store user in session
        session["user_id"] = userInfo[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
