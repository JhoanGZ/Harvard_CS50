import os
import secrets

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from datetime import date

# Configure application
app = Flask(__name__)
app.secret_key = secrets.token_hex(16)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # Extracting form data
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Validating form inputs
        if not all([name, month, day]):
            flash("All fields are required!")
            return redirect("/")
        try:
            month = int(month)
            day = int(day)
        except ValueError:
            flash("Month and day must be valid integers!")
            return redirect("/")

        if month < 1 or month > 12:
            flash("Month must be between 1 and 12!")
            return redirect("/")

        if day < 1 or day > 31:
            flash("Day must be between 1 and 31!")
            return redirect("/")

        # Validating February days
        if month == 2 and day > 29:
            flash("February only has 28 or 29 days!")
            return redirect("/")

        # Validating months with 30 days
        if month in {4, 6, 9, 11} and day > 30:
            flash("Selected month only has 30 days!")
            return redirect("/")

        # Inserting new birthday into DB
        db.execute(
            """
            INSERT INTO birthdays (name, month, day)
            VALUES (?, ?, ?)
            """,
            name,
            month,
            day
        )
        flash("Birthday added successfully!")
        return redirect("/")

    # Searching functionality
    search_query = request.args.get("search")
    if search_query:
        birthdays = db.execute(
            """
            SELECT id, name, month, day
            FROM birthdays
            WHERE name LIKE ?
            """,
            f"%{search_query}%"
        )
    else:
        # Fetching all birthdays from the database
        birthdays = db.execute(
            """
            SELECT id, name, month, day
            FROM birthdays
            """
        )

    # Defining today date
    today = date.today()

    # Calculating countdown to each birthday
    for birthday in birthdays:
        try:
            birthday_date = date(today.year, birthday["month"], birthday["day"])
            if birthday_date < today:
                birthday_date = date(today.year + 1, birthday["month"], birthday["day"])
            birthday["countdown"] = (birthday_date - today).days
        except ValueError:
            birthday["countdown"] = "Invalid Date"

    return render_template("index.html", birthdays=birthdays)

@app.route("/delete", methods=["POST"])
def delete():
    """Delete a birthday"""
    birthday_id = request.form.get("id")

    if not birthday_id:
        flash("Missing ID for deletion!")
        return redirect("/")

    # Deleting the entry from the database
    db.execute(
        """
        DELETE FROM birthdays
        WHERE id = ?
        """,
        birthday_id
    )
    flash("Birthday deleted successfully!")
    return redirect("/")
