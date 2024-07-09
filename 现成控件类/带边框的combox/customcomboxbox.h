#ifndef CUSTOMCOMBOXBOX_H
#define CUSTOMCOMBOXBOX_H

#include <QLabel>
#include <QPushButton>
#include <QWidget>
class GlobalEventFilter;
namespace Ui
{
class CustomComboxBox;
}

class CustomComboxBox : public QWidget
{
    Q_OBJECT

public:
    explicit CustomComboxBox(int width, QWidget *parent = nullptr);
    ~CustomComboxBox();

    void setStringList(QStringList list);
    void setCurrentIndex(int index);
    void setCurrentText(QString text);
    void updateCurrentIndex(int index);
    void setFixedWidthSelf(int width);
    void recycleShow();
    void updateContent();

    void traverseWidgets(QObject *widget, QList<QObject *> &object_list);
    void setStyle(const QString &filename);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

signals:
    void currentIndexChanged(int index);
    void currentTextChanged(QString text);

private:
    Ui::CustomComboxBox *ui;

    QString m_current_text;
    int m_list_height;
    QList<QLabel *> m_labels;
    QList<QPushButton *> m_btns;
    QStringList m_all_string;
    int m_width;

    bool ischecked;
    bool have;




};

#endif // CUSTOMCOMBOXBOX_H
