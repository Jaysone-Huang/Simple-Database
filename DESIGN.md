Design Doc

<p>
Build Table:
Create the Database's table with the size instructed, size will be the number of buckets(I put 10).
Calloc the table to be the dynamic size of the table with 10 buckets. Then calloc each bucket to the size of Customers(the struct with all the info).
</p>

<p>
Add to Table:
You ask the user for an email then hash it. 
With the hashvalue, you decide which bucket to add the new customer to by dividing by the number of buckets.
From there, you add the user's information of email, name, shoe size, and food to that bucket. Will need to calloc enough size for the new customer's info.
</p>

<p>
Look Up:
You ask the user for an email then hash it.
With the hashvalue, you decide which bucket the customer is in by dividing by the number of buckets.
In that bucket, you look for the customer by comparing the input email and the email in the bucket. If it is, print all their information, return true. If not there, search until found, if not there just return false.
</p>

<p>
Email Check:
Similar to look up, you chec the email if it's in the database by hashing the email and looking through the bucket. Search through the bucket, if found return true, return false if not found.
</p>

<p>
List Users:
User a for loop to loop through the table's buckets then use a Customer's node to loop through the arrays and print all the customer's information in a formatted way. 
</p>

<p>
Save File:
Open the "customers.tsv" in a write operation. For loop through the table's buckets then use a Customer's node to write the node's info to the file using fprintf inf a formatted way with correct tab spaces and new lines. Close the file after you're done.
</p>

<p>
Delete User:
Ask the user for the email they want to delete. Hash the email and use the hashvalue to find the bucket In that bucket, search for the user's email and if found, display a message that it was found and free all the information belonging to that email then free that node and set the next node to that position. If not found, display a message that the email doesn't exist. 
</p>

<p>
Delete Table:
Call this at the quit command to end the program and free eveything so no memory leak. 
Use a for loop to loop through the buckets and free eveything inside. While inside that bucket, use a while loop to free every node's content then move on to the next node in the bucket until its NULL.
Free the Database's buckets and and free the table.
</p>

<p>
Main:
Load up the file and get each line so it can strtok the strings into their respective variables. Use the respected variables and add to the table(Database). In a while loop, display and ask the user for their command so each respective function is called. If input ios neither of the command, display a message that it is not a command and ask for a new one. The while loop will only end with the quit command to help free the entire database.
</p>
