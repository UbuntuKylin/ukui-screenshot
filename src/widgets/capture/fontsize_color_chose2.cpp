/*
 *
 * Copyright: 2020 KylinSoft Co., Ltd.
 * Authors:
 *   huanhuan zhang <zhanghuanhuan@kylinos.cn>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "fontsize_color_chose2.h"
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QVector4D>
#define SHADOW_WIDTH  5     // 小三角的阴影宽度
#define TRIANGLE_WIDTH 20    // 小三角的宽度
#define TRIANGLE_HEIGHT 10    // 小三角的高度
#define BORDER_RADIUS 6       // 窗口边角弧度
FontSize_Color_Chose2::FontSize_Color_Chose2(QWidget *parent) :
    QWidget(parent),
    m_startx(5),
    m_triangleWidth(TRIANGLE_WIDTH),
    m_triangleHeight(TRIANGLE_HEIGHT),
    radius(1.5)
{
    context.style_settings = new QGSettings("org.ukui.style");
    context.style_name = context.style_settings->get("style-name").toString();
    setCursor(Qt::ArrowCursor);
    setWindowFlags(Qt::FramelessWindowHint);
////setAttribute(Qt::WA_TranslucentBackground);
// setAttribute(Qt::WA_TranslucentBackground);//设置窗口透明显示(毛玻璃效果)
// auto shadowEffect = new QGraphicsDropShadowEffect(this);
// shadowEffect->setOffset(0,0);
// shadowEffect->setColor(Qt::gray);
// shadowEffect->setBlurRadius(BORDER_RADIUS);
// this->setGraphicsEffect(shadowEffect);
    setProperty("useCustomShadow", true); // 启用协议
    setProperty("customShadowDarkness", 1.0); // 阴影暗度
    setProperty("customShadowWidth", 30); // 阴影边距大小
    setProperty("customShadowRadius", QVector4D(1, 1, 1, 1)); // 阴影圆角，必须大于0，这个值应该和frameless窗口本身绘制的形状吻合
    setProperty("customShadowMargins", QVector4D(30, 30, 30, 30)); // 阴影与窗口边缘的距离，一般和customShadowWidth保持一致
    this->setMouseTracking(true);
    Start_x = 10;
    Start_y = 23;
    for (int i = 0; i < 4; i++) {
        m_colorAreaList.append(QRect(Start_x, Start_y, radius*2, radius*2));
        Start_x += radius*2;
        Start_x += 10;
        Start_y -= (i+1);
        radius += (i+1);
    }
    Start_x = 91;
    Start_y = 8;
    for (int i = 4; i < 8; i++) {
        m_colorAreaList.append(QRect(Start_x, Start_y, 14, 14));
        Start_x += 24;
    }
    Start_x = 91;
    Start_y = 27;
    for (int i = 8; i < 12; i++) {
        m_colorAreaList.append(QRect(Start_x, Start_y, 14, 14));
        Start_x += 24;
    }
    m_colorAreaList.append(QRect(0, 5, 16, 46));
    m_colorAreaList.append(QRect(17, 5, 13, 46));
    m_colorAreaList.append(QRect(31, 5, 17, 46));
    m_colorAreaList.append(QRect(49, 5, 30, 46));
}

void FontSize_Color_Chose2::setStartPos(double startX)
{
    m_startx = startX;
}

void FontSize_Color_Chose2::setTriangleInfo(double width, double height)
{
    m_triangleWidth = width;
    m_triangleHeight = height;
}

void FontSize_Color_Chose2::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    //
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_startx, height()- m_triangleHeight);
    trianglePolygon << QPoint(m_startx+m_triangleWidth/2, height());
    trianglePolygon << QPoint(m_startx + m_triangleWidth, height()-m_triangleHeight);
    QPainterPath drawPath;
    drawPath.addRoundedRect(QRect(0, 0, width(), height()- m_triangleHeight),
                            BORDER_RADIUS, BORDER_RADIUS, Qt::AbsoluteSize);
    drawPath.addPolygon(trianglePolygon);
    if ((context.style_name.compare("ukui-dark") == 0)
        || (context.style_name.compare("ukui-black") == 0)) {
        painter.setBrush(QColor(25, 25, 25, 180));
        painter.drawPath(drawPath);
        for (int i = 12; i < 16; i++) {
            QRect rect = m_colorAreaList.at(i);
            painter.setBrush(QColor(Qt::black));
            painter.setOpacity(0);
            painter.drawEllipse(rect);
        }
        painter.setOpacity(1);
    } else {
        // if((context.style_name.compare("ukui-white")==0) || (context.style_name.compare("ukui-default")==0) || (context.style_name.compare("ukui-light")==0)){
        painter.setBrush(QColor(225, 225, 225, 180));
        painter.drawPath(drawPath);
        for (int i = 12; i < 16; i++) {
            QRect rect = m_colorAreaList.at(i);
            painter.setBrush(QColor(Qt::gray));
            painter.setOpacity(0);
            painter.drawEllipse(rect);
        }
        painter.setOpacity(1);
    }
    for (int i = 0; i < 4; i++) {
        QRect rect = m_colorAreaList.at(i);
        if (color_rect == rect) {
            Rect_h = rect.height()+4;
            Rect_w = rect.width() +4;
            painter.setBrush(QColor(255, 255, 255));
            painter.drawEllipse(QRect(rect.x()-2, rect.y()-2, Rect_h, Rect_w));
            if ((context.style_name.compare("ukui-dark") == 0)
                || (context.style_name.compare("ukui-black") == 0)) {
                painter.setBrush(QColor(Qt::gray));
            } else
                painter.setBrush(QColor(0, 0, 0));
            painter.drawEllipse(rect);
        } else {
            if ((context.style_name.compare("ukui-dark") == 0)
                || (context.style_name.compare("ukui-black") == 0)) {
                painter.setBrush(QColor(Qt::gray));
            } else
                painter.setBrush(QColor(78, 78, 78));
            painter.drawEllipse(rect);
        }
    }
    if ((context.style_name.compare("ukui-dark") == 0)
        || (context.style_name.compare("ukui-black") == 0)) {
        painter.setBrush(QColor(Qt::gray));
    } else
        painter.setBrush(QColor(25, 25, 25, 153));
    painter.drawRect(80, 17, 1.52, 16);
    for (int i = 4; i < 12; i++) {
        QRect rect = m_colorAreaList.at(i);
        QColor color1 = m_colorList.at(i-4);
        if (color == color1) {
            Rect_h = rect.height()+4;
            Rect_w = rect.width()+4;
            painter.setBrush(QColor(255, 255, 255));
            painter.drawRoundedRect(QRect(rect.x()-2,
                                          rect.y()-2, Rect_h, Rect_w), 2, 2, Qt::AbsoluteSize);
        }
        painter.setBrush(color1);
        painter.drawRoundedRect(m_colorAreaList.at(i), 2, 2, Qt::AbsoluteSize);
    }
}

void FontSize_Color_Chose2::mousePressEvent(QMouseEvent *e)
{
    for (int i = 0; i < 12; i++) {
        switch (i) {
        case 0:
            if (m_colorAreaList.at(12).contains(e->pos())) {
                color_rect = m_colorAreaList.at(i);
                emit font_size_change2(1);
            }
            break;
        case 1:
            if (m_colorAreaList.at(13).contains(e->pos())) {
                color_rect = m_colorAreaList.at(i);
                emit font_size_change2(3);
            }
            break;
        case 2:
            if (m_colorAreaList.at(14).contains(e->pos())) {
                color_rect = m_colorAreaList.at(i);
                emit font_size_change2(5);
            }
            break;
        case 3:
            if (m_colorAreaList.at(15).contains(e->pos())) {
                color_rect = m_colorAreaList.at(i);
                emit font_size_change2(8);
            }
            break;
        default:
            if (m_colorAreaList.at(i).contains(e->pos())) {
                color = m_colorList.at(i-4);
                if (i == 11) {
                    emit colorSelected2(QColor(225, 225, 225));
                } else
                    emit colorSelected2(color);
                break;
            }
            update();
        }
    }
}
