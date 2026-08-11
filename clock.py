from datetime import datetime
from zoneinfo import ZoneInfo, ZoneInfoNotFoundError

signature = "Created by Aureus The Femboy"

def getThatTime():
    # Ask the user for their timezone/city
    # Example format: "America/New_York", "Europe/London", "Asia/Tokyo"
    user_tz = input("Enter your timezone (e.g., America/New_York, Europe/London): ").strip()
    
    try:
        # Get the current time in the requested timezone
        tz = ZoneInfo(user_tz)
        now = datetime.now(tz)
        
        # Extract individual components
        day = now.date()
        timeNow = now.time().strftime("%H:%M:%S") # Formatted for readability
        
        print(f"\nIts {now}")
        print(f"Today is {day} and the local time is {timeNow}")
        print(f"{signature}")
        
    except ZoneInfoNotFoundError:
        print(f"\nError: '{user_tz}' is not a recognized timezone.")
        print("Please use the 'Continent/City' format (e.g., America/Los_Angeles).")

getThatTime()
