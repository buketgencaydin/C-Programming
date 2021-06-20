#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct record {
char name[64]; //utf16
char surname[32]; //utf8 
char gender; 
char email[32];
char phone_number[16];
char address[32];
char level_of_education[8];
unsigned int income_level; // given little-endian
unsigned int expenditure; // given big-endian 
char currency_unit[16];
char currentMood[32];
float height;
unsigned int weight;
};


int main(int argc, char **argv)
{
    FILE *input, *output;
    char inputFileName[64], outputFileName[64];

    /* Bin2XML <inputfile> <outputfile> */
    strcpy(inputFileName, argv[1]); // first command line argument: source filename
    strcpy(outputFileName, argv[2]); // second command line argument: target XML filename

    input = fopen(inputFileName, "rb"); // opening input file
    output = fopen(outputFileName, "w"); // opening output file

    struct record *in = malloc(sizeof(struct record)); // dynamic memory allocation for 

    int i=0, j, k=0;
    char character;

    fprintf ( output,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"); // XML header

    /* 
        inputFileName = records.dat
        fileName = records
    */
    char *fileName = strtok(inputFileName, "."); 
    fprintf(output, "<%s>",fileName ); // writing the root element of XML file

    /* loop continues until EOF(End Of the File) is reached */
    while(!feof(input))
	{ 
        /* reading name in UTF-16 format */
        for(j=0 ; j<64 ; j++)
        {
            character = fgetc(input); // reading each character of name
            if(character != 0)
            {
                in->name[k] = character;
                k++;
            }
        }
        in->name[k] = '\0';
        k=0;

        /* reading surname in UTF-8 format */
        for(j=0 ; j<32 ; j++)
        {
            character = fgetc(input); // reading each character of surname
            if(character != 0)
            {
                in->surname[k] = character;
                k++;
            }
        }
        in->surname[k] = '\0';
        k=0;

        /* reading gender, may have one of the values: “M” or “F” */
        fscanf(input, "%c", &in->gender);

        /* reading email, may one of the email addresses: “@gmail.com”, “@hotmail.com”, or “@yahoo.com” */
        fread(&in->email, 1, 32,input);

        /* reading phone number */
        fread(&in->phone_number, 1, 16,input);

        /* reading address */
        fread(&in->address, 1, 32,input);

        /* reading level of education, may have one of the values “PhD”, “MSc”, “BSc”, “HS”, or “PS” */
        fread(&in->level_of_education, 1, 11,input);

        unsigned char byte[4];
        /* reading and shifting income level which is given little-endian*/
        fread(byte, 1, 4,input);
        in->income_level = byte[0] | (byte[1]<<8) | (byte[2]<<16) | (byte[3]<<24);

        /* reading and shifting expenditure which is given big-endian*/
        fread(byte, 1, 4,input);
        in->expenditure = byte[0] | (byte[1]<<8) | (byte[2]<<16) | (byte[3]<<24);

        /* reading currency unit */
        fread(in->currency_unit, 1, 16,input);

        /* reading current mood */
        fread(&in->currentMood, 1, 32,input);

        /* reading height of the person */
        fread(&in->height, 1, sizeof(float),input);

        /* reading weight of the person */
        fread(&in->weight, 1, 4,input);
		
        /* writing the records to XML file */
        if(i != 0 && strlen(in->name)>0 && !feof(input))
        {
            fprintf(output, "\n\t\t<row id=\"%d\">",i); 
            fprintf(output, "\n\t\t\t<name>%s</name>", in->name); 
            fprintf(output, "\n\t\t\t<surname>%s</surname>", in->surname);
            fprintf(output, "\n\t\t\t<gender>%c</gender>", in->gender);
            fprintf(output, "\n\t\t\t<email>%s</email>", in->email);
            fprintf(output, "\n\t\t\t<phone_number>%s</phone_number>", in->phone_number);
            fprintf(output, "\n\t\t\t<address>%s</address>", in->address);
            fprintf(output, "\n\t\t\t<level_of_education>%s</level_of_education>", in->level_of_education);

            /* conversion to Big-Endian */
            unsigned int bigEndian = ((in->income_level & 0x000000ff) << 24u)  | 
                    ((in->income_level & 0x0000ff00) << 8u) | 
                    ((in->income_level & 0x00ff0000) >> 8u) | 
                    ((in->income_level & 0xff000000) >> 24u);

            fprintf(output, "\n\t\t\t<income_level bigEnd=\"%u\">%u</income_level>", bigEndian, in->income_level);

            /* conversion to original value */
            unsigned int value = ((in->expenditure>>24)&0xff) | 
                    ((in->expenditure<<8)&0xff0000) | 
                    ((in->expenditure>>8)&0xff00) | 
                    ((in->expenditure<<24)&0xff000000); 
            fprintf(output, "\n\t\t\t<expenditure bigEnd=\"%u\">%u</expenditure>", in->expenditure, value);

            fprintf(output, "\n\t\t\t<currency_unit>%s</currency_unit>", in->currency_unit);
            fprintf(output, "\n\t\t\t<currentMood>%s</currentMood>", in->currentMood);
            fprintf(output, "\n\t\t\t<height>%.2f</height>", in->height);
            fprintf(output, "\n\t\t\t<weight>%u</weight>", in->weight);
            fprintf(output, "\n\t\t</row>");
        }  
        i++;
	}
    fprintf(output, "\n</%s>", fileName);
    
    fclose(input); // closing the source file
    fclose(output); // closing the XML file
 
    return 0;
}