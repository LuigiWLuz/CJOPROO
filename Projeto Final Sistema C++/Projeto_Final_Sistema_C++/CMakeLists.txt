cmake_minimum_required(VERSION 3.30)
project(_SistemaATM)

set(CMAKE_CXX_STANDARD 20)

add_executable(_SistemaATM main.cpp
            Account.h
            Account.cpp
            ATM.h
            ATM.cpp
            BalanceInquiry.h
            BalanceInquiry.cpp
            BankDatabase.h
            BankDatabase.cpp
            CashDispenser.h
            CashDispenser.cpp
            Deposit.h
            Deposit.cpp
            DepositSlot.h
            DepositSlot.cpp
            Keypad.h
            Keypad.cpp
            Screen.h
            Screen.cpp
            Transaction.h
            Transaction.cpp
            Withdrawal.h
            Withdrawal.cpp)
