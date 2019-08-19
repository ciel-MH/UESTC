#include "markerdialog.h"
#include "ui_markerdialog.h"

MarkerDialog::MarkerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarkerDialog)
{
    ui->setupUi(this);
    pMarkerModel=new MarkerModel();
    InitDialogUi();
}

MarkerDialog::~MarkerDialog()
{
    delete pMarkerModel;
    delete ui;
}

void MarkerDialog::InitDialogUi()
{
    ui->MarkerWaveNo_Label->setText(QString("波形类型:"));
    QStringList MarkerWaveNoList;
    MarkerWaveNoList << QString("正弦波") << QString("方波") << QString("脉冲") << QString("三角波");
    ui->MarkerWaveNo_Cmb->addItems(MarkerWaveNoList);
    ui->MarkerAmp_Label->setText(QString("输出幅度:"));
    ui->MarkerPeriod_Label->setText(QString("时标周期:"));
    QStringList PeriodUnit;
    PeriodUnit << QString("ns") << QString("us") << QString("ms") << QString("s");
    ui->MarkerPeriodUnit_Cmb->addItems(PeriodUnit);
    QStringList MarkerAmpList;
    MarkerAmpList << QString("100 mVpp") << QString("200 mVpp") << QString("500 mVpp")
                  << QString("1 Vpp");
    ui->MarkerAmp_Cmb->addItems(MarkerAmpList);
   // connect(ui->MarkerPeriod_Dial,&QDial::valueChanged,ui->MarkerPeriod_Dsb,&QDoubleSpinBox::setValue);
    connect(ui->MarkerWaveNo_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
             this,static_cast<void(MarkerDialog::*)(int)>(&MarkerDialog::MarkerWaveNo_Cmb_currentIndexChanged));
    connect(ui->MarkerPeriod_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&MarkerDialog::MarkerPeriod_Dsb_valueChanged);
    connect(ui->MarkerPeriodUnit_Cmb,static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentIndexChanged),
             this,static_cast<void(MarkerDialog::*)(const QString&)>(&MarkerDialog::MarkerPeriodUnit_Cmb_currentIndexChanged));
    connect(ui->MarkerPeriodUnit_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
             this,static_cast<void(MarkerDialog::*)(int)>(&MarkerDialog::MarkerPeriodUnit_Cmb_currentIndexChanged));
    connect(ui->MarkerAmp_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
             this,static_cast<void(MarkerDialog::*)(int)>(&MarkerDialog::MarkerWaveAmp_Cmb_valueChanged));
    ui->MarkerAmp_Cmb->setCurrentIndex(1);
    ui->MarkerPeriodUnit_Cmb->setCurrentIndex(1);
    ui->MarkerWaveNo_Cmb->setCurrentIndex(1);
    ui->OutputOn_pushBtn->setText(QString("输出开"));
    ui->StandBy_pushBtn->setText(QString("输出关"));
}

void MarkerDialog::MarkerWaveNo_Cmb_currentIndexChanged(int index)
{
    switch (index){
    case 0:
        pMarkerModel->SetWaveNo(1);
        break;
    case 1:
        pMarkerModel->SetWaveNo(2);
        break;
    case 2:
         pMarkerModel->SetWaveNo(3);
        break;
    case 3:
         pMarkerModel->SetWaveNo(4);
        break;
    default:
        break;
    }
}

void MarkerDialog::MarkerWaveAmp_Cmb_valueChanged(int index)
{
    Para temp;
    switch (index) {
    case 0:
        temp.Value=100;
        temp.Unit=QString("mVpk-pk");
        break;
    case 1:
        temp.Value=200;
        temp.Unit=QString("mVpk-pk");
        break;
    case 2:
        temp.Value=500;
        temp.Unit=QString("mVpk-pk");
        break;
    case 3:
        temp.Value=1;
        temp.Unit=QString("Vpk-pk");
        break;
    default:
        break;
    }
    pMarkerModel->SetWaveAmp(temp);
}

void MarkerDialog::MarkerPeriod_Dsb_valueChanged(double val)
{
    Para temp=pMarkerModel->GetPeriodPara();
    temp.Value=val;
    pMarkerModel->SetPeriodPara(temp);
    ui->lcdNumber->display(QString::number(val));
}

void MarkerDialog::MarkerPeriodUnit_Cmb_currentIndexChanged(const QString &text)
{
    Para temp=pMarkerModel->GetPeriodPara();
    temp.Unit=text;
    pMarkerModel->SetPeriodPara(temp);
}

void MarkerDialog::MarkerPeriodUnit_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:

        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
}

void MarkerDialog::on_StandBy_pushBtn_clicked()
{
    ui->StandBy_pushBtn->setEnabled(false);
    pMarkerModel->Close();
}

void MarkerDialog::on_OutputOn_pushBtn_clicked()
{
    if(!ui->StandBy_pushBtn->isEnabled()){
        ui->StandBy_pushBtn->setEnabled(true);
    }
    pMarkerModel->WaveParaSend();
}
