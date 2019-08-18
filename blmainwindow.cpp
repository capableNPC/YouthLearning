#include "blmainwindow.h"

BLMainWindow::BLMainWindow(QWidget *parent)
    : QDialog(parent)
{
    //this->setWindowTitle(tr("青年大学习"));
    this->resize(450,147);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint|Qt::WindowMinMaxButtonsHint);
    createWidgets();
    createConnects();
    createStyles();
}

BLMainWindow::~BLMainWindow()
{
    delete seedButton;
    delete seedPath;
    delete nameListButton;
    delete nameListEdit;
    delete startButton;
    delete skinButton;
    delete exitButton;
    delete mainLayout;
    delete titleBarLyaout;
    delete seedImage;
    delete thread;
    delete frameTitleBar;
}

void BLMainWindow::createWidgets()
{
    seedButton = new QPushButton;
    seedPath = new QLineEdit;
    nameListButton = new QPushButton;
    nameListEdit = new QLineEdit;
    startButton = new QPushButton;
    skinButton = new QPushButton;
    exitButton = new QPushButton;

    mainLayout = new QVBoxLayout;
    titleBarLyaout = new QHBoxLayout;
    formLayout = new QFormLayout;
    controlLyaout = new QHBoxLayout;
    seedLyaout = new QHBoxLayout;
    nameListLyaout = new QHBoxLayout;

    seedPathStr = "";
    seedImage = new QImage;
    seedLoadFlag = false;
    nameListPathStr = "";

    savePath = "";

    thread = new FileGenerate(this);

    frameTitleBar = new QFrame(this);
    windowTitle = new QLabel(tr("青年大学习"),frameTitleBar);
    minButton = new QToolButton(frameTitleBar);
    closeButton= new QToolButton(frameTitleBar);
    leftBtnClk = false;
}


void BLMainWindow::createStyles()
{
    //获取最小化、关闭按钮图标
    QPixmap minPix  = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    //设置最小化、关闭按钮图标
    minButton->setIcon(minPix);
    closeButton->setIcon(closePix);
    titleBarLyaout->addStretch();
    titleBarLyaout->addWidget(minButton);
    titleBarLyaout->addWidget(closeButton);
    titleBarLyaout->setSpacing(0);
    titleBarLyaout->setMargin(0);
    frameTitleBar->setLayout(titleBarLyaout);
    minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));


    seedButton->setText(tr("源文件"));
    seedPath->setEnabled(false);
    seedPath->setMinimumHeight(25);
    seedLyaout->addWidget(seedButton);
    seedLyaout->addWidget(seedPath);
    formLayout->addRow(seedLyaout);
    seedLyaout->setMargin(2);
    nameListButton->setText(tr("名单"));
    nameListButton->setToolTip(tr("从文件获取名单并覆盖当前名单列表里的名单,文件中一行可以有多个姓名,姓名不可跨行"));
    nameListEdit->setEnabled(true);
    nameListEdit->setToolTip(tr("每个姓名之间以 / 隔开"));
    nameListEdit->setMinimumHeight(25);
    nameListLyaout->addWidget(nameListButton);
    nameListLyaout->addWidget(nameListEdit);
    nameListLyaout->setMargin(2);
    formLayout->addRow(nameListLyaout);
    formLayout->setMargin(0);
    startButton->setText(tr("开始"));
    exitButton->setText(tr("退出"));
    skinButton->setFixedSize(25,25);
    skinButton->setStyleSheet("QPushButton{border-image: url(:/icon/skinChange.png);"
                              "background-color: none;"
                              "border-style: outset;"
                              "border-width: 1px; border-color: green; "
                              "}");
    controlLyaout->addWidget(startButton);
    controlLyaout->addWidget(skinButton);
    controlLyaout->addWidget(exitButton);
    controlLyaout->setStretch(0,3);
    controlLyaout->setStretch(1,1);
    controlLyaout->setStretch(2,3);
    controlLyaout->setMargin(5);
    mainLayout->addWidget(frameTitleBar);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(controlLyaout);
    //mainLayout->addStretch();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(10);
    this->setLayout(mainLayout);
}

void BLMainWindow::createConnects()
{

    connect(closeButton, SIGNAL(clicked()), this, SLOT(windowClosed()) );
    connect(minButton, SIGNAL(clicked()), this, SLOT(windowMin()));


    connect(seedButton,SIGNAL(clicked(bool)),this,SLOT(getSeedPath()));
    connect(nameListButton,SIGNAL(clicked(bool)),this,SLOT(getNameList()));
    connect(nameListEdit,SIGNAL(textChanged(QString)),this,SLOT(changeNameList(QString)));
    connect(startButton,SIGNAL(clicked(bool)),this,SLOT(startGenerate()));
    connect(skinButton,&QPushButton::clicked,this,&BLMainWindow::changeSkin);
    connect(exitButton,SIGNAL(clicked(bool)),this,SLOT(close()));
}

void BLMainWindow::getSeedPath()
{
    seedPathStr = QFileDialog::getOpenFileName(this,tr("打开源文件"),"","jpg files(*.jpg);;png files(*.png)");
    if(!seedPathStr.isEmpty())
    {
         if(!seedImage->load(seedPathStr))
         {
             QMessageBox::critical(this,tr("错误"),tr("不能打开文件"));
             seedPath->setText("");
             seedLoadFlag = false;
             return;
         }
         seedLoadFlag = true;
    }
    seedPath->setText(seedPathStr);
}

void BLMainWindow::getNameList()
{
    nameListPathStr = QFileDialog::getOpenFileName(this,tr("打开源文件"),"","txt files(*.txt)");
    if(!nameListPathStr.isEmpty())
    {
        QFile file(nameListPathStr);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this,tr("错误"),tr("不能打开文件"));
            nameList = "";
            nameListEdit->setText("");
            return;
        }
        QTextStream ins(&file);
        while(!ins.atEnd())
        {
            nameList += ins.readLine();
            nameList += "/";
        }
        file.close();
        nameListEdit->setText(nameList);
    }
}

void BLMainWindow::changeNameList(QString name_list)
{
    nameList = name_list;
}

void BLMainWindow::startGenerate()
{
    if(!seedLoadFlag)
    {
        QMessageBox::critical(this,tr("错误"),tr("源文件未加载"));
        return;
    }
    if(nameList.isEmpty())
    {
        QMessageBox::critical(this,tr("错误"),tr("名单为空"));
        return;
    }
    savePath = QFileDialog::getSaveFileName(this,tr("保存生成的文件"),"/","zip file(*.zip)");
    if(!savePath.isEmpty())
    {
        QFile file(savePath);
        if(file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this,tr("错误"),tr("文件已存在"));
            savePath = "";
            return;
        }
    }
    else
    {
        QMessageBox::critical(this,tr("错误"),tr("文件已存在"));
        savePath = "";
        return;
    }
    //xianchengkaishi
    thread->setArgumentsPathStr(seedPathStr,nameList,savePath);
    thread->run();
}


void BLMainWindow::setStyle(const QString &style)
{
    QFile qss(style);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}


void BLMainWindow::mousePressEvent(QMouseEvent *event)
{

    if( event->button() == Qt::LeftButton &&
            frameTitleBar->frameRect().contains(event->globalPos() - this->frameGeometry().topLeft())){
        m_Press = event->globalPos();
        leftBtnClk = true;
    }
    event->ignore();//表示继续向下传递事件，其他的控件还可以去获取
}

void BLMainWindow::mouseReleaseEvent(QMouseEvent *event)
{

    if( event->button() == Qt::LeftButton ){
        leftBtnClk = false;
    }
    event->ignore();
}

void BLMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if( leftBtnClk ){
        m_Move = event->globalPos();
        this->move( this->pos() + m_Move - m_Press );
        m_Press = m_Move;
    }
    event->ignore();
}


void BLMainWindow::windowClosed()
{
    this->close();
}
void BLMainWindow::windowMin()
{
    this->showMinimized();
}

void BLMainWindow::changeSkin()
{
    static int count = 1;
    switch (count) {
    case 0:
        qApp->setStyleSheet("");
        count = 1;
        break;
    case 1:
        qApp->setStyleSheet("");
        setStyle(":/qss/blackStyle.qss");
        count = 2;
        break;
    case 2:
        qApp->setStyleSheet("");
        setStyle(":/qss/grayStyle.qss");
        count = 3;
        break;
    case 3:
        qApp->setStyleSheet("");
        setStyle(":/qss/khakiStyle.qss");
        count = 0;
        break;
    default:
        break;
    }
}
