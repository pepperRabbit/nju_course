#!/usr/bin/env python
# -*- coding:utf-8 -*-

# 本文件只允许依赖math库
import math


def draw_line(p_list, algorithm):
    """绘制线段

    :param p_list: (list of list of int: [[x0, y0], [x1, y1]]) 线段的起点和终点坐标
    :param algorithm: (string) 绘制使用的算法，包括'DDA'和'Bresenham'，此处的'Naive'仅作为示例，测试时不会出现
    :return: (list of list of int: [[x_0, y_0], [x_1, y_1], [x_2, y_2], ...]) 绘制结果的像素点坐标列表
    """
    # print(p_list[0], p_list[1])
    x0, y0 = p_list[0]
    x1, y1 = p_list[1]
    # print(x0, y0, x1, y1)
    result = []
    if algorithm == 'Naive':
        if x0 == x1:
            for y in range(y0, y1 + 1):
                result.append((x0, y))
        else:
            if x0 > x1:
                x0, y0, x1, y1 = x1, y1, x0, y0
            k = (y1 - y0) / (x1 - x0)
            for x in range(x0, x1 + 1):
                result.append((x, int(y0 + k * (x - x0))))
    elif algorithm == 'DDA':
        if x0 == x1:
            # print(y0, y1)
            if y0 >= y1:
                y0, y1 = y1, y0
            for y in range(y0, y1 + 1):
                result.append((x0, y))
            # print('x0=x1')
            # print(result)
        else:  # y=kx+b
            k = (y1 - y0) / (x1 - x0)
            if abs(k) <= 1:
                # print('abs k<=1')
                if x0 > x1:
                    x0, y0, x1, y1 = x1, y1, x0, y0
                result.append([x0, y0])
                for i in range(1, x1 - x0 + 1):
                    x0 += 1
                    y0 += k
                    result.append([x0, round(y0)])
            else:
                # print('abs k>1')
                if y0 > y1:
                    x0, y0, x1, y1 = x1, y1, x0, y0
                result.append([x0, y0])
                k = 1 / k
                for i in range(1, y1 - y0 + 1):
                    y0 += 1
                    x0 += k
                    result.append([round(x0), y0])
    elif algorithm == 'Bresenham':
        # print('bresenham')
        dx = abs(x1 - x0)
        dy = abs(y1 - y0)
        # print(dx, dy)
        result.append((x0, y0))
        if dx < dy:  # 斜率>1，xy互换
            flag = True
            x0, y0 = y0, x0
            x1, y1 = y1, x1
            dx, dy = dy, dx
        else:
            flag = False
        delta_x = 1
        delta_y = 1
        if x0 > x1:
            delta_x = -1
        if y0 > y1:
            delta_y = -1
        p = 2 * dy - dx
        while x0 != x1:
            x0 += delta_x
            if p < 0:
                p += 2 * dy
            else:
                p += 2 * (dy - dx)
                y0 += delta_y
            if flag:
                result.append((y0, x0))
            else:
                result.append((x0, y0))
    return result


def draw_polygon(p_list, algorithm):
    """绘制多边形

    :param p_list: (list of list of int: [[x0, y0], [x1, y1], [x2, y2], ...]) 多边形的顶点坐标列表
    :param algorithm: (string) 绘制使用的算法，包括'DDA'和'Bresenham'
    :return: (list of list of int: [[x_0, y_0], [x_1, y_1], [x_2, y_2], ...]) 绘制结果的像素点坐标列表
    """
    result = []
    for i in range(len(p_list)):
        # print('draw line')
        # print(p_list[i-1], p_list[i])
        # print(algorithm)
        line = draw_line([p_list[i - 1], p_list[i]], algorithm)
        result += line
    return result


def draw_ellipse(p_list):
    """绘制椭圆（采用中点圆生成算法）

    :param p_list: (list of list of int: [[x0, y0], [x1, y1]]) 椭圆的矩形包围框左上角和右下角顶点坐标
    :return: (list of list of int: [[x_0, y_0], [x_1, y_1], [x_2, y_2], ...]) 绘制结果的像素点坐标列表
    """
    # print('alg draw ellipse')
    # print(p_list)
    result = []
    x0, y0 = p_list[0]
    x1, y1 = p_list[1]
    rx = abs(x0 - x1) // 2
    ry = abs(y0 - y1) // 2
    xc = (x0 + x1) // 2
    yc = (y0 + y1) // 2
    result.append((xc, yc + ry))
    result.append((xc, yc - ry))
    rx_square = rx * rx
    ry_square = ry * ry
    rx_ry_square = rx_square * ry_square
    x = 0
    y = ry
    p = ry_square - rx_square * ry + rx_square / 4
    while ry_square * x < rx_square * y:
        # 区域1
        if p < 0:
            p += 2 * ry_square * x + 3 * ry_square
            result.append((x + 1 + xc, y + yc))
            result.append((x + 1 + xc, yc - y))
            result.append((xc - x - 1, y + yc))
            result.append((xc - x - 1, yc - y))
        else:
            p += 2 * ry_square * x - 2 * rx_square * y + 2 * rx_square + 3 * ry_square
            y -= 1
            result.append((x + 1 + xc, y + yc))
            result.append((x + 1 + xc, yc - y))
            result.append((xc - x - 1, y + yc))
            result.append((xc - x - 1, yc - y))
        x += 1
    p = ry_square * (x + 0.5) * (x + 0.5) + rx_square * (y - 1) * (y - 1) - rx_ry_square
    while y > 0:
        # 区域2
        if p <= 0:
            p += 2 * ry_square * x - 2 * rx_square * y + 2 * ry_square + 3 * rx_square
            x += 1
            result.append((x + xc, y - 1 + yc))
            result.append((xc - x, y - 1 + yc))
            result.append((x + xc, yc - y + 1))
            result.append((xc - x, yc - y + 1))
        else:
            p += 3 * rx_square - 2 * rx_square * y
            result.append((x + xc, y - 1 + yc))
            result.append((xc - x, y - 1 + yc))
            result.append((x + xc, yc - y + 1))
            result.append((xc - x, yc - y + 1))
        y -= 1
    return result


# https://www.jianshu.com/p/8f82db9556d2
def draw_curve(p_list, algorithm):
    """绘制曲线

    :param p_list: (list of list of int: [[x0, y0], [x1, y1], [x2, y2], ...]) 曲线的控制点坐标列表
    :param algorithm: (string) 绘制使用的算法，包括'Bezier'和'B-spline'（三次均匀B样条曲线，曲线不必经过首末控制点）
    :return: (list of list of int: [[x_0, y_0], [x_1, y_1], [x_2, y_2], ...]) 绘制结果的像素点坐标列表
    """
    res = []
    du = 0.001
    u = 0
    if algorithm == 'Bezier':
        # print(p_list)
        while u <= 1:
            # print(u)
            tmp = []
            my_p_list = p_list
            while len(my_p_list) > 1:
                n = len(my_p_list) - 1
                # print(n)
                for i in range(0, n):
                    tx = (1 - u) * my_p_list[i][0] + u * my_p_list[i + 1][0]
                    ty = (1 - u) * my_p_list[i][1] + u * my_p_list[i + 1][1]
                    tmp.append([tx, ty])
                my_p_list = tmp
                tmp = []
                # print('here')
            res.append([round(my_p_list[0][0]), round(my_p_list[0][1])])
            u += du
        return res
    elif algorithm == 'B-spline':
        # 三次均匀B样条曲线，直接用算好的基函数就行了
        while u <= 1:
            u3 = u ** 3
            u2 = u * u
            tmp = [-u3 + 3 * u2 - 3 * u + 1, 3 * u3 - 6 * u2 + 4, -3 * u3 + 3 * u2 + 3 * u + 1, u3]
            for i in range(0, len(p_list) - 3):
                tx = 0
                ty = 0
                for j in range(0, 4):
                    tx += tmp[j] * p_list[i + j][0]
                    ty += tmp[j] * p_list[i + j][1]
                tx /= 6
                ty /= 6
                res.append([round(tx), round(ty)])
            u += du
        return res


def draw_pencil(p_list, algorithm):
    result = []
    for i in range(1, len(p_list)):
        line = draw_line([p_list[i - 1], p_list[i]], algorithm)
        result += line
    # print('res', result)
    return result


def translate(p_list, dx, dy):
    """平移变换

    :param p_list: (list of list of int: [[x0, y0], [x1, y1], [x2, y2], ...]) 图元参数
    :param dx: (int) 水平方向平移量
    :param dy: (int) 垂直方向平移量
    :return: (list of list of int: [[x_0, y_0], [x_1, y_1], [x_2, y_2], ...]) 变换后的图元参数
    """
    result = []
    # print(p_list)
    for x, y in p_list:
        result.append((x + dx, y + dy))
    # print(result)
    return result


def rotate(p_list, x, y, r):
    """旋转变换（除椭圆外）

    :param p_list: (list of list of int: [[x0, y0], [x1, y1], [x2, y2], ...]) 图元参数
    :param x: (int) 旋转中心x坐标
    :param y: (int) 旋转中心y坐标
    :param r: (int) 顺时针旋转角度（°）
    :return: (list of list of int: [[x_0, y_0], [x_1, y_1], [x_2, y_2], ...]) 变换后的图元参数
    """
    res = []
    cos_r = math.cos(r/180*math.pi)
    sin_r = math.sin(r/180*math.pi)
    for p in p_list:
        tx = x + (p[0] - x) * cos_r - (p[1] - y) * sin_r
        ty = y + (p[0] - x) * sin_r + (p[1] - y) * cos_r
        res.append([round(tx), round(ty)])
    return res


def scale(p_list, x, y, s):
    """缩放变换

    :param p_list: (list of list of int: [[x0, y0], [x1, y1], [x2, y2], ...]) 图元参数
    :param x: (int) 缩放中心x坐标
    :param y: (int) 缩放中心y坐标
    :param s: (float) 缩放倍数
    :return: (list of list of int: [[x_0, y_0], [x_1, y_1], [x_2, y_2], ...]) 变换后的图元参数
    """
    result = []
    for p in p_list:
        x0 = round(x + (p[0] - x) * s)
        y0 = round(y + (p[1] - y) * s)
        result.append([x0, y0])
    return result


# https://www.cnblogs.com/cnblog-wuran/p/9813788.html
def clip(p_list, x_min, y_min, x_max, y_max, algorithm):
    """线段裁剪

    :param p_list: (list of list of int: [[x0, y0], [x1, y1]]) 线段的起点和终点坐标
    :param x_min: 裁剪窗口左上角x坐标
    :param y_min: 裁剪窗口左上角y坐标
    :param x_max: 裁剪窗口右下角x坐标
    :param y_max: 裁剪窗口右下角y坐标
    :param algorithm: (string) 使用的裁剪算法，包括'Cohen-Sutherland'和'Liang-Barsky'
    :return: (list of list of int: [[x_0, y_0], [x_1, y_1]]) 裁剪后线段的起点和终点坐标
    """
    # print(p_list)
    if algorithm == 'Cohen-Sutherland':
        # 外1内0
        code0 = compare(p_list[0][0], p_list[0][1], x_min, x_max, y_min, y_max)
        code1 = compare(p_list[1][0], p_list[1][1], x_min, x_max, y_min, y_max)
        if code0 | code1 == 0b0:
            # 全部在里面
            return p_list
        elif code0 & code1 != 0:
            # 全不在
            return []
        else:
            if code0 == 0b0:  # p0在裁剪区域内，交换
                new_p_list = [p_list[1], p_list[0]]
                return clip(new_p_list, x_min, y_min, x_max, y_max, algorithm)
            else:  # 确定p0的位置
                x0, y0, x1, y1 = p_list[0][0], p_list[0][1], p_list[1][0], p_list[1][1]
                if code0 & 0b0001 != 0:  # 左边
                    x = x_min
                    if x0 == x1:
                        new_p_list = [[x, y0], [x1, y1]]
                    else:
                        y = round(y0 + (y1 - y0) * (x_min - x0) / (x1 - x0))
                        new_p_list = [[x, y], [x1, y1]]
                elif code0 & 0b0010 != 0:  # 右边
                    x = x_max
                    if x0 == x1:
                        new_p_list = [[x, y0], [x1, y1]]
                    else:
                        y = round(y0 + (y1 - y0) * (x_max - x0) / (x1 - x0))
                        new_p_list = [[x, y], [x1, y1]]
                elif code0 & 0b0100 != 0:  # 下面
                    y = y_max
                    x = round(x0 + (x1 - x0) * (y_max - y0) / (y1 - y0))
                    new_p_list = [[x, y], [x1, y1]]
                else:  # 上面
                    y = y_min
                    x = round(x0 + (x1 - x0) * (y_min - y0) / (y1 - y0))
                    new_p_list = [[x, y], [x1, y1]]
                return clip(new_p_list, x_min, y_min, x_max, y_max, algorithm)
    elif algorithm == 'Liang-Barsky':
        x1, x2, y1, y2 = p_list[0][0], p_list[1][0], p_list[0][1], p_list[1][1]
        dx = x2 - x1
        dy = y2 - y1
        p = [-dx, dx, -dy, dy]
        u1, u2 = 0, 1
        q = [x1 - x_min, x_max - x1, y1 - y_min, y_max - y1]
        for i in range(0, 4):
            if p[i] == 0:
                if q[i] < 0:  # 平行且完全在窗口外
                    return []
            elif p[i] < 0:  # 入边，找最大
                u1 = max(u1, q[i]/p[i])
            elif p[i] > 0:  # 出边，找最小
                u2 = min(u2, q[i]/p[i])
            if u1 > u2:
                return []
        new_p_list = [[round(x1+u1*dx), round(y1+u1*dy)], [round(x1+u2*dx), round(y1+u2*dy)]]
        return new_p_list


def compare(x, y, x_min, x_max, y_min, y_max):
    """
         1001 |1000| 1010
         ----------------
        0001 |0000| 0010
        ----------------
        0101 |0100| 0110

    """
    up = 0b1000
    down = 0b0100
    right = 0b0010
    left = 0b0001
    result = 0b0
    if y < y_min:
        result += up
    if y > y_max:
        result += down
    if x > x_max:
        result += right
    if x < x_min:
        result += left
    return result
