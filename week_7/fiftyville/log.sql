-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Opening the db
sqlite3 fiftyville.db

-- looking for any data refered to the duck!
SELECT *
FROM crime_scene_reports
WHERE description LIKE '%duck%';

/*
 The results stated that the theft occurred at 10:15 at Humphrey Street -important-
*/

-- Data collected talks about the bakery, so I decided to check for any table realated to places.
.tables

/*
I noticed there's a table called bakery_security_logs, so I checked for any logs related
to the incident's day
*/

-- Querying in that day
SELECT name, transcript
FROM interviews
AND month = 7
AND day = 28
AND transcript LIKE '%bakery%';

/*
This reveals three key pieces of information
Ruth => Thief <left> in a car within <10 minutes of the theft>
Eugene => Thief <withdrew> money from ATM on <Leggett Street> earlier that morning
Raymond => Thief called someone <for less than a minute> and talked about <taking the earliest
flight out tomorrow>

The details refered with <> will be sustantial to narrow the data given for the queries
*/
-- First lead talks about a withdraw in Leggett Street
SELECT *
FROM atm_transactions
WHERE day = 28
AND month = 7
AND atm_location ="Leggett Street"
AND transaction_type = "withdraw";

-- Second lead, the bakery sec logs
SELECT hour, minute, license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND hour = 10
AND minute BETWEEN 15 AND 25
AND activity = 'exit'; -- Checking for cars leaving

-- Third lead the phone call
SELECT *
FROM phone_calls
WHERE month = 7
AND day = 28
AND duration < 60; -- Result mentions witnesses who saw the thief calling for less than a minute

-- And checked for the flights in the respective table seen when used .tables
SELECT flights.*, origin_airport.city AS Origin_city, destination_airport.city AS Destination_city
FROM flights
JOIN airports origin_airport ON flights.origin_airport_id = origin_airport.id
JOIN airports destination_airport ON flights.destination_airport_id = destination_airport.id
WHERE month = 7
AND day = 29
ORDER BY hour, minute -- Checked for the earliest flight
LIMIT 1; -- I needed the first flight

/*
Now I got a better picture, So I put together all the pieces in a massive query
focused to find the suspect
 */

SELECT DISTINCT people.name AS Suspect
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE
-- ATM withdrawal on Leggett Street data
atm_transactions.year = 2023
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw'
-- Car leaving bakery log
AND bakery_security_logs.year = 2023
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <= 25
AND bakery_security_logs.activity = 'exit'
-- Phone call shorter than 60 seconds
AND phone_calls.year = 2023
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60
-- Earliest flight next day
AND passengers.flight_id = (
    SELECT id
    FROM flights
    WHERE month = 7 AND day = 29
    ORDER BY hour, minute
    LIMIT 1
);

/* In order to find the accomplice I narrowd it down to check for the people who
bruce spoke in that day shorter than 60 secs
*/

SELECT people.name AS Accomplice
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60
AND phone_calls.caller = (
    SELECT phone_number
    FROM people
    WHERE name = 'Bruce'
);


/*
The results are conclusive:
CS50 Duck thief is Bruce
Accomplice is Robin
Destination where they went is New York City
*/

