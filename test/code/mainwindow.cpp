#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction *actionPassword = new QAction;
    actionPassword->setText(tr("修改密码"));
    actionPassword->setIcon(QIcon(":/icon/2.png"));
    QAction *actionAbout = new QAction;
    actionAbout->setText(tr("关于我们"));
    actionAbout->setIcon(QIcon(":/icon/2.png"));
    QAction *loginOut = new QAction;
    loginOut->setText(tr("退出登录"));
    loginOut->setIcon(QIcon(":/icon/2.png"));


    QMenu *menu = new QMenu(ui->pushButton);
    QActionGroup *actionGroup = new QActionGroup(this);
    actionGroup->addAction(actionPassword);
    actionGroup->addAction(actionAbout);
    actionGroup->setExclusive(true); // 设置互斥


    menu->addAction(actionPassword);
    menu->addAction(actionAbout);
    menu->addSeparator();
    menu->addAction(loginOut);
    menu->setWindowFlag(Qt::FramelessWindowHint);
    menu->setAttribute(Qt::WA_TranslucentBackground);//设置圆角的关键
    //在windows下，自带的阴影效果仍然是直角，还需设置去除阴影效果
    menu->setWindowFlag(Qt::NoDropShadowWindowHint);
    actionPassword->setChecked(true);
    actionPassword->setCheckable(true);
    actionAbout->setChecked(true);
    actionAbout->setCheckable(true);
    loginOut->setChecked(true);
    loginOut->setCheckable(true);
    menu->setStyleSheet(
                "QMenu {"
                "    background-color: rgb(255, 0, 0);"
                "    /*文字设置有效*/"
                "    font-size: 14px;"
                "    font-family: PingFang SC;"
                "    font-weight: 500;"
                "    /*整体菜单的圆角*/"
                "    border-radius: 8px;"
                "    /*整体的边框*/"
                "    border: 0px solid #4A5059;"
                "    /*整体菜单的宽度*/"
                "    width: 132px;"
                "    color: #0000FF;"
                "}"
                ""
                "/*有效*/"
                "QMenu:disabled {"
                "    background-color: #000000;"
                "}"
                ""
                "/*有效*/"
                "QMenu::item {"
                "    /*item的背景色*/"
                "    background-color: rgb(0, 255, 255);"
                "    border: none;"
                "    /*item的边框*/"
                "    border: 0px solid #4A5059;"
                "    /*item的圆角*/"
                "    border-radius: 8px;"
                "    /*宽度和内容取最大值*/"
                "    padding-left: 45px;"
                "    /*宽度和内容取最大值*/"
                "    width: 80px;"
                "    /*高度有效*/"
                "    height: 32px;"
                "}"
                ""
                "/*item选中设置*/"
                "QMenu::item:selected {"
                "    background-color: rgb(0, 255, 0);"
                "    border: 1px solid #4A5059;"
                "    border-radius: 8px;"
                "    padding-left: 25px;"
                "    width: 130px;"
                "    /*宽度无效*/"
                "    height: 132px;"
                "    /*高度无效*/"
                "}"
                ""
                "/*有效*/"
                "QMenu::item:disabled {"
                "    background: #2E2F30;"
                "    border-color: #404244;"
                "    color: #67696B;"
                "}"
                ""
                "/*item的图标位置*/"
                "QMenu::icon {"
                "    padding-left: 15px;"
                "    padding-right: 0px;"
                "}"
                ""
                "/*可勾选的菜单设置*/"
                "QMenu::indicator:checked {"
                "    width: 13px;"
                "    height: 13px;"
                "    image: url(:/icon/3.png);"
                "}"
                ""
                "QMenu::indicator:unchecked {"
                "    width: 13px;"
                "    height: 13px;"
                "    image: url(:/icon/4.png);"
                "}"
                ""
                "/*分割线的宽度*/"
                "QMenu::separator {"
                "    height: 20px;"
                "    background: #AAAAAA;"
                "}"

               " QMenu:exclusive {                 "
               "     background-color: lightblue;  "
               " }                                 "
               "                                   "
               " QMenu:non-exclusive {    "
               "     background-color: lightgreen; "
               " }                                 "
                );
    ui->pushButton->setMenu(menu);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{

}
