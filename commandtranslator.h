#ifndef COMMANDTRANSLATOR_H
#define COMMANDTRANSLATOR_H

#include "withdrawdialog.h"
#include "ui_withdrawdialog.h"

#include <QMessageBox>

#include <fstream>
using namespace std;

class CommandTranslator
{
public:
    CommandTranslator();

    // check if the index is safety
    bool indexCheck(int num);

    // skip abunai command
    void invalidCommandSkiper(int cmd_index,fstream cmd);

    // GUI withdraw
    void withdrawGUI(string cmd_username,int cmd_index,double cmd_amount,string cmd_desc);

    // GUI deposite
    void depositeGUI(string cmd_username,int cmd_index,double cmd_amount,string cmd_desc);

    // show messagebox with custom string
    void showMessageBox(QString m_msg);

    // create savings account
    void createSavingsAccountGUI(string cmd_username,string cmd_acc_name,double cmd_rate);

    // create credit account
    void createCreditAccountGUI(string cmd_username,string cmd_acc_name,double cmd_credit,double cmd_rate,double cmd_annual_fee);

    // jump to specific date
    void dateChangeGUI(string cmd_username,int cmd_year,int cmd_month,int cmd_day);
};

#endif // COMMANDTRANSLATOR_H
