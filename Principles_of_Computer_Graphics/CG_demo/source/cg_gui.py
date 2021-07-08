#!/usr/bin/env python
# -*- coding:utf-8 -*-
import sys
from typing import Optional

import numpy as np
from PIL import Image
from PyQt5 import QtGui

import cg_algorithms as alg
from PyQt5.QtWidgets import (
    QApplication,
    QMainWindow,
    QGraphicsScene,
    QGraphicsView,
    QGraphicsItem,
    QListWidget,
    QHBoxLayout,
    QWidget,
    QStyleOptionGraphicsItem, QMessageBox, QColorDialog, QFileDialog, QFormLayout, QLabel, QLineEdit,
    QPushButton)
from PyQt5.QtGui import QPainter, QMouseEvent, QColor, QIntValidator
from PyQt5.QtCore import QRectF, Qt


class MyCanvas(QGraphicsView):
    """
    画布窗体类，继承自QGraphicsView，采用QGraphicsView、QGraphicsScene、QGraphicsItem的绘图框架
    """

    def __init__(self, *args):
        super().__init__(*args)
        self.main_window = None
        self.list_widget = None
        self.item_dict = {}
        self.selected_id = ''

        self.status = ''
        self.temp_algorithm = ''
        self.temp_id = ''
        self.temp_item = None
        self.color = QColor(0, 0, 0)

        self.drawing = False
        self.clip = False
        self.translate_x = 0
        self.translate_y = 0
        self.p_list = []
        self.clip_window = None
        self.center = None
        self.center_x = 0
        self.center_y = 0
        self.curve_window = None

    def start_draw_line(self, algorithm):
        self.status = 'line'
        self.temp_algorithm = algorithm

    def start_draw_polygon(self, algorithm):
        self.status = 'polygon'
        self.temp_algorithm = algorithm
        self.drawing = False

    def start_draw_ellipse(self):
        self.status = 'ellipse'

    def start_draw_bezier(self):
        self.status = 'curve'
        self.temp_algorithm = 'Bezier'
        self.drawing = False

    def start_draw_b_spline(self):
        self.status = 'curve'
        self.temp_algorithm = 'B-spline'
        self.drawing = False

    def start_translate(self):
        self.status = 'translate'

    def start_scale(self):
        self.status = 'scale'

    def start_rotate(self):
        self.status = 'rotate'
        self.center_x = -1

    def start_clip(self, algorithm):
        self.status = 'clip'
        self.temp_algorithm = algorithm

    def start_pencil(self):
        self.status = 'pencil'

    def finish_draw(self):
        # print('finish draw')
        self.temp_id = self.main_window.get_id()
        self.main_window.isChanged = True

    def clear_selection(self):
        if self.selected_id != '':
            self.item_dict[self.selected_id].selected = False
            self.selected_id = ''

    def selection_changed(self, selected):
        self.main_window.statusBar().showMessage('图元选择： %s' % selected)
        if self.selected_id != '':
            self.item_dict[self.selected_id].selected = False
            self.item_dict[self.selected_id].update()
        self.selected_id = selected
        self.item_dict[selected].selected = True
        self.item_dict[selected].update()
        self.status = ''
        self.updateScene([self.sceneRect()])

    def mousePressEvent(self, event: QMouseEvent) -> None:
        self.temp_id = self.main_window.get_id2()
        pos = self.mapToScene(event.localPos().toPoint())
        x = int(pos.x())
        y = int(pos.y())
        self.main_window.statusBar().showMessage('mouse pressed, pos x:' + str(x) + ' y:' + str(y))
        if self.status == 'line':
            self.temp_item = MyItem(self.temp_id, self.status, [[x, y], [x, y]], self.temp_algorithm, self.color)
            self.scene().addItem(self.temp_item)
        elif self.status == 'polygon':
            if not self.drawing:
                self.temp_item = MyItem(self.temp_id, self.status, [[x, y], [x, y]], self.temp_algorithm, self.color)
                self.scene().addItem(self.temp_item)
                self.drawing = True
            else:
                if event.button() == Qt.RightButton:
                    pass
                else:
                    self.temp_item.p_list.append([x, y])
                    # print(self.temp_item.p_list)
        elif self.status == 'ellipse':
            # print('ellipse pressed')
            self.temp_item = MyItem(self.temp_id, self.status, [[x, y], [x, y]], '', self.color)
            self.scene().addItem(self.temp_item)
        elif self.status == 'curve':
            if not self.drawing:
                self.temp_item = MyItem(self.temp_id, self.status, [[x, y]], self.temp_algorithm, self.color)
                self.scene().addItem(self.temp_item)
                self.drawing = True
            else:
                if event.button() == Qt.RightButton:
                    pass
                else:
                    self.temp_item.p_list.append([x, y])
            if self.drawing:
                self.main_window.isChanged = True
                window_p_list = self.temp_item.p_list
                if self.curve_window:
                    self.curve_window.p_list = window_p_list
                else:
                    self.curve_window = MyItem(str(-1), 'polygon', window_p_list, 'Bresenham', QColor(255, 0, 0))
                    self.scene().addItem(self.curve_window)
        elif self.status == 'pencil':
            self.temp_item = MyItem(self.temp_id, self.status, [[x, y]], '', self.color)
            self.scene().addItem(self.temp_item)
        elif self.status == 'translate':
            if self.selected_id != '':
                # print('translate')
                # print(self.selected_id)
                self.temp_item = self.item_dict[self.selected_id]
                self.translate_x = x
                self.translate_y = y
                self.p_list = self.temp_item.p_list
            else:
                print('selected id null')
        elif self.status == 'scale':
            # print('here')
            if self.selected_id != '':
                self.temp_item = self.item_dict[self.selected_id]
                x_center, x_min, x_max = 0, 0, 0
                y_center, y_min, y_max = 0, 0, 0
                if self.temp_item.item_type == 'line' or self.temp_item.item_type == 'ellipse':
                    # print(self.p_list)
                    x0, y0 = self.temp_item.p_list[0]
                    x1, y1 = self.temp_item.p_list[1]
                    x_min = min(x0, x1)
                    y_min = min(y0, y1)
                    x_max = max(x0, x1)
                    y_max = max(y0, y1)
                    x_center = (x_min + x_max) // 2
                    y_center = (y_min + y_max) // 2
                elif self.temp_item.item_type == 'polygon' or self.temp_item.item_type == 'pencil' \
                        or self.temp_item.item_type == 'curve':
                    # print('poly')
                    x_list = []
                    y_list = []
                    # print(self.temp_item.p_list)
                    for (x0, y0) in self.temp_item.p_list:
                        x_list.append(x0)
                        y_list.append(y0)
                    x_min = min(x_list)
                    y_min = min(y_list)
                    x_max = max(x_list)
                    y_max = max(y_list)
                    # print(x_min, x_max)
                    x_center = (x_min + x_max) // 2
                    y_center = (y_min + y_max) // 2
                    # print('end')
                self.center = MyItem('-1', 'ellipse', [[x_center - 5, y_center - 5], [x_center + 5, y_center + 5]],
                                     '', QColor(255, 0, 0))
                # print('here')
                self.translate_x = abs(x - x_center) / (x_max - x_min)
                self.translate_y = x_max - x_min
                self.center_x = x_center
                self.center_x = y_center
                self.p_list = self.temp_item.p_list
                self.scene().addItem(self.center)
                # print('press end')
        elif self.status == 'rotate':
            if self.selected_id != '':
                self.temp_item = self.item_dict[self.selected_id]
                # self.p_list = self.temp_item.p_list
                self.center_x = x
                self.center_y = y
        elif self.status == 'clip':
            if self.selected_id != '':
                self.temp_item = self.item_dict[self.selected_id]
                if self.temp_item.item_type == 'line':
                    self.translate_x = x
                    self.translate_y = y
                    self.p_list = self.temp_item.p_list
                    self.clip = True
                else:
                    print('the figure selected must be a line')
        self.updateScene([self.sceneRect()])
        super().mousePressEvent(event)

    def mouseMoveEvent(self, event: QMouseEvent) -> None:
        pos = self.mapToScene(event.localPos().toPoint())
        x = int(pos.x())
        y = int(pos.y())
        if self.status == 'rotate':
            self.main_window.statusBar().showMessage('滚动鼠标滚轮进行旋转!!!')
        else:
            self.main_window.statusBar().showMessage('mouse moving, pos x:' + str(x) + ' y:' + str(y))
        if self.status == 'line':
            self.temp_item.p_list[1] = [x, y]
        elif self.status == 'polygon':
            self.temp_item.p_list[-1] = [x, y]
        elif self.status == 'ellipse':
            self.temp_item.p_list[1] = [x, y]
        elif self.status == 'curve':
            # self.temp_item.p_list[-1] = [x, y]
            pass
        elif self.status == 'pencil':
            self.temp_item.p_list.append([x, y])
        elif self.status == 'translate':
            if self.selected_id != '':
                self.main_window.isChanged = True
                self.temp_item.p_list = alg.translate(self.p_list, x - self.translate_x, y - self.translate_y)
        elif self.status == 'scale':
            if self.selected_id != '':
                # print('moving')
                self.main_window.isChanged = True
                x_center, x_min, x_max = 0, 0, 0
                y_center, y_min, y_max = 0, 0, 0
                if self.temp_item.item_type == 'line' or self.temp_item.item_type == 'ellipse':
                    # print(self.p_list)
                    x0, y0 = self.temp_item.p_list[0]
                    x1, y1 = self.temp_item.p_list[1]
                    x_min = min(x0, x1)
                    y_min = min(y0, y1)
                    x_max = max(x0, x1)
                    y_max = max(y0, y1)
                    x_center = (x_min + x_max) // 2
                    y_center = (y_min + y_max) // 2
                elif self.temp_item.item_type == 'polygon' or self.temp_item.item_type == 'pencil' \
                        or self.temp_item.item_type == 'curve':
                    x_list = []
                    y_list = []
                    for (x0, y0) in self.temp_item.p_list:
                        x_list.append(x0)
                        y_list.append(y0)
                    x_min = min(x_list)
                    y_min = min(y_list)
                    x_max = max(x_list)
                    y_max = max(y_list)
                    x_center = (x_min + x_max) // 2
                    y_center = (y_min + y_max) // 2
                self.center.p_list = [[x_center - 5, y_center - 5], [x_center + 5, y_center + 5]]
                dx = abs(x - self.center_x) / self.translate_y
                s = dx / self.translate_x
                # print(s)
                self.temp_item.p_list = alg.scale(self.p_list, self.center_x, self.center_y, s)
        elif self.status == 'rotate':
            pass
        elif self.status == 'clip':
            if self.clip:
                self.main_window.isChanged = True
                x0 = min(self.translate_x, x)
                x1 = max(self.translate_x, x)
                dx = x1 - x0
                y0 = min(self.translate_y, y)
                y1 = max(self.translate_y, y)
                dy = y1 - y0
                p_list = [(x0, y0), (x0 + dx, y0), (x0 + dx, y0 + dy), (x0, y0 + dy)]
                if self.clip_window:
                    self.clip_window.p_list = p_list
                else:
                    self.clip_window = MyItem(str(-1), 'polygon', p_list, 'Bresenham', QColor(255, 0, 0))
                    self.scene().addItem(self.clip_window)
                # print(self.clip_window.p_list)
        self.updateScene([self.sceneRect()])
        super().mouseMoveEvent(event)

    def mouseReleaseEvent(self, event: QMouseEvent) -> None:
        pos = self.mapToScene(event.localPos().toPoint())
        x = int(pos.x())
        y = int(pos.y())
        self.main_window.statusBar().showMessage('mouse released, pos x:' + str(x) + ' y:' + str(y))
        if self.status == 'line':
            self.item_dict[self.temp_id] = self.temp_item
            self.list_widget.addItem(self.temp_id)
            self.finish_draw()
        elif self.status == 'polygon':
            if event.button() == Qt.RightButton:
                self.drawing = False
                self.finish_draw()
            else:
                self.item_dict[self.temp_id] = self.temp_item
                if not self.list_widget.findItems(self.temp_id, Qt.MatchContains):
                    self.list_widget.addItem(self.temp_id)
        elif self.status == 'ellipse':
            self.item_dict[self.temp_id] = self.temp_item
            self.list_widget.addItem(self.temp_id)
            self.finish_draw()
        elif self.status == 'curve':
            if event.button() == Qt.RightButton:
                self.scene().removeItem(self.curve_window)
                self.curve_window = None
                self.drawing = False
                self.finish_draw()
            else:
                self.item_dict[self.temp_id] = self.temp_item
                if not self.list_widget.findItems(self.temp_id, Qt.MatchContains):
                    self.list_widget.addItem(self.temp_id)
        elif self.status == 'pencil':
            self.item_dict[self.temp_id] = self.temp_item
            self.list_widget.addItem(self.temp_id)
            self.finish_draw()
        elif self.status == 'translate':
            pass
        elif self.status == 'scale':
            self.scene().removeItem(self.center)
            self.center = None
            self.updateScene([self.sceneRect()])
            # print('release')
        elif self.status == 'rotate':
            pass
        elif self.status == 'clip':
            # https://blog.csdn.net/weixin_42296333/article/details/86765297
            if self.clip:
                self.scene().removeItem(self.clip_window)
                self.clip_window = None
                x0, y0, x1, y1 = min(self.translate_x, x), min(self.translate_y, y), max(self.translate_x, x), max(
                    self.translate_y, y)
                p_list = alg.clip(self.p_list, x0, y0, x1, y1, self.temp_algorithm)
                # print(p_list)
                if len(p_list) == 0:
                    # item = self.listWidget.findItems(self.selected_id, Qt.MatchExactly)[0]
                    # print(item)
                    # row = self.list_widget.row(item)
                    # print(row)
                    selected_id = self.selected_id
                    self.clear_selection()
                    self.list_widget.clearSelection()
                    self.scene().removeItem(self.temp_item)
                    # print('remove')
                    self.temp_item = None
                    self.clip = False
                    del self.item_dict[selected_id]
                    # print('del')
                    # self.list_widget.takeItem(row) 服了，这个也是出错Process finished with exit code -1073740791 (0xC0000409)
                    self.main_window.list_widget.hide()
                    self.main_window.list_widget = QListWidget(self)
                    self.main_window.list_widget.setMinimumWidth(200)
                    self.main_window.hbox_layout.addWidget(self.main_window.list_widget, stretch=1)
                    self.main_window.list_widget.show()
                    self.main_window.list_widget.currentTextChanged.connect(self.selection_changed)
                    self.list_widget = self.main_window.list_widget
                    for item in self.item_dict:
                        self.list_widget.addItem(item)
                    # print('done')
                else:
                    self.temp_item.p_list = p_list
                self.updateScene([self.sceneRect()])
        super().mouseReleaseEvent(event)

    # http://blog.sina.com.cn/s/blog_6483fa330102xo6w.html
    def wheelEvent(self, event: QtGui.QWheelEvent) -> None:
        if self.status == 'rotate' and self.selected_id != '':
            r = event.angleDelta() / 10
            self.main_window.isChanged = True
            if self.center_x != -1:
                self.temp_item.p_list = alg.rotate(self.temp_item.p_list, self.center_x, self.center_y, r.y())
            self.updateScene([self.sceneRect()])


class MyItem(QGraphicsItem):
    """
    自定义图元类，继承自QGraphicsItem
    """

    def __init__(self, item_id: str, item_type: str, p_list: list, algorithm: str = '',
                 color=QColor(0, 0, 0), parent: QGraphicsItem = None):
        """

        :param item_id: 图元ID
        :param item_type: 图元类型，'line'、'polygon'、'ellipse'、'curve'等
        :param p_list: 图元参数
        :param algorithm: 绘制算法，'DDA'、'Bresenham'、'Bezier'、'B-spline'等
        :param parent:
        """
        super().__init__(parent)
        self.id = item_id  # 图元ID
        self.item_type = item_type  # 图元类型，'line'、'polygon'、'ellipse'、'curve'等
        self.p_list = p_list  # 图元参数
        self.algorithm = algorithm  # 绘制算法，'DDA'、'Bresenham'、'Bezier'、'B-spline'等
        self.selected = False
        self.color = color

    def paint(self, painter: QPainter, option: QStyleOptionGraphicsItem, widget: Optional[QWidget] = ...) -> None:
        painter.setPen(self.color)
        if self.item_type == 'line':
            item_pixels = alg.draw_line(self.p_list, self.algorithm)
            for p in item_pixels:
                painter.drawPoint(*p)
            if self.selected:
                painter.setPen(QColor(255, 0, 0))
                painter.drawRect(self.boundingRect())
        elif self.item_type == 'polygon':
            item_pixels = alg.draw_polygon(self.p_list, self.algorithm)
            for p in item_pixels:
                painter.drawPoint(*p)
            if self.selected:
                painter.setPen(QColor(255, 0, 0))
                painter.drawRect(self.boundingRect())
        elif self.item_type == 'ellipse':
            # print('paint ellipse')
            item_pixels = alg.draw_ellipse(self.p_list)
            # print(item_pixels)
            for p in item_pixels:
                painter.drawPoint(*p)
            if self.selected:
                painter.setPen(QColor(255, 0, 0))
                painter.drawRect(self.boundingRect())
        elif self.item_type == 'curve':
            item_pixels = alg.draw_curve(self.p_list, self.algorithm)
            for p in item_pixels:
                painter.drawPoint(*p)
            if self.selected:
                painter.setPen(QColor(255, 0, 0))
                painter.drawRect(self.boundingRect())
        elif self.item_type == 'pencil':
            # for p in self.p_list:
            # painter.drawPoint(*p)
            item_pixels = alg.draw_pencil(self.p_list, 'DDA')
            for p in item_pixels:
                painter.drawPoint(*p)
            if self.selected:
                painter.setPen(QColor(255, 0, 0))
                painter.drawRect(self.boundingRect())

    def boundingRect(self) -> QRectF:
        if self.item_type == 'line' or self.item_type == 'ellipse':
            # print(self.p_list)
            x0, y0 = self.p_list[0]
            x1, y1 = self.p_list[1]
            x = min(x0, x1)
            y = min(y0, y1)
            w = max(x0, x1) - x
            h = max(y0, y1) - y
            return QRectF(x - 1, y - 1, w + 2, h + 2)
        elif self.item_type == 'polygon' or self.item_type == 'pencil' or self.item_type == 'curve':
            x = []
            y = []
            for (x0, y0) in self.p_list:
                x.append(x0)
                y.append(y0)
            x_min = min(x)
            y_min = min(y)
            w = max(x) - x_min
            h = max(y) - y_min
            return QRectF(x_min - 1, y_min - 1, w + 2, h + 2)
        elif self.item_type == 'curve':
            pass


class MainWindow(QMainWindow):
    """
    主窗口类
    """

    def __init__(self):
        super().__init__()
        self.item_cnt = 0
        self.isChanged = False
        self.newCanvasWidget = NewCanvasWidget(self)
        self.filename = ''

        # 使用QListWidget来记录已有的图元，并用于选择图元。注：这是图元选择的简单实现方法，更好的实现是在画布中直接用鼠标选择图元
        self.list_widget = QListWidget(self)
        self.list_widget.setMinimumWidth(200)

        # 使用QGraphicsView作为画布
        self.scene = QGraphicsScene(self)
        self.scene.setSceneRect(0, 0, 600, 600)
        self.canvas_widget = MyCanvas(self.scene, self)
        self.canvas_widget.setFixedSize(600, 600)
        self.canvas_widget.main_window = self
        self.canvas_widget.list_widget = self.list_widget

        # 设置菜单栏
        menubar = self.menuBar()
        file_menu = menubar.addMenu('文件')
        set_pen_act = file_menu.addAction('设置画笔')
        set_pen_act.setShortcut('Ctrl+o')
        reset_canvas_act = file_menu.addAction('重置画布')
        reset_canvas_act.setShortcut('Ctrl+r')
        save_act = file_menu.addAction('Save')
        save_act.setShortcut('Ctrl+s')
        exit_act = file_menu.addAction('退出')
        exit_act.setShortcut('Ctrl+x')
        draw_menu = menubar.addMenu('绘制')
        line_menu = draw_menu.addMenu('线段')
        line_naive_act = line_menu.addAction('Naive')
        line_dda_act = line_menu.addAction('DDA')
        line_dda_act.setShortcut('Ctrl+d')
        line_bresenham_act = line_menu.addAction('Bresenham')
        line_bresenham_act.setShortcut('Ctrl+b')
        polygon_menu = draw_menu.addMenu('多边形')
        polygon_dda_act = polygon_menu.addAction('DDA')
        polygon_dda_act.setShortcut('Ctrl+p')
        polygon_bresenham_act = polygon_menu.addAction('Bresenham')
        polygon_bresenham_act.setShortcut('Shift+p')
        ellipse_act = draw_menu.addAction('椭圆')
        ellipse_act.setShortcut('Ctrl+e')
        curve_menu = draw_menu.addMenu('曲线')
        curve_bezier_act = curve_menu.addAction('Bezier')
        curve_bezier_act.setShortcut('Ctrl+z')
        curve_b_spline_act = curve_menu.addAction('B-spline')
        curve_b_spline_act.setShortcut('Shift+b')
        edit_menu = menubar.addMenu('编辑')
        translate_act = edit_menu.addAction('平移')
        translate_act.setShortcut('Ctrl+t')
        rotate_act = edit_menu.addAction('旋转')
        rotate_act.setShortcut('Shift+r')
        scale_act = edit_menu.addAction('缩放')
        scale_act.setShortcut('Shift+s')
        clip_menu = edit_menu.addMenu('裁剪')
        clip_cohen_sutherland_act = clip_menu.addAction('Cohen-Sutherland')
        clip_cohen_sutherland_act.setShortcut('Ctrl+c')
        clip_liang_barsky_act = clip_menu.addAction('Liang-Barsky')
        clip_liang_barsky_act.setShortcut('Shift+c')
        other_menu = menubar.addMenu('Other')
        pencil_act = other_menu.addAction('Pencil')
        pencil_act.setShortcut('ctrl+f')
        about_act = other_menu.addAction('About')
        about_act.setShortcut('ctrl+a')

        # 连接信号和槽函数
        exit_act.triggered.connect(self.closeEvent)
        line_naive_act.triggered.connect(self.line_naive_action)
        line_dda_act.triggered.connect(self.line_dda_action)
        line_bresenham_act.triggered.connect(self.line_bresenham_action)
        polygon_dda_act.triggered.connect(self.polygon_dda_action)
        polygon_bresenham_act.triggered.connect(self.polygon_bresenham_action)
        ellipse_act.triggered.connect(self.ellipse_action)
        curve_bezier_act.triggered.connect(self.bezier_action)
        curve_b_spline_act.triggered.connect(self.b_spline_action)
        pencil_act.triggered.connect(self.pencil_action)
        scale_act.triggered.connect(self.scale_triggered)
        translate_act.triggered.connect(self.translate_triggered)
        rotate_act.triggered.connect(self.rotate_triggered)
        clip_cohen_sutherland_act.triggered.connect(self.clip_cohen_sutherland_triggered)
        clip_liang_barsky_act.triggered.connect(self.clip_liang_barsky_triggered)
        self.list_widget.currentTextChanged.connect(self.canvas_widget.selection_changed)
        reset_canvas_act.triggered.connect(self.actionReset_triggered)
        set_pen_act.triggered.connect(self.actionColor_triggered)
        save_act.triggered.connect(self.actionSave_triggered)
        about_act.triggered.connect(self.actionAbout_triggered)

        # 设置主窗口的布局
        self.hbox_layout = QHBoxLayout()
        self.hbox_layout.addWidget(self.canvas_widget)
        self.hbox_layout.addWidget(self.list_widget, stretch=1)
        self.central_widget = QWidget()
        self.central_widget.setLayout(self.hbox_layout)
        self.setCentralWidget(self.central_widget)
        self.statusBar().showMessage('空闲')
        self.resize(600, 600)
        self.setWindowTitle('CG Demo')

    def get_id(self):
        # print('get id')
        _id = str(self.item_cnt)
        self.item_cnt += 1
        # print(self.item_cnt)
        return _id

    def get_id2(self):
        _id = str(self.item_cnt)
        return _id

    def clear_canvas_status(self):
        if self.canvas_widget.drawing:
            if self.canvas_widget.status == 'curve':
                self.canvas_widget.scene().removeItem(self.canvas_widget.curve_window)
                self.canvas_widget.curve_window = None
            self.canvas_widget.drawing = False
            self.canvas_widget.finish_draw()

    def line_naive_action(self):
        self.clear_canvas_status()
        """if self.canvas_widget.drawing:
            if self.canvas_widget.status == 'curve':
                self.canvas_widget.scene().removeItem(self.canvas_widget.curve_window)
                self.canvas_widget.curve_window = None
            self.canvas_widget.drawing = False
            self.canvas_widget.finish_draw()"""
        self.canvas_widget.start_draw_line('Naive')
        self.statusBar().showMessage('Naive算法绘制线段')
        self.list_widget.clearSelection()
        self.canvas_widget.clear_selection()

    def line_dda_action(self):
        self.clear_canvas_status()
        self.canvas_widget.start_draw_line('DDA')
        self.statusBar().showMessage('DDA算法绘制线段')
        self.list_widget.clearSelection()
        self.canvas_widget.clear_selection()

    def line_bresenham_action(self):
        self.clear_canvas_status()
        self.canvas_widget.start_draw_line('Bresenham')
        self.statusBar().showMessage('Bresenham算法绘制线段')
        self.list_widget.clearSelection()
        self.canvas_widget.clear_selection()

    def polygon_dda_action(self):
        self.clear_canvas_status()
        self.canvas_widget.start_draw_polygon('DDA')
        self.statusBar().showMessage('DDA算法绘制多边形')
        self.list_widget.clearSelection()
        self.canvas_widget.clear_selection()

    def polygon_bresenham_action(self):
        self.clear_canvas_status()
        self.canvas_widget.start_draw_polygon('Bresenham')
        self.statusBar().showMessage('Bresenham算法绘制多边形')
        self.list_widget.clearSelection()
        self.canvas_widget.clear_selection()

    def ellipse_action(self):
        self.clear_canvas_status()
        self.canvas_widget.start_draw_ellipse()
        self.statusBar().showMessage('中点圆生成算法绘制椭圆')
        self.list_widget.clearSelection()
        self.canvas_widget.clear_selection()

    def bezier_action(self):
        self.clear_canvas_status()
        self.canvas_widget.start_draw_bezier()
        self.statusBar().showMessage('绘制曲线Bezier')
        self.list_widget.clearSelection()
        self.canvas_widget.clear_selection()

    def b_spline_action(self):
        self.clear_canvas_status()
        self.canvas_widget.start_draw_b_spline()
        self.statusBar().showMessage('绘制曲线B_spline')
        self.list_widget.clearSelection()
        self.canvas_widget.clear_selection()

    def pencil_action(self):
        self.clear_canvas_status()
        self.canvas_widget.start_pencil()
        self.statusBar().showMessage('铅笔')
        self.list_widget.clearSelection()
        self.canvas_widget.clear_selection()

    def translate_triggered(self):
        self.clear_canvas_status()
        self.canvas_widget.start_translate()
        self.statusBar().showMessage('平移')
        # self.list_widget.clearSelection()
        # self.canvas_widget.clear_selection()

    def scale_triggered(self):
        self.clear_canvas_status()
        self.canvas_widget.start_scale()
        self.statusBar().showMessage('缩放')

    def rotate_triggered(self):
        self.clear_canvas_status()
        self.canvas_widget.start_rotate()
        self.statusBar().showMessage('旋转--点击后滚动鼠标滚轮进行旋转!!!')

    def clip_cohen_sutherland_triggered(self):
        self.clear_canvas_status()
        self.canvas_widget.start_clip('Cohen-Sutherland')
        self.statusBar().showMessage('线段裁剪Cohen-Sutherland')

    def clip_liang_barsky_triggered(self):
        self.clear_canvas_status()
        self.canvas_widget.start_clip('Liang-Barsky')
        self.statusBar().showMessage('线段裁剪Liang-Barsky')

    def resetCanvas(self, width, height):
        self.clear_canvas_status()
        self.list_widget.hide()
        self.list_widget = QListWidget(self)
        self.list_widget.setMinimumWidth(200)
        self.hbox_layout.addWidget(self.list_widget, stretch=1)
        self.list_widget.show()
        self.list_widget.currentTextChanged.connect(self.canvas_widget.selection_changed)
        self.item_cnt = 0
        self.filename = ''
        self.isChanged = False
        # self.list_widget.clearSelection()
        # self.list_widget.clear() 服了，选过之后一clear就出错Process finished with exit code -1073740791 (0xC0000409)
        self.canvas_widget.clear_selection()
        self.canvas_widget.item_dict = {}
        # self.canvas_widget.drawing = False
        self.canvas_widget.temp_algorithm = ''
        self.canvas_widget.temp_id = ''
        self.canvas_widget.temp_item = None
        self.canvas_widget.color = QColor(0, 0, 0)
        self.canvas_widget.scene().clear()
        self.canvas_widget.status = ''
        self.canvas_widget.list_widget = self.list_widget
        self.scene.setSceneRect(0, 0, width, height)
        self.canvas_widget.setFixedSize(width, height)

    def actionReset_triggered(self):
        self.list_widget.clearSelection()
        self.canvas_widget.clear_selection()
        if self.isChanged:
            reply = QMessageBox.question(None, 'Notice', 'Save your canvas?\n',
                                         QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
            if reply == QMessageBox.Yes:
                self.actionSave_triggered()
        self.newCanvasWidget.show()
        # self.resetCanvas(500, 500)

    def actionColor_triggered(self):
        color = QColorDialog.getColor()
        if color.isValid():
            # print(isinstance(color, QColor))
            self.canvas_widget.color = color

    def actionAbout_triggered(self):
        QMessageBox.about(self, 'About', '202220012 吴欣瞳\n\n978613767@qq.com')

    def closeEvent(self, a0: QtGui.QCloseEvent) -> None:
        if self.isChanged:
            reply = QMessageBox.question(None, 'Notice', 'Save your canvas?\n',
                                         QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
            if reply == QMessageBox.Yes:
                self.actionSave_triggered()
        sys.exit()

    def actionSave_triggered(self):
        self.clear_canvas_status()
        name = QFileDialog.getSaveFileName(self, "Save", "./", "Bitmap Files (*.bmp)")[0]
        # print(name)
        if name:
            canvas = np.zeros([self.canvas_widget.height(), self.canvas_widget.width(), 3], np.uint8)
            canvas.fill(255)
            for item in self.canvas_widget.item_dict.values():
                pixels = []
                if item.item_type == 'line':
                    pixels = alg.draw_line(item.p_list, item.algorithm)
                elif item.item_type == 'polygon':
                    pixels = alg.draw_polygon(item.p_list, item.algorithm)
                elif item.item_type == 'ellipse':
                    pixels = alg.draw_ellipse(item.p_list)
                elif item.item_type == 'curve':
                    pixels = alg.draw_curve(item.p_list, item.algorithm)
                elif item.item_type == 'pencil':
                    # print('pencil')
                    # print(item.algorithm)
                    pixels = alg.draw_pencil(item.p_list, 'Bresenham')
                    # print('end')
                    # print(pixels)
                color = item.color.getRgb()
                # print(color)
                pen_color = np.zeros(3, np.uint8)
                pen_color[0], pen_color[1], pen_color[2] = color[0], color[1], color[2]
                for x, y in pixels:
                    canvas[y, x] = np.array(pen_color)
            Image.fromarray(canvas).save(name, 'bmp')
            self.isChanged = False
            self.filename = name


class NewCanvasWidget(QWidget):
    def __init__(self, parent):
        super(NewCanvasWidget, self).__init__()
        self.parent = parent
        self.setWindowTitle("New")
        self.setGeometry(600, 300, 200, 100)
        self.form = QFormLayout()
        self.widthLabel = QLabel("Width:")
        self.widthIn = QLineEdit()
        self.widthIn.setValidator(QIntValidator(0, 65535))
        self.heightLabel = QLabel("Height:")
        self.heightIn = QLineEdit()
        self.heightIn.setValidator(QIntValidator(0, 65535))
        self.btn = QPushButton("OK")
        self.btn.clicked.connect(self.actionOK_triggered)
        self.form.addRow(self.widthLabel, self.widthIn)
        self.form.addRow(self.heightLabel, self.heightIn)
        self.form.addRow(self.btn)
        self.setLayout(self.form)

    def actionOK_triggered(self):
        if len(self.widthIn.text()) != 0 and len(self.heightIn.text()) != 0:
            width = int(self.widthIn.text())
            height = int(self.heightIn.text())
            print(width, height)
            self.parent.resetCanvas(width, height)
            self.hide()
        else:
            QMessageBox.warning(self, "Warning", "Please enter width and height!")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    mw = MainWindow()
    mw.show()
    sys.exit(app.exec_())
