#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/************************************************************************************
 * James Woods
 * CSC230, Summer 2013
 *
 * lateCompile [path to .tex file] [name of file, no extension]
 *
 * takes a .tex file and compiles it using latex to
 * produce a .dvi dvips to produce a .ps and ps2pdf to produce a .pdf file with the
 * same name as the original .tex file. After the pdf has been made letCompile opens 
 * it using the "open" system call.
 *
 * lateCompile takes takes two parameters. 
 *
 * parameter one is the full path to the folder containing the latex file to be compiled.
 * parameter two is the name of the file to be compiled without the file extension.
 ***********************************************************************************/

#define MAX_LENGTH 255
//This should be the additional characters in the longest possible command string
//including the EOL. The current longest command string is the call to latex
//with the --output-directory= call which adds 30 pluss EOL for 31.
#define MAX_EXTRA_CHAR 31
#define TO_DO 3

int main(int argc, char **argv)
{
	//perform some basic input checking on the arguments given by the user.
	if (argc <= 1 || 2*(strlen(argv[1])) + strlen(argv[2]) + MAX_EXTRA_CHAR >= MAX_LENGTH) {
		printf("%s\n", "Invalid arguments: ");
		exit(1);
	}
    
	//Create a list of three commands to execute.
	char *commands[3] = {"latex --output-directory=", "dvips ", "ps2pdf "};

	//Create a list of four file extensions to be used.
	char *extensions[4] = {".tex", ".dvi", ".ps", ".pdf"};

	//Set up a path string to hold the required path argument.
    char path[MAX_LENGTH] = "";
	strncat(path, argv[1], MAX_LENGTH);
	//Add the file name to the path.
    strncat(path, "/", MAX_LENGTH);
	strncat(path, argv[2], MAX_LENGTH);

	//process three commands to produce a finished pdf.
    for (int i = 0; i < TO_DO; i++) {

        //Create the command.
        char command[MAX_LENGTH] = "";
        //Add the command name to the command.
        strncat(command, commands[i], MAX_LENGTH);

        //Add the file path and options to the command.
        if (i == 0) {
            //Assemble the command for latex
            //with redirected output.
            strncat(command, argv[1], MAX_LENGTH);
            strncat(command, " ", MAX_LENGTH);
            strncat(command, path, MAX_LENGTH);
            strncat(command, extensions[i], MAX_LENGTH);
        } else {

            //Assemble the command for dvips
            //or ps2pdf.
            strncat(command, " ", MAX_LENGTH);
            strncat(command, path, MAX_LENGTH);
            //Add the file extension to the path.
            strncat(command, extensions[i], MAX_LENGTH);

            if (i == 1) {
                //Add - o option for dvips
                //to redirect output.
                strncat(command, " -o ", MAX_LENGTH);
            } else {
                //Just add a space to redirect the output of ps2pdf.
                strncat(command, " ", MAX_LENGTH);
            }

            //finish by adding the path where the output should redirect.
            strncat(command, path, MAX_LENGTH);
            strncat(command, extensions[i + 1], MAX_LENGTH);
        }


        //Use system to execute latex command with the given path and file name.
        int ret = system(command);
        if(ret != 0)
            exit(1);

    }
    //Open the pdf to view any changes.
    //Set up the command to close the pdf.
    char command[MAX_LENGTH] = "";

    //Set up the command to open the pdf.
    strncat(command, "open ", MAX_LENGTH);
    strncat(command, path, MAX_LENGTH);
    strncat(command, extensions[3], MAX_LENGTH);
    //Make the system call to open the .pdf
    system(command);
    
    return(0);
}

