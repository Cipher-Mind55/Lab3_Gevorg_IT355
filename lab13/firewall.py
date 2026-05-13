import psutil
import json
from datetime import datetime

PORT_PROTOCOLS = {
    80: "HTTP",
    443: "HTTPS",
    21: "FTP",
    22: "SSH",
    25: "SMTP",
    53: "DNS"
}

firewall_rules = {
    "blocked_in": set(),
    "blocked_out": set()
}

def get_open_ports():
    ports = {}
    for conn in psutil.net_connections(kind='inet'):
        try:
            port = conn.laddr.port
            if port not in ports:
                ports[port] = 0
            ports[port] += 1
        except:
            pass
    return ports

def analyze_traffic(ports):
    sorted_ports = sorted(ports.items(), key=lambda x: x[1], reverse=True)
    return sorted_ports

def block_port(port, direction="in"):
    if direction == "in":
        firewall_rules["blocked_in"].add(port)
    elif direction == "out":
        firewall_rules["blocked_out"].add(port)

def open_port(port, direction="in"):
    if direction == "in" and port in firewall_rules["blocked_in"]:
        firewall_rules["blocked_in"].remove(port)
    elif direction == "out" and port in firewall_rules["blocked_out"]:
        firewall_rules["blocked_out"].remove(port)

def save_log(open_ports, loaded_ports):
    timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M")
    filename = f"firewall_log_{timestamp}.json"
    
    log_data = {
        "open_ports": [
            {"port": p, "protocol": PORT_PROTOCOLS.get(p, "TCP/UDP"), "connections": count}
            for p, count in open_ports.items()
        ],
        "heavily_loaded_ports": [
            {"port": p[0], "connections": p[1]} for p in loaded_ports[:5]
        ],
        "firewall_rules": {
            "blocked_in": list(firewall_rules["blocked_in"]),
            "blocked_out": list(firewall_rules["blocked_out"])
        }
    }
    
    with open(filename, "w", encoding="utf-8") as f:
        json.dump(log_data, f, indent=4)
    print(f"Log saved to {filename}")

if __name__ == "__main__":
    print("Scanning open ports...")
    ports = get_open_ports()
    
    print("Analyzing traffic...")
    loaded = analyze_traffic(ports)
    
    print("Blocking port 80 (inbound) and 21 (outbound)...")
    block_port(80, "in")
    block_port(21, "out")
    
    save_log(ports, loaded)
