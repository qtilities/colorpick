from PyQt4.QtCore import *
from PyQt4.QtGui import *

from PyKDE4.kdecore import *
from PyKDE4.kdeui import *

from coloreditor import ColorEditor
from colorpicker import ColorPicker

def bound(min, val, max):
    if val < min:
        return min
    if val > max:
        return max
    return val

class ColorWidget(QWidget):
    colorChanged = pyqtSignal(QColor)

    def __init__(self, parent = None):
        QWidget.__init__(self, parent)
        self.color = QColor()
        self.luminance = 0

        self.colorButton = KColorButton(self)
        self.colorButton.setFixedWidth(48)

        self.edit = QLineEdit()

        self.darkerButton = QToolButton()
        self.darkerButton.setArrowType(Qt.DownArrow)
        self.lighterButton = QToolButton()
        self.lighterButton.setArrowType(Qt.UpArrow)
        self.pickerButton = QToolButton()
        self.pickerButton.setIcon(KIcon("color-picker"))

        self.colorEditor = ColorEditor()

        self.luminanceLabel = QLabel()

        self.layout = QGridLayout(self)
        self.layout.setMargin(0)
        self.layout.addWidget(self.colorButton, 0, 0)
        self.layout.addWidget(self.edit, 0, 1)
        self.layout.addWidget(self.darkerButton, 0, 2)
        self.layout.addWidget(self.lighterButton, 0, 3)
        self.layout.addWidget(self.pickerButton, 0, 4)
        self.layout.addWidget(self.colorEditor, 1, 0, 1, 5)
        self.layout.addWidget(self.luminanceLabel, 2, 0, 1, 5)

        self.colorButton.changed.connect(self.setColor)
        self.colorEditor.changed.connect(self.setColor)
        self.edit.textChanged.connect(self.slotTextChanged)
        self.darkerButton.clicked.connect(self.darken)
        self.lighterButton.clicked.connect(self.lighten)
        self.pickerButton.clicked.connect(self.startPicking)
        self.updateLuminanceLabel()

    def darken(self):
        self.adjustValue(-10)

    def lighten(self):
        self.adjustValue(+10)

    def adjustValue(self, delta):
        h, s, v, a = self.color.getHsv()
        self.setColor(QColor.fromHsv(h, s, bound(0, v + delta, 255)))

    def setColor(self, color):
        if self.color == color:
            return
        self.color = color
        self.colorChanged.emit(color)
        self.updateWidgets()

    def slotTextChanged(self, txt):
        if QColor.isValidColor(txt):
            self.setColor(QColor(txt))

    def updateWidgets(self):
        if not self.edit.hasFocus():
            self.edit.setText(self.color.name())
        self.colorButton.setColor(self.color)
        self.colorEditor.setColor(self.color)
        self.luminance = KColorUtils.luma(self.color)
        self.updateLuminanceLabel()

    def updateLuminanceLabel(self):
        txt = i18n("Luminance: %1", KGlobal.locale().formatNumber(self.luminance, 3))
        self.luminanceLabel.setText(txt)

    def startPicking(self):
        picker = ColorPicker()
        picker.picked.connect(self.setColor)
        picker.exec_()
