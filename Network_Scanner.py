import socket
import urllib.request
import re
import scapy.all as scapy
from datetime import datetime  # Crucial: Moved up top for efficiency

# --- PHASE 1: Scapy Network Mapping ---
def scan_local_network(ip_range):
    """Broadcasts Layer 2 ARP requests to discover devices on the subnet."""
    arp_request = scapy.ARP(pdst=ip_range)
    broadcast_frame = scapy.Ether(dst="ff:ff:ff:ff:ff:ff")
    packet = broadcast_frame / arp_request
    answered_list, _ = scapy.srp(packet, timeout=2, verbose=False)
    
    discovered_devices = []
    for _, received_reply in answered_list:
        discovered_devices.append({
            "ip": received_reply.psrc,
            "mac": received_reply.hwsrc
        })
    return discovered_devices

# --- PHASE 2: Socket Web Port Profiling ---
def profile_web_ports(ip_address):
    """Probes a target IP address for responsive web infrastructure ports."""
    target_ports = [80, 443, 8080, 8443]
    open_ports = []
    
    for port in target_ports:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(0.5)
        result = s.connect_ex((ip_address, port))
        if result == 0:
            open_ports.append(port)
        s.close()
    return open_ports

# --- PHASE 3: Intelligence Gathering & Threat Flagging ---
def extract_html_title(ip_address, port):
    """Connects to an open web port and extracts the text inside the HTML <title> tag."""
    protocol = "https" if port in [443, 8443] else "http"
    url = f"{protocol}://{ip_address}:{port}"
    
    try:
        req = urllib.request.Request(
            url, 
            headers={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64)'}
        )
        with urllib.request.urlopen(req, timeout=1.0) as response:
            html_content = response.read().decode('utf-8', errors='ignore')
            title_match = re.search(r'<title.*?>(.*?)</title>', html_content, re.IGNORECASE | re.DOTALL)
            if title_match:
                return title_match.group(1).strip()
            return "No Title Found"
    except Exception:
        return "Connection Reset / Authenticated Web UI"

def analyze_host_threat(open_ports, title_string):
    """Applies security logic rules to assess potential host anomalies."""
    if not open_ports:
        return "LOW-MEDIUM", "Stealth Host (No web interfaces exposed)"
    if 8080 in open_ports or 8443 in open_ports:
        return "MEDIUM", "Exposes alternative/unstandardized management ports"
        
    suspicious_keywords = ["backdoor", "exploit", "test", "debug", "root", "admin", "setup"]
    for keyword in suspicious_keywords:
        if keyword in title_string.lower():
            return "HIGH", f"Suspicious administrative keyword found in HTML title: '{keyword}'"
            
    return "SAFE", "Standard active web host"

# --- MAIN OPERATION ---
if __name__ == "__main__":
    target_subnet = "192.168.1.0/24"
    
    print("[*] Launching Tier-3 Wi-Fi Network Profiler...")
    devices = scan_local_network(target_subnet)
    
    print(f"\n[+] Processing Phase 3 Reconnaissance on {len(devices)} targets...")
    print("=" * 100)
    print(f"{'IP Address':<16}{'Open Ports':<15}{'HTML Document Title / System Identification':<45}{'Threat Level':<12}")
    print("=" * 100)
    
    for device in devices:
        ip = device["ip"]
        ports = profile_web_ports(ip)
        
        # Gather title from the first open port available
        title = "N/A"
        if ports:
            title = extract_html_title(ip, ports[0])
            
        # Run threat intelligence parsing
        threat_level, description = analyze_host_threat(ports, title)
        
        # --- FIXED LOG MAKING EXECUTION BLOCK ---
        current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        
        with open("network_audit.log", "a", encoding="utf-8") as log_file:
            # Prepend the timestamp and write full host metrics cleanly
            log_file.write(f"[{current_time}] IP: {ip} | Ports: {ports} | Title: {title} | Threat: {threat_level}\n")
            if threat_level in ["MEDIUM", "HIGH"]:
                log_file.write(f"    └── [ALERT] {description}\n")
        
        # --- UI FORMATTING OUTPUT ---
        ports_str = ", ".join(map(str, ports)) if ports else "None"
        display_title = title[:42] + "..." if len(title) > 42 else title
        
        print(f"{ip:<16}{ports_str:<15}{display_title:<45}{threat_level:<12}")
        if threat_level in ["MEDIUM", "HIGH"]:
            print(f"    └── [ALERT] {description}")
