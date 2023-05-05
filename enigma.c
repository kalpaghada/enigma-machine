/*
 * enigma.c
 * 1 2 3 8 15 20
 * RBINEZBJN DC ASGH TVESFG
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int rotor1[2][26] = {
    {5,11,13,6,12,7,4,17,22,26,14,20,15,23,25,8,24,21,19,16,1,9,2,18,3,10},
    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26}
};
int rotor2[2][26] = {
    {1,10,4,11,19,9,18,21,24,2,12,8,23,20,13,3,17,7,26,14,16,25,6,22,15,5},
    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26}
};
int rotor3[2][26] = {
    {2,4,6,8,10,12,3,16,18,20,24,22,26,14,25,5,9,23,7,1,11,13,21,19,17,15},
    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26}
};

int reflector[26] = {
    1,2,3,4,
    5,6,7,
    4,9,10,11,
    7,13,11,
    13,9,5,2,
    6,20,3,22,
    22,10,1,
    20
};

int input[1024];
int output[1024];

void initialize_input(char *string)
{
    int i = 0;
    while (string[i])
    {
        if (string[i] == ' ' || toupper(string[i])-'A' < 0 || toupper(string[i])-'A' > 25) {
            input[i] = -2;
            i++;
            continue;
        }
        // printf("%d\n",(toupper(string[i])-'A')+1);
        input[i] = (toupper(string[i])-'A')+1;
        //printf("%d\n",input[i]);
        i++;
    }
    input[i] = -1;
}

void shift_rotor(int rotor[2][26])
{
    int temp[2] = {rotor[0][0], rotor[1][0]};
    for (int i = 0; i<25; i++) {
        rotor[0][i] = rotor[0][i+1];
        rotor[1][i] = rotor[1][i+1];
    }
    rotor[0][25] = temp[0];
    rotor[1][25] = temp[1];
}

void decode(int leftrotor[2][26], int centerrotor[2][26], int rightrotor[2][26], int leftwheel, int centerwheel, int rightwheel)
{
    /*WHEEL CONFIGURATION*/
    for (int temp = 1; temp<leftwheel; temp++) {
        shift_rotor(leftrotor);
    }
    for (int temp = 1; temp<centerwheel; temp++) {
        shift_rotor(centerrotor);
    }
    for (int temp = 1; temp<rightwheel; temp++) {
        shift_rotor(rightrotor);
    }


    /*PROCESS*/
    int iterator = 0;
    int index = 0;
    while (input[iterator] != -1)
    {
        if (input[iterator] == -2) { /*takes care of spaces*/
            output[iterator] = -2;
            iterator++;
            continue;
        }

        /*if notch, shift rotors center and/or left*/
        if (rightrotor[1][0] == 22 && centerrotor[1][0] == 5) {
            shift_rotor(leftrotor);
            shift_rotor(centerrotor);
        }
        else if (rightrotor[1][0] == 22 && centerrotor[1][0] != 5) {
            shift_rotor(centerrotor);
        }
        shift_rotor(rightrotor);

        /*ROTOR 3*/
        // printf("input[i] = %c ",input[iterator] + ('A'-1));
        // printf("letter = %c\n",rightrotor[0][input[iterator]-1] + ('A'-1));

        for (int j = 0; j<26; j++)
        {
            if (rightrotor[1][j] == rightrotor[0][input[iterator]-1])
            {
                index = j;
                // printf("index = %d\n",index);
                //printf("rightrotor[1][j] = %c\n",rightrotor[1][j] + ('A'-1));
                break;
            }
        }

        /*ROTOR 2*/
        // printf("centerrotor = %c\n",centerrotor[0][index] + ('A'-1));
        for (int j = 0; j<26; j++)
        {
            if (centerrotor[1][j] == centerrotor[0][index])
            {
                index = j;
                // printf("index = %d\n",index);
                // printf("centerrotor[1][index] = %c\n",centerrotor[1][index] + ('A'-1));
                break;
            }
        }

        /*ROTOR 1*/
        // printf("leftrotor = %c\n",leftrotor[0][index] + ('A'-1));
        for (int j = 0; j<26; j++)
        {
            if (leftrotor[1][j] == leftrotor[0][index])
            {
                index = j;
                // printf("index = %d\n",index);
                // printf("leftrotor[1][index] = %c\n",leftrotor[1][index] + ('A'-1));
                break;
            }
        }

        /*REFLECTOR*/
        // printf("reflector = %c\n",reflector[index] + ('A'-1));
        /*search for next occurence of reflector letter*/
        int found = 0;
        for (int j = 0; j<index; j++)
        {
            if (reflector[j] == reflector[index])
            {
                found = 1;
                index = j;
                // printf("backward reflected one at (%d)th\n", j+1);
            }
        }
        if (!found) {
            for (int j = index+1; j<26;j++) {
                if (reflector[j] == reflector[index])
                {
                    found = 1;
                    index = j;
                    // printf("forward reflected one at (%d)th\n", j+1);
                }
            }
        }

        /*BACKWARDS ROTOR 1*/
        // printf("BACK leftrotor = %c\n",leftrotor[1][index] + ('A'-1));
        for (int j = 0; j<26; j++)
        {
            if (leftrotor[0][j] == leftrotor[1][index])
            {
                index = j;
                // printf("index = %d\n",index);
                // printf("leftrotor[0][index] = %c\n",leftrotor[0][index] + ('A'-1));
                break;
            }
        }

        /*BACKWARDS ROTOR 2*/
        // printf("BACK centerrotor = %c\n",centerrotor[1][index] + ('A'-1));
        for (int j = 0; j<26; j++)
        {
            if (centerrotor[0][j] == centerrotor[1][index])
            {
                index = j;
                // printf("index = %d\n",index);
                // printf("centerrotor[0][index] = %c\n",centerrotor[0][index] + ('A'-1));
                break;
            }
        }

        /*BACKWARDS ROTOR 3*/
        // printf("BACK rightrotor = %c\n",rightrotor[1][index] + ('A'-1));
        for (int j = 0; j<26; j++)
        {
            if (rightrotor[0][j] == rightrotor[1][index])
            {
                index = j;
                // printf("index = %d\n",index);
                // printf("rightrotor[0][index] = %c\n",rightrotor[0][index] + ('A'-1));
                break;
            }
        }

        /*OUTPUT*/
        // printf("OUTPUT = %c\n", index + 'A');
        output[iterator] = index;

        
        /*INCREMENT ITERATOR*/
        iterator++;
        // printf("\n");
    }
    output[iterator] = -1;
}

void print_output()
{
	printf(">");
    int i = 0;
    while (output[i] != -1)
    {
        if (output[i] == -2) {
            printf(" ");
            i++;
            continue;
        }
        printf("%c",output[i] + 'A');
        i++;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc == 4)
    {
        for (int i = 1; i<3; i++) /*to check length of configuration numbers*/
        {
            if (strlen(argv[i]) != 6) {
                printf("Invalid argument\n");
                return 1;
            }
        }
        for (int i = 0; i<strlen(argv[1]); i += 2) /*to see rotor config values are valid*/
        {
            if ((argv[1][i]-'0') != 0) { /*they should be single digit integers => the first digits have to be zero*/
                printf("Invalid argument\n");
                printf("Rotor config values have to be single digit integers like so - 0n\n");
                return 1;
            }
            if ((argv[1][i+1]-'0') != 1 && (argv[1][i+1]-'0') != 2 && (argv[1][i+1]-'0') != 3) { /*the second digits have to be either 1, 2 or 3*/
                printf("Invalid argument\n");
                printf("Rotor config values have to be either 01, 02 or 03\n");
                return 1;
            }
            if ((argv[2][i]-'0') > 2 || (argv[2][i]-'0') < 0 || (argv[2][i+1]-'0') > 9 || (argv[2][i+1]-'0') < 0) /*The individual characters should be integers*/
            {
                printf("Invalid argument\n");
                return 1;
            }
            if ((argv[2][i]-'0') == 2) /*The numbers should be in between 1 and 26*/
            {
                if ((argv[2][i+1])-'0' > 6) {
                    printf("Invalid argument\n");
                    printf("Wheel config values should be between 1 and 26\n");
                    return 1;
                }
            }
        }
        if (strlen(argv[3]) > 1000) {
            printf("Message too long\n");
            return 1;
        }
        for (int i = 0; i<strlen(argv[3]); i++) /*message has to be only letters*/
        {
            if (((toupper(argv[3][i])-'A') < 0 || (toupper(argv[3][i])-'A') > 25) && (argv[3][i] != ' ')) {
                
                printf("Invalid argument\n");
                printf("Message must contain only letters and spaces enclosed within double quotes\n");
                return 1;
            }
        }

        printf("Arguments given:\n");
        for (int i = 1; i<4; i++)
        {
            printf("\t%s ",argv[i]);
            printf("(%ld)\n",strlen(argv[i]));
        }

        initialize_input(argv[3]);

        /*Command line message process*/
        if (argv[1][1]-'0' == 1 && argv[1][3]-'0' == 2 && argv[1][5]-'0' == 3) {
            decode(rotor1, rotor2, rotor3, ((argv[2][0]-'0')*10 + (argv[2][1]-'0')), ((argv[2][2]-'0')*10 + (argv[2][3]-'0')), ((argv[2][4]-'0')*10 + (argv[2][5]-'0')));
            print_output();
        }
        else if (argv[1][1]-'0' == 3 && argv[1][3]-'0' == 1 && argv[1][5]-'0' == 2) {
            decode(rotor3, rotor1, rotor2, ((argv[2][0]-'0')*10 + (argv[2][1]-'0')), ((argv[2][2]-'0')*10 + (argv[2][3]-'0')), ((argv[2][4]-'0')*10 + (argv[2][5]-'0')));
            print_output();
        }
        else if (argv[1][1]-'0' == 2 && argv[1][1]-'0' == 3 && argv[1][5]-'0' == 1) {
            decode(rotor2, rotor3, rotor1, ((argv[2][0]-'0')*10 + (argv[2][1]-'0')), ((argv[2][2]-'0')*10 + (argv[2][3]-'0')), ((argv[2][4]-'0')*10 + (argv[2][5]-'0')));
            print_output();
        }
        else if (argv[1][1]-'0' == 2 && argv[1][3]-'0' == 1 && argv[1][5]-'0' == 3) {
            decode(rotor2, rotor1, rotor3, ((argv[2][0]-'0')*10 + (argv[2][1]-'0')), ((argv[2][2]-'0')*10 + (argv[2][3]-'0')), ((argv[2][4]-'0')*10 + (argv[2][5]-'0')));
            print_output();
        }
        else if (argv[1][1]-'0' == 1 && argv[1][3]-'0' == 3 && argv[1][5]-'0' == 2) {
            decode(rotor1, rotor3, rotor2, ((argv[2][0]-'0')*10 + (argv[2][1]-'0')), ((argv[2][2]-'0')*10 + (argv[2][3]-'0')), ((argv[2][4]-'0')*10 + (argv[2][5]-'0')));
            print_output();
        }
        else if (argv[1][1]-'0' == 3 && argv[1][3]-'0' == 2 && argv[1][5]-'0' == 1) {
            decode(rotor3, rotor2, rotor1, ((argv[2][0]-'0')*10 + (argv[2][1]-'0')), ((argv[2][2]-'0')*10 + (argv[2][3]-'0')), ((argv[2][4]-'0')*10 + (argv[2][5]-'0')));
            print_output();
        }

        return 0;
    }
    

    /*in tool configuration variables*/
    char string[1024];

    int rotorconf[3];
    int wheelconf[3];

    printf("Rotor configuration\n");
    if (!scanf("%d %d %d",&rotorconf[0], &rotorconf[1], &rotorconf[2])) {
		printf("Cannot take input\n");
		return 1;
	}

    for (int i = 0; i<3; i++) {
        if (rotorconf[i] < 1 || rotorconf[i] > 3)
        {
            printf("Invalid configuration\n");
            return 1;
        }
    }
    if (rotorconf[0] == rotorconf[1] || rotorconf[1] == rotorconf[2] || rotorconf[2] == rotorconf[0])
    {
        printf("Invalid configuration\n");
        return 1;
    }

    printf("Rotor wheel configuration\n");
    if (!scanf("%d %d %d",&wheelconf[0], &wheelconf[1], &wheelconf[2])) {
		printf("Cannot take input\n");
		return 1;
	}
    for (int i = 0; i<3; i++) {
        if (wheelconf[i] < 1 || wheelconf[i] > 26)
        {
            printf("Invalid configuration\n");
            return 1;
        }
    }

    printf("Enter message\n");
    if (!scanf(" %1024[^\n]%*c",string)) {
		printf("Cannot take input\n");
		return 1;
	}

    initialize_input(string);

    /*In tool message process*/
    if (rotorconf[0] == 1 && rotorconf[1] == 2 && rotorconf[2] == 3) {
        decode(rotor1, rotor2, rotor3, wheelconf[0], wheelconf[1], wheelconf[2]);
        print_output();
    }
    else if (rotorconf[0] == 3 && rotorconf[1] == 1 && rotorconf[2] == 2) {
        decode(rotor3, rotor1, rotor2, wheelconf[0], wheelconf[1], wheelconf[2]);
        print_output();
    }
    else if (rotorconf[0] == 2 && rotorconf[1] == 3 && rotorconf[2] == 1) {
        decode(rotor2, rotor3, rotor1, wheelconf[0], wheelconf[1], wheelconf[2]);
        print_output();
    }
    else if (rotorconf[0] == 2 && rotorconf[1] == 1 && rotorconf[2] == 3) {
        decode(rotor2, rotor1, rotor3, wheelconf[0], wheelconf[1], wheelconf[2]);
        print_output();
    }
    else if (rotorconf[0] == 1 && rotorconf[1] == 3 && rotorconf[2] == 2) {
        decode(rotor1, rotor3, rotor2, wheelconf[0], wheelconf[1], wheelconf[2]);
        print_output();
    }
    else if (rotorconf[0] == 3 && rotorconf[1] == 2 && rotorconf[2] == 1) {
        decode(rotor3, rotor2, rotor1, wheelconf[0], wheelconf[1], wheelconf[2]);
        print_output();
    }

    return 0;
}
