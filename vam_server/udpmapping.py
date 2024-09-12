import sys
import socket
import os
import json
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
from PyQt5.QtCore import QUrl, QTimer, QThread, pyqtSignal
from PyQt5.QtWebEngineWidgets import QWebEngineView, QWebEngineSettings
from PyQt5.QtGui import QFont

# Define constants for socket communication
BUFLEN = 512  # Max length of buffer
PORT = 4320   # The port on which to listen for incoming data

# Worker thread class for receiving data via UDP
class SocketThread(QThread):
    position_received = pyqtSignal(float, float)  # Signal to send latitude and longitude

    def __init__(self):
        super().__init__()

    def run(self):
        # Set up the UDP socket
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        server_address = ('', PORT)
        s.bind(server_address)

        while True:
            # Receive data from the socket
            data, address = s.recvfrom(BUFLEN)
            try:
                message = data.decode()
                lat, lon = None, None

                # Try to parse the received JSON data
                json_data=json.loads(message)
                if 'lat' in json_data and 'lon' in json_data:
                    lat=json_data['lat']
                    lon=json_data['lon']
                    self.position_received.emit(lat, lon)  # Emit signal with coordinates
                else:
                    print("Received data does not contain valid coordinates")
            except json.JSONDecodeError:
                print("Failed to parse Json data.")

class MapWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('Real-time Map Display 2')
        self.setGeometry(100, 100, 800, 600)

        # Set up central widget with QWebEngineView for displaying the map
        central_widget = QWidget(self)
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout(central_widget)
        self.web_view = QWebEngineView()
        layout.addWidget(self.web_view)
        self.web_view.settings().setAttribute(QWebEngineSettings.JavascriptEnabled, True)
        central_widget.setLayout(layout)

        # Start displaying the map with the initial position
        self.lat = 51.2638
        self.lon = 13.7205
        self.display_map(self.lat, self.lon)

    def display_map(self, lat, lon):
        # Load the local HTML file with the map
        map_path = os.path.abspath('map.html')
        print("Loading map from:", map_path)
        local_url = QUrl.fromLocalFile(map_path)
        self.web_view.load(local_url)

    def update_marker(self, lat, lon):
        self.lat = lat
        self.lon = lon
        js_code = f"updateMarker({self.lat}, {self.lon});"
        print(f"Updating marker to: Latitude={self.lat}, Longitude={self.lon}")
        self.web_view.page().runJavaScript(js_code, self.js_callback)

    def js_callback(self, result):
        if result is not None:
            print("JavaScript executed successfully, result:", result)
        else:
            print("JavaScript execution failed")

if __name__ == '__main__':
    # Start the PyQt5 application
    app = QApplication(sys.argv)
    app.setFont(QFont("Arial"))

    # Initialize the main window
    ex = MapWindow()

    # Create and start the socket thread to receive position data
    socket_thread = SocketThread()
    socket_thread.position_received.connect(ex.update_marker)  # Connect signal to update marker
    socket_thread.start()  # Start listening for UDP data

    # Show the map window
    ex.show()
    sys.exit(app.exec_())
