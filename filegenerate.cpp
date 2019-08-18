#include "filegenerate.h"

FileGenerate::FileGenerate(QObject * parent):QThread(parent)
{
    seedImage = new QImage;
}

FileGenerate::~FileGenerate()
{
    delete seedImage;
}

void FileGenerate::setArgumentsPathStr(QString seedPathStr,QString nameList,QString savePath)
{
    this->seedPathStr = seedPathStr;
    this->nameListStr = nameList;
    this->savePath = savePath;
}

void FileGenerate::run()
{
    QMutexLocker locker(&m_mutex);
    seedImage->load(seedPathStr);
    int height = seedImage->height();
    int width = seedImage->width();
    QString tempPath = "c:/YouthLearning_v0.1/";

    QDir dir;
    if(!dir.exists(tempPath)){
        dir.mkdir(tempPath);
    }
    QString tempName = "";
    int count = 0;//do-while中临时变量     定义  有错？
    do
    {
        tempName = nameListStr.section("/",count,count);
        nameList << tempName;
        ++count;
    }while (!tempName.isEmpty());//此处会在末尾插入一个空字符串
    int totalNum = nameList.size() - 1;//在总数目中减去一个
    for(int i = 0;i < totalNum;i++)
    {
        QRgb *line = (QRgb*)seedImage->scanLine(height-1);
        for(int j = 0;j<width;j++)
        {
            int r = (111+j)%255;
            int g = (100+2*j)%255;
            int b = (200+j/2)%255;
            *line = qRgb(r,g,b);
            ++line;
        }
        QString fileName = tempPath;
        seedImage->save(fileName.append(nameList.at(i)).append(seedPathStr.right(4)),nullptr,-1);
    }
    JlCompress::compressDir(savePath, tempPath);//压缩
    deleteDirectory(tempPath);
}


bool FileGenerate::deleteDirectory(const QString &path)
{
    if (path.isEmpty())
        return false;
    QDir dir(path);
    if(!dir.exists())
        return true;
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            deleteDirectory(fi.absoluteFilePath());
    }
    return dir.rmpath(dir.absolutePath());
}
