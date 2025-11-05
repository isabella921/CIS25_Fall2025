this code simulates a bank account's transactions and records it in a text file transactions.txt (included in branch).
i used a c++ file stream in order to read and write to the transactions.txt file.
first, this code implements a bank_account class that manages the account's balance and operations.
the bank_account class is initialized with an intial balance and records an initial deposit.
then, the deposit method allows the user to add funds to the balance and the transaction will be recorded in the text file
the makepurchase method firstly deducts the cost from the bank account balance(only if there are enough funds) and then it records the purchase along with the item name in the text file
the print final balance method displays the current balance to the terminal/console
i used a helper function savetransaction in order to save each deposit, transaction, and the intial deposit into the text file
i also used displaytransaction history to read the transactions.txt file and print it to the console.

when this file is run,  it first adds the initial deposit of $650 to the empty bank account.
then there is a transaction for $25.50 at a cafe
then there is a transaction that cannot go through (apple laptop) because there is not enough funds in the bank account
then there is a deposit of $200 which is added to the total balance in the bank account
then there is a transaction for $50.00 at trader joes for groceries.
all of these transactions are recorded in the attatched text file (transactions.txt)

i have also included a screenshot as pdf of the outputs from the console when this code is ran.
