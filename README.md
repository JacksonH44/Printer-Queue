# A class assignment written in C that simulates a printer queue. The printer will take in printer jobs and cycle through the process of printing one out. All code is 100% mine. 

The printer queue contains printer jobs, that unlike a real printer, are dealt with based on cycles. Instead of continuously printing the jobs, the printer cycles through 
printing the jobs until all the jobs have been printed. Jobs have a priority and number pages attribute, which are used to order the print jobs in the queue. There is also a 
bonus feature that moves the print job up to the front of the printer queue if that job has been in the queue too long.
