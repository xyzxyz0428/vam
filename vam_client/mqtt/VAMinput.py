import socket
import paho.mqtt.client as mqtt
import threading

# MQTT Settings
MQTT_BROKER = "172.26.123.88"
MQTT_PORT = 1883
MQTT_TOPIC = 'tud/vpa/PB/gpsEmulator'

# UDP Settings
UDP_IP = "141.30.187.201"
UDP_PORT = 8888

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Callback when connecting to the MQTT broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
        # Subscribe to the topic
        client.subscribe(MQTT_TOPIC)
    else:
        print("Failed to connect, return code %d\n", rc)

# Callback when receiving a message from the MQTT broker
def on_message(client, userdata, message):
    print(f"Received message '{message.payload}' from topic '{message.topic}'")
    # Send the received message via UDP
    sock.sendto(message.payload, (UDP_IP, UDP_PORT))
    print(type(message.payload))

# Setup MQTT client
mqtt_client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1)
mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message

# Connect to MQTT broker
mqtt_client.connect(MQTT_BROKER, MQTT_PORT, 60)

def udp_server():
    # Create a UDP socket for receiving
    recv_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    recv_sock.bind((UDP_IP, UDP_PORT))

    while True:
        # Buffer size is 1024 bytes
        data, addr = recv_sock.recvfrom(1024)
        print(f"Received message: {data.decode()} from {addr}")

# Run MQTT client in a separate thread
threading.Thread(target=mqtt_client.loop_forever).start()

# Run UDP server in a separate thread
threading.Thread(target=udp_server).start()

