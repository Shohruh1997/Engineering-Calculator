#include "calculator.h"
#include "ui_calculator.h"
#include <QRegularExpression>
static double calcval = 0;
double math;
bool divTrigger = false;
bool addTrigger = false;
bool multTrigger = false;
bool subTrigger = false;
bool PercTrigger = false;
bool MminusTrigger = false;
bool ACTrigger = false;
bool DotTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcval));
    QPushButton *numButtons[10];
    for(int i=0;i<10;i++)
    {
        QString butName = "Button_"+QString::number(i);
        numButtons[i]=Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i],SIGNAL(released()),this,
                SLOT(NumberPressed()));
    }
    connect(ui->Button_plus, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Button_minus, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Button_multiple, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Button_divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Button_perc, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Button_del, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Button_AC, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Button_dot, SIGNAL(released()), this,
            SLOT(DotDouble()));
    connect(ui->Button_equal, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));
    connect(ui->Button_sign, SIGNAL(released()), this,
            SLOT(SignButton()));
    math=0;
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumberPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text();
    QString DisplayVal = ui->Display->text();
    if(DotTrigger)
    {
        if(DisplayVal.toDouble()==0)
        {
            ui->Display->setText(DisplayVal+'.'+butval);
        }else{
            QString NewVal = DisplayVal +'.'+ butval;
            double dblNewVal = NewVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal,'g',16));
        }
        DotTrigger = false;
    }else
    {
        if(DisplayVal.toDouble()==0.0)
        {
           ui->Display->setText(DisplayVal+butval);
        }else{
            QString NewVal = DisplayVal + butval;
            double dblNewVal = NewVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal,'g',16));
        }
    }
}

void Calculator::MathButtonPressed()
{
    divTrigger = false;
    addTrigger = false;
    multTrigger = false;
    subTrigger = false;
    PercTrigger = false;
    MminusTrigger = false;
    ACTrigger = false;

    QString displayVal = ui->Display->text();
    calcval=displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text();
    if(QString::compare(butval,"/",Qt::CaseInsensitive)==0)
    {
        divTrigger=true;
    }else if(QString::compare(butval,"x",Qt::CaseInsensitive)==0)
    {
        multTrigger=true;
    }else if(QString::compare(butval,"+",Qt::CaseInsensitive)==0)
    {
        addTrigger=true;
    }else if(QString::compare(butval,"-",Qt::CaseInsensitive)==0)
    {
        subTrigger=true;
    }else if(QString::compare(butval,"M+",Qt::CaseInsensitive)==0)
    {
        PercTrigger=true;
    }else if(QString::compare(butval,"M-",Qt::CaseInsensitive)==0)
    {
        MminusTrigger=true;
    }else if(QString::compare(butval,"AC",Qt::CaseInsensitive)==0)
    {
        ACTrigger=true;
    }

    ui->Display->setText("");
}

void Calculator::EqualButtonPressed()
{
    double solution =0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger||subTrigger||multTrigger||divTrigger||PercTrigger||MminusTrigger||ACTrigger)
    {
        if(addTrigger)
        {
            solution = calcval + dblDisplayVal;
        }else if(subTrigger)
        {
            solution = calcval - dblDisplayVal;
        }else if(multTrigger)
        {
            solution = calcval * dblDisplayVal;
        }else if(divTrigger)
        {
            solution = calcval / dblDisplayVal;
        }else if(ACTrigger)
        {
            solution = 0.0;
        }
    }

        ui->Display->setText(QString::number(solution));
}


void Calculator::SignButton()
{
    QString displayVal = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayVal);
    if(match.hasMatch()) {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void Calculator::DotDouble()
{
DotTrigger = true;
}
