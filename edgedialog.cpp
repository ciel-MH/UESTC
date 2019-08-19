#include "edgedialog.h"
#include "ui_edgedialog.h"

EdgeDialog::EdgeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdgeDialog)
{
    ui->setupUi(this);
    pEdgeModel=new EdgeModel();
    InitDialogUi();
}

EdgeDialog::~EdgeDialog()
{
    delete pEdgeModel;
    delete ui;
}

void EdgeDialog::InitDialogUi()
{
    QStringList UpDownList;
    UpDownList << QString("上升沿") << QString("下降沿");
    ui->EdgeUpDown_Cmb->addItems(UpDownList);
    ui->EdgeWaveNo_Label->setText(QString("波形类型:"));
    QStringList WaveNoList;
    WaveNoList << QString("500ps") << QString("150ps");
    ui->EdgeWaveNo_Cmb->addItems(WaveNoList);
    ui->EdgeAmp_Label->setText(QString("输出幅度:"));
    ui->EdgeFreq_Label->setText(QString("输出频率:"));
    QStringList AmpUnitList;
    AmpUnitList << QString("uVpk-pk") << QString("mVpk-pk") << QString("Vpk-pk");
    ui->EdgeAmpUnit_Cmb->addItems(AmpUnitList);
    QStringList FreqUnitList;
    FreqUnitList << QString("Hz") << QString("kHz") << QString("MHz");
    ui->EdgeFreqUnit_Cmb->addItems(FreqUnitList);


    connect(ui->EdgeWaveNo_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&EdgeDialog::EdgeWaveNo_Cmb_currentIndexChanged);
    connect(ui->EdgeUpDown_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&EdgeDialog::EdgeUpDown_Cmb_currentIndexChanged);
    connect(ui->EdgeAmp_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&EdgeDialog::EdgeAmp_Dsb_valueChanged);
    connect(ui->EdgeAmpUnit_Cmb,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(EdgeDialog::*)(const QString &)>(&EdgeDialog::EdgeAmpUnit_Cmb_currentIndexChanged));
  //  connect(ui->EdgeAmp_Dial,&QDial::valueChanged,ui->EdgeAmp_Dsb,&QDoubleSpinBox::setValue);
    connect(ui->EdgeAmpUnit_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(EdgeDialog::*)(int)>(&EdgeDialog::EdgeAmpUnit_Cmb_currentIndexChanged));

    connect(ui->EdgeFreq_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&EdgeDialog::EdgeFreq_Dsb_valueChanged);
    connect(ui->EdgeFreqUnit_Cmb,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(EdgeDialog::*)(const QString &)>(&EdgeDialog::EdgeFreqUnit_Cmb_currentIndexChanged));
  //  connect(ui->EdgeFreq_Dial,&QDial::valueChanged,ui->EdgeFreq_Dsb,&QDoubleSpinBox::setValue);
    connect(ui->EdgeFreqUnit_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(EdgeDialog::*)(int)>(&EdgeDialog::EdgeFreqUnit_Cmb_currentIndexChanged));

    ui->EdgeAmpUnit_Cmb->setCurrentIndex(1);
    ui->EdgeFreqUnit_Cmb->setCurrentIndex(1);
    ui->EdgeWaveNo_Cmb->setCurrentIndex(1);
    ui->EdgeUpDown_Cmb->setCurrentIndex(0);

    ui->EdgeWaveNo_Cmb->hide();
    ui->EdgeWaveNo_Label->hide();

    ui->OutputOn_pushBtn->setText(QString("输出开"));
    ui->StandBy_pushBtn->setText(QString("输出关"));
}




void EdgeDialog::EdgeWaveNo_Cmb_currentIndexChanged(int index)
{
    switch (index){
    case 0:
        pEdgeModel->SetWaveNo(Edge_500ps);
        break;
    case 1:
        pEdgeModel->SetWaveNo(Edge_150ps);
        break;
    default:
        break;
    }
}

void EdgeDialog::EdgeAmp_Dsb_valueChanged(double val)
{
    Para temp=pEdgeModel->GetWaveAmp();
    temp.Value=val;
    pEdgeModel->SetWaveAmp(temp);
    ui->lcdNumber->display(QString::number(val));
}

void EdgeDialog::EdgeAmpUnit_Cmb_currentIndexChanged(const QString &text)
{
    Para temp=pEdgeModel->GetWaveAmp();
    temp.Unit=text;
    pEdgeModel->SetWaveAmp(temp);
}

void EdgeDialog::EdgeAmpUnit_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->EdgeAmp_Dsb->setRange(0,1000);
        ui->EdgeAmp_Dial->setRange(0,1000);
        break;
    case 1:
        ui->EdgeAmp_Dsb->setRange(0,1000);
        ui->EdgeAmp_Dial->setRange(0,1000);
        break;
    case 2:
        ui->EdgeAmp_Dial->setRange(0,5);
        ui->EdgeAmp_Dsb->setRange(0,5);
        break;
    default:
        break;
    }
}

void EdgeDialog::EdgeFreq_Dsb_valueChanged(double val)
{
    Para temp=pEdgeModel->GetFrequencePara();
    temp.Value=val;
    pEdgeModel->SetFrequencePara(temp);
}

void EdgeDialog::EdgeFreqUnit_Cmb_currentIndexChanged(const QString &text)
{
    Para temp=pEdgeModel->GetFrequencePara();
    temp.Unit=text;
    pEdgeModel->SetFrequencePara(temp);
}

void EdgeDialog::EdgeFreqUnit_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->EdgeFreq_Dsb->setRange(0,1000);
        ui->EdgeFreq_Dial->setRange(0,1000);
        break;
    case 1:
        ui->EdgeFreq_Dsb->setRange(0,1000);
        ui->EdgeFreq_Dial->setRange(0,1000);
        break;
    case 2:
        ui->EdgeFreq_Dsb->setRange(0,3);
        ui->EdgeFreq_Dial->setRange(0,3);
        break;
    default:
        break;
    }
}

void EdgeDialog::EdgeUpDown_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        pEdgeModel->SetRisingFallingFlag(Edge_Rising);
        break;
    case 1:
        pEdgeModel->SetRisingFallingFlag(Edge_Falling);
        break;
    default:
        break;
    }
}

void EdgeDialog::on_StandBy_pushBtn_clicked()
{
    pEdgeModel->Close();
    ui->StandBy_pushBtn->setEnabled(false);
}

void EdgeDialog::on_OutputOn_pushBtn_clicked()
{
    if(!ui->StandBy_pushBtn->isEnabled()){
        ui->StandBy_pushBtn->setEnabled(true);
    }
    pEdgeModel->WaveParaSend();
}
