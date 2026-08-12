import socket
import ssl
import sys
from datetime import datetime

def sslSocketHandshake():
    while True:
        # ipv4 --> Domain name!!!
        target_host = input("Enter website name (no https://, e.g., example.com) or 'exit' to quit: ").strip()
        
        if target_host.lower() == 'exit':
            print("Exiting program.")
            break
            
        if not target_host:
            print("Please enter a valid website name.")
            continue

        try:
            # Resolve domain name to an IP address
            target_ip = socket.gethostbyname(target_host)
            print(f"Target IP Address: {target_ip}")
            
            # 1. TCP Socket initialization (Raw Socket)
            raw_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            
            # 2. Create a secure SSL context with default configurations (loads system certificates)
            context = ssl.create_default_context()
            
            # 3. Wrap the raw socket in SSL
            # server_hostname is critical for SNI (Server Name Indication) so the server knows which cert to send
            client = context.wrap_socket(raw_client, server_hostname=target_host)
            
            # 4. Connection on port 443 (standard HTTPS port)
            client.connect((target_ip, 443))
            
            # Construct a raw HTTP request string
            request = f"GET / HTTP/1.1\r\nHost: {target_host}\r\nConnection: close\r\n\r\n"
            
            # Send the request securely over the SSL/TLS tunnel as bytes
            client.send(request.encode())
            
            # Receive up to 4096 bytes of decrypted data from the website
            response = client.recv(4096)
            
            # Decode using errors='ignore' to prevent crashes on non-UTF-8 characters
            decoded_response = response.decode(errors='ignore')
            print("\n--- Secure HTTPS Response Received ---")
            print(decoded_response)
            print("--------------------------------------\n")
            
            # Always close your connections when done to free up system resources
            client.close()
            
            ask_for_save = input("Do you want to save?? Y or N (capital please)........ ").strip()
            if "Y" in ask_for_save:
                # Capture and format the current local date and time
                timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                
                with open("networkLog.txt", "a") as file:
                    file.write(f"Timestamp: {timestamp}\nHost: {target_host} (HTTPS)\nRequest:\n{request}Response:\n{decoded_response}\n{'='*50}\n")
                print("Log successfully saved to networkLog.txt.")
            elif "N" in ask_for_save:
                print("Skipping save.")
                break
            else:
                print("DAWG YOU AINT FOLLOW DIRECTIONS")
                
        except socket.gaierror:
            print(f"Error: Unable to resolve host '{target_host}'. Please check the URL syntax.")
        except ssl.SSLError as e:
            print(f"SSL/TLS Handshake Error: {e}")
        except Exception as e:
            print(f"An unexpected error occurred: {e}")
            
        # Keeping your signature!
        print("\nCreated by Aureus the Femboy\n")

if __name__ == "__main__":
    sslSocketHandshake()
