#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QBrush>
#include <QObject>
#include <QDebug>
#include <QMouseEvent>
#include <QList>

class AbstractInstrument;

class DrawingBoard : public QQuickPaintedItem
{
    Q_OBJECT

public:
    DrawingBoard(QQuickItem *parent = 0);

    // paint() will be called when update() is called
    void paint(QPainter *painter);

public:
    Q_INVOKABLE void handleMousePress(int x, int y, int button, int buttons, int modifiers);
    Q_INVOKABLE void handleMouseRelease(int x, int y, int button, int buttons, int modifiers);
    Q_INVOKABLE void handleMouseMove(int x, int y, int button, int buttons, int modifiers);
    Q_PROPERTY(InstrumentType instrument READ instrument WRITE setInstrument)
    Q_PROPERTY(int thickness READ thickness WRITE setThickness)
    Q_PROPERTY(int opaqueness READ opaqueness WRITE setOpaqueness)
    Q_PROPERTY(QColor brushColor READ brushColor WRITE setBrushColor)

public:
    enum InstrumentType {
        INSTRUMENT_NONE = 0,
        BRUSH_PIXEL,
        SHAPE_LINE,

        // Don't use it. (Used to know count of instruments)
        INSTRUMENTS_COUNT
    };
    Q_ENUM(InstrumentType)

public:
    void setIsInPaint(bool isInPaint) { m_isInPaint = isInPaint; }
    bool isInPaint() { return m_isInPaint; }
    QImage* getImage() { return m_image; }
    void setImage(const QImage &image) { *m_image = image; }
    InstrumentType instrument() { return m_instrument; }
    void setInstrument(InstrumentType instrument) { m_instrument = instrument; qDebug() << instrument;}
    int thickness() { return m_thickness; }
    void setThickness(int thickness) { m_thickness = thickness; qDebug() << thickness; }
    int opaqueness() { return m_opaqueness; }
    void setOpaqueness(int opaqueness) { m_opaqueness = opaqueness; qDebug() << opaqueness; }
    QColor brushColor() { return m_brushColor; }
    void setBrushColor(QColor brushColor) { m_brushColor = brushColor; qDebug() << brushColor; }

private:
    QImage *m_image = nullptr;
    bool m_isInPaint = false;
    int m_thickness = 1;
    int m_opaqueness = 100; // 1~100
    QColor m_brushColor = Qt::black;
    QVector<AbstractInstrument*> m_instrumentHandlers;
    InstrumentType m_instrument = INSTRUMENT_NONE;
};

#endif // DRAWINGBOARD_H
