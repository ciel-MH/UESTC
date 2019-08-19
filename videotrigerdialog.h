#ifndef VIDEOTRIGERDIALOG_H
#define VIDEOTRIGERDIALOG_H
#include "videotrigermodel.h"
#include <QDialog>

namespace Ui {
class VideoTrigerDialog;
}

class VideoTrigerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VideoTrigerDialog(QWidget *parent = 0);
    ~VideoTrigerDialog();

private slots:
    void on_StandBy_pushBtn_clicked();

    void on_OutputOn_pushBtn_clicked();

    void on_VideoTriger_Polarity_Cmb_currentIndexChanged(int index);

    void on_VideoTriger_BrightLevel_Cmb_currentIndexChanged(int index);

    void on_VideoTriger_Sync_Cmb_currentIndexChanged(int index);

private:
    Ui::VideoTrigerDialog *ui;
    VideoTrigerModel *pVideoTrigerModel;
private:
   void InitDialogUi(void);
};

#endif // VIDEOTRIGERDIALOG_H
