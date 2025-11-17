#ifndef CBULIDINBLG_H
#define CBULIDINBLG_H

#include <QDialog>
#include <QtWidgets>
#include <QDebug>
class CBulidinBlg : public QDialog
{
    Q_OBJECT

public:
    CBulidinBlg(QWidget *parent = nullptr);
    ~CBulidinBlg();
private:
    QTextEdit*   displayTextEdit;
    QPushButton* colorPushBtn;
    QPushButton* errorPushBtn;
    QPushButton* filePushBtn;
    QPushButton* fontPushBtn;
    QPushButton* inputPushBtn;
    QPushButton* pagePushBtn;
    QPushButton* progressPushBtn;
    QPushButton* printPushBtn;
    QPushButton* infrontcolor;
    QPushButton* textcolorPushBtn;
private slots:
    void doPushbtn();
    void doTextcolor();


};
#endif // CBULIDINBLG_H
