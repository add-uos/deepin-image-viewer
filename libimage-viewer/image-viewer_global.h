#ifndef IMAGEVIEWER_GLOBAL_H
#define IMAGEVIEWER_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QString>
#include <QPixmap>
#include <QImage>

#if defined(IMAGEVIEWER_LIBRARY)
#  define IMAGEVIEWERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define IMAGEVIEWERSHARED_EXPORT Q_DECL_IMPORT
#endif

//image viewer plugin space
namespace imageViewerSpace {

enum ItemInfoType {
    ItemTypeBlank = 1,//空白项，最上面留空使用
    ItemTypePic,
    ItemTypeVideo,
    ItemTypeTimeLineTitle, //时间线标题
    ItemTypeImportTimeLineTitle, //已导入时间线标题
    ItemTypeMountImg //设备图片
};
//图片类型
enum ImageType {
    ImageTypeBlank = 0,     //空白项，最上面留空使用
    ImageTypeDynamic,       //所有动态图
    ImageTypeStatic,        //所有静态图
    ImageTypeMulti,         //所有多页图
    ImageTypeDamaged        //所有损坏图片
};
//路径类型
enum PathType {
    PathTypeBlank = 0,     //空白项，最上面留空使用
    PathTypeLOCAL,         //本地
    PathTypeSMB,           //
    PathTypeFTP,           //
    PathTypeMTP,           //
    PathTypePTP,           //
    PathTypeAPPLE,         //苹果手机
};

struct ItemInfo {
    QString name = "";
    QString path = "";                   //路径信息
    QString md5Hash = "";                //文件md5 hash值
    ImageType imageType = ImageTypeBlank;//图片类型
    PathType pathType = PathTypeBlank;   //路径类型
    int imgOriginalWidth = 0;            //原图大小,导入图片子线程中读取
    int imgOriginalHeight = 0;           //原图大小,导入图片子线程中读取
    int imgWidth = 0;
    int imgHeight = 0;
    QString remainDays = QObject::tr("day");
    bool isSelected;
    ItemInfoType itemType = ItemTypePic;//类型，空白，图片，视频
    QImage image = QImage();
    QImage damagedPixmap = QImage();
    bool bNotSupportedOrDamaged = false;
    bool bNeedDelete = false;//删除时间线与已导入标题时使用

    QString date;
    QString num;

    friend bool operator== (const ItemInfo &left, const ItemInfo &right)
    {
        if (left.image == right.image)
            return true;
        return false;
    }
};

//图片展示方式
enum ImgViewerType {
    ImgViewerTypeNull = 0,//默认
    ImgViewerTypeLocal,   //本地图片浏览
    ImgViewerTypeAlbum    //相册浏览使用
};

}

Q_DECLARE_METATYPE(imageViewerSpace::ItemInfo)
#endif // IMAGEVIEWER_GLOBAL_H
