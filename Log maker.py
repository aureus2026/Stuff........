from datetime import datetime

# Get current timestamp
now = datetime.now()
current_time_string = now.strftime("%Y-%m-%d %H:%M:%S")

# Get user inputs
file_name = input("What's the name of the file (without extension): ")
file_type = input("Enter file type (e.g., py, js, txt): ").strip().replace(".", "")
keyword = input("Enter the keyword to search for: ")

try:
    target_file = f"{file_name}.{file_type}"
    
    with open(target_file, "r") as search_file:
        for line in search_file:
            if keyword in line:
                # Use a different variable name (log_file) to avoid shadowing
                with open("log.txt", "a") as log_file:
                    log_file.write(f"[{current_time_string}] '{keyword}' found in {target_file}\n")
                
                
                print(f"Keyword found and logged to log")
                break 
        else:
            print("Keyword not found in the file.")

except FileNotFoundError:
    print(f"Error: The file '{file_name}.{file_type}' not in directory.")
