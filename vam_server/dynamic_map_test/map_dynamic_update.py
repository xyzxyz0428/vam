import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
from PyQt5.QtCore import QUrl, QTimer
from PyQt5.QtWebEngineWidgets import QWebEngineView, QWebEngineSettings,QWebEngineProfile
from PyQt5.QtGui import QFont
import os

class MapWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('Real-time Map Display 2')
        self.setGeometry(100, 100, 800, 600)

        central_widget = QWidget(self)
        self.setCentralWidget(central_widget)
        layout = QVBoxLayout(central_widget)
        self.web_view = QWebEngineView()
        layout.addWidget(self.web_view)
        self.web_view.settings().setAttribute(QWebEngineSettings.JavascriptEnabled, True)
        central_widget.setLayout(layout)

        # Define the starting point and step size for movement
        self.lat = 51.2638
        self.lon = 13.7205
        self.lat_step = 0.001  # Adjust the step size as needed
        self.lon_step = 0.001  # Adjust the step size as needed

        # Start displaying the map
        self.display_map(self.lat, self.lon)

        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_marker)
        self.timer.start(1000)

    def display_map(self, lat, lon):
        # Load the local HTML file with the map
        map_path = os.path.abspath('map.html')
        print("Loading map from:", map_path)
        local_url = QUrl.fromLocalFile(map_path)
        self.web_view.load(local_url)

    def update_marker(self):
        self.lat += self.lat_step
        self.lon += self.lon_step
        js_code = f"updateMarker({self.lat}, {self.lon});"
        print("js_code:", js_code)
        self.web_view.page().runJavaScript(js_code,self.js_callback)

    def js_callback(self, result):
        if result is not None:
            print("JavaScript executed successfully, result:", result)
        else:
            print("JavaScript execution failed")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    app.setFont(QFont("Arial"))

    ex = MapWindow()
    ex.show()
    sys.exit(app.exec_())

