import re
from collections import defaultdict
# Please have Network_Scanner.py in the same directory this is in, otherwise your computer will die..............
import Network_Scanner
maxFailedAttempts = 3
errorCodes = {'401', '403', '404'}
targetRoute = "/login"
incidentTracker = defaultdict(int)

# Standard Common Log Format (CLF) expression matching pattern
LOG_PATTERN = r'(?P<ip>\S+)\s+\S+\s+\S+\s+\[(?P<time>[^\]]+)\]\s+"(?P<method>\S+)\s+(?P<route>\S+)\s+[^"]+"\s+(?P<status>\d+)\s+(?P<size>\S+)'
log_regex = re.compile(LOG_PATTERN)

def extractLogData(raw_line):
    match = log_regex.match(raw_line)
    if match:
        return match.groupdict() # Returns a dictionary of fields
    return None
def log_incident(ip_address, status_code, requested_route):
    # Monitor for unauthorized application access points or forbidden paths
    if status_code in errorCodes or targetRoute in requested_route:
        incidentTracker[ip_address] += 1
def evaluate_security_state(ip_address):
    current_count = incidentTracker[ip_address]
    if current_count >= maxFailedAttempts:
        print(f"[🚨 INT_DETECTION] Host {ip_address} has triggered {current_count} anomalies. Isolating node...")
        print(f"[🔍 RECON] Launching Network_Scanner.py against rogue node {ip_address}...")
        Network_Scanner._____(ip_address)
