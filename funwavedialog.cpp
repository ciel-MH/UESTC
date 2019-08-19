#include "funwavedialog.h"
#include "ui_funwavedialog.h"

FunWaveDialog::FunWaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FunWaveDialog)
{
    ui->setupUi(this);
    pFunWaveModel=new FunWaveModel();
    InitDialogUi();
}

FunWaveDialog::~FunWaveDialog()
{
    delete pFunWaveModel;
    delete ui;
}

void FunWaveDialog::InitDialogUi()
{

    ui->FunWaveAmp_Label->setText(QString("输出幅度:"));
    ui->FunWaveFreq_Label->setText(QString("输出频率:"));
    ui->FunWaveNo_Label->setText(QString("波形类型:"));

    ui->OutputOn_pushBtn->setText(QString("输出开"));
    ui->StandBy_pushBtn->setText(QString("输出关"));
    QStringList AmpUnitList;
    AmpUnitList << QString("uVpk-pk") << QString("mVpk-pk") << QString("Vpk-pk");
    ui->FunWaveAmpUnit_Cmb->addItems(AmpUnitList);
    QStringList FreqUnitList;
    FreqUnitList << QString("Hz") << QString("kHz");
    ui->FunWaveFreqUnit_Cmb->addItems(FreqUnitList);
    QStringList WaveNoList;
    WaveNoList <<  QString("正弦波") << QString("线性三角波")
               << QString("方波");
    ui->FunWaveNo_Cmb->addItems(WaveNoList);

    QStringList FunWaveOhmList;
    FunWaveOhmList<< QString("1M Ω") << QString("50 Ω");
    ui->FunOhm_Cmb->addItems(FunWaveOhmList);
    connect(ui->FunWaveNo_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&FunWaveDialog::FunWaveNo_Cmb_currentIndexChanged);

    connect(ui->FunWaveAmp_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&FunWaveDialog::FunWaveAmp_Dsb_valueChanged);
    connect(ui->FunWaveAmpUnit_Cmb,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(FunWaveDialog::*)(const QString &)>(&FunWaveDialog::FunWaveAmpUnit_Cmb_currentIndexChanged));
  //  connect(ui->FunWaveAmp_Dial,&QDial::valueChanged,ui->FunWaveAmp_Dsb,&QDoubleSpinBox::setValue);
    connect(ui->FunWaveAmpUnit_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(FunWaveDialog::*)(int)>(&FunWaveDialog::FunWaveAmpUnit_Cmb_currentIndexChanged));

    connect(ui->FunWaveFreq_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&FunWaveDialog::FunWaveFreq_Dsb_valueChanged);
    connect(ui->FunWaveFreqUnit_Cmb,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(FunWaveDialog::*)(const QString &)>(&FunWaveDialog::FunWaveFreqUnit_Cmb_currentIndexChanged));
  //  connect(ui->FunWaveFreq_Dial,&QDial::valueChanged,ui->FunWaveFreq_Dsb,&QDoubleSpinBox::setValue);
    connect(ui->FunWaveFreqUnit_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(FunWaveDialog::*)(int)>(&FunWaveDialog::FunWaveFreqUnit_Cmb_currentIndexChanged));
    connect(ui->FunOhm_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&FunWaveDialog::FunWaveOhm_Cmb_currentIndexChanged);
}

void FunWaveDialog::FunWaveOhm_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        pFunWaveModel->SetSignalChannelOhm(HIGH_OHM);
        if(ui->FunWaveAmpUnit_Cmb->currentIndex() == 2){
            ui->FunWaveAmp_Dsb->setRange(0,150);
            ui->FunWaveAmp_Dial->setRange(0,150);
        }
        break;
    case 1:
        pFunWaveModel->SetSignalChannelOhm(LOW_OHM);
        if(ui->FunWaveAmpUnit_Cmb->currentIndex() == 2){
            ui->FunWaveAmp_Dsb->setRange(0,6);
            ui->FunWaveAmp_Dial->setRange(0,6);
        }
        break;
    default:
        break;
    }
}


void FunWaveDialog::FunWaveNo_Cmb_currentIndexChanged(int Index)
{
    switch (Index) {
    case 0:
        pFunWaveModel->SetWaveNo(1);
        break;
    case 1:
        pFunWaveModel->SetWaveNo(2);
        break;
    case 2:
        pFunWaveModel->SetWaveNo(3);
        break;
    default:
        break;
    }
}

void FunWaveDialog::FunWaveAmp_Dsb_valueChanged(double val)
{
    Para temp=pFunWaveModel->GetWaveAmp();
    temp.Value=val;
    pFunWaveModel->SetWaveAmp(temp);
    ui->lcdNumber->display(QString::number(val));
}

void FunWaveDialog::FunWaveAmpUnit_Cmb_currentIndexChanged(const QString &text)
{
    Para temp=pFunWaveModel->GetWaveAmp();
    temp.Unit=text;
    pFunWaveModel->SetWaveAmp(temp);
}

void FunWaveDialog::FunWaveAmpUnit_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->FunWaveAmp_Dsb->setRange(0,1000);
        ui->FunWaveAmp_Dial->setRange(0,1000);
        break;
    case 1:
        ui->FunWaveAmp_Dsb->setRange(0,1000);
        ui->FunWaveAmp_Dial->setRange(0,1000);
        break;
    case 2:
        if(ui->FunOhm_Cmb->currentIndex() == 1){
            ui->FunWaveAmp_Dial->setRange(0,6);
            ui->FunWaveAmp_Dsb->setRange(0,6);
        }
        if(ui->FunOhm_Cmb->currentIndex() == 0){
            ui->FunWaveAmp_Dial->setRange(0,150);
            ui->FunWaveAmp_Dsb->setRange(0,150);
        }
        break;
    default:
        break;
    }
}

void FunWaveDialog::FunWaveFreq_Dsb_valueChanged(double freq)
{
    Para temp=pFunWaveModel->GetFrequencePara();
    temp.Value=freq;
    pFunWaveModel->SetFrequencePara(temp);
}

void FunWaveDialog::FunWaveFreqUnit_Cmb_currentIndexChanged(const QString &text)
{
    Para temp=pFunWaveModel->GetFrequencePara();
    temp.Unit=text;
    pFunWaveModel->SetFrequencePara(temp);
}

void FunWaveDialog::FunWaveFreqUnit_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->FunWaveFreq_Dsb->setRange(0,1000);
        ui->FunWaveFreq_Dial->setRange(0,1000);
        break;
    case 1:
        ui->FunWaveFreq_Dsb->setRange(0,1000);
        ui->FunWaveFreq_Dial->setRange(0,1000);
        break;
    case 2:
        ui->FunWaveFreq_Dsb->setRange(0,1);
        ui->FunWaveFreq_Dial->setRange(0,1);
        break;
    case 3:
        ui->FunWaveFreq_Dsb->setRange(0,1);
        ui->FunWaveFreq_Dial->setRange(0,1);
        break;
    default:
        break;
    }
}

void FunWaveDialog::on_StandBy_pushBtn_clicked()
{
    ui->StandBy_pushBtn->setEnabled(false);
    pFunWaveModel->Close();
}

void FunWaveDialog::on_OutputOn_pushBtn_clicked()
{
    if(!ui->StandBy_pushBtn->isEnabled()){
        ui->StandBy_pushBtn->setEnabled(true);
    }
    pFunWaveModel->WaveParaSend();
}
