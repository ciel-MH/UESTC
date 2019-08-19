#include "videotrigerdialog.h"
#include "ui_videotrigerdialog.h"

VideoTrigerDialog::VideoTrigerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VideoTrigerDialog)
{
    ui->setupUi(this);
    pVideoTrigerModel=new VideoTrigerModel();
    InitDialogUi();
}

VideoTrigerDialog::~VideoTrigerDialog()
{
    delete pVideoTrigerModel;
    delete ui;
}

void VideoTrigerDialog::on_StandBy_pushBtn_clicked()
{
    ui->StandBy_pushBtn->setEnabled(false);
    pVideoTrigerModel->close();
}

void VideoTrigerDialog::on_OutputOn_pushBtn_clicked()
{
    if(!ui->StandBy_pushBtn->isEnabled()){
        ui->StandBy_pushBtn->setEnabled(true);
    }
    pVideoTrigerModel->WaveParaSend();
}

void VideoTrigerDialog::on_VideoTriger_Polarity_Cmb_currentIndexChanged(int index)
{
    switch (index) {
        case 0:
            pVideoTrigerModel->SetPolarity(TV_POLARITY_POS);
            break;
        case 1:
            pVideoTrigerModel->SetPolarity(TV_POLARITY_NEG);
            break;
        default:
            pVideoTrigerModel->SetPolarity(TV_POLARITY_POS);
            break;
    }
}

void VideoTrigerDialog::on_VideoTriger_BrightLevel_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        pVideoTrigerModel->SetBrightLevel(TV_BRIGHTLEVEL_WHITE);
        break;
    case 1:
        pVideoTrigerModel->SetBrightLevel(TV_BRIGHTLEVEL_GRAY);
        break;
    case 2:
        pVideoTrigerModel->SetBrightLevel(TV_BRIGHTLEVEL_BLACK);
        break;
    default:
         pVideoTrigerModel->SetBrightLevel(TV_BRIGHTLEVEL_WHITE);
        break;
    }
}

void VideoTrigerDialog::on_VideoTriger_Sync_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        pVideoTrigerModel->SetSync(TV_SYNC_625);
        break;
    case 1:
        pVideoTrigerModel->SetSync(TV_SYNC_525);
        break;
    default:
        break;
    }
}

void VideoTrigerDialog::InitDialogUi()
{
    ui->VideoTriger_BrightLevel_Label->setText(QString("亮度等级"));
    ui->VideoTriger_Polarity_Label->setText(QString("极性"));
    ui->VideoTriger_Sync_Label->setText(QString("制式"));

    QStringList BrightLevelList;
    BrightLevelList << QString("白色") << QString("灰色") << QString("黑色");
    QStringList PolarityList;
    PolarityList << QString("正向") << QString("负向");
    QStringList SyncList;
    SyncList << QString("625线50HZ") << QString("525线60HZ");
    ui->VideoTriger_BrightLevel_Cmb->addItems(BrightLevelList);
    ui->VideoTriger_Polarity_Cmb->addItems(PolarityList);
    ui->VideoTriger_Sync_Cmb->addItems(SyncList);
    ui->VideoTriger_BrightLevel_Cmb->setCurrentIndex(0);
    ui->VideoTriger_Polarity_Cmb->setCurrentIndex(0);
    ui->VideoTriger_Sync_Cmb->setCurrentIndex(0);

    ui->OutputOn_pushBtn->setText(QString("输出开"));
    ui->StandBy_pushBtn->setText(QString("输出关"));
}
