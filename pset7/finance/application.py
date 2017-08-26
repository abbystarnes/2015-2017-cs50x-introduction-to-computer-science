from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
from passlib.context import CryptContext
myctx = CryptContext(schemes=["sha256_crypt", "md5_crypt", "des_crypt"])

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = True
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        def money(number):
            number = number.strip('$')
            try:
                [num,dec]=number.rsplit('.')
                dec = int(dec)
                aside = str(dec)
                x = int('1'+'0'*len(aside))
                price = float(dec)/x
                num = num.replace(',','')
                num = int(num)
                price = num + price
            except:
                price = int(number)
            return price

        if (money(request.form.get("add_cash"))) <= 0:
            return apology("cash to be added must be a positive value")

        session_id = session["user_id"]
        cashObj = db.execute("SELECT cash FROM users WHERE id = :session_id", session_id=session_id)
        cash = cashObj[0].get('cash')
        add_cash = money(request.form.get("add_cash"))
        db.execute("UPDATE USERS SET cash= :cash WHERE id = :session_id", cash=cash+add_cash, session_id=session_id)
        return redirect(url_for("index"))
    else:
        return render_template("add_cash.html")
@app.route("/")
@login_required
def index():
    session_id = session["user_id"]
    cashObj = db.execute("SELECT cash FROM users WHERE id = :session_id", session_id=session_id)
    cash = cashObj[0].get('cash')
    cash = float("{0:.2f}".format(cash))
    #print(cash, 'cash')
    stock_worth = 0
    total_value = 0;

    stocks = []

    portfolio = db.execute("SELECT stock_symbol, sum(total_cost), sum(num_shares) FROM portfolio WHERE user_id = :session_id GROUP BY stock_symbol ORDER BY stock_symbol", session_id=session_id)
    #print(portfolio, 'portfolio')
    #print(portfolio[0].get('sum(total_cost)'))
    for item in portfolio:
        stock = {}
        stock['symbol'] = item.get('stock_symbol')

        quote = lookup(item.get('stock_symbol'))
        stockprice = quote.get('price')
        stock['price'] = stockprice

        stock_worth = stock_worth + (item.get('sum(total_cost)'))
        stock_worth = float("{0:.2f}".format(stock_worth))
        stock['total'] = stock_worth

        stock['num_shares'] = item.get('sum(num_shares)')
        if stock['num_shares'] > 0:
            stocks.append(stock)
    total_value = cash + stock_worth
    total_value = float("{0:.2f}".format(total_value))
    return render_template("index.html", stocks=stocks, cash=cash, total=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # ensure num shares is positive
        if (int(request.form.get("numshares"))) <= 0:
            return apology("num shares must be greater than 0")

        quote = lookup(request.form.get("stocksymbol"))
        garbagequote = lookup("garbagevalue")
        if (quote == garbagequote):
            return apology("invalid stock symbol")
        session_id = session["user_id"]
        cashObj = db.execute("SELECT cash FROM users WHERE id = :session_id", session_id=session_id)


        cash = cashObj[0].get('cash')
        numshares = request.form.get("numshares")
        stockprice = quote.get('price')
        totalcost = stockprice * int(numshares)
        newcash = cash-totalcost

        if (stockprice * int(numshares) > cash):
            return apology("not enough cash to purchase shares")
        else:
            print('can purchase')
            db.execute("UPDATE USERS SET cash= :cash WHERE id = :session_id", cash=cash-totalcost, session_id=session_id)
            #db.execute("UPDATE users SET cash = cash WHERE id=1", cash=newcash)
            db.execute("INSERT INTO portfolio (user_id, stock_symbol, stock_price, num_shares, total_cost) VALUES(:user_id, :stock_symbol, :stock_price, :num_shares, :total_cost)", user_id=1, stock_symbol=request.form.get("stocksymbol"), stock_price=stockprice, num_shares=numshares, total_cost=totalcost)
            return redirect(url_for("index"))
    else:
        return render_template("buy.html")


@app.route("/history", methods=["GET"])
@login_required
def history():
    """Show history of transactions."""
    session_id = session["user_id"]
    transaction_list=[]
    transactions = db.execute("SELECT * FROM portfolio WHERE user_id = :session_id", session_id=session_id)
    #print(transactions, 'transactions')
    for item in transactions:
        transaction={}
        if item['num_shares'] > 0:
            type = 'BUY'
        else:
            type = 'SELL'
        transaction['transaction_type'] = type
        transaction['stock_symbol'] = item['stock_symbol']
        transaction['num_shares'] = abs(item['num_shares'])

        quote = lookup(item['stock_symbol'])
        stockprice = quote.get('price')
        transaction['price_at_time'] = stockprice
        time_date = item['timestamp'].split()
        print(time_date, 'time date')
        transaction['date'] = time_date[0]
        transaction['time'] = time_date[1]
        transaction_list.append(transaction)
    print(transaction_list, 'transactions')
    # if user reached route via POST (as by submitting a form via POST)
    return render_template("history.html", transactions=transaction_list)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # ensure stock symbol was submitted
        garbagevalue = 'ljl4kr4j2wlekwdsdsaddd'
        if not request.form.get("stocksymbol"):
            return apology("must provide stock symbol")
        quote = lookup(request.form.get("stocksymbol"))
        garbagequote = lookup("garbagevalue")
        if (quote == garbagequote):
            return apology("invalid stock symbol")
        print(quote, 'quote')
        #.name, .price, .symbol
        return render_template("quoted.html", quote=quote)
    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # ensure password was reentered
        elif not request.form.get("password2"):
            return apology("must reenter password")

        # ensure passwords match
        elif ((request.form.get("password")) != (request.form.get("password2"))):
            return apology("passwords must match")


        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows):
            return apology("username already exists")

        hash = myctx.hash(request.form.get("password"))

        db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get("username"), hash=hash)

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        selected_symbol =  request.form.get("selected_symbol")
        print(selected_symbol, 'selected symbol')
        session_id = session["user_id"]
        selected_stock = db.execute("SELECT stock_symbol, sum(total_cost), sum(num_shares) FROM portfolio WHERE user_id = :user_id AND stock_symbol = :stock_symbol GROUP BY stock_symbol ORDER BY stock_symbol", user_id=session_id, stock_symbol = selected_symbol)
        print(selected_stock, 'selected stock')
        # get current stock price
        quote = lookup(selected_symbol)
        current_price = quote.get('price')
        # multiply current stock price * # shares selling
        num_shares = selected_stock[0]['sum(num_shares)']
        money_earned = num_shares * current_price
        print(money_earned, 'money earned')
        # add result back to cost
        cashObj = db.execute("SELECT cash FROM users WHERE id = :session_id", session_id=session_id)
        cash = cashObj[0].get('cash')
        db.execute("UPDATE USERS SET cash= :cash WHERE id = :session_id", cash=cash+money_earned, session_id=session_id)
        # delete rows with that stock symbol
        #db.execute("DELETE FROM PORTFOLIO WHERE user_id = :session_id AND stock_symbol = :stock_symbol", session_id=session_id, stock_symbol=selected_symbol)
        db.execute("INSERT INTO portfolio (user_id, stock_symbol, stock_price, num_shares, total_cost) VALUES(:user_id, :stock_symbol, :stock_price, :num_shares, :total_cost)", user_id=session_id, stock_symbol=selected_symbol, stock_price=current_price, num_shares=-num_shares, total_cost=-money_earned)
        return redirect(url_for("index"))
    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        # query database for username
        session_id = session["user_id"]
        symbols_list = []
        symbols = db.execute("SELECT stock_symbol FROM portfolio WHERE user_id = :session_id GROUP BY stock_symbol", session_id=session_id)
        for symbol in symbols:
            symbols_list.append(symbol['stock_symbol'])
        # print(symbols_list, 'symbols')
        return render_template("sell.html", symbols=symbols_list)

