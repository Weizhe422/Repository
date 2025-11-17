#include "cbulidinblg.h"
#include <QtPrintSupport/qprinter.h>
#include <QtPrintSupport/qpagesetupdialog.h>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
CBulidinBlg::CBulidinBlg(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout* gridLayout = new QGridLayout;
    displayTextEdit = new  QTextEdit(QStringLiteral("QT的標準通用對話盒"));
    colorPushBtn = new  QPushButton(QStringLiteral("顏色對話盒"));
    errorPushBtn = new  QPushButton(QStringLiteral("錯誤訊息盒"));
    filePushBtn = new  QPushButton(QStringLiteral("檔案對話盒"));
    fontPushBtn = new  QPushButton(QStringLiteral("字體對話盒"));
    inputPushBtn = new  QPushButton(QStringLiteral("輸入對話盒"));
    pagePushBtn = new  QPushButton(QStringLiteral("頁面設定對話盒"));
    progressPushBtn = new  QPushButton(QStringLiteral("進度對話盒"));
    printPushBtn = new  QPushButton(QStringLiteral("列印對話盒"));
    textcolorPushBtn = new  QPushButton(QStringLiteral("設定文字顏色"));


    gridLayout->addWidget(colorPushBtn,0,0,1,1);
    gridLayout->addWidget(errorPushBtn,0,1,1,1);
    gridLayout->addWidget(filePushBtn,0,2,1,1);
    gridLayout->addWidget(fontPushBtn,1,0,1,1);
    gridLayout->addWidget(inputPushBtn,1,1,1,1);
    gridLayout->addWidget(pagePushBtn,1,2,1,1);
    gridLayout->addWidget(progressPushBtn,2,0,1,1);
    gridLayout->addWidget(printPushBtn,2,1,1,1);
    gridLayout->addWidget(displayTextEdit,3,0,3,3);
    gridLayout->addWidget(textcolorPushBtn,2,2,1,1);


    setLayout(gridLayout);
    setWindowTitle(QStringLiteral("內建對話盒展示"));
    resize(400,300);
    connect(colorPushBtn,SIGNAL(clicked()),this,SLOT(doPushbtn()));
    connect(errorPushBtn,SIGNAL(clicked()),this,SLOT(doPushbtn()));
    connect(filePushBtn,SIGNAL(clicked()),this,SLOT(doPushbtn()));
    connect(fontPushBtn,SIGNAL(clicked()),this,SLOT(doPushbtn()));
    connect(inputPushBtn,SIGNAL(clicked()),this,SLOT(doPushbtn()));
    connect(pagePushBtn,SIGNAL(clicked()),this,SLOT(doPushbtn()));
    connect(progressPushBtn,SIGNAL(clicked()),this,SLOT(doPushbtn()));
    connect(printPushBtn,SIGNAL(clicked()),this,SLOT(doPushbtn()));
    connect(textcolorPushBtn,SIGNAL(clicked()),this,SLOT(doTextcolor()));

}


CBulidinBlg::~CBulidinBlg() {}

void CBulidinBlg::doPushbtn()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(btn==colorPushBtn)
    {
        QPalette palette = displayTextEdit->palette();
        const QColor& color=
            QColorDialog::getColor(palette.color(QPalette::Base),
                                                     this,QStringLiteral("設定背景顏色"));
        if(color.isValid())
        {
            palette.setColor(QPalette::Base,color);
            displayTextEdit->setPalette(palette);
        }
    }
    if(btn == errorPushBtn)
    {
        QErrorMessage box(this);
        box.setWindowTitle(QStringLiteral("錯誤訊息盒"));
        box.showMessage(QStringLiteral("錯誤訊息盒實例xx:"));
        box.showMessage(QStringLiteral("錯誤訊息盒實例yy:"));
        box.showMessage(QStringLiteral("錯誤訊息盒實例zz:"));
        box.exec();
    }
    if(btn == filePushBtn)
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        QStringLiteral("打開檔案"),".",QStringLiteral("任何檔案(*.*)"
                                                                       ";;文字檔(*.txt)"
                                                                       ";;XML檔(*.xml)"));
        displayTextEdit->setText(fileName);
    }
    if(btn == fontPushBtn){
        bool ok;
        const QFont& font = QFontDialog::getFont(&ok,displayTextEdit->font(),this,QStringLiteral("字體對話盒"));
        if(ok) displayTextEdit->setFont(font);
    }
    if(btn == inputPushBtn)
    {
        bool ok;
        QString text = QInputDialog::getText(this,
                                             tr("輸入對話盒"),
                                             tr("輸入文字"),
                                             QLineEdit::Normal,
                                             QDir::home().dirName(),
                                             &ok
                                             );
        if(ok &&!text.isEmpty()) displayTextEdit->setText(text);
    }
    if(btn == pagePushBtn)
    {
        QPrinter printer(QPrinter::HighResolution);
        QPageSetupDialog* dlg = new QPageSetupDialog(&printer,this);
        dlg->setWindowTitle(tr("頁面設定話方塊"));
        if(dlg->exec()==QDialog::Accepted)
        {

        }
    }
    if(btn == progressPushBtn)
    {
        QProgressDialog progress(tr("正在複製檔案..."),
                                 tr("cancel"),
                                 0,
                                 10000,
                                 this);
        progress.setWindowTitle(tr("進度對話盒"));
        progress.show();
        for(int i =0;i<10000;i++){
            progress.setValue(i);
            qApp->processEvents();
            qDebug()<<i;
        }
        //_sleep(10000);
    }
    if(btn==infrontcolor)
    {
        QPalette palette = displayTextEdit->palette();
        const QColor& color=
            QColorDialog::getColor(palette.color(QPalette::Base),
                                   this,QStringLiteral("設定背景顏色"));
        if(color.isValid())
        {
            palette.setColor(QPalette::Base,color);
            displayTextEdit->setPalette(palette);
        }
    }
    if (btn == printPushBtn)
    {
        // Declare the printer object and print dialog
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog dialog(&printer, this);

        // Open the print dialog and check if the user accepted the dialog
        if (dialog.exec() != QDialog::Accepted)
            return; // Exit if the user cancels the dialog

        // If needed, you can now add printing logic here, like using QPainter
        // Example: Printing some basic text
        QPainter painter(&printer);
        if (painter.begin(&printer)) {
            painter.drawText(100, 100, "Hello, this is a test print!");
            painter.end(); // End the painter operation
        }
    }
}
void CBulidinBlg::doTextcolor()
{
    QColor color = QColorDialog::getColor(Qt::black, this, QStringLiteral("設定文字顏色"));
    if (color.isValid())
    {
        // 取得 QTextCursor
        QTextCursor cursor = displayTextEdit->textCursor();

        // 選取全部文字
        cursor.select(QTextCursor::Document);

        // 設定文字顏色
        QTextCharFormat fmt;
        fmt.setForeground(color);
        cursor.mergeCharFormat(fmt);
    }
}
