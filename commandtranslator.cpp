#include "commandtranslator.h"
#include "config.h"

CommandTranslator::CommandTranslator()
{

}

void CommandTranslator::showMessageBox(QString m_msg)
{
    QMessageBox msg;
    msg.setText(m_msg);
    msg.exec();
}

void CommandTranslator::createSavingsAccountGUI(string cmd_username,string cmd_acc_name, double cmd_rate)
{
    fstream trans_stream;
    trans_stream.open(cmd_username+".txt", ios::app);
    trans_stream<<"a s "<<" "<<cmd_acc_name<<" "<<cmd_rate<<"\n";
    showMessageBox("Create Success!");
    trans_stream.close();
}

void CommandTranslator::createCreditAccountGUI(string cmd_username, string cmd_acc_name, double cmd_credit, double cmd_rate, double cmd_annual_fee)
{
    fstream trans_stream;
    trans_stream.open(cmd_username+".txt", ios::app);
    trans_stream<<"a c "<<" "<<cmd_acc_name<<" "<<cmd_credit<<" "<<cmd_rate<<" "<<cmd_annual_fee<<"\n";
    showMessageBox("Create Success!");
    trans_stream.close();
}

void CommandTranslator::dateChangeGUI(string cmd_username, int cmd_year, int cmd_month, int cmd_day)
{
    fstream trans_stream;
    trans_stream.open(cmd_username+".txt", ios::app);
    trans_stream<<"j "<<cmd_year<<" "<<cmd_month<<" "<<cmd_day<<"\n";
    trans_stream.close();
}

bool CommandTranslator::indexCheck(int num)
{
    if(num>=DEFAULT_ACCOUNT_INDEX)
        return false;

    else
        return true;
}

void CommandTranslator::invalidCommandSkiper(int cmd_index,fstream cmd)
{
    string cmd_trash;
    if(!indexCheck(cmd_index))
        getline(cmd,cmd_trash);
}

void CommandTranslator::withdrawGUI(string cmd_username, int cmd_index, double cmd_amount, string cmd_desc)
{
    //fstream *trans_stream=new fstream;
    fstream trans_stream;
    trans_stream.open(cmd_username+".txt", ios::app);
    trans_stream<<"w "<<cmd_index<<" "<<cmd_amount<<" "<<cmd_desc<<"\n";
    showMessageBox("withdraw Success!");
    trans_stream.close();
    //delete trans_stream;
}

void CommandTranslator::depositeGUI(string cmd_username, int cmd_index, double cmd_amount, string cmd_desc)
{
    fstream trans_stream;
    trans_stream.open(cmd_username+".txt", ios::app);
    trans_stream<<"d "<<cmd_index<<" "<<cmd_amount<<" "<<cmd_desc<<"\n";
    showMessageBox("Deposite Success!");
    trans_stream.close();

}


