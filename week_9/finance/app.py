import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # Querying for user's stock holdings
    rows = db.execute(
        """
        SELECT symbol, SUM(shares) AS shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING SUM(shares) > 0
        """,
        user_id,
    )

    # Initializing portfolio and total value
    holdings = []
    total_portfolio_value = 0

    # Fetching stock details for each holding
    for row in rows:
        stock = lookup(row["symbol"])
        if not stock:
            return apology("stock lookup failed", 500)

        total_value = stock["price"] * row["shares"]
        total_portfolio_value += total_value
        holdings.append({
            "symbol": row["symbol"],
            "name": stock["name"],
            "shares": row["shares"],
            "price": stock["price"],
            "total": total_value,
        })

    # Fetching user's available cash
    user_cash = db.execute(
        "SELECT cash FROM users WHERE id = ?",
        user_id,
    )[0]["cash"]

    # Calculating grand total (cash + portfolio value)
    grand_total = total_portfolio_value + user_cash

    # Rendering index template with portfolio data
    return render_template(
        "index.html",
        holdings=holdings,
        cash=user_cash,
        total=grand_total,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validating inputs
        if not symbol:
            return apology("must provide symbol", 400)
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("shares must be a positive integer", 400)

        # Lookup stock symbol
        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        # Calculating total cost
        shares = int(shares)
        total_cost = stock["price"] * shares

        # Checking user's cash balance
        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        if total_cost > user_cash:
            return apology("can't afford", 400)

        # Deducting cash and logging transaction
        db.execute(
            """
            UPDATE users
            SET cash = cash - ?
            WHERE id = ?
            """,
            total_cost,
            user_id,
        )
        db.execute(
            """
            INSERT INTO transactions (user_id, symbol, shares, price, type)
            VALUES (?, ?, ?, ?, 'BUY')
            """,
            user_id,
            stock["symbol"],
            shares,
            stock["price"],
        )

        # Redirecting
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    # Fetch transaction history
    transactions = db.execute(
        """
        SELECT symbol, shares, price, type, timestamp
        FROM transactions
        WHERE user_id = ?
        ORDER BY timestamp DESC
        """,
        user_id,
    )
    return render_template("history.html", transactions=transactions)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must provide symbol", 400)
        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid symbol", 400)
        return render_template("quoted.html", stock=stock)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Checking for any missing input
        if not username:
            return apology("Must provide correct username", 400)
        if not password:
            return apology("Must provide password", 400)
        if password != confirmation:
            return apology("Password do not match", 400)

        # Inserting user into database
        try:
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)",
                username,
                generate_password_hash(password),
            )
        except ValueError:
            return apology("User already exists", 400)

        # Redirecting to login
        return redirect("/login")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validating inputs
        if not symbol:
            return apology("must provide symbol", 400)
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("must provide valid shares", 400)

        shares = int(shares)

        # Checking for user's holdings
        holdings = db.execute(
            """
            SELECT SUM(shares) AS shares
            FROM transactions
            WHERE user_id = ? AND symbol = ?
            GROUP BY symbol
            """,
            user_id,
            symbol,
        )
        if not holdings or holdings[0]["shares"] < shares:
            return apology("not enough shares", 400)

        # Lookup stock price
        stock = lookup(symbol)
        if stock is None:
            return apology("invalid symbol", 400)

        # Calculating sale value
        sale_value = stock["price"] * shares

        # Updating user's cash
        db.execute(
            """
            UPDATE users
            SET cash = cash + ?
            WHERE id = ?
            """,
            sale_value,
            user_id,
        )

        # Logging the sale in transactions
        db.execute(
            """
            INSERT INTO transactions (user_id, symbol, shares, price, type)
            VALUES (?, ?, ?, ?, 'SELL')
            """,
            user_id,
            symbol,
            -shares,  # Negative shares to indicate sale
            stock["price"],
        )

        # Redirect to index
        return redirect("/")

    # Fetching user's holdings for the dropdown menu (for GET requests)
    holdings = db.execute(
        """
        SELECT symbol
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING SUM(shares) > 0
        """,
        user_id,
    )

    return render_template("sell.html", holdings=holdings)


@app.route("/watchlist", methods=["GET", "POST"])
@login_required
def watchlist():
    """Manage the stock watchlist"""
    user_id = session["user_id"]

    if request.method == "POST":
        # Adding a stock to the watchlist
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must provide symbol", 400)

        # Checkig if the symbol exists
        stock = lookup(symbol)
        if not stock:
            return apology("Invalid symbol", 400)

        # Adding the stock to the user's watchlist
        db.execute(
            """
            INSERT INTO watchlist (user_id, symbol)
            VALUES (?, ?)
            """,
            user_id,
            symbol.upper(),
        )
        return redirect("/watchlist")

    # For GET requests, show the current watchlist
    watchlist_items = db.execute(
        """
        SELECT symbol
        FROM watchlist
        WHERE user_id = ?
        """,
        user_id,
    )

    # Fetching stock details for the watchlist
    watchlist_details = []
    for item in watchlist_items:
        stock = lookup(item["symbol"])
        if stock:
            watchlist_details.append({
                "symbol": stock["symbol"],
                "name": stock["name"],
                "price": usd(stock["price"]),
            })

    return render_template("watchlist.html", watchlist=watchlist_details)
