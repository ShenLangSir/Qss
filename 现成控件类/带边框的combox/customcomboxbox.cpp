#include "customcomboxbox.h"
#include "ui_customcomboxbox.h"

#include <QPushButton>
#include <QDebug>
#include <QMouseEvent>
#include <QStyle>


CustomComboxBox::CustomComboxBox(int width, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomComboxBox),
    m_width(width)
{
    ui->setupUi(this);
    ischecked = false;
    ui->checkButton->setCheckable(true);
//    ui->widget->setWindowFlags(Qt::Popup);


    connect(ui->checkButton, &QPushButton::clicked,
            this, [ = ](bool ischeck)
    {
        ischecked = ischeck;
        if(ischeck)
        {


            ui->frame->setProperty("CustomStyle", "checked");
            ui->frame->style()->unpolish(ui->frame);
            ui->frame->style()->polish(ui->frame);
            ui->frame->update();
            this->setFocus();
            this->setFixedSize(m_width, m_list_height + 32);

            for(int i = 0; i < m_labels.size(); i++)
            {
                if(m_labels.at(i)->objectName() == m_current_text)
                {
                    m_labels.at(i)->setVisible(true);
                    m_btns.at(i)->setProperty("CustomStyle", "checked");
                    m_btns.at(i)->style()->unpolish(m_btns.at(i));
                    m_btns.at(i)->style()->polish(m_btns.at(i));
                    m_btns.at(i)->update();

                }
                else
                {
                    m_labels.at(i)->setVisible(false);
                    m_btns.at(i)->setProperty("CustomStyle", "unchecked");
                    m_btns.at(i)->style()->unpolish(m_btns.at(i));
                    m_btns.at(i)->style()->polish(m_btns.at(i));
                    m_btns.at(i)->update();

                }
            }


//            QPoint posRelativeToParent = mapToGlobal(QPoint(0, 0)); // 获取相对于父部件的位置
//            qDebug() << "posRelativeToParent" << posRelativeToParent << endl;
//            ui->widget->setGeometry(posRelativeToParent.x(), posRelativeToParent.y() + 32, this->width(), m_list_height);
            ui->widget->show();

        }
        else
        {

            ui->frame->setProperty("CustomStyle", "unchecked");
            ui->frame->style()->unpolish(ui->frame);
            ui->frame->style()->polish(ui->frame);
            ui->frame->update();
            this->setFixedSize(m_width, 32);
            ui->widget->hide();
        }
    });
    this->setFixedSize(m_width, 32);
    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout->setSpacing(0);
    ui->widget->hide();
    setFocusPolicy(Qt::StrongFocus);
    this->installEventFilter(this);
    ui->frame->setProperty("CustomStyle", "unchecked");

}

//NOTE:外部通过文件qss设置颜色不能使用rgb的格式设置，否则会失效！！！
void CustomComboxBox::setStyle(const QString &filename)
{
    QFile m_qss;
    m_qss.setFileName(filename);
    if(m_qss.open(QFile::ReadOnly))
    {
        QString style = QLatin1String(m_qss.readAll());
        this->setStyleSheet(style);
        m_qss.close();
    }
}
CustomComboxBox::~CustomComboxBox()
{
    delete ui;
}

void CustomComboxBox::setStringList(QStringList list)
{
    foreach(auto widget, m_btns)
    {
        ui->verticalLayout->removeWidget(widget);
        delete widget;
    }
    m_btns.clear();
    m_labels.clear();

    m_all_string.clear();
    m_all_string = list;

    m_list_height = list.size() * 30;
    for(int i = 0; i < list.size(); i++)
    {

        if(i == 0)
        {
            ui->checkButton->setText(list.at(0));
            m_current_text = list.at(0);
        }

        QPushButton *button = new QPushButton();

        m_btns.append(button);
        button->setFixedSize(m_width, 30);
        button->setText(list.at(i));
        QLabel *label = new QLabel(button);
        label->setObjectName(list.at(i));
        m_labels.append(label);
        label->setPixmap(QPixmap(":/view/view/customview/select_drow.png"));
        label->setFixedSize(22, 22);
        label->move(button->width() - 27, 3);
        connect(button, &QPushButton::clicked,
                this, [ = ]()
        {
            qDebug() << "按钮点击事件" << endl;

            m_current_text = button->text();
            ui->checkButton->setText(button->text());
            if(ui->checkButton->isChecked())
            {
                ui->checkButton->click();
            }
            emit currentIndexChanged(i);
            emit currentTextChanged(list.at(i));
        });

        ui->verticalLayout->addWidget(button);

    }

    if(ui->widget->isVisible())
    {
        this->setFixedSize(m_width, m_list_height + 32);

        for(int i = 0; i < m_labels.size(); i++)
        {
            if(m_labels.at(i)->objectName() == m_current_text)
            {
                m_labels.at(i)->setVisible(true);
                m_btns.at(i)->setProperty("CustomStyle", "checked");
                m_btns.at(i)->style()->unpolish(m_btns.at(i));
                m_btns.at(i)->style()->polish(m_btns.at(i));
                m_btns.at(i)->update();

            }
            else
            {
                m_labels.at(i)->setVisible(false);
                m_btns.at(i)->setProperty("CustomStyle", "unchecked");
                m_btns.at(i)->style()->unpolish(m_btns.at(i));
                m_btns.at(i)->style()->polish(m_btns.at(i));
                m_btns.at(i)->update();
            }
        }
    }

}
//实际为切换  通过index
void CustomComboxBox::setCurrentIndex(int index)
{
    emit currentIndexChanged(index);
}

//通过文字
void CustomComboxBox::setCurrentText(QString text)
{

    ui->checkButton->setText(text);
    m_current_text = text;

    emit currentTextChanged(text);
}

void CustomComboxBox::updateCurrentIndex(int index)
{
    ui->checkButton->setText(m_labels.at(index)->objectName());
    m_current_text = m_labels.at(index)->objectName();
}

void CustomComboxBox::setFixedWidthSelf(int width)
{
    m_width = width;
}

void CustomComboxBox::recycleShow()
{
    if(ischecked)
    {
        ui->checkButton->click();
    }
}

void CustomComboxBox::mousePressEvent(QMouseEvent *event)
{
    this->setFocus();

}
void CustomComboxBox::traverseWidgets(QObject *widget, QList<QObject *> &object_list)
{
    QObjectList children = widget->children();
    for(QObject *child : children)
    {
        // 处理子部件
        object_list.append(child);
        // 递归遍历子部件的子部件
        traverseWidgets(child, object_list);
    }
}
void CustomComboxBox::focusOutEvent(QFocusEvent *event)
{

    QObjectList children = this->children();
    QList<QObject *> object_list;
    traverseWidgets(this, object_list);
    bool have = false;
    for(QObject *child : object_list)
    {
        if(qApp->widgetAt(QCursor::pos()) == child)
        {
            have = true;
        }
    }
    if(have)
    {

    }
    else
    {
        this->recycleShow();
    }

}

