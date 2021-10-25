#include "commandtranslator.h"
#include "config.h"

CommandTranslator::CommandTranslator()
{

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
    //delete trans_stream;
}

void CommandTranslator::depositeGUI(string cmd_username, int cmd_index, double cmd_amount, string cmd_desc)
{
    fstream trans_stream;
    trans_stream.open(cmd_username+".txt", ios::app);
    trans_stream<<"d "<<cmd_index<<" "<<cmd_amount<<" "<<cmd_desc<<"\n";

}
