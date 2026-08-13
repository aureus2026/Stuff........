import re
from collections import defaultdict
# Please have Network_Scanner.py in the same directory this is in, otherwise your computer will die..............
import Network_Scanner

maxFailedAttempts = 3
errorCodes = {'401', '403', '404'}
targetRoute = "/login"
incidentTracker = defaultdict(int)
sig = "Created by Aureus The Femboy"

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
    # FIXED: Swapped to camelCase to match your global variables
    current_count = incidentTracker[ip_address]
    if current_count >= maxFailedAttempts:
        print(f"\n[🚨 INT_DETECTION] Host {ip_address} has triggered {current_count} anomalies. Isolating node...")
        
        print(f"[🔍 RECON] Triggering automated active profiling on {ip_address}...")
        
        # Run Phase 2: Profile web infrastructure ports
        open_ports = Network_Scanner.profile_web_ports(ip_address)
        
        # Run Phase 3: Extract title safely if any web ports are open
        title = "N/A"
        if open_ports:
            title = Network_Scanner.extract_html_title(ip_address, open_ports[0])
            
        # Run Threat Intel rules
        threat_level, description = Network_Scanner.analyze_host_threat(open_ports, title)
        
        # Output the combined intelligence data
        print(f"    ├── Open Web Ports: {open_ports if open_ports else 'None'}")
        print(f"    ├── Extracted Title: {title}")
        print(f"    └── Threat Classification: [{threat_level}] - {description}\n")

print(f"{sig}")
