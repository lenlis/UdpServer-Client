#ifndef HEIGHTINDICATORWIDGET_H
#define HEIGHTINDICATORWIDGET_H
#include <QMainWindow>
#include <QPainter>
#include <cmath>

class HeightIndicatorWidget : public QWidget
{
    Q_OBJECT

public:
    HeightIndicatorWidget(QWidget* parent = nullptr);
    void setHeight(int height){
        m_height = height;
    };


protected:

    void paintEvent(QPaintEvent*) override{
        float size = 0;

        if (width() > height()){
            size = window()->height()-50;
        }
        else{
            size = window()->width()-50;
        }
        QPainter painter(this);

        painter.setRenderHint(QPainter::HighQualityAntialiasing);

        painter.setPen( QPen(Qt::white,3));
        painter.setBrush(QBrush(Qt::black));
        QRectF rectWidjet;
        rectWidjet.setX(25);
        rectWidjet.setY(25);
        rectWidjet.setWidth(size);
        rectWidjet.setHeight(size);
        painter.drawRect(rectWidjet);
        painter.drawEllipse(25, 25, size, size);


        QPainter graduation(this);
        graduation.setPen(QPen(Qt::white, 3, Qt::SolidLine, Qt::FlatCap));
        graduation.setRenderHint(QPainter::HighQualityAntialiasing);
        graduation.translate(size/2+25, size/2+25);
        double newRadius = (size - 50) / 2;
        qreal angleStep = 360 / 10;
        for (int i = 0; i <= 9; i++)
        {
            graduation.save();
            graduation.rotate(i * angleStep + 270);
            graduation.drawLine(newRadius-8,0,newRadius, 0);
            graduation.restore();
            double xpos=(newRadius - 30)*cos((i * angleStep + 270.)/360.*2.*3.14159);
            double ypos=(newRadius - 30)*sin((i * angleStep + 270.)/360.*2.*3.14159);
            graduation.setFont(QFont("Comic Sans MS", size/23));
            QRectF rectF;
            rectF.setX(xpos - 20*2);
            rectF.setY(ypos - 30/2.0);
            rectF.setWidth(80);
            rectF.setHeight(30);

            graduation.drawText(rectF, Qt::AlignCenter, QString::number(i));

        }
            QPoint thousendHand[3] = {
                QPoint(15, 16),
                QPoint(-15, 16),
                QPoint(0, (-(size) / 5))
            };
            QPoint hundredHand[3] = {
                QPoint(7, 8),
                QPoint(-7, 8),
                QPoint(0, (-(size) / 3))
            };
            graduation.drawText(-(size/5.5/2), +(size/4/2), QString("Метры"));
            graduation.rotate(36.0 * ((float(m_height % 1000) / 100)));
            graduation.setBrush(QBrush(Qt::blue));
            graduation.drawConvexPolygon(hundredHand, 3);
            graduation.resetTransform();

            graduation.translate(size/2+25, size/2+25);
            graduation.rotate(36.0 * ((m_height / 1000.0)));
            graduation.setBrush(QBrush(Qt::red));
            graduation.drawConvexPolygon(thousendHand, 3);



        QPainter heightPen(this);
        heightPen.setPen(QPen(Qt::white, 2, Qt::SolidLine, Qt::FlatCap));
        heightPen.setBrush(QBrush(Qt::black));
        heightPen.setRenderHint(QPainter::HighQualityAntialiasing);
        heightPen.setFont(QFont("Comic Sans MS", size/23));
        QRectF rectH;
        rectH.setX(size/2-(size/5/2)+25);
        rectH.setY(size/2-(size/15/2)+25);
        rectH.setWidth(size/5);
        rectH.setHeight(size/15);

        heightPen.drawRect(rectH);
        heightPen.drawText(rectH, Qt::AlignCenter, QString::number(m_height));


    };

private:
    int m_height = 0;
};

#endif // HEIGHTINDICATORWIDGET_H
