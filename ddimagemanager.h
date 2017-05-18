#ifndef DDIMAGEMANAGER_H
#define DDIMAGEMANAGER_H

#include <QObject>
#include <QImage>
#include <QColor>

class DDImageManager : public QObject
{
    Q_OBJECT
public:
    explicit DDImageManager(QObject *parent = 0);

    ///
    /// \brief greyScale
    /// \param origin
    /// \return
    ///  灰度处理
    ///
    QImage *greyScale(QImage *origin);
    ///
    /// \brief warm
    /// \param delta -为暗 +为亮
    /// \param origin
    /// \return
    /// 亮度处理 暖色调
    QImage *warm(int delta, QImage *origin);
    ///
    /// \brief cool
    /// \param delta
    /// \param origin
    /// \return
    ///  冷色调如果说暖色调的图片偏黄色，那么冷色调的图片应该就是偏蓝色了。
    ///  在这个方法里面我们只增加蓝色通道的值，红色和绿色的值不变。
    ///  冷色调的图片可以联想到未来，死亡或者，冷。
    ///
    QImage *cool(int delta, QImage *origin);
    ///
    /// \brief saturation
    /// \param delta
    /// \param origin
    /// \return
    /// 饱和度 我们已经说了，颜色由三个通道组成：红，绿，蓝，尽管如此，RGB不是唯一一个表示色彩的方式，
    /// 在这里，我们使用HSL格式表示色彩 - hue（色相）, saturation（饱和度）, lightness（明度）。
    /// 饱和的图像拥有更加生动的颜色，通常会比较好看，但是有一点要记住：不要滥用饱和度，因为很容易出现失真。
    ///
    QImage *saturation(int delta, QImage *origin);
    ///
    /// \brief blur
    /// \param origin
    /// \return
    /// 模糊效果
    /// 这个效果相对于之前的有一点点复杂。我们会用到一个卷积滤波器，
    /// 根据当前像素的颜色和相邻像素的颜色来获得一个新的颜色。
    /// 同时还有一个kernel的矩阵来决定计算中相邻像素的影响程度。
    QImage *blur(QImage *origin);
    ///
    /// \brief sharpen
    /// \param origin
    /// \return
    /// 锐化效果 像模糊中一样，锐化一张图片也会使用一个卷积滤波器，
    /// 但是kernel矩阵是不一样的，相邻像素对应的值是负的。
    /// 锐化能够处理模糊的照片，能够提升细节
    ///
    QImage *sharpen(QImage *origin);
signals:

public slots:
};

#endif // DDIMAGEMANAGER_H
