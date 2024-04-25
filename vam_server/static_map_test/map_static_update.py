import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
from PyQt5.QtCore import QUrl, QTimer
from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtGui import QFont
import folium
import os

class MapWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('Real-time Map Display 1')
        self.setGeometry(100, 100, 800, 600)

        # Create a central widget and set it
        central_widget = QWidget(self)
        self.setCentralWidget(central_widget)

        # Create a QVBoxLayout instance
        layout = QVBoxLayout(central_widget)

        # Create an instance of QWebEngineView
        self.web_view = QWebEngineView()

        # Add the QWebEngineView to the layout
        layout.addWidget(self.web_view)

        # The layout is automatically set for the central widget
        central_widget.setLayout(layout)

        # Define the starting point and step size for movement
        self.lat = 51.2638
        self.lon = 13.7205
        self.lat_step = 0.001  # Adjust the step size as needed
        self.lon_step = 0.001  # Adjust the step size as needed

        # Start displaying the map
        self.display_map(self.lat, self.lon)

        # Create a QTimer to update marker position dynamically
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_marker)
        self.timer.start(1000)  # Update every 5 seconds

    def display_map(self, lat, lon):
        # Use folium to create the map
        self.map = folium.Map(location=[lat, lon], zoom_start=12)
        self.marker = folium.Marker([lat, lon], popup='Current Position')
        self.map.add_child(self.marker)

        # Save the map as HTML
        map_path = 'realtime_map.html'
        self.map.save(map_path)

        # Load the map into QWebEngineView
        local_url = QUrl.fromLocalFile(os.path.abspath(map_path))
        self.web_view.load(local_url)

    def update_marker(self):
        # Increment the latitude and longitude values
        self.lat += self.lat_step
        self.lon += self.lon_step
        
        # Update marker position
        self.marker.location = [self.lat, self.lon]

        # Save and reload the map
        self.map.save('realtime_map.html')
        self.web_view.reload()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    app.setFont(QFont("Arial"))
    ex = MapWindow()
    ex.show()
    sys.exit(app.exec_())
