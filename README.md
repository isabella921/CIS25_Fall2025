Week 6:
This code defines an object, saves its data to a file, and then later restores that data by loading back from the file it was saved to.
The item class stores the name of the tool as a string in the variable nameand saves the quantity as an integer in the variable quantity.
The item class has a savetofile method that saves the current data to a file using an output file stream, checks if the file was opened successfuly, and then if successful, it saves the item's name and quantity to the file.
The item class also has a loadfromfile method that using an input file stream, checks if the file caan be oepened, and then reads the data saved to the file and assigns the data back to the item;s name and quantity variable.
the main function first creates an item object named tool, initializes the name and quantity values to Wrench and 25, saves that data to the data.txt file, loads it from the file and overwrites the placeholder value, and then prints the retrieved data to make sure it was run correctly.
