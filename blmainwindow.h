#ifndef BLMAINWINDOW_H
#define BLMAINWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "filegenerate.h"
#include <QApplication>
#include <QMouseEvent>
#include <QFrame>
#include <QPoint>
#include <QToolButton>
#include <QPixmap>
#include <QStyle>
#include <QLabel>
#include <QTextStream>

class BLMainWindow : public QDialog
{
    Q_OBJECT

public:
    BLMainWindow(QWidget *parent = 0);
    ~BLMainWindow();
    static void setStyle(const QString &style);
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void createWidgets();
    void createConnects();
    void createStyles();


private slots:
    void getSeedPath();
    void getNameList();
    void startGenerate();
    void changeSkin();
    void changeNameList(QString);
    void windowClosed();
    void windowMin();

private:
    QLabel * windowTitle;

    QPushButton * seedButton;
    QLineEdit * seedPath;
    QPushButton * nameListButton;
    QLineEdit * nameListEdit;
    QPushButton * startButton;
    QPushButton * skinButton;
    QPushButton * exitButton;
    QVBoxLayout * mainLayout;
    QHBoxLayout * titleBarLyaout;
    QFormLayout * formLayout;
    QHBoxLayout * controlLyaout;
    QHBoxLayout * seedLyaout;
    QHBoxLayout * nameListLyaout;

    QString seedPathStr;
    QImage * seedImage;
    bool seedLoadFlag;

    QString nameListPathStr;
    QString nameList;

    QString savePath;

    FileGenerate * thread;

    QFrame *frameTitleBar;
    QToolButton *minButton;
    QToolButton *closeButton;

    QPoint m_Press;
    QPoint m_Move;
    bool leftBtnClk;

};

#endif // BLMAINWINDOW_H
