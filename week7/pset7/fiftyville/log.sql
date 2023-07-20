-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check interview about the crime
SELECT * FROM interviews
WHERE month = 7
AND day = 28;

SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10;

SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28;

SELECT * FROM flights WHERE month = 7 AND day = 29 AND origin_airport_id = 8 ORDER BY hour;

SELECT * FROM airports;

SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60;

SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60
) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10
);

SELECT passport_number FROM passengers WHERE flight_id = 6;

SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60
) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25
) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36
) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number from atm_transactions WHERE month = 7 AND day = 28 and atm_location = "Leggett Street" AND transaction_type = "withdraw")
);

SELECT * from atm_transactions WHERE month = 7 AND day = 28 and atm_location = "Leggett Street" AND transaction_type = "withdraw";

SELECT * FROM bank_accounts WHERE account_number IN (SELECT account_number from atm_transactions WHERE month = 7 AND day = 28 and atm_location = "Leggett Street" AND transaction_type = "withdraw");

SELECT * FROM people WHERE id = 686048;

SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE id = 686048);

SELECT * FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE id = 686048));