#include "dcdialog.h"
#include "ui_dcdialog.h"
#include <QDebug>

DcDialog::DcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DcDialog)
{
    ui->setupUi(this);
    pDcModel=new DcModel();
    InitDialogUi();
}

DcDialog::~DcDialog()
{
    delete pDcModel;
    qDebug() << "delete pDcModel";
    delete ui;
}




void DcDialog::DcWaveNo_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        pDcModel->SetWaveNo(POSITIVE_DC);
        break;
    case 1:
        pDcModel->SetWaveNo(NEGATIVE_DC);
        break;
    default:
        break;
    }
}

void DcDialog::DcAmp_Dsb_valueChanged(double val)
{
    Para temp=pDcModel->GetWaveAmp();
    temp.Value=val;
    pDcModel->SetWaveAmp(temp);
    ui->lcdNumber->display(QString::number(val));
}

void DcDialog::DcAmpUnit_Cmb_currentIndexChanged(const QString &text)
{
    Para temp=pDcModel->GetWaveAmp();
    temp.Unit=text;
    pDcModel->SetWaveAmp(temp);
}

void DcDialog::DcAmpUnit_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->DcAmp_Dsb->setRange(0,1000);
        ui->DcAmp_Dial->setRange(0,1000);
        break;
    case 1:
        ui->DcAmp_Dsb->setRange(0,1000);
        ui->DcAmp_Dial->setRange(0,1000);
        break;
    case 2:
        if(ui->DcOhm_Cmb->currentIndex() == 0){
            ui->DcAmp_Dsb->setRange(0,150);
            ui->DcAmp_Dial->setRange(0,150);
        }else{
            ui->DcAmp_Dsb->setRange(0,8);
            ui->DcAmp_Dial->setRange(0,8);
        }
        break;
    default:
        break;
    }

}

void DcDialog::DcOhm_Cmb_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        pDcModel->SetSignalChannelOhm(HIGH_OHM);
        if(ui->DcAmpUnit_Cmb->currentIndex() == 2){
            ui->DcAmp_Dsb->setRange(0,160);
            ui->DcAmp_Dial->setRange(0,160);
        }
        break;
    case 1:
        pDcModel->SetSignalChannelOhm(LOW_OHM);
        if(ui->DcAmpUnit_Cmb->currentIndex() == 2){
            ui->DcAmp_Dsb->setRange(0,7);
            ui->DcAmp_Dial->setRange(0,7);
        }
        break;
    default:
        break;
    }
}

void DcDialog::InitDialogUi()
{

    QStringList WaveNoList;
    WaveNoList << QString("正直流") << QString("负直流");
    ui->DcWaveNo_Cmb->addItems(WaveNoList);
    QStringList AmpUnitList;
    AmpUnitList << QString("uV") << QString("mV") << QString("V");
    ui->DcAmpUnit_Cmb->addItems(AmpUnitList);
    QStringList DcOhmList;
    DcOhmList << QString("1M Ω") << QString("50 Ω");
    ui->DcOhm_Cmb->addItems(DcOhmList);



    ui->DcAmpUnit_Cmb->setCurrentIndex(1);
    ui->DcAmp_Dsb->setRange(0,1000);
    ui->DcAmp_Dial->setRange(0,1000);
    ui->DcWaveNo_Cmb->setCurrentIndex(0);
    ui->DcOhm_Cmb->setCurrentIndex(1);

    connect(ui->DcWaveNo_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&DcDialog::DcWaveNo_Cmb_currentIndexChanged);
    connect(ui->DcAmp_Dsb,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&DcDialog::DcAmp_Dsb_valueChanged);
    connect(ui->DcAmpUnit_Cmb,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(DcDialog::*)(const QString &)>(&DcDialog::DcAmpUnit_Cmb_currentIndexChanged));
  //  connect(ui->DcAmp_Dial,&QDial::valueChanged,ui->DcAmp_Dsb,&QDoubleSpinBox::setValue);
    connect(ui->DcAmpUnit_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,static_cast<void(DcDialog::*)(int)>(&DcDialog::DcAmpUnit_Cmb_currentIndexChanged));
    connect(ui->DcOhm_Cmb,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&DcDialog::DcOhm_Cmb_currentIndexChanged);

    ui->OutputOn_pushBtn->setText(QString("输出开"));
    ui->StandBy_pushBtn->setText(QString("输出关"));
}

void DcDialog::on_StandBy_pushBtn_clicked()
{
    ui->StandBy_pushBtn->setEnabled(false);
    pDcModel->Close();
}

void DcDialog::on_OutputOn_pushBtn_clicked()
{
    if(!ui->StandBy_pushBtn->isEnabled()){
        ui->StandBy_pushBtn->setEnabled(true);
    }

    pDcModel->WaveParaSend();
}
