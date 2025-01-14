#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

int n_lines = 1;
char Alpha[26];	// List of all alphabets
char E_Alpha[26]; // List of encrypted Alphabets
char file[10000][10000]; // Complete file which is input to ecryption/decryption algorithms
char PassKey[100];	// Holds the password used in encryption/decryption
int caesar_c = 0; // Shift value for alphabets
int caesar_c_num = 0;	// Shift value for numbers
int scrambler = 0;	//Shift value for scrambling
char heading[56]={"\t\t<<<----------------IMITATION------------------>>>\n\n\n"};
char help1[500]={"\n\nImitation is an encryption program. This is the Help for Imitatio\n\n\tEncrypt:\n\tThe program uses an input in the form of a *.txt file\n\tThe user has to manually enter the password\n\tAn Encrypted file is produced in output.txt in the same folder\n\n\tDecryption:\n\tIn this mode, the user must copy the encrypted text in input.txt in the same folder and mention the key as before\n\tA Decrypted file is produced in the selected output.txt which is also present in the same folder\n"};
char Enc_head[26]={"\t\t\t\\ENCRYPTION MODE\\"};
char Dec_head[26]={"\t\t\t\\DECRYPTION MODE\\"};

             //FUNCTION PROTOTYPES//
char* encrypt( char*, char*, char* );
char* decrypt( char*, char*, char* );
void OPEN_RUN( char*, char* );
char* CLOSE_RUN( char* );
void app_string( char*, char* );
void pass_entry( char*, char, int);
void show_heading(int);
void typeout(char*, char, int);	// Output a string on the console as if being typed
    
            //MAIN FUNCTIONS//

void typeout(char* input, char time_type, int time_in_ms)
/*
time_type:
	i : individual
	t : total
*/
{
	int delay = 0;
	switch( time_type )
	{
		case 'i':
			delay = time_in_ms;	// if type is 'i', each letter will take that much time to print
			break;
		case 't':
			delay = time_in_ms / strlen( input );	// if type is 't', whole word is printed in that much time
			break;
	}
	
	Sleep( delay );
	for(int i=0; i<strlen( input ); i++)
	{
		cout << input[i];
		Sleep( delay );
	}
	
	return;
}

void show_heading(int animation)

{
	system("cls");
	switch(animation)
	{
		case 0:
			typeout(Enc_head,'t',800);
			Sleep(500);
			break;
		case 1:
			typeout(heading, 't', 1000);
			typeout(help1,'t',600);
			//typeout(version, 't', 300);
			Sleep(500);
			break;
		case 2:
			typeout(Dec_head,'t',800);
			Sleep(500);
			break;
	}
}


void pass_entry(char* password_array, char hide_char, int max_length)
{
	
	for(int i=0; i <= max_length; i++)
	{
		password_array[i] = '\0';
	}
	char pwd[max_length + 2];
	for(int i=0; i<(max_length+2); i++)
	{
		pwd[i]='\0';
	}
	
	int i=0;
	while(1)
	{
		pwd[i]=getch();
		
		if(i < max_length)
		{
			switch(pwd[i])
			{
				case 13:	// 13: Return Key
					pwd[i] = '\0';
					cout << endl;
					goto ESC;
				case 8:	// 8: Backspace
					if(i <= 0)	// Only input password can get erased
					{
						pwd[i] = '\0';
					}
					else
					{
						cout << "\b \b";
						pwd[i] = '\0';
						i = i - 1;
					}
					break;
				case 27:	// 27: Esc Key
					pwd[i] = '\0';	// Clear this char
					break;
				default:
					if(hide_char == 0)	// No special char used if 0
					{
						cout << pwd[i];
						i++;
					}
					else
					{
						cout << hide_char;
						i++;
					}
			}
		}
		else
		{
			switch(pwd[i])
			{
				case 13:
					pwd[i] = '\0';
					cout << endl;
					goto ESC;
				case 8:
					cout << "\b \b";
					pwd[i] = '\0';
					i = i - 1;
					break;
				default:
					break;	// No data entry after maximum limit
			}
		}
	}
	
	ESC:
	for(int i=0; i < max_length; i++)
	{
		password_array[i] = pwd[i];
	}
	return;
}

char* encrypt(char* input, char* password, char* output = "**")
{
	OPEN_RUN(input, password);
	
	// Caesar Cipher
	for(int i = 0; i < n_lines; i++)
	{
		for(int j = 0; j < strlen( file[i] ); j++)
		{
			// Alphabets
			if( ( file[i][j] >= 'a' && file[i][j] <='z' ) )	// If input is a small alphabet
			{
				if( file[i][j] + caesar_c - 'a' < 26 )	// If adding the shift keeps it between 'a' to 'z'
				{
					file[i][j] += caesar_c;	// Add shift
				}
				else
				{
					file[i][j] += ( caesar_c - 26 );	// Else add shift and subtract 26 to go back to the beginning of the alphabet 
				}
			}
			else if( ( file[i][j] >= 'A' && file[i][j] <='Z' ) )	// If input is a capital aplhabet
			{
				if( file[i][j] + caesar_c - 'A' < 26 )	// If adding the shift keeps it between 'A' to 'Z'
				{
					file[i][j] += caesar_c;	// Add shift
				}
				else
				{
					file[i][j] += ( caesar_c - 26 );	// Else add shift and subtract 26 to go back to the beginning of the alphabet
				}
			}
			
			
			// Numbers
			else if( file[i][j] >= '0' && file[i][j] <= '9' )	// If input is a number
			{
				if( file[i][j] + caesar_c_num - '0' <= 9 )	// If adding the shift keeps it betwwen '0' to '9'
				{
					file[i][j] += caesar_c_num;	// Add shift
				}
				else
				{
					file[i][j] += ( caesar_c_num - 10 );	// Else add shift and subtract 10 to go back to beginnnig of the number series
				}
			}
		}
	}
	
	
	// Secret Encryption
	for( int i = 0; i < n_lines; i++)
	{
		for( int j = 0; j < strlen( file[i] ); j++)
		{
			for( int k = 0; k < 26; k++)
			{
				if( file[i][j] == Alpha[k] )	// If input matches a small alphabet
				{
					file[i][j] = E_Alpha[k];	// Replace it with respective Encrypted alphabet
					break;
				}
				else if( file[i][j] == ( Alpha[k] + 'A' - 'a' ) )	// If input matches a capital alphabet
				{	
					file[i][j] = E_Alpha[k] + 'A' - 'a';	// Replace it with respective Encrypted capital alphabet
					break;
				}
			}
		}
	}
	
	
	// Scrambler
	scrambler = 0;	// Scrambler picks up the sum of current position as its value (in the algorithm)
	for(int i = 0; i < n_lines; i++)
	{
		for(int j = 0; j < strlen( file[i] ); j++)
		{
			
			// Alphabets
			if( ( file[i][j] >= 'a' && file[i][j] <='z' ) )	// If input is a small alphabet
			{
				scrambler = ( i + j ) % 26;	// Scrambler for alphabets must be between 0 - 25
				
				if( file[i][j] + scrambler - 'a' < 26 )	// If adding the shift keeps it between 'a' to 'z'
				{
					file[i][j] += scrambler;	// Add shift
				}
				else
				{
					file[i][j] += ( scrambler - 26 );	// Else add shift and subtract 26 to go back to the beginning of the alphabet 
				}
			}
			else if( ( file[i][j] >= 'A' && file[i][j] <='Z' ) )	// If input is a capital aplhabet
			{
				scrambler = ( i + j ) % 26;	// Scrambler for alphabets must be between 0 - 25
				if( file[i][j] + scrambler - 'A' < 26 )	// If adding the shift keeps it between 'A' to 'Z'
				{
					file[i][j] += scrambler;	// Add shift
				}
				else
				{
					file[i][j] += ( scrambler - 26 );	// Else add shift and subtract 26 to go back to the beginning of the alphabet
				}
			}
			
			
			// Numbers
			else if( file[i][j] >= '0' && file[i][j] <= '9' )	// If input is a number
			{
				scrambler = ( i + j ) % 10;	// Scrambler for alphabets must be between 0 - 9
				if( file[i][j] + scrambler - '0' <= 9 )	// If adding the shift keeps it betwwen '0' to '9'
				{
					file[i][j] += scrambler;	// Add shift
				}
				else
				{
					file[i][j] += ( scrambler - 10 );	// Else add shift and subtract 10 to go back to beginnnig of the number series
				}
			}
		}
	}
	
	char* rval;
	rval=CLOSE_RUN( output );
	
	return rval;
	
	
	return output;
}

char* decrypt(char* input, char* password, char* output = "**")
{
	OPEN_RUN(input, password);
	
	
	// De-Scrambler
	scrambler = 0;	// Scrambler picks up the sum of current position as its value (in the algorithm)
	for(int i = 0; i < n_lines; i++)
	{
		for(int j = 0; j < strlen( file[i] ); j++)
		{
			
			// Alphabets
			if( ( file[i][j] >= 'a' && file[i][j] <='z' ) )	// If input is a small alphabet
			{
				scrambler = ( i + j ) % 26;	// Scrambler for alphabets must be between 0 - 25
				
				if( file[i][j] - scrambler - 'a' >= 0 )	// If adding the shift keeps it between 'a' to 'z'
				{
					file[i][j] -= scrambler;	// Add shift
				}
				else
				{
					file[i][j] -= ( scrambler - 26 );	// Else add shift and subtract 26 to go back to the beginning of the alphabet
				}
			}
			else if( ( file[i][j] >= 'A' && file[i][j] <='Z' ) )	// If input is a capital aplhabet
			{
				scrambler = ( i + j ) % 26;	// Scrambler for alphabets must be between 0 - 25
				if( file[i][j] - scrambler - 'A' >= 0 )	// If adding the shift keeps it between 'A' to 'Z'
				{
					file[i][j] -= scrambler;	// Add shift
				}
				else
				{
					file[i][j] -= ( scrambler - 26 );	// Else add shift and subtract 26 to go back to the beginning of the alphabet
				}
			}
			
			
			// Numbers
			else if( file[i][j] >= '0' && file[i][j] <= '9' )	// If input is a number
			{
				scrambler = ( i + j ) % 10;	// Scrambler for alphabets must be between 0 - 9
				if( file[i][j] - scrambler - '0' >= 0 )	// If adding the shift keeps it betwwen '0' to '9'
				{
					file[i][j] -= scrambler;	// Add shift
				}
				else
				{
					file[i][j] -= ( scrambler - 10 );	// Else add shift and subtract 10 to go back to beginnnig of the number series
				}
			}
		}
	}	
	

	// De- Secret Encryption
	for( int i = 0; i < n_lines; i++)
	{
		for( int j = 0; j < strlen( file[i] ); j++)
		{
			for( int k = 0; k < 26; k++)
			{
				if( file[i][j] == E_Alpha[k] )	// If input matches a small alphabet
				{
					file[i][j] = Alpha[k];	// Replace it with respective Encrypted alphabet
					break;
				}
				else if( file[i][j] == ( E_Alpha[k] + 'A' - 'a' ) )	// If input matches a capital alphabet
				{	
					file[i][j] = Alpha[k] + 'A' - 'a';	// Replace it with respective Encrypted capital alphabet
					break;
				}
			}
		}
	}
	
	
	// De- Caesar Cipher
	for(int i = 0; i < n_lines; i++)
	{
		for(int j = 0; j < strlen( file[i] ); j++)
		{
			// Alphabets
			if( ( file[i][j] >= 'a' && file[i][j] <='z' ) )	// If input is a small alphabet
			{
				if( file[i][j] - caesar_c - 'a' >= 0 )	// If adding the shift keeps it between 'a' to 'z'
				{
					file[i][j] -= caesar_c;	// Add shift
				}
				else
				{
					file[i][j] -= ( caesar_c - 26 );	// Else add shift and subtract 26 to go back to the beginning of the alphabet
				}
			}
			else if( ( file[i][j] >= 'A' && file[i][j] <='Z' ) )	// If input is a capital aplhabet
			{
				if( file[i][j] - caesar_c - 'A' >= 0 )	// If adding the shift keeps it between 'A' to 'Z'
				{
					file[i][j] -= caesar_c;	// Add shift
				}
				else
				{
					file[i][j] -= ( caesar_c - 26 );	// Else add shift and subtract 26 to go back to the beginning of the alphabet
				}
			}
			
			
			// Numbers
			else if( file[i][j] >= '0' && file[i][j] <= '9' )	// If input is a number
			{
				if( file[i][j] - caesar_c_num - '0' >= 0 )	// If adding the shift keeps it betwwen '0' to '9'
				{
					file[i][j] -= caesar_c_num;	// Add shift
				}
				else
				{
					file[i][j] -= ( caesar_c_num - 10 );	// Else add shift and subtract 10 to go back to beginnnig of the number series
				}
			}
		}
	}
	
	char* rval;
	rval = CLOSE_RUN( output );
	
	return rval;	
}

void OPEN_RUN(char* input, char* password)
{
	int counter = 0;	// Variable to used as a recursive counter
	
	for( int i = 0; i < 100; i++)
	{
		PassKey[i] = '\0';	// Clearing PassKey
	}
	
	for( int i = 0; i < 10000; i++ )
	{
		for( int j = 0; j < 10000; j++ )
		{
			file[i][j] = '\0';	// Clearing the input
		}
	}
	
	fstream fin;
	fin.open(input, ios::in);
	
	fin.seekg(0, ios::end);
	if( fin && fin.tellg() != 0)	// If file exists and is not empty
	{
		fin.seekg(0, ios::beg);
		
		counter = 0;
		char line[10000];
		while( fin.getline( line, 10000 ) )
		{
			for( int i=0; i < strlen( line ); i++)
			{
				file[counter][i] = line[i];	// Save all content of file into variable 'file'
			}
			counter++;
		}
		n_lines = counter;
		
		fin.close();
	}
	else if( !fin )	// If input specified is not a valid file
	{
		if( strlen( input ) == 0)	// If input is empty
		{
			cout << "\n\n:: HEADER FILE -------- Invalid Entry into Parameter ::\n\n";
			
			cout << "## length of input > 0 = FALSE\n";
			
			cout << "Press any key to terminate...\n";
			getch();
			exit(1);
		}
		else
		{
			counter = 0;
			for(int i = 0, j = 0; i < strlen( input ); i++, j++ )
			{
				if( input[i] == '\n' )	// '\n' in input must not be saved. It switches to the next row/line
				{
					j = -1;	// Loop will add 1 to j, hence making it 0 for the next line
					counter++;
					continue;
				}
				
				file[counter][j] = input[i];	// Import the input itself as if it was the content of a file
			}
			n_lines = counter + 1;	// counter is 0 if there is 1 line
		}
	}
	else if( fin.tellg() == 0 )	// If the file is Empty
	{
		cout << "\n\n:: HEADER FILE -------- Invalid Entry into Parameter ::\n\n";
		
		cout << "## data from input file = FALSE\n";
		
		cout << "Press any key to terminate...\n";
		getch();
		exit(1);
	}
	
	if( strlen( password ) < 4 )
	{
		cout << "\n\n:: HEADER FILE -------- Invalid PassKey ::\n\n";
		
		cout << "## length of password > 3 = FALSE";
		
		cout << "Press any key to terminate...\n";
		getch();
		exit(1);
	}
	else
	{
		strcpy( PassKey, password );
	}
	
	// Getting Caesar Cipher shift value
	caesar_c = 0;
	for( int i = 0; i < strlen( PassKey ); i++)
	{
		if( PassKey[i] >= '0' && PassKey[i] <= '9')
		{
			caesar_c += PassKey[i] - '0';	// Save numeric value of character numbers into caesar_c_num
		}
	}
	
	//Caesar shift for numbers is in range 1 - 9
	caesar_c_num = caesar_c % 10;
	if( caesar_c_num == 0 )
	{
		caesar_c_num = 1;
	}
	
	// Caesar shift for alphabets is in range 1 - 25
	caesar_c = caesar_c % 26;
	if( caesar_c == 0 )
	{
		caesar_c = 1;
	}
	
	
	// Eliminating special characters from PassKey
	char PassKey_temp[100];	// Temporary storing PassKey
	for( int i = 0; i < 100; i++)
	{
		PassKey_temp[i] = '\0';	// Clearing PassKey_temp (To temporarily store PassKey)
	}
	
	for( int i = 0, j = 0; i < strlen( PassKey ); i++)
	{
		if( ( PassKey[i] >= 'a' && PassKey[i] <= 'z' ) || ( PassKey[i] >= 'A' && PassKey[i] <= 'Z' ) || (PassKey[i] == '\0') )	// Only Alphabets Allowed
		{
			PassKey_temp[j] = PassKey[i];
			j++;
		}
	}
	strcpy( PassKey, PassKey_temp);
	
	// Converting to Small ( A -> a )
	for( int i = 0; i < strlen( PassKey ); i++)
	{
		if( PassKey[i] >= 'A' && PassKey[i] <= 'Z')	// If alphabet is capital
		{
			PassKey[i] -= 'A' - 'a';	// Subtract the difference of capital and small alphabets
		}
	}
	
	
	
	// Eliminating Repitition
	
	int counter_temp = 0;	// A temporary Counter
	char used_alpha_list[26];	// List to store used alphabets in the password
	for(int i = 0; i < 26; i++)
	{
		used_alpha_list[i] = '\0';	// Clearing used_alpha_list
	}
	for(int i = 0; i < 100; i++)
	{
		PassKey_temp[i] = '\0';	// Clearing PassKey_temp (To temporarily store PassKey)
	}
	
	for(int i = 0; i < strlen( PassKey ); i++)
	{
		counter = 0;
		for(int j = 0; j < 26; j++)
		{
			if(PassKey[i] == used_alpha_list[j])	// Checking if the alphabet has been used previously
			{
				break;
			}
			else
			{
				counter++;
			}
		}
		
		if( counter == 26 )	// If alphabet has not been used, counter would reach 26 = number of times the loop can run
		{
			PassKey_temp[counter_temp] = PassKey[i];
			counter_temp++;
			for(int j = 0; j < 26; j++)
			{
				if( used_alpha_list[j] == '\0' )
				{
					used_alpha_list[j] = PassKey[i];	// Adding the alphabet to used_alpha_list
					break;
				}
			}
		}
	}
	strcpy(PassKey, PassKey_temp);
	
	
	for(int i = 0; i < 26; i++)
	{
		Alpha[i] = 'a' + i;	// Filling up alphabet list
	}
	
	for(int i = 0; i < strlen( PassKey ); i++)
	{
		E_Alpha[i] = PassKey[i];	// List of Encrypted Alphabets starts with the alphabets in PassKey
	}
	
	// Filling up Encrypted Alphabet list
	char alphabet = 'a';
	for( int i = strlen( PassKey ); i < 26; i++)
	{
		counter = 0;
		for( int k = 0; k < strlen( PassKey ); k++)
		{
			if( alphabet == PassKey[k])	// Checking if the alphabet is already stored in the list
			{
				counter = 1;
				break;
			}
		}
		
		if( counter != 1)
		{
			E_Alpha[i] = alphabet;	// Add alphabet to list if it is not already present
		}
		else
		{
			i -= 1;	// As this position is not yet filled, subtract 1 from i and the loop will add 1 to it in the end, thus net change in i = 0
		}
		
		alphabet++;	// Go on to the next alphabet
	}
	
	return;
}



char* CLOSE_RUN(char* output)
{
	if( strcmp( output, "**" ) != 0 )	// If an output parameter is given
	{
		// Writing the output in the appropriate location
		fstream fout;
		fout.open( output, ios::out | ios::trunc );
		
		if ( fout )	// If the location is valid
		{
			for(int i = 0; i < n_lines; i++)
			{
				fout.write( file[i], strlen( file[i] ) );
				fout<<endl;
			}	
		}
		else
		{
			cout << "\n\n:: HEADER FILE -------- Invalid Entry into Parameter ::\n\n";
		
			cout<<"## output location did not open\n";
		
			cout << "Press any key to terminate...\n";
			getch();
			exit(1);
		}
		
		fout.close();
	}
	else
	{
		// If there is no output parameter, return the output as a variable
		// Do note that data loss is possible if the input is too big!!! This is a limit of C++
		char file_temp[2000000];
		for( int i = 0; i < 2000000; i++)
		{
			file_temp[i] = '\0';	// Clearing the variable file_temp to remove junk from previous runs
		}
		
		for(int i = 0; i < n_lines; i++)
		{
			app_string( file_temp, file[i] );
			app_string( file_temp, "\n" );
		}
		
		return file_temp;
	}
	
	return "\0";
}

void app_string(char* Destination_String, char* Source_String)
{
	int i = strlen( Destination_String );
	
	for(int j=0; j < strlen( Source_String ); j++, i++)
	{
		Destination_String[i] = Source_String[j];	// From end of the Dest, all chars in src are placed in order
	}
	Destination_String[i] = '\0';
	
	return;
}

int main() 
 {
 		
		show_heading(1);

	char input[200];
	char output [200];
	char password[8];
	char selection;
	char selection2;
	
	do {
		cout << "<1>. Encrypt\n<2>. Decrypt\n<3>. Exit  ::";
		selection=getch();
		system( "cls" );
		switch( selection ) {
			case '1':
				show_heading(0);
				cout<<"\n<1>. Encryption a string in the program\n<2>. Encrypting a file\n::";
				selection2 = getch(); ;
				system( "cls" );
				switch( selection2 ) 
	    		{
					case'1':
						cout << "Enter the string to be Encrypted :: " << endl;
						cin.getline( input, 200 );
						cout << "Enter password :: ";
						pass_entry( password, '*', 8 );
						strcpy( output, encrypt( input, password ) );
						cout << "The Encrypted string :: " << output << endl;
						break;
					case '2':
						cout << "enter password :: ";
						pass_entry( password, '*', 8 );
						encrypt( "input.txt", password, "output.txt" );
						cout<<"\n\n\t\t\tYOUR FILE HAS BEEN ENCRYPTED.";
						break;
				}
				system( "cls");
		 		break;		    
	    	case '2' :
		    	show_heading(2) ;
				cout<<"\n<1>. Decryption a string in the program\n<2>. Decrypting a file\n::";
				char selection3= getch();
				system("cls");
				switch( selection3 ) 
		  		{
					case'1':
						cout << "Enter the code to be Decrypted:: " << endl;
						cin.getline( input, 200 );
						cout << "Enter password:: ";
						pass_entry( password, '*', 8 );
						strcpy( output, decrypt( input, password ) );
						cout << "Your Decrypted code :: " << output << endl;
			
						break;
					case '2':
						cout << "enter password: ";
						pass_entry( password, '*', 8 );
						decrypt( "input.txt", password, "output.txt" );
						cout<<"\n\n\t\t\tYOUR FILE HAS BEEN DECRYPTED.";
						break;
	     		}   
	     		system( "cls");
		 		break;
        }
	}
	while(selection != '3');
	cout<<" Exiting the program!!!";
	return 0;
}
