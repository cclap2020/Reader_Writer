#include <iostream>
using namespace std;

//global variable
//This program uses TestandSet method.

bool key = true;
bool writerkey = true;
bool readerkey = true;
bool lock = false;
int CSvalue = 0;
int r1counter = 0, r2counter = 0, r3counter = 0, w1counter = 0, w2counter = 0; // Counter, used to change cases.

bool TestandSet(bool *target)
{
	bool rv = *target;
	*target = true;
	return rv;

}


void Reader1()
{
	switch (r1counter)
	{
		//==========================In Non-Critical Section=================================================
	case 0: cout << "This is reader 1, I am in non-critial section.\n"; r1counter++; break;
	case 1: cout << "This is reader 1, I want to enter critial section\n"; r1counter++; break;
		//==========================Checking the lock=======================================================
	case 2:
		if (writerkey == readerkey && readerkey != lock) {
			readerkey = false;
			
				while (TestandSet(&lock))
				{
					cout << "R1, the door is locked"; break;// announce door is lock. 
				}
				r1counter++; // r1counter after break allows me to move to other process when it find out it is locked. It will back to here. 
			
		}
		//==========================In the Critical Section==========================================================
	case 3:	cout << "\n*****Reader 1 is in CS. Reader 1 reads CSvalue, and the value is: " << CSvalue << "*****\n" << endl; r1counter++;
		//==========================Release the lock========================================================
	case 4:	lock = false;
		readerkey = true; cout << "R1, Lock is released.\n"; r1counter++; break; // TestandSet method.
	//==========================Accounce the process is completed=======================================
	case 5: cout << "Reader1 was done.\n";  break;
	default: cout << "R1, NO CASE FOUND!! ERROR.\n" << endl;

	}
}

void Reader2()
{
	switch (r2counter)
	{
		//==========================In Non-Critical Section================================================
	case 0: cout << "This is reader 2, I am in non-critial section.\n"; r2counter++; break;
	case 1: cout << "This is reader 2, I want to enter critial section\n";  r2counter++; break;
		//==========================Checking the lock======================================================
	case 2:
		if (writerkey == readerkey && readerkey != lock)
		{
			readerkey = false;
			
				while (TestandSet(&lock))
				{
					cout << "R2, the door is locked";  // announce door is lock. 
				}
				r2counter++; // r2counter after break allows me to move to other process when it find out it is locked. It will back to here. 
			
		}//==========================In Critical Section====================================================
	case 3:	cout << "\n*****Reader 2 is in CS. Reader 2 reads CSvalue, and the value is: " << CSvalue << "*****"
		<< endl << endl; r2counter++; break;
		//==========================Releasing the lock=====================================================
	case 4: lock = false; 
			readerkey = true; cout << "R2, Lock is released.\n"; r2counter++; break;
		//==========================Accounce the Reader 2 has finished=====================================
	case 5: cout << "Reader2 was done.\n"; break;
	default: cout << "R2, NO CASE FOUND!! ERROR.\n" << endl;

	}
}


void Reader3()
{
	switch (r3counter)
	{
		//===========================In Non-Critical Section===============================================
	case 0: cout << "This is reader 3, I want to enter critial section\n"; r3counter++; break;
		//===========================Checking the lock=====================================================
	case 1:
		if (writerkey == readerkey && readerkey != lock)
		{
			readerkey = false;
			
				while (TestandSet(&lock))
				{
					cout << "R3, the door is locked"; break; // announce door is lock. 
				}
				r3counter++; // r3counter after break allows me to move to other process when it find out it is locked. It will back to here. 
			
		}
		//===========================In Critical Section===================================================
	case 2: cout << "\n*****Reader 3 is in CS now. Reader 3 reads CSvalue, and the value is: " << CSvalue << "*****\n" << endl; r3counter++; break;
		//===========================Release the lock======================================================
	case 3: lock = false;
		readerkey = true; cout << "R3, Lock is released.\n"; r3counter++; break; // TestandSet method.
	//===========================Accounce Reader 3 has finished========================================
	case 4: cout << "Reader3 was done.\n";  break;
	default: cout << "\nR3, NO CASE FOUND!! ERROR.\n";

	}
}

int Writer1()
{
	switch (w1counter)
	{
		//===========================In non critical section===============================================
	case 0: cout << "I am writer 1, and I am doing nothing now, because I am lazy.\n"; w1counter++; break;
	case 1: cout << "I am writer 1, I finally want to write something to CSValue now\n"; w1counter++; break;
		//===========================checking lock before CS===================================================
	case 2:
		if (writerkey == readerkey && writerkey != lock) // This allows check for either if there is any reader in there or not.
		{
			writerkey = false;
			{
				while (TestandSet(&lock))
				{
					cout << "w1, the door is locked"; break; // announce door is lock. 
				}
				w1counter++; // w1counter after break allows me to move to other process when it find out it is locked. It will back to here. 
			}		//===========================CS==================================================
	case 3: for (int i = 0; i <= 20; i++) { CSvalue++; }
		  cout << "\n*****I am writer 1, and I am done. I am going to release the lock.*****\n" << endl; w1counter++; break;
		  //===========================Release the lock============================================================
	case 4:  lock = false;
			 writerkey = true; cout << "W1 Lock is released.\n"; w1counter++; break;
		//===========================Accounce Writer 1 has finished===============================================
	case 5: cout << "Writer 1 was done.\n"; break;
	default: cout << "W1, NO CASE FOUND!! ERROR.\n" << endl;
		}
	}
	return CSvalue;
}
int Writer2()
{
	switch (w2counter)
	{
		//===========================In non critical section===============================================
	case 0: cout << "I am writer 2, I want to write something to CSValue now\n"; w2counter++; break;
		//===========================checking lock before CS===================================================
	case 1:
		if (writerkey == readerkey && writerkey != lock)
		{
			writerkey = false;
			
			{
				while (TestandSet(&lock))
				{
					cout << "w2, the door is locked"; break; // announce door is lock. 
				}
				w2counter++; // w2counter after break allows me to move to other process when it find out it is locked. It will back to here. 
			}
		}//===========================CS==================================================
	case 2: CSvalue = 2; cout << "\n*****I am writer 2 , and I changed CSvalue to 2.*****\n" << endl; w2counter++; break;
		//===========================Release the lock============================================================
	case 3: lock = false;
			writerkey = true; cout << "W2 Lock is released.\n";  w2counter++; break;
		//============================Accounce Writer 2 has finshed==============================================
	case 4: cout << "Writer 2 was done.\n"; break;
	default: cout << "W2, NO CASE FOUND!! ERROR.\n" << endl;
	}
	return CSvalue;
}


int main()
{

	int choose;
	int number = 32;

	cout << "\nProgram Test For TestandSet Start.\n==============================================\n";

	while (number != 0)
	{
		choose = rand() % 5;
		switch (choose)
		{
		case 0: Reader1(); break;
		case 1: Reader2(); break;
		case 2: Reader3(); break;
		case 3: Writer1(); break;
		case 4: Writer2(); break;
		default: cout << "Something is wrong!!!!!!!!!!";
		}
		number--;
	}

	cout << "\nPrograme Test has finished.\n\n\n==============================================";
	return 0;
}


