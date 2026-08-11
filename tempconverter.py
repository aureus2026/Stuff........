import datetime
import tkinter as tk
from tkinter import messagebox

def celsius_to_fahrenheit():
    """Prompts for Celsius and prints the Fahrenheit conversion."""
    try:
        c = float(input("What's Celsius?? "))
        f = (c * 1.8) + 32
        print(f"{f:.1f} degrees Fahrenheit\n")
    except ValueError:
        print("Oops! That wasn't a valid number. Please try again.\n")

def fahrenheit_to_celsius():
    """Prompts for Fahrenheit and prints the Celsius conversion."""
    try:
        f = float(input("What's Fahrenheit?? "))
        c = (f - 32) * (5 / 9)
        print(f"{c:.1f} degrees Celsius\n")
    except ValueError:
        print("Oops! That wasn't a valid number. Please try again.\n")

# Main program loop
print("=== Welcome to the Temperature Converter ===")
while True:
    choice = input("Convert to Fahrenheit (F), Celsius (C), or Quit (Q): ").strip().upper()

    if choice == "F":
        fahrenheit_to_celsius()
    elif choice == "C":
        celsius_to_fahrenheit()
    elif choice == "Q":
        print("Thanks for using the converter. Goodbye!")
        break  # Safely exits the while loop
    else:
        # Handle the invalid choice layout with Tkinter popups
        root = tk.Tk()
        root.withdraw() 
        messagebox.showinfo("CANT DO THAT", "WHAT U DOING FOLLOW INSTRUCTIONS!!")
        root.destroy()
        
        # Log the error with a timestamp
        now = datetime.datetime.now()
        with open("log.txt", "a") as file:
            file.write(f"Invalid input choice '{choice}' entered on {now}\n")
        
        print("Invalid instructions followed! Error has been logged. Try again.\n")
