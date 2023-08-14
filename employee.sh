#!/bin/bash
filename="Employee.txt"
echo "Select the option";
echo "1. insert record"
echo "2. search"
echo "3. display specific employee record"
echo "4. Delete the records"
echo "5. list the records"
echo "6. Sort record "
echo "7. Exit from menu "
echo -n "Enter your menu choice [1-6]: "

Insert(){
	echo "Enter Employee Name: \c"
	read ename

        echo "Enter Employee id: \c"
        read eid

        echo "Enter Employee mobile number \c"
        read eno

      
        echo "$eid,$ename,$eno" >> Employee.txt

        echo "Insert Sucessfully"
}

Search(){
	echo "enter the employee id"
	read eid

        flag=0
        for j in `cat Employee.txt`
        do
                    eno=$(echo "$j" | cut -d "," -f1)
                    enm=$(echo "$j" | cut -d "," -f2)
                    eage=$(echo "$j" | cut -d "," -f3)
                    if [ $eid -eq $eno ]
                    then
                            flag=1
                         echo "EName : $enm            "
                    fi
        done
        if [ $flag = 0 ]
        then
             echo "No Record Found"
        fi
}

Display(){
	echo "enter the employee id"
	read inp

        flag=0
        for j in `cat Employee.txt`
        do
                    eid1=$(echo "$j" | cut -d "," -f1)                  
		    if [ $inp -eq $eid1 ]
		    then 
		    	enm1=$(echo "$j" | cut -d "," -f2)
                    	eno1=$(echo "$j" | cut -d "," -f3)  
                    	echo "Name: $enm1"
                    	echo "Employee id: $eid1"
                    	echo "Employee number: $eno1"
		    fi
        done
 
}

Delete(){

echo "enter the employee id"
read inp
sed "/^$inp/d" $filename > "newfile.txt"
mv "newfile.txt" $filename
}

List(){
for j in `cat Employee.txt`
        do
                    eid1=$(echo "$j" | cut -d "," -f1)                  
		    	enm1=$(echo "$j" | cut -d "," -f2)
                    	eno1=$(echo "$j" | cut -d "," -f3)  
                    	echo -n "Name: $enm1  "
                    	echo -n "Employee id: $eid1  "
                    	echo -n "Employee number: $eno1"
                    	echo ""
        done
}

while true;
do

read choice

case $choice in

  1)  Insert;;

  2)  Search;;

  3)  Display;;

  4)  Delete;;
	
  5)  List;;
  7)  echo "Exit"
      exit;;

  *) echo "invalid option";;

esac
  echo -n "Enter your menu choice [1-6]: "
done
