import sys
from PyQt5.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout,
    QLabel, QLineEdit, QPushButton
)
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure


class DDADrawer(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Рябов.В.Ю. гр.3413")
        self.setGeometry(100, 100, 800, 600)
        self.scale = 20  # Масштаб для начальных пределов осей

        self.initUI()

        self.figure = Figure()
        self.canvas = FigureCanvas(self.figure)
        self.ax = self.figure.add_subplot(111)
        self.layout().addWidget(self.canvas)

        self.canvas.mpl_connect("scroll_event", self.on_scroll)

        self.xlim = [-self.scale, self.scale]
        self.ylim = [-self.scale, self.scale]

    def initUI(self):
        main_layout = QVBoxLayout()

        input_layout = QHBoxLayout()
        self.x0_input = QLineEdit()
        self.y0_input = QLineEdit()
        self.x1_input = QLineEdit()
        self.y1_input = QLineEdit()

        self.x0_input.setPlaceholderText("x0")
        self.y0_input.setPlaceholderText("y0")
        self.x1_input.setPlaceholderText("x1")
        self.y1_input.setPlaceholderText("y1")

        input_layout.addWidget(QLabel("Начальная точка:"))
        input_layout.addWidget(self.x0_input)
        input_layout.addWidget(self.y0_input)
        input_layout.addWidget(QLabel("Конечная точка:"))
        input_layout.addWidget(self.x1_input)
        input_layout.addWidget(self.y1_input)

        self.draw_button = QPushButton("Нарисовать")
        self.draw_button.clicked.connect(self.plot_dda)

        main_layout.addLayout(input_layout)
        main_layout.addWidget(self.draw_button)
        self.setLayout(main_layout)

    def plot_dda(self):
        try:
            x0 = int(self.x0_input.text())
            y0 = int(self.y0_input.text())
            x1 = int(self.x1_input.text())
            y1 = int(self.y1_input.text())
        except ValueError:
            return

        dx = x1 - x0
        dy = y1 - y0
        steps = max(abs(dx), abs(dy))
        x_inc = dx / steps
        y_inc = dy / steps

        x = x0
        y = y0
        self.points = []

        for _ in range(steps + 1):
            self.points.append((round(x), round(y)))
            x += x_inc
            y += y_inc

        self.update_plot()

    def update_plot(self):
        self.ax.clear()
        self.ax.set_title("Реализация алгоритма")
        self.ax.set_xlabel("X")
        self.ax.set_ylabel("Y")

        self.ax.grid(True, which='both', linestyle='-', color='orange')
        self.ax.axhline(0, color='blue', linewidth=1)
        self.ax.axvline(0, color='blue', linewidth=1)

        self.ax.set_xlim(self.xlim)
        self.ax.set_ylim(self.ylim)

        if hasattr(self, 'points'):
            xs, ys = zip(*self.points)
            self.ax.plot(xs, ys, 'ro')

        self.canvas.draw()

    def on_scroll(self, event):
        zoom_factor = 1.2 if event.button == 'up' else 0.8

        def zoom(lim):
            center = (lim[0] + lim[1]) / 2
            width = (lim[1] - lim[0]) * zoom_factor
            return [center - width / 2, center + width / 2]

        self.xlim = zoom(self.xlim)
        self.ylim = zoom(self.ylim)

        self.update_plot()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = DDADrawer()
    window.show()
    sys.exit(app.exec_())


