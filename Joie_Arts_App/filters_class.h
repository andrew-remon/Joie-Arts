#ifndef FILTERS_CLASS_H
#define FILTERS_CLASS_H
#include <QImage>
#include <QQmlEngine>
#include <QObject>
#include <qstandardpaths.h>
#include <QDir>
#include <stack>



class choice{
public:
    enum mainMenuChoice
    {
        load = 1,
        AddFrame = 2, BlackAndWhite = 3, Blur = 4,
        Crop = 5, DarkenOrLighten = 6, DetectEdge = 7,
        Flip = 8, Grayscale = 9, Invert = 10, Merge = 11,
        NaturalSunlight = 12 , OilPainting = 13,
        Old_Tv = 14, Resize = 15, Rotate = 16,
        save = 17, undo = 18, redo = 19, end = 20
    };
    enum FlipFilter {
        Horizontal=1,
        Vertical=2
    };
    enum RotationAngle{
        _90degrees =1, _180degrees = 2, _270degrees=3
    };
    enum mode{
        darken=1, lighten=2
    };
};

class Filters_Class: public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged)

public:
    explicit Filters_Class(QObject *parent = nullptr);

    Q_INVOKABLE void loadImage(const QString &path);
    Q_INVOKABLE void loadSecondImage(const QString &path);

    QUrl imageSource() const;

    void setImageSource(const QUrl &source) {
        if (m_imageSource != source) {
            m_imageSource = source;
            emit imageSourceChanged();
        }
    }

    Q_INVOKABLE void saveImage(const QString &path);


    Q_INVOKABLE void applyGrayscale();
    Q_INVOKABLE void applyBnW();
    Q_INVOKABLE void applyInvert();
    Q_INVOKABLE void applyFlipFilter(int x);
    Q_INVOKABLE void applyDarkenOrLighten(float x);
    Q_INVOKABLE void applyRotatefilter(int x);
    Q_INVOKABLE void applyResizeFilter();
    Q_INVOKABLE void applyInfraRedFilter();
    Q_INVOKABLE void applyCropFilter();
    Q_INVOKABLE void applyEdgeDetetction();
    Q_INVOKABLE void applyBlur();
    Q_INVOKABLE void applyTVstatic();
    Q_INVOKABLE void applyOilFilter();
    Q_INVOKABLE void applyNaturalSunlight();
    Q_INVOKABLE void applyMergeFilter(int x);
    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();
    Q_INVOKABLE void resize(int x , int y);
    Q_INVOKABLE void crop(int x , int y , int w , int h);
    Q_INVOKABLE void applyInfraRed();
    Q_INVOKABLE void applyMidNight();
    Q_INVOKABLE void skewImage(float x);
    Q_INVOKABLE void applyGamma(float x);
    Q_INVOKABLE void applyContrast(float x);
    Q_INVOKABLE void applyVignette(float x);
    Q_INVOKABLE void applyNoise(float x);
    Q_INVOKABLE void applyFishEye();
    Q_INVOKABLE void applyToonyEffect();
    Q_INVOKABLE void applyEmboss();
    Q_INVOKABLE void applyFrame(int frameType , int thickness , int inner , int gap ,unsigned int R , unsigned int G , unsigned int B );
    Q_INVOKABLE void applyHue(float x , float y , float z);
    Q_INVOKABLE void applyGlitch();
    Q_INVOKABLE void applyPixelArt();
    Q_INVOKABLE void sharpen();
    Q_INVOKABLE void applyNightyeffect();
    Q_INVOKABLE void reset();


signals:
    void imageSourceChanged();
private:

    QUrl m_imageSource;
    QImage m_image;

    void updatePreview();

};
class Image;
extern Image secondImage;
extern Image currentImage;

#endif // FILTERS_CLASS_H
