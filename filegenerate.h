#ifndef FILEGENERATE_H
#define FILEGENERATE_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QStringList>
#include <QImage>
#include <JlCompress.h>
class FileGenerate : public QThread
{
    Q_OBJECT


private:
    bool deleteDirectory(const QString &path);

public:
    FileGenerate(QObject * parent = 0);
    ~FileGenerate();
    void run();
    void setArgumentsPathStr(QString seedPathStr,QString nameList,QString savePath);


private:
    QMutex m_mutex; //锁

    QString seedPathStr;
    QString nameListStr;
    QString savePath;
    QStringList nameList;

    QImage * seedImage;
};

#endif // FILEGENERATE_H
