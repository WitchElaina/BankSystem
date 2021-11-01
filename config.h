#ifndef CONFIG_H
#define CONFIG_H

// System config
//  UserData file name
#define USER_DATA_FILE "UserData.txt"

// 储蓄账户结算周期(天)
#define SAVING_ACCOUNT_PERIOD 365

// 信用卡账户结算周期(天)
#define CREDIT_ACCOUNT_PERIOD 31

// 信用卡年费
#define CREDIT_ACCOUNT_ANNUAL_FEE 50

// invalid characters
#define INVALID_CHAR invalid_chars
#define INVALID_CHAR_NUM 10

// copyright msg
#define COPYRIGHT_MESSAGE "Author: 42024203 in USTB"
#define GITHUB_REPO_URL "\nGithub_Repo: https://github.com/LinYuanChan/BankSystem"

// index
#define SAVINGS_ACCOUNT_INDEX 0
#define CREDIT_ACCOUNT_INDEX 1
#define DEFAULT_ACCOUNT_INDEX 2

// System valid year range
#define SYSTEM_MINIMUM_YEAR 1949
#define SYSTEM_MAXIMUM_YEAR 9999

// includes
#include <QString>
#include <stdexcept>

// System file dir
// QString SYS_DIR;

#endif // CONFIG_H
